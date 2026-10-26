# STLSoft - Concepts <!-- omit in toc -->


## Table of Contents <!-- omit in toc -->

- [Introduction](#introduction)
- [Classic buffer-and-length OS APIs](#classic-buffer-and-length-os-apis)
  - [What goes wrong](#what-goes-wrong)
  - [Gold standard: probe, then fill](#gold-standard-probe-then-fill)
- [The Resizeable Buffer concept](#the-resizeable-buffer-concept)
  - [Motivation](#motivation)
  - [Requirements](#requirements)
  - [Models and non-models](#models-and-non-models)
  - [Helper: `resizeable_buffer_resize`](#helper-resizeable_buffer_resize)
  - [Contract for traits overloads that take an `rb`](#contract-for-traits-overloads-that-take-an-rb)
- [See also](#see-also)


## Introduction

This document records **concepts** used across **STLSoft** — structural
requirements that are not (necessarily) reified as language-level concepts
or base classes, but that several APIs assume. The first entry is the
**Resizeable Buffer** concept used by **UnixSTL** / **WinSTL**
`system_traits` and `filesystem_traits` overloads that accept a generic
buffer rather than a raw pointer and length.


## Classic buffer-and-length OS APIs

A large class of operating-system and C library functions take a
**destination buffer** and a **capacity** (in characters or bytes), and
return either a written length or a failure code. Familiar examples
include `getcwd` / `_getcwd`, `GetCurrentDirectory`,
`GetEnvironmentVariable`, `ExpandEnvironmentStrings`, and
`GetModuleFileName`.

Callers typically need either:

* to **fill** a buffer they already own; or
* to **discover** how large a buffer is required before allocating;


### What goes wrong

Historical APIs do not share one contract. Common failure modes include:

* **Fixed ceilings** — e.g. relying solely on `_MAX_PATH` / `PATH_MAX`,
  which is wrong for long paths and for systems without a compile-time
  maximum;
* **Truncation without a true demand** — e.g. raw Windows'
  [`GetModuleFileName`](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew)
  may truncate into the supplied buffer and return a value equal to the
  capacity, without reporting the size that would have been sufficient
  (callers then grow-and-retry, or wrap the API);
* **Ambiguous “empty destination”** — passing a **non-null** buffer with
  **capacity 0** is *not* a reliable size probe on many APIs: it often
  means “write nothing into this empty buffer” and returns `0` or fails,
  rather than returning the required length;
* **Inconsistent NUL character accounting** — some returns count the
  terminating `NUL`, some do not, and some change meaning between the
  “too small” and “success” cases;


### Gold standard: probe, then fill

The normative, unambiguous pattern preferred in **STLSoft** facades is a
**two-phase** protocol:

1. **Probe** — call with a **null** buffer and a **zero** capacity
   (`buff == nullptr` and `cch == 0`). The function returns a **demand**:
   a character count of *at least* the full result length **plus one** for
   the terminating `NUL` (it may return more than that minimum);
2. **Allocate** — obtain storage of at least that demand (stack, heap,
   `auto_buffer`, `vector`, …);
3. **Fill** — call again with a non-null buffer and that capacity. On
   success the return is the **length of the string excluding the
   `NUL`**;

Preconditions on the raw overloads take the form:

```text
0 == cch  ||  nullptr != buff
```

so that a zero capacity is allowed **only** when the buffer pointer is
null (the probe), and a non-null buffer always has a positive capacity
for a fill.

**Do not** probe by passing a non-null buffer with length zero. That
conflates “empty destination” with “size query” and is not portable
across OS APIs. Prefer **null buffer + zero length** for the probe;
wrappers that must paper over defective native APIs (such as
`GetModuleFileName`) should still *present* this gold contract to their
callers.

This probe-vs-fill convention is the gold standard summarised in the
discussion of required-length probing
([Ask Brave — probe with 0 length vs null buffer](https://search.brave.com/ask?q=What+about+when+wanting+to+probe+the+actual+required+length.+Should+the+caller+pass+0+length%2C+or+NUL...&source=quick-answer-followup&conversation=09aef0cd1c6f4bfdcbbb5fc05969c1dbd832)).


## The Resizeable Buffer concept

### Motivation

Repeating probe / allocate / fill at every call site is verbose and
easy to get wrong (especially NUL accounting and failure paths).
**STLSoft** therefore offers overloads that take a **resizeable
buffer** — any contiguous, resizable character sequence that can grow
to the demanded size — and perform the two-phase protocol internally.


### Requirements

A type `T` models **Resizeable Buffer** for an element type `CharT` when
it provides at least:

| Member | Meaning |
| --- | --- |
| `value_type` | Element type (typically `char` or `wchar_t`); |
| `size_type` | Unsigned size type; |
| `size() const` | Number of elements currently managed **including** the trailing `NUL` when the buffer is used as a C-string; |
| `empty() const` | Equivalent to `0 == size()`; |
| `operator[](size_type)` | Mutable access; contiguous storage so that `&rb[0]` addresses the first element when `size() > 0`; |
| `operator[](size_type) const` | Const access (needed by read-only helpers such as `has_dir_end`); |
| `resize(size_type)` | Change the number of managed elements. May return `bool` (`true` on success) or `void` (failure via exception or as documented for that type); |

**Invariants** assumed by path-oriented APIs:

* when `!empty()`, `rb[size() - 1] == CharT(0)` (trailing `NUL`);
* `resize` **preserves** existing elements up to the new size when
  shrinking or growing (so helpers such as `ensure_dir_end` may append
  in place);
* storage is **contiguous**;


### Models and non-models

| Type | Models? | Notes |
| --- | --- | --- |
| `stlsoft::auto_buffer<CharT>` | ✅ | Preferred; `resize` returns `bool`; |
| `std::vector<CharT>` | ✅ | `resize` returns `void`; use `resizeable_buffer_resize`; |
| `stlsoft::basic_path_buffer<…>` | ❌ | `size()` **excludes** the `NUL`; off-by-one if passed as an `rb`; |
| `winstl::basic_file_path_buffer<…>` | ❌ | `resize` is a no-op in some specialisations; |


### Helper: `resizeable_buffer_resize`

Declared in
[`stlsoft/util/resizeable_buffer_helpers.hpp`](./include/stlsoft/util/resizeable_buffer_helpers.hpp)
(Doxygen on the file and on the function documents parameters, return
values, failure policy, and the expectation that callers set
`ENOMEM` / `ERROR_OUTOFMEMORY` themselves).

`stlsoft::resizeable_buffer_resize(rb, newSize)` invokes `rb.resize(newSize)`
whether that member returns `bool` or `void`, and whether `resize` is a
one-argument member or a two-argument member with a defaulted fill (as on
pre-C++11 `std::vector`), and always returns `bool` (`true` on success).
Prefer it over calling `rb.resize` directly in generic code.


### Contract for traits overloads that take an `rb`

Overloads of the form `get_*(…, T_resizeableBuffer& rb)` (and similar)
should follow this gold sequence:

1. **Probe** via the raw overload with a null buffer and zero capacity;
2. If the probe returns `0` (failure) — **leave `rb` unchanged**, do
   **not** take `&rb[0]`, return `0`;
3. If `rb.size() < cchRequired` — call `resizeable_buffer_resize(rb,
   cchRequired)`; on failure set an appropriate out-of-memory status
   (`ENOMEM` / `ERROR_OUTOFMEMORY`) and return `0` without taking
   `&rb[0]` on an empty buffer;
4. **Fill** via the raw overload into `&rb[0]` with capacity `rb.size()`;
5. Optional out-parameters that point into the result (e.g. a basename
   separator pointer) are computed **only after** the final fill — never
   across a resize;

On success, the return value matches the raw fill overload (typically
the string length **excluding** the `NUL`). The buffer’s `size()` remains
the allocated demand (typically at least length + 1).


## See also

* Example:
  [`examples/by_concept/resizeable_buffer/`](./examples/by_concept/resizeable_buffer/main.cpp);
* Pseudo-struct documentation in
  `unixstl::filesystem_traits` / `winstl::filesystem_traits`
  (`struct resizeable_buffer` under `\name concepts`);
* Unit tests:
  [`test/unit/stlsoft/util/resizeable_buffer_helpers/`](./test/unit/stlsoft/util/resizeable_buffer_helpers/);
* [FAQ.md](./FAQ.md), [INSTALL.md](./INSTALL.md), [EXAMPLES.md](./EXAMPLES.md);


<!-- ########################### end of file ########################### -->
