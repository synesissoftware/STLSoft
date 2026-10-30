#! /usr/bin/env ruby

# ######################################################################## #
# File:     .dev/bin/generate_cmakelists.rb
#
# Purpose:  Creates or regenerates CMakeLists.txt files in a manner
#           compatible with Synesis Information Systems' libraries.
#
# Created:  9th January 2025
# Updated:  30th October 2026
#
# Author:   Matthew Wilson
#
# Copyright (c) Matthew Wilson, Synesis Information Systems
# All rights reserved
#
# ######################################################################## #


# ######################################################################## #
# requires

require 'highline'
require 'libclimate'
require 'recls'
require 'xqsr3/extensions/string/map_option_string'


# ######################################################################## #
# includes


# ######################################################################## #
# constants

PROGRAM_VER_MAJOR = 0
PROGRAM_VER_MINOR = 2
PROGRAM_VER_PATCH = 0

DIRECTORY_PARTS_TO_IGNORE = [
  '.dev/',
  'cmake/',
  'doc/',
  'include/',
  'strategy/',
]

EYECATCHER = '# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten'

FILES_TO_IGNORE = [
  'implicit_link.c',
  'implicit_link.cpp',
  /\.dsp$/,
  /\.vcproj$/,
  /\.vcxproj$/,
  /\.vcxproj.filters$/,
  lambda { |fe| DIRECTORY_PARTS_TO_IGNORE.any? { |part| fe.directory_parts.include?(part) }},
]

NAME_MODE_STRINGS = %w{
  [le]gacy
  [m]odern
}

# Extensions and stems for which xTests infers a runner name from __FILE__.
SOURCE_EXTENSIONS = %w{
  .c
  .cc
  .cpp
  .cxx
}

STOCK_STEMS = %w{
  entry
  main
}


# ######################################################################## #
# functions

def dead_directory? subdirectory, contents, **options

  return true if contents.empty?

  false
end

# Path relative to the current directory when +path+ is under it.
def display_path path

  full    = File.expand_path(path)
  prefix  = Dir.pwd + File::SEPARATOR

  return full[(prefix.size)..-1] if full.start_with?(prefix)

  full
end

def get_program_source_entry entries, **options

  all_files   = entries.select { |fe| fe.file? }
  c_cpp_files = all_files.select { |fe| [ '.c', '.cpp' ].include?(fe.extension) }

  return c_cpp_files[0] if c_cpp_files.size == 1
end

# The xTests' +__FILE__+ runner name for +source_path+, or +nil+ when the
# path is not a stock +entry+ / +main+ source under +test+ or +examples+.
def inferred_program_name source_path

  parts = source_path.split(%r{[/\\]}).reject { |part| part.empty? }

  return nil if parts.size < 2

  filename    = parts.last
  directories = parts[0...-1]
  extension   = File.extname(filename)

  return nil unless SOURCE_EXTENSIONS.include?(extension)

  stem = filename[0...-extension.size]
  leaf = directories.last

  unless STOCK_STEMS.include?(stem)

    return stem if stem == leaf

    return nil
  end

  return leaf if prefixed_name?(leaf, 'example.') || prefixed_name?(leaf, 'test.')

  (directories.size - 1).downto(1) do |index|

    anchor = case directories[index - 1]
    when 'example', 'examples'

      'example'
    when 'test'

      'test'
    end

    next unless anchor

    return ([ anchor ] + directories[index..-1]).join('.')
  end

  nil
end

# Stock leaf +CMakeLists.txt+ text for +fe_prg+: the eyecatcher and one
# +define_*+ call, named for +name_mode+.
def leaf_cmake_text fe_prg, name_mode

  macro = case fe_prg.stem
  when 'entry'

    'define_automated_test_program'
  when 'main'

    'define_example_program'
  else

    if fe_prg.directory_parts.include?('test/') && [ 'component/', 'unit/' ].any? { |dirname| fe_prg.directory_parts.include?(dirname) }

      'define_automated_test_program'
    else

      'define_example_program'
    end
  end

  name = program_name(fe_prg.path, name_mode)

  "#{EYECATCHER}\n#{macro}(#{name} #{fe_prg.basename})\n"
end

