# STLSoft - Doxygen Member Groups <!-- omit in toc -->

Strategy note for **STLSoft** (this tree, **STLSoft.b**) defining the two forms in which member groups of aggregate types (`class`, `struct`, `union`) are written, and the tool that converts between them.

- [Forms](#forms)
  - [Full Group Form (FGF)](#full-group-form-fgf)
  - [Simplified Group Form (SGF)](#simplified-group-form-sgf)
- [Rules](#rules)
- [Section mappings](#section-mappings)
- [Tool](#tool)
  - [Validation](#validation)
  - [Triple-slash exemptions](#triple-slash-exemptions)
  - [Modes of SGF to FGF](#modes-of-sgf-to-fgf)
  - [Doxygen integration](#doxygen-integration)
  - [Reversibility](#reversibility)
- [Reported conditions](#reported-conditions)


## Forms

### Full Group Form (FGF)

The form Doxygen requires: a two-line opener, the access specifier, and an explicit closer.

```cpp
/// \name Member Types
/// @{
public:
    typedef int                                             value_type;
/// @}
```

### Simplified Group Form (SGF)

The form programmers write and read: the access specifier carries a trailing comment naming the group; there is no closer.

```cpp
public: // types
    typedef int                                             value_type;
```

**SGF** is the canonical on-disk form. **FGF** is generated for Doxygen only (see [Doxygen integration](#doxygen-integration)).


## Rules

* an SGF opener is an access specifier (`public:`, `protected:`, `private:`) followed on the same line by `//` and a group name;
* a group closes implicitly at the first of:
  * the next group opener (SGF, or the `/// \name` line of an FGF group) at the same or lesser indent;
  * the end of the type: a line beginning with `}` at the same or lesser indent as the opener;
* the SGF group name is lowercase and may be fewer words than the FGF title (`types` for `Member Types`);
* preprocessor conditionals are ignored, whether within a group, around a group, or around the end of a group (`#if 0` included);
* in FGF, the closer follows the last line of the group, including any `#endif` that closes a conditional opened within the group;
* a blank line separates a closer from the next opener; the first opener in a type has none inserted before it;
* a bare access specifier with no group comment is not a group opener, and never becomes one.


## Section mappings

The correspondence between FGF titles and SGF names is held in [**.dev/config/doc/group-section-mappings.PSV**](../.dev/config/doc/group-section-mappings.PSV): pipe-separated columns, `<fgf-title>|<sgf-name>[|<sgf-alias>]...`.

* the first column is the FGF title, which appears once only;
* the second column is the canonical SGF name, written by `--to-sgf`;
* any further columns are SGF aliases: accepted by `--to-fgf`, and reported (and optionally fixed) by `--validate`;
* no column may be blank;
* every SGF name and alias must be lowercase, and unique across the whole file, so that the mapping is reversible;
* entries are sorted lexicographically (case-insensitively) by FGF title;
* an SGF name or FGF title that is not in the file is reported, never guessed.

To add a section, add a line to the file. To accept a synonym, append it as an alias.


## Tool

[**.dev/bin/convert-doxy-groups.rb**](../.dev/bin/convert-doxy-groups.rb) requires **HighLine** and **libCLImate.Ruby** (see the **Gemfile**).

```bash
# FGF -> SGF, in place
.dev/bin/convert-doxy-groups.rb --to-sgf --in-place include/unixstl/synch/exceptions.hpp

# SGF -> FGF, to standard output
.dev/bin/convert-doxy-groups.rb --to-fgf include/winstl/synch/exceptions.hpp

# which files would change?
.dev/bin/convert-doxy-groups.rb --to-sgf --check $(find include -name '*.h*')
```

### Validation

```bash
# report only
.dev/bin/convert-doxy-groups.rb --validate $(find include -name '*.h*')

# rewrite aliased names to canonical form, in place
.dev/bin/convert-doxy-groups.rb --validate --fix $(find include -name '*.h*')
```

`--validate` reports unmapped SGF names, unmapped FGF titles (of aggregate-type groups), and aliased SGF names. `--fix` rewrites only the aliased names; unmapped names remain reported. The exit status is non-zero while anything unfixed is reported.


### Triple-slash exemptions

With `--allow-sgf-triple-exemptions`, an SGF opener whose comment begins `///` is an *exempt* group: its label is the FGF title itself, and the mappings file is bypassed.

```cpp
private: /// My Fields          // <-> /// \name My Fields
```

* `--to-fgf` expands `private: /// My Fields` to the FGF title `My Fields`;
* `--to-sgf` writes a group whose title is not in the mappings file as `private: /// <title>`, rather than reporting it;
* `--validate` accepts exempt groups;
* without the flag, a `///` opener is not recognised as a group opener at all.


### Modes of SGF to FGF

| Mode | Output | Intended use |
| --- | --- | --- |
| `expansive` (default) | the canonical multi-line FGF, as hand-written | permanent source conversion; other projects' source |
| `line-preserving` | the same number of lines as the input | Doxygen `INPUT_FILTER` |

In `line-preserving` mode the opener becomes a single line, and the closer is placed on an existing blank line, or appended to the last line of the group, or (when that line ends with a `//` comment) prefixed to the line that ends the group:

```cpp
/** \name Member Types */ /** @{ */ public:
    typedef int     value_type;
#endif /** @} */
```

`@{` must be in a comment separate from `\name`; otherwise Doxygen absorbs it into the title and reports unbalanced grouping.

`--in-place` is available only for `expansive`.

### Doxygen integration

The **Doxyfile** sets:

```text
INPUT_FILTER = "ruby .dev/bin/convert-doxy-groups.rb --to-fgf --mode line-preserving --warn-only"
```

so that Doxygen sees FGF for all input, and reports warnings and source links at the original line numbers. `--warn-only` makes problems visible on standard error without failing the filter. `SOURCE_BROWSER` listings show the SGF source as written.

### Reversibility

`--to-sgf` converts a group only if expanding the result reproduces the original text exactly; otherwise the group is reported and left in FGF. Mixed files are therefore valid, and a conversion can never silently change the meaning of a file.


## Reported conditions

The tool reports, and leaves unchanged, any group it cannot process. The operator corrects the source (or the mappings file), and runs it again.

| Condition | Typical cause |
| --- | --- |
| unmapped group label / title | name or title absent from the mappings file |
| alias (`--validate` only) | a valid SGF name that is not the canonical name |
| no end of type found | unbalanced braces, or an opener outside a type |
| no closer found | a malformed `/// @}` (e.g. `///  @}`), or an unterminated group |
| cannot be represented losslessly | non-canonical layout, e.g. a blank line before the closer, or a bare access specifier following a group |


<!-- ########################### end of file ########################### -->
