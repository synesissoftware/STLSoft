#! /usr/bin/env ruby

# ######################################################################## #
# File:     .dev/test/unit/test_convert-doxy-groups.rb
#
# Purpose:  Unit tests for .dev/bin/convert-doxy-groups.rb
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


require 'minitest/autorun'
require 'open3'
require 'tmpdir'

class Test_convert_doxy_groups < Minitest::Test

  SCRIPT = File.expand_path('../../bin/convert-doxy-groups.rb', __dir__)
  MAPPINGS = File.expand_path('../../config/doc/group-section-mappings.PSV', __dir__)

  SGF = <<~'EOF'
    class X
    {
    public: // types
        typedef int a;

    public: // construction
        X();
    #ifndef FOO
        X(int);
    #endif
    public: // operations
        void f();

    private: // fields
        int m_x;
    };
  EOF

  FGF = <<~'EOF'
    class X
    {
    /// \name Member Types
    /// @{
    public:
        typedef int a;
    /// @}

    /// \name Construction
    /// @{
    public:
        X();
    #ifndef FOO
        X(int);
    #endif
    /// @}

    /// \name Operations
    /// @{
    public:
        void f();
    /// @}

    /// \name Members
    /// @{
    private:
        int m_x;
    /// @}
    };
  EOF

  LINE_PRESERVING = <<~'EOF'
    class X
    {
    /** \name Member Types */ /** @{ */ public:
        typedef int a;
    /// @}
    /** \name Construction */ /** @{ */ public:
        X();
    #ifndef FOO
        X(int);
    #endif /** @} */
    /** \name Operations */ /** @{ */ public:
        void f();
    /// @}
    /** \name Members */ /** @{ */ private:
        int m_x; /** @} */
    };
  EOF

  # SGF equivalent of FGF: the blank lines between groups are canonical
  SGF_CANONICAL = <<~'EOF'
    class X
    {
    public: // types
        typedef int a;

    public: // construction
        X();
    #ifndef FOO
        X(int);
    #endif

    public: // operations
        void f();

    private: // fields
        int m_x;
    };
  EOF

  def run_tool(*args, input)

    Dir.mktmpdir do |dir|

      path = File.join(dir, 'input.hpp')

      File.binwrite(path, input)

      out, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', MAPPINGS, *args, path)

      [ out, err.gsub(path, 'input.hpp'), status.exitstatus ]
    end
  end

  def test_to_fgf_expansive

    out, err, status = run_tool('--to-fgf', SGF)

    assert_equal(FGF, out)
    assert_equal('', err)
    assert_equal(0, status)
  end

  def test_to_fgf_expansive_is_default_mode

    out, = run_tool('--to-fgf', '--mode', 'expansive', SGF)

    assert_equal(FGF, out)
  end

  def test_to_fgf_line_preserving

    out, err, status = run_tool('--to-fgf', '--mode', 'line-preserving', SGF)

    assert_equal(LINE_PRESERVING, out)
    assert_equal(SGF.lines.size, out.lines.size)
    assert_equal('', err)
    assert_equal(0, status)
  end

  def test_to_sgf

    out, err, status = run_tool('--to-sgf', FGF)

    assert_equal(SGF_CANONICAL, out)
    assert_equal('', err)
    assert_equal(0, status)
  end

  def test_round_trip_fgf_sgf_fgf_is_identity

    sgf, = run_tool('--to-sgf', FGF)
    fgf, = run_tool('--to-fgf', sgf)

    assert_equal(FGF, fgf)
  end

  def test_no_blank_line_inserted_before_first_opener

    out, = run_tool('--to-fgf', "struct S\n{\npublic: // types\n    int a;\n};\n")

    assert_equal("struct S\n{\n/// \\name Member Types\n/// @{\npublic:\n    int a;\n/// @}\n};\n", out)
  end

  def test_blank_line_inserted_between_closer_and_next_opener

    out, = run_tool('--to-fgf', "struct S\n{\npublic: // types\n    int a;\npublic: // fields\n    int b;\n};\n")

    assert_match(/^\/\/\/ @\}\n\n\/\/\/ \\name Members$/, out)
  end

  def test_nested_type_groups_are_processed_independently

    sgf = <<~'EOF'
      class Outer
      {
      public: // types
          struct Inner
          {
          public: // fields
              int i;
          };
      public: // operations
          void f();
      };
    EOF

    out, err, = run_tool('--to-fgf', sgf)

    assert_equal('', err)
    assert_equal(3, out.scan(/^\s*\/\/\/ @\{$/).size)
    assert_equal(3, out.scan(/^\s*\/\/\/ @\}$/).size)

    back, = run_tool('--to-sgf', out)
    again, = run_tool('--to-fgf', back)

    assert_equal(out, again)
  end

  def test_unmapped_name_is_reported_and_left_unchanged

    input = "struct S\n{\npublic: // gobbledegook\n    int a;\n};\n"

    out, err, status = run_tool('--to-fgf', input)

    assert_equal(input, out)
    assert_match(/input\.hpp:3: unmapped group label 'gobbledegook'/, err)
    assert_equal(1, status)
  end

  def test_warn_only_exits_zero

    _, err, status = run_tool('--to-fgf', '--warn-only', "struct S\n{\npublic: // gobbledegook\n    int a;\n};\n")

    refute_empty(err)
    assert_equal(0, status)
  end

  def test_unmapped_title_is_reported_and_left_in_fgf

    input = "struct S\n{\n/// \\name Gobbledegook\n/// @{\npublic:\n    int a;\n/// @}\n};\n"

    out, err, status = run_tool('--to-sgf', input)

    assert_equal(input, out)
    assert_match(/input\.hpp:3: unmapped group label 'Gobbledegook'/, err)
    assert_equal(1, status)
  end

  def test_namespace_level_groups_are_ignored

    input = "/// \\name Functions\n/// @{\nvoid f();\n/// @}\n"

    out, err, status = run_tool('--to-sgf', input)

    assert_equal(input, out)
    assert_equal('', err)
    assert_equal(0, status)
  end

  def test_non_canonical_layout_is_reported_and_left_in_fgf

    # a blank line before the closer would not survive the round trip
    input = "struct S\n{\n/// \\name Member Types\n/// @{\npublic:\n    int a;\n\n/// @}\n};\n"

    out, err, = run_tool('--to-sgf', input)

    assert_equal(input, out)
    assert_match(/cannot be represented losslessly/, err)
  end

  def test_crlf_is_preserved

    out, = run_tool('--to-fgf', SGF.gsub("\n", "\r\n"))

    assert_equal(FGF.gsub("\n", "\r\n"), out)
  end

  def test_check_reports_files_that_would_change

    out, _, status = run_tool('--to-fgf', '--check', SGF)

    assert_match(/input\.hpp: would change/, out)
    assert_equal(1, status)
  end

  def test_in_place_requires_expansive_mode

    _, err, status = run_tool('--to-fgf', '--in-place', '--mode', 'line-preserving', SGF)

    assert_match(/--in-place requires --mode expansive/, err)
    refute_equal(0, status)
  end

  def test_mode_is_rejected_for_to_sgf

    _, err, status = run_tool('--to-sgf', '--mode', 'line-preserving', FGF)

    assert_match(/--mode only applies to --to-fgf/, err)
    refute_equal(0, status)
  end

  def test_blank_mapping_name_is_rejected

    Dir.mktmpdir do |dir|

      psv = File.join(dir, 'm.PSV')
      src = File.join(dir, 'a.hpp')

      File.write(psv, "Member Types|\n")
      File.write(src, SGF)

      _, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--to-fgf', src)

      assert_match(/m\.PSV:1: blank canonical name/, err)
      refute_equal(0, status)
    end
  end

  def test_blank_mapping_title_is_rejected

    Dir.mktmpdir do |dir|

      psv = File.join(dir, 'm.PSV')
      src = File.join(dir, 'a.hpp')

      File.write(psv, "|types\n")
      File.write(src, SGF)

      _, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--to-fgf', src)

      assert_match(/m\.PSV:1: blank title/, err)
      refute_equal(0, status)
    end
  end

  def with_files(psv_text, src_text)

    Dir.mktmpdir do |dir|

      psv = File.join(dir, 'm.PSV')
      src = File.join(dir, 'a.hpp')

      File.write(psv, psv_text)
      File.write(src, src_text)

      yield psv, src
    end
  end

  def test_alias_is_accepted_by_to_fgf_and_canonical_by_to_sgf

    with_files("Construction|construction\nMember Types|types|member types\nMembers|fields\nOperations|operations\n", SGF.sub('// types', '// member types')) do |psv, src|

      out, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--to-fgf', src)

      assert_equal('', err)
      assert_equal(0, status.exitstatus)
      assert_match(%r{/// \\name Member Types}, out)

      File.write(src, out)

      out, _, = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--to-sgf', src)

      assert_match(%r{public: // types$}, out)
    end
  end

  def test_duplicate_alias_is_rejected

    with_files("A|a|x\nB|b|x\n", SGF) do |psv, src|

      _, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--to-fgf', src)

      assert_match(/m\.PSV:2: duplicate name 'x'/, err)
      refute_equal(0, status.exitstatus)
    end
  end

  def test_uppercase_alias_is_rejected

    with_files("A|a|Bb\n", SGF) do |psv, src|

      _, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--to-fgf', src)

      assert_match(/m\.PSV:1: name 'Bb' is not lowercase/, err)
      refute_equal(0, status.exitstatus)
    end
  end

  def test_validate_reports_alias_and_unmapped_without_writing

    src_text = SGF.sub('// types', '// member types') + "\nclass X\n{\npublic: // nonesuch\n};\n"

    with_files("Member Types|types|member types\n", src_text) do |psv, src|

      _, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--validate', src)

      assert_match(/is an alias; canonical name is 'types'/, err)
      assert_match(/unmapped group label 'nonesuch'/, err)
      assert_equal(1, status.exitstatus)
      assert_equal(src_text, File.read(src))
    end
  end

  def test_validate_fix_rewrites_aliases_and_keeps_unmapped

    src_text = SGF.sub('// types', '// member types') + "\nclass X\n{\npublic: // nonesuch\n};\n"

    with_files("Member Types|types|member types\n", src_text) do |psv, src|

      out, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--validate', '--fix', src)

      assert_match(/fixed 1 group name/, out)
      assert_match(/unmapped group label 'nonesuch'/, err)
      refute_match(/alias/, err)
      assert_equal(1, status.exitstatus)
      assert_equal(src_text.sub('// member types', '// types'), File.read(src))
    end
  end

  def test_validate_fix_exits_zero_when_all_fixed

    with_files("Construction|construction\nMember Types|types|member types\nMembers|fields\nOperations|operations\n", SGF.sub('// types', '// member types')) do |psv, src|

      _, err, status = Open3.capture3('ruby', SCRIPT, '--mappings', psv, '--validate', '--fix', src)

      assert_equal('', err)
      assert_equal(0, status.exitstatus)
      assert_equal(SGF, File.read(src))
    end
  end

  def test_fix_requires_validate

    _, err, status = run_tool('--to-fgf', '--fix', FGF)

    assert_match(/--fix only applies to --validate/, err)
    refute_equal(0, status)
  end

  TRIPLE_SGF = <<~EOF
    class X
    {
    public: // types
        typedef int a;

    private: /// My Fields
        int m_x;
    };
  EOF

  def test_triple_is_ignored_without_flag

    out, err, status = run_tool('--to-fgf', TRIPLE_SGF)

    assert_equal('', err)
    assert_equal(0, status)
    refute_match(/My Fields/, out.lines.grep(/\\name/).join)
    assert_match(%r{^private: /// My Fields$}, out)
  end

  def test_triple_is_expanded_with_flag

    out, err, status = run_tool('--to-fgf', '--allow-sgf-triple-exemptions', TRIPLE_SGF)

    assert_equal('', err)
    assert_equal(0, status)
    assert_match(%r{^/// \\name My Fields$}, out)
    assert_match(%r{^/// \\name Member Types$}, out)
  end

  def test_unmapped_title_becomes_triple_with_flag

    fgf, = run_tool('--to-fgf', '--allow-sgf-triple-exemptions', TRIPLE_SGF)

    out, err, status = run_tool('--to-sgf', '--allow-sgf-triple-exemptions', fgf)

    assert_equal('', err)
    assert_equal(0, status)
    assert_equal(TRIPLE_SGF, out)
  end

  def test_unmapped_title_is_reported_without_flag

    fgf, = run_tool('--to-fgf', '--allow-sgf-triple-exemptions', TRIPLE_SGF)

    _, err, status = run_tool('--to-sgf', fgf)

    assert_match(/unmapped group label 'My Fields'/, err)
    assert_equal(1, status)
  end

  def test_validate_accepts_triple_with_flag

    _, err, status = run_tool('--validate', '--allow-sgf-triple-exemptions', TRIPLE_SGF)

    assert_equal('', err)
    assert_equal(0, status)
  end

  def test_shipped_mappings_file_loads

    _, err, status = run_tool('--to-fgf', '')

    assert_equal('', err)
    assert_equal(0, status)
  end

end


# ############################## end of file ############################# #
