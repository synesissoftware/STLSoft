# STLSoft.b - Bit Functions <!-- omit in toc -->

Strategy note for **STLSoft.b** bit utilities. Measurements are of the performance program **test/performance/stlsoft/bit_functions/main.cpp**. Library sources are **include/stlsoft/util/bits/count_functions.h**, **include/stlsoft/util/bits/test_functions.h**, and **include/stlsoft/util/bits/xor_functions.h**. Intrinsic detection and naming live in **include/stlsoft/api/external/bitfns.h** and **include/stlsoft/api/internal/bitfns.h**.


## Question

If intrinsics are never adopted, should `count_bits()` use Kernighan on Apple and the 8-bit table everywhere else?

No. The fast Kernighan numbers are Apple Clang rewriting the loop into a hardware popcount. They are not a property of Apple hardware. On every other toolchain measured here, that rewrite did not happen, and the table is several times faster. A default keyed on Apple, or on ARM, would be right only while the compiler keeps doing that rewrite, and badly wrong when it does not.

The cost of leaving the table in place on Apple Clang is a fraction of a nanosecond per call. The cost of leaving Kernighan in place on a compiler that executes the source loop is about 12 ns (`uint32_t`, all ones) and about 24 ns (`uint64_t`, all ones), against about 1 ns and 2 ns for the table.


## What was measured

Two bodies of results. Both are optimised release builds (`optimisation: speed`, `NDEBUG`), five-sample medians, 20,000,000 iterations. Anchors match across machines, so the loops did the same work.

* **Cross-platform, commit `74b74407875100e0f1b6f5f7658a714c9a8d57b3`.** Sequential `i`, dense `~i`, volatile all-ones, and `ones^1`, plus `find_highest_bit` and `calculate_xor_over_range`. Linux Clang 18.1.3, Linux GCC 13.3, two macOS runs, Windows MSVC 18, Windows MinGW GCC 15.2.
* **Later local Apple Clang 21 only.** Adds volatile zero, a rotating one-hot bit, a both-halves-live pattern, and the unselected intrinsic rows, and prints ns/call on the same row. Use it for the one-hot, zero, and intrinsic cases. Do not treat it as a second cross-platform matrix.

The run labeled macOS GCC printed `compiler: Clang 21.0.0`. Both Mac columns are Apple Clang. There is no GCC result from macOS in this set.


### Popcount, cross-platform

Nanoseconds per call, `uint32_t` / `uint64_t`. Divide the printed loop time by 20,000,000.

| Row | Linux Clang 18 | Linux GCC 13.3 | macOS Clang 21 | macOS Clang 21 (2nd) | Windows MSVC 18 | MinGW GCC 15.2 |
| --- | --- | --- | --- | --- | --- | --- |
| Kernighan, sequential `i` | 4.9 / 4.9 | 4.8 / 4.8 | 0.21 / 0.20 | 0.18 / 0.18 | 4.9 / 5.3 | 5.3 / 5.5 |
| Kernighan, all-ones | 11.9 / 26.1 | 11.5 / 22.6 | 0.35 / 0.68 | 0.34 / 0.64 | 11.7 / 24.4 | 11.3 / 24.6 |
| 8-bit table, sequential `i` | 0.98 / 0.98 | 0.94 / 0.94 | 1.7 / 1.2 | 1.3 / 0.95 | 1.4 / 1.3 | 0.96 / 0.95 |
| 8-bit table, all-ones | 0.94 / 1.9 | 0.93 / 1.9 | 1.1 / 1.3 | 1.0 / 1.3 | 1.3 / 2.1 | 0.94 / 1.8 |

`count_bits()` tracks the table on every toolchain, including Apple Clang. One MSVC cell is slower than the named table entry (sequential `uint64_t`, about 3.1 ns against 1.3 ns). The others match. The dispatcher is not the Kernighan path unless `STLSOFT_BIT_COUNT_BY_Kernighan` is defined.


### Apple Clang 21, intrinsics included

Nanoseconds per call. Popcount cells are `uint32_t` / `uint64_t`. `count_bits()` matches the table on every row below, so it is omitted. Anchors match the earlier Apple run, including `/bit` at `40,000,000` and `/0` at `0`.

