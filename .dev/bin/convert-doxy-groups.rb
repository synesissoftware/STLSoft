#! /usr/bin/env ruby

# ######################################################################## #
# File:     .dev/bin/convert-doxy-groups.rb
#
# Purpose:  Converts between the Full Group Form (FGF) and the Simplified
#           Group Form (SGF) of Doxygen member groups in aggregate types
#           (class, struct, union), and acts as a Doxygen INPUT_FILTER.
#
#           FGF:
#
#               /// \name Member Types
#               /// @{
#               public:
#                   typedef int     value_type;
#               /// @}
#
#           SGF:
#
#               public: // types
#                   typedef int     value_type;
#
#           The SGF group name is mapped to the FGF title via the mappings
#           file (default: .dev/config/doc/group-section-mappings.PSV).
#
#           A group closes implicitly at the next group opener of the same
#           (or lesser) indent, or at the end of the type (a line that
#           begins with '}' at the same or lesser indent).
#
# Created:  12th November 2026
# Updated:  12th November 2026
#
# Author:   Matthew Wilson
#
# Copyright (c) 2026, Synesis Information Systems
# All rights reserved
#
# ######################################################################## #


# ######################################################################## #
# requires

require 'highline'
require 'libclimate'


# ######################################################################## #
# constants

PROGRAM_VER_MAJOR = 0
PROGRAM_VER_MINOR = 1
PROGRAM_VER_PATCH = 0

DEFAULT_MAPPINGS_PATH = File.expand_path('../config/doc/group-section-mappings.PSV', __dir__)

MODES = %w{
  expansive
  line-preserving
}

ACCESS_BARE_RE = /\A(?<indent>[ \t]*)(?<access>public|protected|private):[ \t]*\z/
ACCESS_ANY_RE = /\A[ \t]*(?:public|protected|private):/
FGF_CLOSE_RE = /\A[ \t]*\/\/\/ @\}[ \t]*\z/
FGF_NAME_RE = /\A(?<indent>[ \t]*)\/\/\/ \\name (?<title>\S.*?)[ \t]*\z/
FGF_OPEN_RE = /\A[ \t]*\/\/\/ @\{[ \t]*\z/
PP_IF_RE = /\A[ \t]*#[ \t]*if/
PP_ENDIF_RE = /\A[ \t]*#[ \t]*endif/
PP_RE = /\A[ \t]*#/
SGF_OPENER_RE = /\A(?<indent>[ \t]*)(?<access>public|protected|private):[ \t]*(?<marker>\/\/\/?)[ \t]*(?<name>\S.*?)[ \t]*\z/
TYPE_END_RE = /\A(?<indent>[ \t]*)\}/

# Matches an SGF opener; a triple-slash opener ('private: /// Title') is
# recognised only when +allow_triple+ is true.
def match_opener(line, allow_triple)

  m = SGF_OPENER_RE.match(line) or return nil

  return nil if '///' == m[:marker] && !allow_triple

  m
end


# ######################################################################## #
# classes

class MappingError < StandardError; end

class Mappings

  attr_reader :forward    # every SGF name (canonical or alias) => FGF title
  attr_reader :reverse    # FGF title => canonical SGF name

  def initialize(forward, reverse)

    @forward = forward
    @reverse = reverse
  end

  # True if +name+ is a valid SGF name that is not the canonical form
  def alias?(name)

    title = @forward[name] or return false

    @reverse[title] != name
  end

  def self.load(path)

    forward = {}
    reverse = {}

    File.foreach(path, mode: 'rb').with_index(1) do |line, index|

      line = line.chomp.sub(/\r\z/, '')

      next if line.strip.empty?
      next if line =~ /\A\s*#/

      cols = line.split('|', -1)
      where = "#{path}:#{index}"

      raise MappingError, "#{where}: expected at least two pipe-separated columns" if cols.size < 2

      title, *names = cols.map { |c| c.strip.b }

      raise MappingError, "#{where}: blank title" if title.empty?
      raise MappingError, "#{where}: duplicate title '#{title}'" if reverse.key?(title)

      names.each_with_index do |name, ix|

        raise MappingError, "#{where}: blank #{0 == ix ? 'canonical name' : 'alias'}" if name.empty?
        raise MappingError, "#{where}: name '#{name}' is not lowercase" unless name == name.downcase
        raise MappingError, "#{where}: duplicate name '#{name}'" if forward.key?(name)

        forward[name] = title
      end

      reverse[title] = names.first
    end

    new(forward, reverse)
  end
end


# ######################################################################## #
# functions

