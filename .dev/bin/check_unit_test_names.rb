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
PROGRAM_VER_MINOR = 1
PROGRAM_VER_PATCH = 0

PROCESS_MODE_STRINGS = %w{
    [b]oth
    [f]ile
    [r]unner
}

# ######################################################################## #
# functions


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

directories.each do |directory|

  $stdout.puts "processing in #{HighLine.color(directory, :blue, :bold)} ..." if options[:verbose]

  Recls.file_rsearch(directory, '*.c|*.cpp').each do |fe|

    srp = fe.search_relative_path

    puts "\t#{srp}" if options[:verbose]

    lines = IO.readlines fe, chomp: true

    this_dir = fe.directory_parts[-1]

    expected_name = "#{this_dir}#{fe.basename}"

    # "File:" processing?

    case options[:process_mode]
    when :both, :file

      line_File = lines.find { |line| line =~ / File: / }

      if line_File
        line_File =~ / File:\s+(.+)$/

        file_name = $1

        if expected_name != file_name

          $stderr.puts "\t#{srp}'s '#{HighLine.color(line_File, :magenta, :bold)}' does not match '#{HighLine.color(expected_name, :green)}'"
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
            end
          end
        end
      end
    end
  end
end

# ############################## end of file ############################# #