# Stock non-leaf +CMakeLists.txt+ text: the eyecatcher and a sorted
# +add_subdirectory+ line for each entry in +contents+.
def nonleaf_cmake_text contents

  lines = [ EYECATCHER ]

  contents.map { |fe| fe.basename }.sort.each do |subdir_name|

    next if subdir_name == 'CMakeLists.txt'

    lines << "add_subdirectory(#{subdir_name})"
  end

  lines.join("\n") + "\n"
end

# +n+ in green when it is zero (already good), and in +colour+ when it
# is not. Red is only for a broken count; this summary has none.
def num_clr n, colour

  case n
  when 0

    HighLine.color(n.to_s, :green)
  else

    HighLine.color(n.to_s, colour, :bold)
  end
end

# +true+ when +name+ begins with +prefix+ and has at least one further
# character, as with +test.<X>+ and +example.<X>+.
def prefixed_name? name, prefix

  name.start_with?(prefix) && name.size > prefix.size
end

# Program name for the leaf source +source_path+ under +mode+.
#
# :modern follows xTests infer_name_ (__FILE__ passed to
# XTESTS_START_RUNNER): a stem of "entry" or "main" walks up to the
# nearest "test", "example", or "examples" directory ("examples" becomes
# "example") and joins that anchor to the leaf with '.'. A leaf already
# named "test.<X>" or "example.<X>" is the whole name. A stem equal to
# its leaf directory is that stem.
#
# When that rule does not apply, the name is the leaf directory. :legacy
# is always the leaf directory.
def program_name source_path, mode

  leaf            = source_path.split(%r{[/\\]}).reject { |part| part.empty? }
  leaf_directory  = leaf.empty? ? source_path : leaf[-2] || leaf[-1]

  return leaf_directory if mode == :legacy

  inferred_program_name(source_path) || leaf_directory
end

# Writes +text+ to +path+ unless +dry_run+ is set. Returns +:create+ or
# +:update+ when the bytes differ, and +nil+ when the file already
# matches. A dry-run reports that difference and does not write.
def publish_cmake_list path, text, dry_run

  existing = File.file?(path) ? IO.read(path) : nil

  return nil if existing == text

  report_cmake_change path, existing, text if dry_run

  File.write path, text unless dry_run

  existing.nil? ? :create : :update
end

# Prints how +proposed+ differs from +existing+ at +path+. +existing+ is
# +nil+ when the file is absent.
def report_cmake_change path, existing, proposed

  $stdout.puts "#{existing.nil? ? 'create' : 'update'} #{display_path(path)}"

  old_lines = existing.nil? ? [] : existing.lines
  new_lines = proposed.lines
  count     = [ old_lines.size, new_lines.size ].max

  count.times do |index|

    old_line = old_lines[index]
    new_line = new_lines[index]

    next if old_line == new_line

    $stdout.puts "\t- #{old_line.chomp}" if old_line
    $stdout.puts "\t+ #{new_line.chomp}" if new_line
  end
end

def strip_excludes entries, ignore_list, **options

  def match_item fe, ignore_list

    ignore_list.each do |ignore|

      case ignore
      when ::Regexp

        return true if ignore =~ fe.basename
      when ::String

        return true if ignore == fe.basename
      when ::Proc

        return true if ignore.call fe
      else
      end
    end

    false
  end

  entries.reject { |fe| match_item fe, ignore_list }
end


# ######################################################################## #
# command-line handling

options = {}
climate = LibCLImate::Climate.new do |cl|

  cl.add_flag('--dry-run', alias: '-d', help: 'does not make any changes, but reports which changes would be made') { options[:dry_run] = true }
  cl.add_flag('--verbose', alias: '-v', help: 'operate verbosely') { options[:verbose] = true }

  cl.add_option('--mode', alias: '-m', help: "Program-name mode. 'modern' (the default) follows the xTests __FILE__ runner-name rule. 'legacy' uses the leaf directory name", values: NAME_MODE_STRINGS) do |o, sp|

    cl.abort "program-name mode already specified; use --help for usage" if options[:name_mode]

    options[:name_mode] = o.value.map_option_string(NAME_MODE_STRINGS) or cl.abort "invalid program-name mode '#{o.value}'; use --help for usage"
  end

  cl.info_lines = [
    'STLSoft Development Tools',
    'Copyright Synesis Software Pty Ltd (c) 1999-2019, Synesis Information Systems Pty Ltd (c) 2019-2026',
    :version,
    "Creates or regenerates CMakeLists.txt files in a manner compatible with Synesis Information Systems' libraries",
    nil,
  ]
  cl.value_names = [ 'directory' ]
  cl.constrain_values = 1..;
  cl.usage_values = '<directory-1> [ ... <directory-N> ]'