# Colours text only when the stream is a terminal, so that output captured
# by Doxygen (as an INPUT_FILTER) or by a pipe is free of escape codes.
def colour_stderr(text, *styles)

  $stderr.tty? ? HighLine.color(text, *styles) : text
end

def colour_stdout(text, *styles)

  $stdout.tty? ? HighLine.color(text, *styles) : text
end

def width(indent)

  indent.gsub("\t", '    ').size
end

def split_text(text)

  eol = text.include?("\r\n") ? "\r\n" : "\n"

  [ text.gsub("\r\n", "\n").split("\n", -1), eol ]
end

# Expands every SGF group in +text+ into FGF.
#
# Returns [ text, errors ]; each error is [ line_number, message ].
def to_fgf(text, mappings, mode, allow_triple = false)

  lines, eol = split_text(text)
  errors = []

  replacements = {}   # opener index => replacement line(s)
  appends = Hash.new { |h, k| h[k] = [] }       # index => strings appended to line
  prefixes = Hash.new { |h, k| h[k] = [] }      # index => strings prefixed after indent
  after = Hash.new { |h, k| h[k] = [] }         # index => lines inserted after line
  blank_replacements = {}                       # index => closer replacing a blank line

  lines.each_with_index do |line, i|

    m = match_opener(line, allow_triple) or next

    title = '///' == m[:marker] ? m[:name] : mappings.forward[m[:name].b]

    if title.nil?

      errors << [ i + 1, "unmapped group label '#{m[:name]}'" ]
      next
    end

    w = width(m[:indent])
    t = nil

    ((i + 1)...lines.size).each do |j|

      l = lines[j]

      if (mo = match_opener(l, allow_triple))

        (t = j; break) if width(mo[:indent]) <= w
      elsif (me = TYPE_END_RE.match(l))

        (t = j; break) if width(me[:indent]) <= w
      elsif (mn = FGF_NAME_RE.match(l))

        (t = j; break) if width(mn[:indent]) <= w && lines[j + 1] =~ FGF_OPEN_RE
      end
    end

    if t.nil?

      errors << [ i + 1, "no end of type found for group '#{m[:name]}'" ]
      next
    end

    # find the last line of the group (L): the last code line, extended to
    # cover any trailing #endif that closes a conditional opened within
    # the group

    code_last = i
    depth = 0
    endif_last = i

    ((i + 1)...t).each do |j|

      l = lines[j]

      if PP_IF_RE =~ l

        depth += 1
      elsif PP_ENDIF_RE =~ l

        if depth > 0

          depth -= 1
          endif_last = j
        end
      end

      code_last = j unless l.strip.empty? || PP_RE =~ l
    end

    last = [ code_last, endif_last ].max

    closer = "#{m[:indent]}/// @}"
    terminator_is_opener = !(TYPE_END_RE =~ lines[t])

    case mode
    when 'expansive'

      after[last] << closer

      if terminator_is_opener

        has_blank = ((last + 1)...t).any? { |j| lines[j].strip.empty? }

        after[last] << '' unless has_blank
      end

      replacements[i] = [
        "#{m[:indent]}/// \\name #{title}",
        "#{m[:indent]}/// @{",
        "#{m[:indent]}#{m[:access]}:",
      ]
    when 'line-preserving'

      # NOTE: '@{' must be in a comment separate from '\name', otherwise
      # Doxygen absorbs it into the title and reports unbalanced grouping.
      replacements[i] = [
        "#{m[:indent]}/** \\name #{title} */ /** @{ */ #{m[:access]}:",
      ]

      if (last + 1) < t && lines[last + 1].strip.empty?

        blank_replacements[last + 1] = closer
      elsif !lines[last].include?('//')

        appends[last] << ' /** @} */'
      else

        prefixes[t] << '/** @} */ '
      end
    end
  end

  out = []

  lines.each_with_index do |line, i|

    if blank_replacements.key?(i)

      out << blank_replacements[i]
    elsif replacements.key?(i)

      rep = replacements[i].dup

      unless prefixes[i].empty?

        indent = line[/\A[ \t]*/]

        rep[0] = rep[0].sub(/\A#{Regexp.escape(indent)}/) { indent + prefixes[i].join }
      end

      rep[-1] += appends[i].join

      out.concat(rep)
    else

      l = line

      unless prefixes[i].empty?

        indent = l[/\A[ \t]*/]

        l = indent + prefixes[i].join + l[indent.size..-1]
      end

      out << (l + appends[i].join)
    end

    out.concat(after[i])
  end

  [ out.join(eol), errors ]
end

# Collapses every FGF group in +text+ into SGF, retaining only those groups
# for which the conversion is lossless.
#
# Returns [ text, errors ]; each error is [ line_number, message ].
def to_sgf(text, mappings, allow_triple = false)

  lines, eol = split_text(text)
  errors = []
  candidates = []

  lines.each_with_index do |line, i|

    mn = FGF_NAME_RE.match(line) or next

    lines[i + 1] =~ FGF_OPEN_RE or next

    ma = ACCESS_BARE_RE.match(lines[i + 2] || '')

    if ma.nil?

      # not a group of an aggregate type, unless it has an access specifier

      if lines[i + 2] =~ ACCESS_ANY_RE

        errors << [ i + 3, "access specifier of group '#{mn[:title]}' has trailing content" ]
      end

      next
    end

    sgf_name = mappings.reverse[mn[:title].b]

    triple = false

    if sgf_name.nil? && allow_triple

      sgf_name = mn[:title]
      triple = true
    end

    if sgf_name.nil?

      errors << [ i + 1, "unmapped group label '#{mn[:title]}'" ]
      next
    end

    depth = 1
    closer = nil

    ((i + 3)...lines.size).each do |j|

      if FGF_OPEN_RE =~ lines[j]

        depth += 1
      elsif FGF_CLOSE_RE =~ lines[j]

        depth -= 1

        (closer = j; break) if 0 == depth
      end
    end

    if closer.nil?

      errors << [ i + 1, "no closer found for group '#{mn[:title]}'" ]
      next
    end

    candidates << {
      closer: closer,
      line: i + 1,
      opener: i,
      sgf: "#{ma[:indent]}#{ma[:access]}: #{triple ? '///' : '//'} #{sgf_name}",
      title: mn[:title],
    }
  end

  apply = lambda do |subset|

    drop = {}
    replace = {}

    subset.each do |c|

      replace[c[:opener]] = c[:sgf]
      drop[c[:opener] + 1] = true
      drop[c[:opener] + 2] = true
      drop[c[:closer]] = true
    end

    out = []

    lines.each_with_index do |line, i|

      next if drop.key?(i)

      out << (replace[i] || line)
    end

    out.join(eol)
  end

  reference, = to_fgf(text, mappings, 'expansive', allow_triple)

  accepted = candidates

  unless to_fgf(apply.call(accepted), mappings, 'expansive', allow_triple).first == reference

    accepted = []

    candidates.each do |c|

      trial = accepted + [ c ]

      if to_fgf(apply.call(trial), mappings, 'expansive', allow_triple).first == reference

        accepted = trial
      else

        errors << [ c[:line], "group '#{c[:title]}' cannot be represented losslessly; left in FGF" ]
      end
    end
  end

  [ apply.call(accepted), errors ]
end


# Validates the SGF group names (and FGF group titles) in +text+.
#
# Returns [ text, findings ]; each finding is [ line_number, message,
# fixable ]. A fixable finding is a valid alias that +text+ (the first
# element) has rewritten to its canonical name.
def validate(text, mappings, allow_triple = false)

  lines, eol = split_text(text)
  findings = []

  lines.each_with_index do |line, i|

    if (m = match_opener(line, allow_triple))

      next if '///' == m[:marker]

      name = m[:name].b
      title = mappings.forward[name]

      if title.nil?

        findings << [ i + 1, "unmapped group label '#{m[:name]}'", false ]
      elsif mappings.alias?(name)

        canonical = mappings.reverse[title]

        findings << [ i + 1, "group name '#{m[:name]}' is an alias; canonical name is '#{canonical}'", true ]

        lines[i] = line[0...m.begin(:name)] + canonical + line[m.end(:name)..-1]
      end
    elsif (m = FGF_NAME_RE.match(line)) && lines[i + 1] =~ FGF_OPEN_RE && ACCESS_BARE_RE =~ (lines[i + 2] || '')

      unless allow_triple || mappings.reverse.key?(m[:title].b)

        findings << [ i + 1, "unmapped group label '#{m[:title]}'", false ]
      end
    end
  end

  [ lines.join(eol), findings ]
end


# ######################################################################## #
# command-line handling

options = {
  action: nil,
  allow_triple: false,
  check: false,
  fix: false,
  in_place: false,
  mappings: DEFAULT_MAPPINGS_PATH,
  mode: 'expansive',
  warn_only: false,
}

climate = LibCLImate::Climate.new do |cl|

  cl.add_flag('--allow-sgf-triple-exemptions', help: "Treats 'private: /// Title' as an SGF group whose label is the FGF title, bypassing the mappings file") { options[:allow_triple] = true }

  cl.add_flag('--check', help: 'Reports files that would change; writes nothing; exits 1 if any would') { options[:check] = true }

  cl.add_flag('--fix', help: 'With --validate, rewrites aliased group names to canonical form, in place') { options[:fix] = true }

  cl.add_flag('--in-place', help: 'Rewrites the files in place (expansive form only)') { options[:in_place] = true }

  cl.add_option('--mappings', alias: '-M', help: "Mappings file. Defaults to #{DEFAULT_MAPPINGS_PATH}") do |o, sp|

    options[:mappings] = o.value
  end

  cl.add_option('--mode', alias: '-m', help: "SGF->FGF mode. Defaults to 'expansive'", values: MODES) do |o, sp|

    options[:mode] = o.value
  end

  cl.add_flag('--to-fgf', help: 'Converts SGF to FGF') do

    cl.abort "conversion direction already specified; use --help for usage" if options[:action]

    options[:action] = :to_fgf
  end

  cl.add_flag('--to-sgf', help: 'Converts FGF to SGF') do

    cl.abort "conversion direction already specified; use --help for usage" if options[:action]

    options[:action] = :to_sgf
  end

  cl.add_flag('--validate', help: 'Validates the SGF group names; reports only, unless --fix is given') do

    cl.abort "conversion direction already specified; use --help for usage" if options[:action]

    options[:action] = :validate
  end

  cl.add_flag('--warn-only', help: 'Always exits 0 when problems are reported (for use as a Doxygen INPUT_FILTER)') { options[:warn_only] = true }

  cl.info_lines = [
    'STLSoft Development Tools',
    'Copyright Synesis Information Systems Pty Ltd (c) 2026',
    :version,
    'Converts Doxygen member groups between Full Group Form (FGF) and Simplified Group Form (SGF)',
    nil,
  ]
  cl.value_names = [ 'file' ]
  cl.constrain_values = (1..)
  cl.usage_values = '<file-1> [ ... <file-N> ]'
end

r = climate.run ARGV

files = r.values

climate.abort 'must specify --to-fgf, --to-sgf or --validate; use --help for usage' if options[:action].nil?
climate.abort '--fix only applies to --validate; use --help for usage' if options[:fix] && :validate != options[:action]
climate.abort '--in-place and --check do not apply to --validate; use --fix or no flag; use --help for usage' if :validate == options[:action] && (options[:in_place] || options[:check])
climate.abort '--mode only applies to --to-fgf; use --help for usage' if :to_fgf != options[:action] && 'expansive' != options[:mode]
climate.abort '--in-place and --check are mutually exclusive; use --help for usage' if options[:in_place] && options[:check]
climate.abort '--in-place requires --mode expansive; use --help for usage' if options[:in_place] && 'expansive' != options[:mode]
climate.abort 'more than one file requires --check or --in-place; use --help for usage' if files.size > 1 && !(options[:in_place] || options[:check] || :validate == options[:action])

begin

  mappings = Mappings.load(options[:mappings])
rescue MappingError, SystemCallError => x

  climate.abort x.message
end


# ######################################################################## #
# main()

$stdout.binmode

problems = 0
changed = 0

files.each do |file|

  unless File.file?(file)

    climate.abort "'#{file}' is not a file"
  end

  text = File.binread(file)

  result, errors = case options[:action]
                   when :to_fgf then to_fgf(text, mappings, options[:mode], options[:allow_triple])
                   when :validate then validate(text, mappings, options[:allow_triple])
                   else to_sgf(text, mappings, options[:allow_triple])
                   end

  fixed = 0

  errors.each do |line, message, fixable|

    if fixable && options[:fix]

      fixed += 1

      next
    end

    $stderr.puts "#{colour_stderr("#{file}:#{line}", :white, :bold)}: #{colour_stderr(message, :magenta, :bold)}"

    problems += 1
  end

  if :validate == options[:action]

    if options[:fix] && result != text

      File.binwrite(file, result)

      $stdout.puts "#{colour_stdout(file, :blue, :bold)}: #{colour_stdout("fixed #{fixed} group name(s)", :green)}"

      changed += 1
    end
  elsif options[:check]

    if result != text

      $stdout.puts "#{colour_stdout(file, :blue, :bold)}: #{colour_stdout('would change', :yellow)}"

      changed += 1
    end
  elsif options[:in_place]

    if result != text

      File.binwrite(file, result)

      changed += 1
    end
  else

    $stdout.write(result)
  end
end

exit 0 if options[:warn_only]
exit 1 if problems > 0
exit 1 if options[:check] && changed > 0

exit 0


# ############################## end of file ############################# #