| Row | Kernighan | 8-bit table | intrinsic |
| --- | --- | --- | --- |
| sequential `i` | 0.114 / 0.119 | 0.913 / 0.689 | 0.116 / 0.116 |
| `~i` | 0.127 / 0.141 | 0.900 / 0.901 | 0.128 / 0.130 |
| all-ones | 0.248 / 0.347 | 0.681 / 0.735 | 0.246 / 0.226 |
| `ones^1` | 0.200 / 0.359 | 0.929 / 0.788 | 0.199 / 0.236 |
| volatile zero | 0.227 / 0.346 | 0.681 / 0.708 | 0.232 / 0.247 |
| rotating bit | 0 / 0 | 0.915 / 0.723 | 0 / 0 |
| both halves live | 0.141 / 0.142 | 0.326 / 0.421 | 0.145 / 0.176 |

The rotating-bit times of 0 are deleted loops. The anchor is still `40,000,000`. The table on that row stayed near 0.9 ns.

`find_highest_bit` cells are `uint8_t` / `uint16_t` / `uint32_t` / `uint64_t`.

| Row | scan | intrinsic |
| --- | --- | --- |
| sequential `i` | 0.294 / 0.468 / 0.434 / 0.435 | 0.197 / 0.198 / 0.113 / 0.113 |
| volatile zero | 0.236 / 0.423 / 0.504 / 0.827 | 0.224 / 0.227 / 0.234 / 0.223 |
| rotating bit | 0.111 / 0.225 / 0.340 / 0.473 | 0.129 / 0.148 / 0.112 / 0.111 |
| both halves live | 0.297 / 0.473 / 0.378 / 0.465 | 0.197 / 0.197 / 0.199 / 0.232 |


## Learnings

* **Kernighan scales with the number of set bits when the compiler leaves the loop alone.** All-ones is about 32 iterations at ~0.4 ns each for `uint32_t`, and about twice that for `uint64_t`, because the 64-bit function is two 32-bit calls. That is Linux Clang 18, Linux GCC 13.3, MSVC, and MinGW GCC 15.2.
* **Apple Clang rewrites the Kernighan source into the same instruction as the intrinsic.** On 32-bit rows the two times match (all-ones 0.248 ns and 0.246 ns). On 64-bit rows with a live high half the intrinsic is one `__builtin_popcountll` and Kernighan is still two 32-bit popcounts: all-ones 0.226 ns against 0.347 ns, `ones^1` 0.236 ns against 0.359 ns, volatile zero 0.247 ns against 0.346 ns. Sequential `uint64_t` does not show that gap, because its high half is zero. The both-halves-live row goes the other way by a small amount (Kernighan 0.142 ns, intrinsic 0.176 ns): the high half is a copy of a sparse `i`, not a dense word.
* **Generic x86-64 does not emit `POPCNT` for this loop.** The instruction is outside the baseline `-march=x86-64` target. Clang 18, GCC 13, GCC 15, and MSVC all kept the source loop in these release builds. Recognition of the idiom is not enough if the target forbids the instruction.
* **A one-hot input can delete both the Kernighan loop and the popcount intrinsic.** On Apple Clang 21, `count_bits_by_Kernighan_method()/bit` and `count_bits_by_intrinsic()/bit` reported 0 ns while the anchor stayed `40,000,000`. The table on that input stayed near 0.9 ns, and `count_bits()` followed the table. Do not read a zero time as "sparse popcount is free".
* **Sequential `uint64_t` is not a 64-bit input.** `uint64_t v = i` with `i` below 2^25 has a zero high half. Equal `uint32_t` and `uint64_t` times on that row do not mean the wide operation is free. All-ones and `~i` are the rows that exercise the high half.
* **The table is density-insensitive, with two shortcuts.** Four lookups are about 1 ns; eight are about 2 ns when the high half is real. All-zero and all-ones are cheaper when every byte hits the same slot. The both-halves-live row on Apple Clang was cheaper still, because the two halves are copies and the compiler reused lookups. That row is not the cost of arbitrary 64-bit data.
* **`find_highest_bit` is a software scan on every toolchain in the cross-platform matrix.** `uint32_t` and `uint64_t` stay close on the sequential input because the high half is zero. MSVC is the slowest and the one case where that zero high half still costs extra. On Apple Clang 21 the scan still grows with width: zero is 0.236 / 0.423 / 0.504 / 0.827 ns, and a rotating bit is 0.111 / 0.225 / 0.340 / 0.473 ns.
* **The `clz` intrinsic is flat on that same Apple Clang run.** Zero is about 0.22–0.23 ns at every width, which is the explicit zero test (`clz` of zero is undefined), not a descent. A rotating bit is 0.129 / 0.148 / 0.112 / 0.111 ns. The 8-bit scan is still slightly faster on that one-hot row (0.111 ns), because the intrinsic is a 32-bit `clz` of a zero-extended value. From 16 bits upward the intrinsic wins, and the both-halves-live `uint64_t` row is 0.232 ns against 0.465 ns for the scan.
* **XOR is a range scan.** At an average length of 32.5 elements it is several nanoseconds per call. `uint64_t` was the expensive width on Linux and MinGW, and the cheap width on Apple Clang. It is not comparable to the scalar rows, and it does not justify SIMD on this harness (`n` at most 64, data in L1).