end

r = climate.run ARGV

directories = r.values

directories.all? { |directory| Recls.directory? directory } or climate.abort "one or more of given arguments is not a directory"

options[:name_mode] ||= :modern


# ######################################################################## #
# main()

num_directories_processed     = 0
num_custom_directories_found  = 0
num_missing_makelists_created = 0
num_stock_makelists_replaced  = 0
num_dead_directories          = 0
num_lists_created             = 0
num_lists_updated             = 0


directories.each do |directory|

  # Search each top-level directory for its subdirectories

  $stdout.puts "processing in #{HighLine.color(directory, :blue, :bold)} ..." if options[:verbose]

  subdirectories = Recls.rsearch(directory, nil, Recls::DIRECTORIES).to_a#.map { |fe| fe.path }

  # now process each of these according to whether it is leaf or not

  subdirectories.each do |subdirectory|

    $stdout.print "\tprocessing #{HighLine.color(subdirectory.search_relative_path, :blue, :bold)} - " if options[:verbose]

    num_directories_processed += 1

    cml_path = Recls.combine_paths(subdirectory, 'CMakeLists.txt')
    cml = Recls.stat(cml_path)

    regenerate_cml = false

    if cml

      lines = IO.readlines cml_path

      if lines.empty?

        num_missing_makelists_created += 1

        regenerate_cml = true
      elsif lines[0].strip == EYECATCHER

        regenerate_cml = true

        num_stock_makelists_replaced += 1
      else

        $stdout.puts HighLine.color("ignoring custom 'CMakeLists.txt'", :cyan, :bold) if options[:verbose]
      end
    else

      num_missing_makelists_created += 1

      regenerate_cml = true
    end

    unless regenerate_cml

      num_custom_directories_found += 1
    end

    if regenerate_cml

      contents  = Recls.search(subdirectory, nil, Recls::FILES | Recls::DIRECTORIES).to_a

      contents  = strip_excludes contents, FILES_TO_IGNORE, **options

      fe_prg    = get_program_source_entry contents

      is_leaf   = true
      is_leaf   = is_leaf && fe_prg

      action    = options[:dry_run] ? 'would generate' : 'generating'

      if is_leaf

        $stdout.puts HighLine.color("#{action} LEAF", :magenta, :bold) if options[:verbose]

        if options[:verbose] && options[:name_mode] == :modern && inferred_program_name(fe_prg.path).nil?

          $stdout.puts HighLine.color("program name is the leaf directory", :yellow)
        end

        result = publish_cmake_list cml_path, leaf_cmake_text(fe_prg, options[:name_mode]), options[:dry_run]
      else

        # not-leaf, but might be a dead directory

        if dead_directory? subdirectory, contents, **options

          $stdout.puts HighLine.color("ignoring DEAD", :green, :bold) if options[:verbose]

          num_dead_directories += 1

          next
        end

        $stdout.puts HighLine.color("#{action} non-LEAF", :magenta, :bold) if options[:verbose]

        result = publish_cmake_list cml_path, nonleaf_cmake_text(contents), options[:dry_run]
      end

      case result
      when :create

        num_lists_created += 1
      when :update

        num_lists_updated += 1
      end
    end
  end
end

processed       = HighLine.color(num_directories_processed.to_s, :blue, :bold)

summary         = "#{processed} directories processed, in which there were #{num_clr(num_custom_directories_found, :cyan)} custom configuration(s), #{num_clr(num_missing_makelists_created, :magenta)} missing configuration(s), #{num_clr(num_stock_makelists_replaced, :green)} stock configuration(s); #{num_clr(num_dead_directories, :green)} dead directories"

created_phrase  = options[:dry_run] ? 'would be created' : 'created'
updated_phrase  = options[:dry_run] ? 'would be updated' : 'updated'

summary += "; #{num_clr(num_lists_created, :magenta)} #{created_phrase}, #{num_clr(num_lists_updated, :magenta)} #{updated_phrase}"

$stdout.puts summary


# ############################## end of file ############################# #

