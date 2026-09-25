# STLSoft.b - Bit Functions <!-- omit in toc -->

Strategy note for **STLSoft.b** bit utilities. Measurements are of the performance program **test/performance/stlsoft/bit_functions/main.cpp**. Library sources are **include/stlsoft/util/bits/count_functions.h**, **include/stlsoft/util/bits/test_functions.h**, and **include/stlsoft/util/bits/xor_functions.h**. Intrinsic detection and naming live in **include/stlsoft/api/external/bitfns.h** and **include/stlsoft/api/internal/bitfns.h**.


## Question

If intrinsics are never adopted, should `count_bits()` use Kernighan on Apple and the 8-bit table everywhere else?

No. The fast Kernighan numbers are Apple Clang rewriting the loop into a hardware popcount. They are not a property of Apple hardware. On every other toolchain measured here, that rewrite did not happen, and the table is several times faster. A default keyed on Apple, or on ARM, would be right only while the compiler keeps doing that rewrite, and badly wrong when it does not.

The cost of leaving the table in place on Apple Clang is a fraction of a nanosecond per call. The cost of leaving Kernighan in place on a compiler that executes the source loop is about 12 ns (`uint32_t`, all ones) and about 24 ns (`uint64_t`, all ones), against about 1 ns and 2 ns for the table.


## What was measured

Optimised release builds (`optimisation: speed`, `NDEBUG`), five-sample medians, 20,000,000 iterations. Anchors match across machines for the same input pattern, so the loops did the same work.

* **Cross-platform, commit `74b74407875100e0f1b6f5f7658a714c9a8d57b3`.** Sequential `i`, dense `~i`, volatile all-ones, and `ones^1`, plus `find_highest_bit` and `calculate_xor_over_range`. Linux Clang 18.1.3, Linux GCC 13.3, two macOS runs, Windows MSVC 18, Windows MinGW GCC 15.2. No intrinsic rows.
* **Later local Apple Clang 21**, then **CI** (GitHub Actions): full matrix of widths including `uint8_t` / `uint16_t`, plus unselected intrinsic rows, zero, one-hot, and both-halves-live patterns. Use CI for cross-compiler intrinsic evidence; use the early matrix for pre-intrinsic baselines.


### Popcount, cross-platform (pre-intrinsic)

Nanoseconds per call, `uint32_t` / `uint64_t`. Divide the printed loop time by 20,000,000.

| Row | Linux Clang 18 | Linux GCC 13.3 | macOS Clang 21 | macOS Clang 21 (2nd) | Windows MSVC 18 | MinGW GCC 15.2 |
| --- | --- | --- | --- | --- | --- | --- |
| Kernighan, sequential `i` | 4.9 / 4.9 | 4.8 / 4.8 | 0.21 / 0.20 | 0.18 / 0.18 | 4.9 / 5.3 | 5.3 / 5.5 |
| Kernighan, all-ones | 11.9 / 26.1 | 11.5 / 22.6 | 0.35 / 0.68 | 0.34 / 0.64 | 11.7 / 24.4 | 11.3 / 24.6 |
| 8-bit table, sequential `i` | 0.98 / 0.98 | 0.94 / 0.94 | 1.7 / 1.2 | 1.3 / 0.95 | 1.4 / 1.3 | 0.96 / 0.95 |
| 8-bit table, all-ones | 0.94 / 1.9 | 0.93 / 1.9 | 1.1 / 1.3 | 1.0 / 1.3 | 1.3 / 2.1 | 0.94 / 1.8 |

`count_bits()` tracks the table on every toolchain, including Apple Clang.


### CI: Linux GCC 13.3 (ubuntu, intrinsic rows)

Nanoseconds per call. Popcount cells shown as `uint8_t` / `uint16_t` / `uint32_t` / `uint64_t` where useful; otherwise `uint32_t` / `uint64_t`.

| Row | Kernighan | 8-bit table | intrinsic |
| --- | --- | --- | --- |
| sequential `i` | 1.83 / 3.22 / 4.77 / 4.78 | 0.63 / 0.64 / 0.94 / 0.95 | 3.11 / 3.11 / 3.12 / 3.12 |
| `~i` | 1.62 / 3.60 / 8.84 / 14.09 | 0.63 / 0.83 / 0.94 / 0.94 | 3.11 / 3.11 / 3.11 / 3.11 |
| all-ones | 2.80 / 9.98 / 11.26 / 31.48 | 0.62 / 0.64 / 0.97 / 1.84 | 3.11 / 3.12 / 3.11 / 3.12 |
| rotating bit | 0.62 / 0.62 / 0.62 / 0.94 | 1.18 / 1.19 / 1.06 / 1.87 | 3.43 / 3.11 / 3.11 / 3.11 |

`count_bits()` tracks the table. The intrinsic is flat at about **3.11 ns** on every density and width — a libgcc-style helper, not hardware `POPCNT`. The table wins by about 3× on sequential and dense inputs. Dense Kernighan still scales with set-bit count (all-ones `uint64_t` ~31 ns).