## Strategy

* **Keep the 8-bit table as the default** for `count_bits()`, on every architecture.
* **Do not select Kernighan by Apple, by ARM, or by Clang.** The measured switch is "this compiler, on this target, rewrote this loop". Apple Clang 21 did. Linux Clang 18 did not. GCC on Apple Silicon has not been measured.
* **Leave `STLSOFT_BIT_COUNT_BY_Kernighan` as an opt-in** for a build that has been measured. The macro calls `count_bits_by_Kernighan_method`.
* **Keep `count_bits_by_intrinsic()` unselected until it is measured off Apple Clang.** The call goes through `STLSOFT_API_INTERNAL_bitfns_popcount_uint32` / `uint64`, which prefer `__builtin_popcount` / `__builtin_popcountll` and otherwise use `__popcnt` / `__popcnt64`. On Apple Clang 21 that matches rewritten Kernighan for 32-bit values and beats it for a dense 64-bit value, and it beats the table on every row whose loop was not deleted. `__builtin_popcount` without a `POPCNT` target can be a library call. That case is the one that could lose to the table, and it has not been timed. `count_bits()` still uses the table.
* **Keep `find_highest_bit_by_intrinsic()` unselected for the same reason.** It is 1-based and returns 0 for a zero input. GCC and Clang use `__builtin_clz` / `__builtin_clzll`; MSVC uses `_BitScanReverse` / `_BitScanReverse64`, with the index converted to the same 1-based result. The 8-bit and 16-bit forms are a 32-bit operation on a zero-extended value. On Apple Clang 21 it is the faster form from 16 bits up, including zero and a live high half. One Linux or Windows run of the same four rows is enough to decide whether the scan stays the default. `find_highest_bit()` still uses the shift-and-split scan.
* **MSVC popcount is gated by architecture and toolset, in `external/bitfns.h`.** `__popcnt16` and `__popcnt` are x86 and x64 from MSVC 15.00, and ARM64 from Visual Studio 2022 17.11 (`_MSC_VER` 1941). They are not promised for 32-bit ARM or for ARM64EC. `__popcnt64` is x64 from MSVC 15.00, and ARM64 and ARM64EC from 17.11. `_BitScanReverse64` is ARM64, ARM64EC, and x64 from MSVC 14.00. When a GCC/Clang builtin and an MSVC intrinsic are both visible, the builtin is the one the internal popcount function calls.
* **Do not change `calculate_xor_over_range` for performance** on the strength of this harness.


## Not yet done

* Selecting `count_bits_by_intrinsic()` or `find_highest_bit_by_intrinsic()` into the dispatchers. Apple Clang 21 favours both. The missing evidence is the same rows on Linux Clang, Linux GCC, MSVC, and MinGW, including a target where `POPCNT` is not a baseline instruction.
* GCC, or Clang, on Apple Silicon as a compiler that is not Apple Clang.
* Linux or Windows built with `-march=native` or `/arch` that allows `POPCNT`, for the Kernighan idiom and for the explicit intrinsic.


<!-- ########################### end of file ########################### -->
