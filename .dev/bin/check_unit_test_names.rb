#! /usr/bin/env ruby

# ######################################################################## #
# File:     dev/bin/check_unit_test_names.rb
#
# Purpose:  Searches unit-test files to verify the test names and file
#           labels.
#
# Created:  23rd August 2025
# Updated:  23rd August 2025
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


# ######################################################################## #
# includes


# ######################################################################## #
# constants

PROGRAM_VER_MAJOR = 0
PROGRAM_VER_MINOR = 0
PROGRAM_VER_PATCH = 0


# ######################################################################## #
# functions


# ######################################################################## #
# command-line handling

options = {}
climate = LibCLImate::Climate.new do |cl|

  cl.add_flag('--verbose', alias: '-v', help: 'operate verbosely') { options[:verbose] = true }

  cl.info_lines = [
    'STLSoft Development Tools',
    'Copyright Synesis Information Systems Pty Ltd (c) 2025',
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


# ######################################################################## #
# main()

directories.each do |directory|

  $stdout.puts "processing in #{HighLine.color(directory, :blue, :bold)} ..." if options[:verbose]

  Recls.file_rsearch(directory, '*.c|*.cpp').each do |fe|

    srp = fe.search_relative_path

    puts "\t#{srp}" if options[:verbose]

    lines = IO.readlines fe, chomp: true

    line_File = lines.find { |line| line =~ / File: / }
    lines_START_RUNNER = lines.select { |line| line =~ /XTESTS_START_RUNNER\w*\(/ }

    this_dir = fe.directory_parts[-1]

    if line_File
      line_File =~ / File:\s+(.+)$/

      file_name = $1
      expected_name = "#{this_dir}#{fe.basename}"

      if expected_name != file_name

        $stderr.puts "\t#{srp}'s #{HighLine.color(file_name, :green, :bold)} does not match"
      end
    end

    unless lines_START_RUNNER.empty?

      lines_START_RUNNER.each do |line|

        if line =~ /XTESTS_START_RUNNER\w*\s*\(\s*"([^"]+)"/

          name = $1

          if this_dir != (name + '/')

            $stderr.puts "\t#{srp}'s #{HighLine.color(line, :green, :bold)} does not match"
          end
        end
      end
    end
  end
end


# ############################## end of file ############################# #


