#! /usr/bin/env ruby

# ######################################################################## #
# File:     dev/bin/check_unit_test_names.rb
#
# Purpose:  Searches unit-test files to verify the test names and file
#           labels.
#
# Created:  23rd August 2025
# Updated:  29th October 2026
#
# Author:   Matthew Wilson
#
# Copyright (c) 2025-2026, Matthew Wilson and Synesis Information Systems
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
PROGRAM_VER_PATCH = 1

PROCESS_MODE_STRINGS = %w{
    [b]oth
    [f]ile
    [r]unner
}

PROJECT_ROOT = File.expand_path('../..', __dir__)


# ######################################################################## #
# functions

def num_clr(n)

  case n
  when 0
    HighLine.color(n.to_s, :green, :blue)
  else
    HighLine.color(n.to_s, :red, :bold)
  end
end

# Path of +entry+ relative to the STLSoft project root. For a test or
# example this is the File: label, e.g.
# `test/component/inetstl/util/uds_helpers/entry.cpp`. xTests infers a
# runner name from the same path; the label keeps the slashes.
def project_relative_path(entry)

  Recls.derive_relative_path(PROJECT_ROOT, entry.path)
end


# ######################################################################## #
# command-line handling

options = {}
climate = LibCLImate::Climate.new do |cl|

  cl.add_flag('--verbose', alias: '-v', help: 'Operate verbosely') { options[:verbose] = true }

  cl.add_option('--mode', alias: '-m', help: "Processing mode. Defaults to 'both'", values: PROCESS_MODE_STRINGS) do |o, sp|

    cl.abort "processing mode already specified; use --help for usage" if options[:process_mode]

    options[:process_mode] = o.value.map_option_string(PROCESS_MODE_STRINGS) or cl.abort "invalid processing mode '#{o.value}'; use --help for usage"
  end

  cl.info_lines = [
    'STLSoft Development Tools',
    'Copyright Synesis Information Systems Pty Ltd (c) 2025-2026',
    :version,
    "Searches unit-test files to verify the test names and file labels",
    nil,
  ]
  cl.value_names = [ 'directory' ]
  cl.constrain_values = 1..;
  cl.usage_values = '<directory-1> [ ... <directory-N> ]'
end

r = climate.run ARGV

directories = r.values

directories.all? { |directory| Recls.directory? directory } or climate.abort "one or more of given arguments is not a directory"

options[:process_mode] ||= :both


# ######################################################################## #
# main()

num_files             = 0
num_files_bad_File    = 0
num_files_bad_RUNNER  = 0

directories.each do |directory|

  $stdout.puts "processing in #{HighLine.color(directory, :blue, :bold)} ..." if options[:verbose]

  Recls.file_rsearch(directory, '*.c|*.cpp').each do |fe|

    srp = fe.search_relative_path

    puts "\t#{srp}" if options[:verbose]

    lines = IO.readlines fe, chomp: true

    this_dir = fe.directory_parts[-1]

    relative_path = project_relative_path fe

    expected_file = if relative_path =~ %r{\A(?:example|examples|test)/}

      relative_path
    else

      "#{this_dir}#{fe.basename}"
    end

    expected_name = "#{this_dir}#{fe.basename}"


    num_files += 1

    # "File:" processing?

    case options[:process_mode]
    when :both, :file

      line_File = lines.find { |line| line =~ / File: / }

      if line_File
        line_File =~ / File:\s+(.+)$/

        file_name = $1

        if expected_file != file_name

          $stderr.puts "\t#{srp}'s '#{HighLine.color(line_File, :magenta, :bold)}' does not match '#{HighLine.color(expected_file, :green)}'"

          num_files_bad_File += 1
        end
      end
    end

    # runner processing?

    case options[:process_mode]
    when :both, :runner

      lines_START_RUNNER = lines.select { |line| line =~ /XTESTS_START_RUNNER\w*\(/ }

      unless lines_START_RUNNER.empty?

        lines_START_RUNNER.each do |line|

          if line =~ /XTESTS_START_RUNNER\w*\s*\(\s*"([^"]+)"/

            name = $1

            if this_dir != (name + '/')

              $stderr.puts "\t#{srp}'s '#{HighLine.color(line, :magenta, :bold)}' does not match '#{HighLine.color(expected_name, :green)}'"

              num_files_bad_RUNNER += 1
            end
          end
        end
      end
    end
  end
end

case options[:process_mode]
when :file

  $stdout.puts "processed #{HighLine.color(num_files.to_s, :green, :blue)} files, of which #{num_clr(num_files_bad_File)} had bad 'File:' labels"
when :runner

  $stdout.puts "processed #{HighLine.color(num_files.to_s, :green, :blue)} files, of which #{num_clr(num_files_bad_RUNNER)} had bad START_RUNNER labels"
else

  $stdout.puts "processed #{HighLine.color(num_files.to_s, :green, :blue)} files, of which #{num_clr(num_files_bad_File)} had bad 'File:' labels and #{num_clr(num_files_bad_RUNNER)} had bad START_RUNNER labels"
end


# ############################## end of file ############################# #