### CI: Apple Clang 21 (macos)

| Row | Kernighan | 8-bit table | intrinsic |
| --- | --- | --- | --- |
| sequential `i` (32/64) | 0.21 / 0.25 | 1.69 / 1.20 | 0.36 / 0.40 |
| all-ones (32/64) | 0.44 / 0.81 | 1.47 / 2.03 | 0.49 / 0.44 |
| rotating bit (32/64) | 0 / 0.47 | 1.77 / 1.98 | 0 / 0 |

Kernighan and the intrinsic stay in the same hardware-popcount band; `/bit` again deletes several loops (0 ns, anchor still `80,000,000` with 8/16 columns). The table remains ~1–2 ns. `find_highest_bit_by_intrinsic` is clearly faster than the scan from 16 bits up (sequential 0.32 / 0.19 / 0.22 vs 1.53 / 1.25 / 1.23 for 16/32/64).


## Learnings

* **Kernighan scales with the number of set bits when the compiler leaves the loop alone.** All-ones is about 32 iterations for `uint32_t`, and about twice that for `uint64_t` (two 32-bit calls). That is Linux Clang 18, Linux GCC 13.3, MSVC, and MinGW GCC 15.2.
* **Apple Clang rewrites the Kernighan source into the same class of instruction as the intrinsic.** CI macOS Clang 21 reproduces that. Local runs with a live high half showed the intrinsic beating two-call Kernighan on dense 64-bit words.
* **Generic x86-64 does not emit `POPCNT` for this loop or for `__builtin_popcount`.** CI Linux GCC 13.3 is the decisive measurement: the explicit intrinsic is a flat ~3.11 ns call (library helper), while the table is ~0.6–1.0 ns. Recognition of the idiom is not enough if the target forbids the instruction.
* **A one-hot input can delete Kernighan and the popcount intrinsic on Apple Clang.** `/bit` reports 0 ns while the anchor stays non-zero. The table stays near 1–2 ns. Do not read a zero time as "sparse popcount is free". Linux GCC does not delete those loops (~0.6 ns Kernighan, ~3.1 ns intrinsic).
* **Sequential `uint64_t` is not a 64-bit input.** `uint64_t v = i` with `i` below 2^25 has a zero high half. All-ones and `~i` are the rows that exercise the high half.
* **The table is density-insensitive relative to Kernighan**, with byte-wise shortcuts on all-zero / all-ones and on copied halves.
* **`find_highest_bit` is a software scan by default.** On Apple Clang the `clz` / `BitScanReverse` intrinsic is faster from 16 bits up. On Linux GCC 13.3 the intrinsic is only sometimes better (sequential 32-bit 1.24 vs 1.67; elsewhere similar or worse), so it does not justify a default switch on that toolchain alone.
* **XOR is a range scan** and does not justify SIMD on this harness (`n` at most 64, data in L1).


## Strategy

* **Keep the 8-bit table as the default** for `count_bits()`, on every architecture.
* **Do not select Kernighan by Apple, by ARM, or by Clang.** The measured switch is "this compiler, on this target, rewrote this loop". Apple Clang 21 did. Linux GCC 13.3 did not.
* **Leave `STLSOFT_BIT_COUNT_BY_Kernighan` as an opt-in** for a build that has been measured.
* **Keep `count_bits_by_intrinsic()` unselected.** On Apple Clang it matches rewritten Kernighan and beats the table when the loop is not deleted. On Linux GCC 13.3 without a `POPCNT`-legal arch it is ~3× slower than the table. `count_bits()` still uses the table.
* **Keep `find_highest_bit_by_intrinsic()` unselected.** Favourable on Apple Clang from 16 bits up; mixed on Linux GCC 13.3. `find_highest_bit()` still uses the shift-and-split scan.
* **MSVC popcount is gated by architecture and toolset, in `external/bitfns.h`.** `__popcnt16` / `__popcnt`: x86 and x64 from MSVC 15.00, ARM64 from VS 2022 17.11 (`_MSC_VER` 1941); not 32-bit ARM or ARM64EC. `__popcnt64`: x64 from 15.00, ARM64 and ARM64EC from 17.11. `_BitScanReverse64`: ARM64, ARM64EC, and x64 from 14.00. When a GCC/Clang builtin and an MSVC intrinsic are both visible, the builtin wins.
* **Do not change `calculate_xor_over_range` for performance** on the strength of this harness.


## Not yet done

* Selecting either intrinsic into the dispatchers. Apple Clang favours both; Linux GCC 13.3 favours the table for popcount and is mixed for highest-bit. Still wanted: MSVC and MinGW intrinsic rows, and a build with `-march=native` / `-mpopcnt` / `/arch` that allows `POPCNT`.
* GCC, or non-Apple Clang, on Apple Silicon.
* Correct INTERNAL `clz(0)` to full width (`32` / `64`), then optionally drive `find_highest_bit_by_intrinsic` through those adapters.


<!-- ########################### end of file ########################### -->
