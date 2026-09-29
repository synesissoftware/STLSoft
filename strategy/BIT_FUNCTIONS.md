# STLSoft.b - Bit Functions <!-- omit in toc -->

Strategy note for **STLSoft.b** bit utilities. Measurements are of the performance program **test/performance/stlsoft/bit_functions/main.cpp**. Library sources are **include/stlsoft/util/bits/count_functions.h**, **include/stlsoft/util/bits/test_functions.h**, and **include/stlsoft/util/bits/xor_functions.h**. Intrinsic detection and naming live in **include/stlsoft/api/external/bitfns.h** and **include/stlsoft/api/internal/bitfns.h**.


## Question

If intrinsics are never adopted, should `count_bits()` use Kernighan on Apple and the 8-bit table everywhere else?

**No**. The fast Kernighan numbers are Apple Clang rewriting the loop into a hardware popcount. They are not a property of Apple hardware. On every other toolchain measured here, that rewrite did not happen, and the table is several times faster. A default keyed on Apple, or on ARM, would be right only while the compiler keeps doing that rewrite, and badly wrong when it does not.

The cost of leaving the table in place on Apple Clang is a fraction of a nanosecond per call. The cost of leaving Kernighan in place on a compiler that executes the source loop is about 10–12 ns (`uint32_t`, all ones) and about 23–33 ns (`uint64_t`, all ones), against about 1–2 ns for the table.


## What was measured

Optimised release builds (`optimisation: speed`, `NDEBUG`), five-sample medians, 20,000,000 iterations. Anchors match across cells for the same input pattern. CI exports `SIS_PERFTESTS_GROUPGAPS=1` (harness banner `Env: SIS_PERFTESTS_GROUPGAPS=1` only when truey).

* **Full CI wave (GitHub Actions), with intrinsic rows:** `linux-clang` (Clang 18.1.3), `linux-gcc` (GNU 13.3), `macos-clang` (Clang 21.0.0), `macos-gcc` (job label; harness still reports Clang 21.0.0 — Apple’s `gcc` driver), `windows-cl` (Visual C++ 18.x), `windows-mingw` (GNU 15.2). Widths `uint8_t` … `uint64_t` (+ `int` on `count_bits()`); patterns sequential `i`, `~i`, ones, `ones^1`, zero, rotating bit, both-halves-live (`/wide`).
* **Earlier pre-intrinsic matrix** (commit `74b74407875100e0f1b6f5f7658a714c9a8d57b3`) remains useful as a baseline without intrinsic columns; numbers below supersede it for policy.


### Population Count, CI summary (`uint32_t` / `uint64_t` ns/call)

| Cell | Kernighan ones | Table ones | Intrinsic ones | Intrinsic sequential |
| --- | --- | --- | --- | --- |
| Linux Clang 18.1.3 | 16.48 / 33.45 | 0.92 / 2.02 | 1.29 / 1.29 | 0.85 / 0.85 |
| Linux GCC 13.3 | 9.82 / 27.58 | 0.82 / 1.58 | 2.76 / 2.75 | 2.73 / 2.73 |
| macOS Clang 21 | 0.51 / 0.93 | 1.50 / 2.16 | 0.57 / 0.53 | 0.27 / 0.24 |
| macOS “gcc” (Clang 21) | 0.39 / 0.71 | 1.13 / 1.44 | 0.43 / 0.40 | 0.23 / 0.22 |
| Windows MSVC 18 | 11.42 / 23.08 | 1.01 / 3.13 | 0.32 / 0.32 | 0.32 / 0.32 |
| Windows MinGW GCC 15.2 | 11.85 / 24.04 | 0.97 / 1.73 | 2.21 / 2.20 | 2.21 / 2.20 |

`count_bits()` tracks the table on every cell.


### Population Count detail by cell

Cells are ns/call for `uint8_t` / `uint16_t` / `uint32_t` / `uint64_t` unless noted.

**Linux Clang 18.1.3** — table usually best on dense; intrinsic competitive (~0.85–1.3 ns) and sometimes ahead of the table on sequential. Not a flat libcall. `/bit` **deletes** the intrinsic (0 ns, anchor still `80,000,000`); Kernighan and table remain live.

| Row | Kernighan | 8-bit table | intrinsic |
| --- | --- | --- | --- |
| sequential `i` | 1.94 / 4.14 / 5.80 / 5.78 | 0.29 / 0.43 / 1.16 / 1.11 | 1.00 / 0.92 / 0.85 / 0.85 |
| all-ones | 3.33 / 7.00 / 16.48 / 33.45 | 0.31 / 0.45 / 0.92 / 2.02 | 1.09 / 1.36 / 1.29 / 1.29 |
| rotating bit | 0.89 / 0.89 / 0.89 / 1.38 | 0.46 / 0.70 / 1.24 / 2.25 | 0 / 0 / 0 / 0 |

**Linux GCC 13.3** — soft intrinsic, flat ~2.73 ns; table wins ~3×.

| Row | Kernighan | 8-bit table | intrinsic |
| --- | --- | --- | --- |
| sequential `i` | 1.52 / 2.59 / 3.84 / 3.86 | 0.55 / 0.55 / 0.83 / 0.83 | 2.73 / 2.73 / 2.73 / 2.73 |
| all-ones | 2.46 / 8.73 / 9.82 / 27.58 | 0.55 / 0.56 / 0.82 / 1.58 | 2.76 / 2.76 / 2.76 / 2.75 |
| rotating bit | 0.55 / 0.55 / 0.55 / 0.81 | 1.03 / 1.03 / 0.92 / 1.64 | 2.73 / 2.73 / 2.73 / 2.73 |

**macOS Clang 21** (and **macos-gcc**, same Clang 21 banner) — Kernighan rewritten into the intrinsic class; `/bit` deletes Kernighan (8/16/32) and intrinsic (all widths). Table stays ~0.4–2.2 ns.

| Row (32/64) | Kernighan | 8-bit table | intrinsic |
| --- | --- | --- | --- |
| sequential `i` (clang) | 0.23 / 0.25 | 1.87 / 1.47 | 0.27 / 0.24 |
| all-ones (clang) | 0.51 / 0.93 | 1.50 / 2.16 | 0.57 / 0.53 |
| sequential `i` (“gcc”) | 0.19 / 0.20 | 1.59 / 1.19 | 0.23 / 0.22 |
| all-ones (“gcc”) | 0.39 / 0.71 | 1.13 / 1.44 | 0.43 / 0.40 |

**Windows MSVC 18** — real hardware popcount on 16/32/64 (~0.32 ns). `uint8_t` intrinsic often slower (~1.56 sequential). Intrinsic beats the table on dense 32/64. Kernighan still executes as a loop.

| Row | Kernighan | 8-bit table | intrinsic |
| --- | --- | --- | --- |
| sequential `i` | 3.39 / 4.47 / 6.05 / 6.82 | 1.58 / 1.89 / 2.20 / 3.14 | 1.57 / 0.33 / 0.32 / 0.32 |
| all-ones | 4.07 / 6.32 / 11.42 / 23.08 | 1.88 / 0.63 / 1.01 / 3.13 | 0.32 / 0.34 / 0.32 / 0.32 |
| rotating bit | 0.77 / 0.79 / 1.56 / 0.95 | 0.63 / 2.20 / 1.24 / 2.25 | 0.63 / 0.63 / 0.63 / 0.63 |

**Windows MinGW GCC 15.2** — same soft-intrinsic story as Linux GCC (~2.2 ns flat); table wins.

| Row | Kernighan | 8-bit table | intrinsic |
| --- | --- | --- | --- |
| sequential `i` | 1.83 / 3.23 / 4.82 / 5.10 | 0.64 / 0.65 / 0.95 / 0.95 | 2.19 / 2.20 / 2.21 / 2.20 |
| all-ones | 2.83 / 5.33 / 11.85 / 24.04 | 0.45 / 0.66 / 0.97 / 1.73 | 2.20 / 2.20 / 2.21 / 2.20 |


### Highest-bit, CI summary (sequential ns/call, 16 / 32 / 64)

| Cell | Scan | Intrinsic |
| --- | --- | --- |
| Linux Clang 18.1.3 | 3.03 / 3.39 / 3.40 | 0.89 / 0.57 / 0.57 |
| Linux GCC 13.3 | 0.55 / 0.55 / 0.55 | 0.55 / 0.57 / 0.95 |
| macOS Clang 21 | 1.47 / 1.45 / 1.33 | 0.34 / 0.30 / 0.29 |
| macOS “gcc” (Clang 21) | 1.25 / 1.01 / 0.99 | 0.32 / 0.19 / 0.20 |
| Windows MSVC 18 | 3.77 / 3.53 / 3.99 | 1.88 / 1.57 / 2.19 |
| Windows MinGW GCC 15.2 | 1.57 / 1.73 / 1.68 | 1.57 / 1.25 / 1.57 |

Intrinsic is a clear win on Apple Clang and Linux Clang; mixed or similar on Linux GCC / MinGW; modestly better on MSVC sequential, mixed on `/bit`.


## Learnings

* **Kernighan scales with set-bit count when the compiler leaves the loop alone** (Linux Clang, Linux GCC, MSVC, MinGW). All-ones `uint64_t` is about twice all-ones `uint32_t` because of the two 32-bit calls.
* **Apple Clang rewrites Kernighan into the same class as the popcount intrinsic.** CI `macos-clang` and `macos-gcc` both report Clang 21.0.0; treat `macos-gcc` as a second Apple Clang sample, not as GNU on Darwin.
* **Intrinsics are not one story on generic x86-64:**
  * **Linux GCC / MinGW:** `__builtin_popcount*` ≈ flat libcall (~2.2–2.7 ns) — slower than the table.
  * **Linux Clang 18:** competitive hardware-ish popcount (~0.85–1.3 ns); sometimes beats the table on sequential, often loses on dense; `/bit` can delete the intrinsic.
  * **MSVC:** `__popcnt*` is hardware on 16/32/64 (~0.32 ns) and beats the table there; `uint8_t` is weaker.
* **Zero-time `/bit` rows are optimisations, not free popcount.** Apple Clang deletes Kernighan and the intrinsic; Linux Clang deletes only the intrinsic; Linux GCC / MinGW / MSVC keep live loops. Anchors stay non-zero.
* **Sequential `uint64_t` is not a 64-bit input** (`v = i` with `i` below 2^25). Prefer ones / `~i` / `/wide` for the high half.
* **The table is density-insensitive relative to Kernighan** and remains a safe portable default.
* **`find_highest_bit_by_intrinsic` is favourable on Apple Clang and Linux Clang**, not a clear global win on GCC/MinGW, and only a modest sequential win on MSVC.
* **XOR remains a short range scan** — no SIMD case from this harness.


## Strategy

* **Keep the 8-bit table as the default** for `count_bits()`, on every architecture.
* **Do not select Kernighan by Apple, by ARM, or by Clang.** The measured switch is “this compiler, on this target, rewrote this loop”.
* **Leave `STLSOFT_BIT_COUNT_BY_Kernighan` as an opt-in** for a build that has been measured.
* **Keep `count_bits_by_intrinsic()` unselected.** A global switch would win on MSVC (and often on Apple Clang) but lose ~2–3× on Linux GCC and MinGW. `count_bits()` stays on the table.
* **Keep `find_highest_bit_by_intrinsic()` unselected.** Strong on Apple Clang and Linux Clang; not justified as a portable default from GCC/MinGW/MSVC alone.
* **MSVC popcount is gated by architecture and toolset, in `external/bitfns.h`.** `__popcnt16` / `__popcnt`: x86 and x64 from MSVC 15.00, ARM64 from VS 2022 17.11 (`_MSC_VER` 1941); not 32-bit ARM or ARM64EC. `__popcnt64`: x64 from 15.00, ARM64 and ARM64EC from 17.11. `_BitScanReverse64`: ARM64, ARM64EC, and x64 from 14.00. When a GCC/Clang builtin and an MSVC intrinsic are both visible, the builtin wins.
* **Do not change `calculate_xor_over_range` for performance** on the strength of this harness.


## Not yet done

* Selecting either intrinsic into the dispatchers under a **narrow, measured** gate (e.g. MSVC-only popcount, or a `POPCNT`-legal `-march` / `/arch` build). Full-matrix evidence is in; a portable default still loses on soft GCC.
* A CI (or local) cell with `-march=native` / `-mpopcnt` / `/arch:AVX2` (or equivalent) that allows `POPCNT` under GCC/Clang on Linux.
* Real **GNU GCC or non-Apple Clang on Darwin** (not the `gcc` → Clang driver).
* Correct INTERNAL `clz(0)` to full width (`32` / `64`), then optionally drive `find_highest_bit_by_intrinsic` through those adapters.


<!-- ########################### end of file ########################### -->
