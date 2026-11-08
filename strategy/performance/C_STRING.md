# STLSoft - C-string Performance <!-- omit in toc -->

Strategy note for the **STLSoft** C string helpers. Measurements are of **test/performance/stlsoft/string/c_string/main.cpp** (`test.performance.stlsoft.string.c_string`). Library sources are **include/stlsoft/string/c_string/strnicmp.h**, **strnchr.h**, **strnistrn.h**, **strnpbrkn.h**, **strnrchr.h**, and **strnstrn.h**.

The char forms are timed. The wide forms are not in this program.


## Status

The local mains-power run and the six CI cells of this wave are recorded: `linux-gcc`, `linux-clang`, `macos-gcc`, `macos-clang`, `windows-cl`, and `windows-mingw`. Anchors match within every pair on every run, so each pair did the same work. The local paragraphs describe that machine only. **Summary** is the cross-cell comparison. **Directions so far** is the reading of those tables. Compiler banners are still missing, so that reading is not yet a settled claim.


## What was measured

1,000,000 iterations. Haystack length 96. Case-insensitive compare length 45 (`"The Quick Brown Fox Jumps Over The Lazy Dog!!"`, with the other side case-flipped). The harness times each row twice and prints the second pass. `SIS_PERFTESTS_GROUPGAPS=1` inserts a blank line between groups.

Printed **nanoseconds** are the total for that pass, not nanoseconds per call. Divide by 1,000,000 for a per-call figure. The **anchor** is the sum of the return values over the pass: comparison sign (`+1`, `0`, `-1`) or byte index, or `-1` for a miss. A matching anchor means both functions did the same work.

Search positions in the haystack:

* character near the start: index 3 (`Q`);
* character near the end: index 92 (`Z`);
* needle near the start: index 8 (`brown` / `BROWN`);
* needle near the end: index 84 (`jumps` / `JUMPS`);
* character-set needles are four bytes (`xyzQ`, `xyzZ`, `xyz#`).

`strpbrk` and `strstr` are NUL-terminated. The fixture places a NUL at index 96, so on this haystack they scan the same 96 bytes as the length-bounded helpers. `strncasecmp` is the non-Windows name of the case-insensitive baseline (`_strnicmp` on Windows). `local_strnrchr` is a reverse scan written in the performance program, the same shape as `stlsoft_C_strnrchr`. `stlsoft_C_strnistrn` has no paired baseline.


## Local: Gorbicx-MacBook-Pro, mains power, 27th October 2026

Built with `./build_cmake.sh test.performance.stlsoft.string.c_string` and run with `SIS_PERFTESTS_GROUPGAPS=1`. Compiler, optimisation level, and CPU model were not recorded with the log.


### `strnicmp` (total ns)

| Function             | Scenario     | Nanoseconds |     Anchor |
| -------------------- | ------------ | ----------- | ---------- |
| `stlsoft_C_strnicmp` | differ-early |   1,122,791 |  1,000,000 |
| `strncasecmp`        | differ-early |   2,506,375 |  1,000,000 |
| `stlsoft_C_strnicmp` | differ-late  |  23,609,000 | -1,000,000 |
| `strncasecmp`        | differ-late  |  29,995,250 | -1,000,000 |
| `stlsoft_C_strnicmp` | equal        |  24,446,375 |          0 |
| `strncasecmp`        | equal        |  27,942,125 |          0 |

`stlsoft_C_strnicmp` is about 2.2× faster when the strings differ at the first byte, about 1.3× when they differ at the last byte, and about 1.1× when they compare equal.


### `strnchr` (total ns)

| Function            | Scenario   | Nanoseconds |     Anchor |
| ------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnchr` | near-start |   1,906,750 |  3,000,000 |
| `memchr`            | near-start |   1,905,375 |  3,000,000 |
| `stlsoft_C_strnchr` | near-end   |   3,285,250 | 92,000,000 |
| `memchr`            | near-end   |   3,266,875 | 92,000,000 |
| `stlsoft_C_strnchr` | miss       |   3,042,042 | -1,000,000 |
| `memchr`            | miss       |   3,043,958 | -1,000,000 |

The three needles are ASCII. `stlsoft_C_strnchr` calls `memchr` for a needle in 0–127, and the totals match `memchr` within about 1%.


### `strnistrn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnistrn` | near-start |   4,170,750 |  8,000,000 |
| `stlsoft_C_strnistrn` | near-end   |  30,920,458 | 84,000,000 |
| `stlsoft_C_strnistrn` | miss       |  32,696,042 | -1,000,000 |

No paired function. A hit at index 8 costs about 4.2 ms for the pass. A hit at index 84 and a full miss both cost about 31–33 ms.


### `strnpbrkn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnpbrkn` | near-start |   1,570,750 |  3,000,000 |
| `strpbrk`             | near-start |   6,051,041 |  3,000,000 |
| `stlsoft_C_strnpbrkn` | near-end   |  28,256,583 | 92,000,000 |
| `strpbrk`             | near-end   | 111,063,917 | 92,000,000 |
| `stlsoft_C_strnpbrkn` | miss       |  22,008,584 | -1,000,000 |
| `strpbrk`             | miss       | 114,684,875 | -1,000,000 |

On this four-byte set, `stlsoft_C_strnpbrkn` is about 3.9× faster for both hits and about 5.2× faster on a miss.


### `strnrchr` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnrchr` | near-start |  22,345,375 |  3,000,000 |
| `local_strnrchr`     | near-start |  22,353,958 |  3,000,000 |
| `stlsoft_C_strnrchr` | near-end   |   1,570,917 | 92,000,000 |
| `local_strnrchr`     | near-end   |   1,572,625 | 92,000,000 |
| `stlsoft_C_strnrchr` | miss       |  23,019,708 | -1,000,000 |
| `local_strnrchr`     | miss       |  23,153,875 | -1,000,000 |

The two reverse scans match within about 1%. A hit at index 92 is the short walk. A hit at index 3 and a miss both walk almost the whole haystack.


### `strnstrn` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnstrn` | near-start |   2,381,125 |  8,000,000 |
| `strstr`             | near-start |   5,680,209 |  8,000,000 |
| `stlsoft_C_strnstrn` | near-end   |   3,370,500 | 84,000,000 |
| `strstr`             | near-end   |  24,235,375 | 84,000,000 |
| `stlsoft_C_strnstrn` | miss       |   3,357,291 | -1,000,000 |
| `strstr`             | miss       |  25,758,125 | -1,000,000 |

`stlsoft_C_strnstrn` searches with `memchr` and `memcmp`. It is about 2.4× faster than `strstr` for the early needle, and about 7× faster for the late needle and the miss.


## CI: `linux-gcc`, 27th October 2026

GitHub-hosted Linux runner. Log path `/home/runner/work/STLSoft/STLSoft/build/test/performance/stlsoft/string/c_string/test.performance.stlsoft.string.c_string`. Compiler version was not in the log. Baseline name `strncasecmp`.


### `strnicmp` (total ns)

| Function             | Scenario     | Nanoseconds |     Anchor |
| -------------------- | ------------ | ----------- | ---------- |
| `stlsoft_C_strnicmp` | differ-early |   1,306,644 |  1,000,000 |
| `strncasecmp`        | differ-early |   2,431,603 |  1,000,000 |
| `stlsoft_C_strnicmp` | differ-late  |  33,280,865 | -1,000,000 |
| `strncasecmp`        | differ-late  |   3,354,707 | -1,000,000 |
| `stlsoft_C_strnicmp` | equal        |  32,641,089 |          0 |
| `strncasecmp`        | equal        |   2,959,610 |          0 |

Early difference: `stlsoft_C_strnicmp` is about 1.9× faster. A compare that walks all 45 bytes goes the other way: `strncasecmp` is about 10× faster on `differ-late` and about 11× faster on `equal`.


### `strnchr` (total ns)

| Function            | Scenario   | Nanoseconds |     Anchor |
| ------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnchr` | near-start |   2,408,749 |  3,000,000 |
| `memchr`            | near-start |   2,147,924 |  3,000,000 |
| `stlsoft_C_strnchr` | near-end   |   2,361,727 | 92,000,000 |
| `memchr`            | near-end   |   2,127,463 | 92,000,000 |
| `stlsoft_C_strnchr` | miss       |   2,594,659 | -1,000,000 |
| `memchr`            | miss       |   2,613,036 | -1,000,000 |

Hits are about 11–12% slower than `memchr`. The miss matches.


### `strnistrn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnistrn` | near-start |   3,513,096 |  8,000,000 |
| `stlsoft_C_strnistrn` | near-end   |  21,807,977 | 84,000,000 |
| `stlsoft_C_strnistrn` | miss       |  23,401,324 | -1,000,000 |

No paired function. Early hit about 3.5 ms for the pass. Late hit and miss about 22–23 ms.


### `strnpbrkn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnpbrkn` | near-start |   2,578,625 |  3,000,000 |
| `strpbrk`             | near-start |   3,125,110 |  3,000,000 |
| `stlsoft_C_strnpbrkn` | near-end   |  12,024,270 | 92,000,000 |
| `strpbrk`             | near-end   |   5,966,191 | 92,000,000 |
| `stlsoft_C_strnpbrkn` | miss       |   1,947,021 | -1,000,000 |
| `strpbrk`             | miss       |   7,771,849 | -1,000,000 |

Early hit: `stlsoft_C_strnpbrkn` is about 1.2× faster. Late hit: `strpbrk` is about 2× faster. Miss: `stlsoft_C_strnpbrkn` is about 4× faster.


### `strnrchr` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnrchr` | near-start |   8,243,921 |  3,000,000 |
| `local_strnrchr`     | near-start |   8,170,841 |  3,000,000 |
| `stlsoft_C_strnrchr` | near-end   |   2,076,877 | 92,000,000 |
| `local_strnrchr`     | near-end   |   2,142,867 | 92,000,000 |
| `stlsoft_C_strnrchr` | miss       |   1,667,779 | -1,000,000 |
| `local_strnrchr`     | miss       |   1,667,698 | -1,000,000 |

The two reverse scans match.


### `strnstrn` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnstrn` | near-start |   2,137,469 |  8,000,000 |
| `strstr`             | near-start |   7,696,324 |  8,000,000 |
| `stlsoft_C_strnstrn` | near-end   |   2,403,370 | 84,000,000 |
| `strstr`             | near-end   |   7,782,854 | 84,000,000 |
| `stlsoft_C_strnstrn` | miss       |   2,362,438 | -1,000,000 |
| `strstr`             | miss       |   4,263,720 | -1,000,000 |

`stlsoft_C_strnstrn` is about 3.6× faster on the early needle, about 3.2× on the late needle, and about 1.8× on the miss.


## CI: `linux-clang`, 27th October 2026

GitHub-hosted Linux runner. Same log path shape as `linux-gcc`. Compiler version was not in the log. Baseline name `strncasecmp`.


### `strnicmp` (total ns)

| Function             | Scenario     | Nanoseconds |     Anchor |
| -------------------- | ------------ | ----------- | ---------- |
| `stlsoft_C_strnicmp` | differ-early |   2,352,087 |  1,000,000 |
| `strncasecmp`        | differ-early |   5,621,520 |  1,000,000 |
| `stlsoft_C_strnicmp` | differ-late  |  54,867,515 | -1,000,000 |
| `strncasecmp`        | differ-late  |   5,678,476 | -1,000,000 |
| `stlsoft_C_strnicmp` | equal        |  58,239,579 |          0 |
| `strncasecmp`        | equal        |   6,235,392 |          0 |

Early difference: `stlsoft_C_strnicmp` is about 2.4× faster. Full compares: `strncasecmp` is about 9.7× faster on `differ-late` and about 9.3× faster on `equal`.


### `strnchr` (total ns)

| Function            | Scenario   | Nanoseconds |     Anchor |
| ------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnchr` | near-start |   4,683,385 |  3,000,000 |
| `memchr`            | near-start |   4,659,881 |  3,000,000 |
| `stlsoft_C_strnchr` | near-end   |   5,914,095 | 92,000,000 |
| `memchr`            | near-end   |   5,915,517 | 92,000,000 |
| `stlsoft_C_strnchr` | miss       |   5,921,138 | -1,000,000 |
| `memchr`            | miss       |   5,914,916 | -1,000,000 |

The totals match `memchr`.


### `strnistrn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnistrn` | near-start |  10,443,673 |  8,000,000 |
| `stlsoft_C_strnistrn` | near-end   |  70,170,801 | 84,000,000 |
| `stlsoft_C_strnistrn` | miss       |  88,993,444 | -1,000,000 |

No paired function. Early hit about 10 ms for the pass. Late hit about 70 ms. Miss about 89 ms.


### `strnpbrkn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnpbrkn` | near-start |   3,416,647 |  3,000,000 |
| `strpbrk`             | near-start |   5,287,069 |  3,000,000 |
| `stlsoft_C_strnpbrkn` | near-end   |  40,470,816 | 92,000,000 |
| `strpbrk`             | near-end   |   9,745,945 | 92,000,000 |
| `stlsoft_C_strnpbrkn` | miss       |  38,400,505 | -1,000,000 |
| `strpbrk`             | miss       |  10,286,771 | -1,000,000 |

Early hit: `stlsoft_C_strnpbrkn` is about 1.5× faster. Late hit: `strpbrk` is about 4.2× faster. Miss: `strpbrk` is about 3.7× faster.


### `strnrchr` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnrchr` | near-start |  21,246,034 |  3,000,000 |
| `local_strnrchr`     | near-start |  22,013,291 |  3,000,000 |
| `stlsoft_C_strnrchr` | near-end   |   2,548,813 | 92,000,000 |
| `local_strnrchr`     | near-end   |   3,678,845 | 92,000,000 |
| `stlsoft_C_strnrchr` | miss       |  22,545,882 | -1,000,000 |
| `local_strnrchr`     | miss       |  23,680,623 | -1,000,000 |

Near-start and miss match within about 5%. On the short walk, `local_strnrchr` is about 1.4× slower.


### `strnstrn` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnstrn` | near-start |   4,671,913 |  8,000,000 |
| `strstr`             | near-start |  13,699,301 |  8,000,000 |
| `stlsoft_C_strnstrn` | near-end   |   6,226,656 | 84,000,000 |
| `strstr`             | near-end   |  15,013,356 | 84,000,000 |
| `stlsoft_C_strnstrn` | miss       |   7,156,116 | -1,000,000 |
| `strstr`             | miss       |   9,722,912 | -1,000,000 |

`stlsoft_C_strnstrn` is about 2.9× faster on the early needle, about 2.4× on the late needle, and about 1.4× on the miss.


## CI: `windows-cl`, 27th October 2026

GitHub-hosted Windows runner. The log path includes `Release`: `D:\a\STLSoft\STLSoft\build\test\performance\stlsoft\string\c_string\Release\test.performance.stlsoft.string.c_string.exe`. Compiler version was not in the log. Baseline name `_strnicmp`.


### `strnicmp` (total ns)

| Function             | Scenario     | Nanoseconds |     Anchor |
| -------------------- | ------------ | ----------- | ---------- |
| `stlsoft_C_strnicmp` | differ-early |   2,115,700 |  1,000,000 |
| `_strnicmp`          | differ-early |   6,005,500 |  1,000,000 |
| `stlsoft_C_strnicmp` | differ-late  |  67,217,000 | -1,000,000 |
| `_strnicmp`          | differ-late  |  58,964,300 | -1,000,000 |
| `stlsoft_C_strnicmp` | equal        |  67,159,500 |          0 |
| `_strnicmp`          | equal        |  57,670,400 |          0 |

Early difference: `stlsoft_C_strnicmp` is about 2.8× faster. Full compares: `_strnicmp` is about 1.1× faster on `differ-late` and about 1.2× faster on `equal`.


### `strnchr` (total ns)

| Function            | Scenario   | Nanoseconds |     Anchor |
| ------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnchr` | near-start |   4,227,900 |  3,000,000 |
| `memchr`            | near-start |   4,227,100 |  3,000,000 |
| `stlsoft_C_strnchr` | near-end   |   7,072,900 | 92,000,000 |
| `memchr`            | near-end   |   7,068,500 | 92,000,000 |
| `stlsoft_C_strnchr` | miss       |   7,901,100 | -1,000,000 |
| `memchr`            | miss       |   5,649,600 | -1,000,000 |

Both hits match `memchr`. The miss is about 1.4× slower than `memchr`.


### `strnistrn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnistrn` | near-start |  12,717,900 |  8,000,000 |
| `stlsoft_C_strnistrn` | near-end   | 125,310,200 | 84,000,000 |
| `stlsoft_C_strnistrn` | miss       |  83,978,900 | -1,000,000 |

No paired function. Early hit about 13 ms for the pass. Late hit about 125 ms. Miss about 84 ms.


### `strnpbrkn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnpbrkn` | near-start |   9,904,300 |  3,000,000 |
| `strpbrk`             | near-start |   7,802,700 |  3,000,000 |
| `stlsoft_C_strnpbrkn` | near-end   | 173,617,700 | 92,000,000 |
| `strpbrk`             | near-end   |  75,973,400 | 92,000,000 |
| `stlsoft_C_strnpbrkn` | miss       | 170,429,600 | -1,000,000 |
| `strpbrk`             | miss       |  78,826,700 | -1,000,000 |

`strpbrk` is faster on all three scenarios: about 1.3× on the early hit, about 2.3× on the late hit, and about 2.2× on the miss.


### `strnrchr` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnrchr` | near-start |  40,073,000 |  3,000,000 |
| `local_strnrchr`     | near-start |  42,470,500 |  3,000,000 |
| `stlsoft_C_strnrchr` | near-end   |   4,252,000 | 92,000,000 |
| `local_strnrchr`     | near-end   |   4,224,000 | 92,000,000 |
| `stlsoft_C_strnrchr` | miss       |  36,445,600 | -1,000,000 |
| `local_strnrchr`     | miss       |  36,491,200 | -1,000,000 |

The two reverse scans match within about 6%.


### `strnstrn` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnstrn` | near-start |   5,296,300 |  8,000,000 |
| `strstr`             | near-start |   6,715,400 |  8,000,000 |
| `stlsoft_C_strnstrn` | near-end   |  15,942,700 | 84,000,000 |
| `strstr`             | near-end   |  10,608,000 | 84,000,000 |
| `stlsoft_C_strnstrn` | miss       |  15,908,300 | -1,000,000 |
| `strstr`             | miss       |  10,243,700 | -1,000,000 |

Early needle: `stlsoft_C_strnstrn` is about 1.3× faster. Late needle and miss: `strstr` is about 1.5× faster.


## CI: `windows-mingw`, 27th October 2026

GitHub-hosted Windows runner. Log path `D:\a\STLSoft\STLSoft\build\test\performance\stlsoft\string\c_string\test.performance.stlsoft.string.c_string.exe`. Compiler version was not in the log. Baseline name `_strnicmp`.


### `strnicmp` (total ns)

| Function             | Scenario     | Nanoseconds |     Anchor |
| -------------------- | ------------ | ----------- | ---------- |
| `stlsoft_C_strnicmp` | differ-early |   2,824,100 |  1,000,000 |
| `_strnicmp`          | differ-early |   4,920,600 |  1,000,000 |
| `stlsoft_C_strnicmp` | differ-late  |  49,843,900 | -1,000,000 |
| `_strnicmp`          | differ-late  |  55,206,000 | -1,000,000 |
| `stlsoft_C_strnicmp` | equal        |  48,906,500 |          0 |
| `_strnicmp`          | equal        |  53,434,000 |          0 |

`stlsoft_C_strnicmp` is faster on all three scenarios: about 1.7× on an early difference, and about 1.1× when the compare walks all 45 bytes.


### `strnchr` (total ns)

| Function            | Scenario   | Nanoseconds |     Anchor |
| ------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnchr` | near-start |   3,775,100 |  3,000,000 |
| `memchr`            | near-start |   4,178,200 |  3,000,000 |
| `stlsoft_C_strnchr` | near-end   |   8,832,200 | 92,000,000 |
| `memchr`            | near-end   |   8,823,100 | 92,000,000 |
| `stlsoft_C_strnchr` | miss       |  11,899,800 | -1,000,000 |
| `memchr`            | miss       |   9,913,400 | -1,000,000 |

The early hit is about 10% faster than `memchr`. The late hit matches. The miss is about 1.2× slower than `memchr`.


### `strnistrn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnistrn` | near-start |   5,942,800 |  8,000,000 |
| `stlsoft_C_strnistrn` | near-end   |  30,763,200 | 84,000,000 |
| `stlsoft_C_strnistrn` | miss       |  39,626,000 | -1,000,000 |

No paired function. Early hit about 5.9 ms for the pass. Late hit about 31 ms. Miss about 40 ms.


### `strnpbrkn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnpbrkn` | near-start |   3,105,900 |  3,000,000 |
| `strpbrk`             | near-start |   9,204,800 |  3,000,000 |
| `stlsoft_C_strnpbrkn` | near-end   |  54,639,400 | 92,000,000 |
| `strpbrk`             | near-end   |  86,318,100 | 92,000,000 |
| `stlsoft_C_strnpbrkn` | miss       |  46,111,200 | -1,000,000 |
| `strpbrk`             | miss       |  75,250,200 | -1,000,000 |

`stlsoft_C_strnpbrkn` is faster on all three scenarios: about 3.0× on the early hit, and about 1.6× on the late hit and the miss.


### `strnrchr` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnrchr` | near-start |  37,272,200 |  3,000,000 |
| `local_strnrchr`     | near-start |  37,243,400 |  3,000,000 |
| `stlsoft_C_strnrchr` | near-end   |   3,753,200 | 92,000,000 |
| `local_strnrchr`     | near-end   |   3,750,600 | 92,000,000 |
| `stlsoft_C_strnrchr` | miss       |  33,195,500 | -1,000,000 |
| `local_strnrchr`     | miss       |  32,295,000 | -1,000,000 |

The two reverse scans match. On the miss, `local_strnrchr` is about 3% faster.


### `strnstrn` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnstrn` | near-start |   4,077,600 |  8,000,000 |
| `strstr`             | near-start |   5,372,700 |  8,000,000 |
| `stlsoft_C_strnstrn` | near-end   |  19,505,800 | 84,000,000 |
| `strstr`             | near-end   |  10,045,600 | 84,000,000 |
| `stlsoft_C_strnstrn` | miss       |  26,070,700 | -1,000,000 |
| `strstr`             | miss       |  10,585,500 | -1,000,000 |

Early needle: `stlsoft_C_strnstrn` is about 1.3× faster. Late needle: `strstr` is about 1.9× faster. Miss: `strstr` is about 2.5× faster.


## CI: `macos-gcc`, 27th October 2026

GitHub-hosted macOS runner. Log path `/Users/runner/work/STLSoft/STLSoft/build/test/performance/stlsoft/string/c_string/test.performance.stlsoft.string.c_string`. The job label is `macos-gcc`. The compiler banner was not in the log. Baseline name `strncasecmp`.


### `strnicmp` (total ns)

| Function             | Scenario     | Nanoseconds |     Anchor |
| -------------------- | ------------ | ----------- | ---------- |
| `stlsoft_C_strnicmp` | differ-early |   2,394,458 |  1,000,000 |
| `strncasecmp`        | differ-early |   6,480,250 |  1,000,000 |
| `stlsoft_C_strnicmp` | differ-late  |  51,592,250 | -1,000,000 |
| `strncasecmp`        | differ-late  |  62,526,166 | -1,000,000 |
| `stlsoft_C_strnicmp` | equal        |  50,033,334 |          0 |
| `strncasecmp`        | equal        |  70,283,917 |          0 |

`stlsoft_C_strnicmp` is faster on all three scenarios: about 2.7× on an early difference, about 1.2× on `differ-late`, and about 1.4× on `equal`.


### `strnchr` (total ns)

| Function            | Scenario   | Nanoseconds |     Anchor |
| ------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnchr` | near-start |   2,898,250 |  3,000,000 |
| `memchr`            | near-start |   2,736,916 |  3,000,000 |
| `stlsoft_C_strnchr` | near-end   |   5,399,916 | 92,000,000 |
| `memchr`            | near-end   |   5,618,667 | 92,000,000 |
| `stlsoft_C_strnchr` | miss       |   6,546,416 | -1,000,000 |
| `memchr`            | miss       |   7,220,917 | -1,000,000 |

The early hit is about 6% slower than `memchr`. The late hit is about 4% faster. The miss is about 10% faster.


### `strnistrn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnistrn` | near-start |   9,386,750 |  8,000,000 |
| `stlsoft_C_strnistrn` | near-end   |  62,101,083 | 84,000,000 |
| `stlsoft_C_strnistrn` | miss       |  67,250,583 | -1,000,000 |

No paired function. Early hit about 9.4 ms for the pass. Late hit about 62 ms. Miss about 67 ms.


### `strnpbrkn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnpbrkn` | near-start |   2,814,000 |  3,000,000 |
| `strpbrk`             | near-start |  11,398,458 |  3,000,000 |
| `stlsoft_C_strnpbrkn` | near-end   |  53,440,167 | 92,000,000 |
| `strpbrk`             | near-end   | 233,870,083 | 92,000,000 |
| `stlsoft_C_strnpbrkn` | miss       |  49,903,667 | -1,000,000 |
| `strpbrk`             | miss       | 282,749,459 | -1,000,000 |

`stlsoft_C_strnpbrkn` is faster on all three scenarios: about 4.1× on the early hit, about 4.4× on the late hit, and about 5.7× on the miss.


### `strnrchr` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnrchr` | near-start |  39,948,000 |  3,000,000 |
| `local_strnrchr`     | near-start |  37,833,666 |  3,000,000 |
| `stlsoft_C_strnrchr` | near-end   |   3,498,167 | 92,000,000 |
| `local_strnrchr`     | near-end   |   3,501,333 | 92,000,000 |
| `stlsoft_C_strnrchr` | miss       |  40,382,959 | -1,000,000 |
| `local_strnrchr`     | miss       |  36,178,583 | -1,000,000 |

The short walk matches. On the long walks `local_strnrchr` is about 6% faster for the early hit and about 12% faster on the miss.


### `strnstrn` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnstrn` | near-start |   3,406,208 |  8,000,000 |
| `strstr`             | near-start |  10,469,375 |  8,000,000 |
| `stlsoft_C_strnstrn` | near-end   |   5,458,958 | 84,000,000 |
| `strstr`             | near-end   |  37,513,500 | 84,000,000 |
| `stlsoft_C_strnstrn` | miss       |  11,252,917 | -1,000,000 |
| `strstr`             | miss       |  37,514,000 | -1,000,000 |

`stlsoft_C_strnstrn` is about 3.1× faster on the early needle, about 6.9× on the late needle, and about 3.3× on the miss.


## CI: `macos-clang`, 27th October 2026

GitHub-hosted macOS runner. Same log path shape as `macos-gcc`. Compiler version was not in the log. Baseline name `strncasecmp`.


### `strnicmp` (total ns)

| Function             | Scenario     | Nanoseconds |     Anchor |
| -------------------- | ------------ | ----------- | ---------- |
| `stlsoft_C_strnicmp` | differ-early |   1,881,375 |  1,000,000 |
| `strncasecmp`        | differ-early |   4,066,208 |  1,000,000 |
| `stlsoft_C_strnicmp` | differ-late  |  42,403,042 | -1,000,000 |
| `strncasecmp`        | differ-late  |  53,013,167 | -1,000,000 |
| `stlsoft_C_strnicmp` | equal        |  44,810,917 |          0 |
| `strncasecmp`        | equal        |  55,570,375 |          0 |

`stlsoft_C_strnicmp` is faster on all three scenarios: about 2.2× on an early difference, about 1.3× on `differ-late`, and about 1.2× on `equal`.


### `strnchr` (total ns)

| Function            | Scenario   | Nanoseconds |     Anchor |
| ------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnchr` | near-start |   2,498,042 |  3,000,000 |
| `memchr`            | near-start |   2,513,750 |  3,000,000 |
| `stlsoft_C_strnchr` | near-end   |   5,011,708 | 92,000,000 |
| `memchr`            | near-end   |   5,605,417 | 92,000,000 |
| `stlsoft_C_strnchr` | miss       |   6,333,500 | -1,000,000 |
| `memchr`            | miss       |   6,872,458 | -1,000,000 |

The early hit matches `memchr`. The late hit is about 12% faster. The miss is about 9% faster.


### `strnistrn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnistrn` | near-start |   9,103,375 |  8,000,000 |
| `stlsoft_C_strnistrn` | near-end   |  61,779,041 | 84,000,000 |
| `stlsoft_C_strnistrn` | miss       |  65,838,750 | -1,000,000 |

No paired function. Early hit about 9.1 ms for the pass. Late hit about 62 ms. Miss about 66 ms.


### `strnpbrkn` (total ns)

| Function              | Scenario   | Nanoseconds |     Anchor |
| --------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnpbrkn` | near-start |   2,856,500 |  3,000,000 |
| `strpbrk`             | near-start |  11,621,750 |  3,000,000 |
| `stlsoft_C_strnpbrkn` | near-end   |  50,464,459 | 92,000,000 |
| `strpbrk`             | near-end   | 234,734,667 | 92,000,000 |
| `stlsoft_C_strnpbrkn` | miss       |  47,424,500 | -1,000,000 |
| `strpbrk`             | miss       | 237,860,709 | -1,000,000 |

`stlsoft_C_strnpbrkn` is faster on all three scenarios: about 4.1× on the early hit, about 4.7× on the late hit, and about 5.0× on the miss.


### `strnrchr` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnrchr` | near-start |  34,054,083 |  3,000,000 |
| `local_strnrchr`     | near-start |  36,654,167 |  3,000,000 |
| `stlsoft_C_strnrchr` | near-end   |   3,205,334 | 92,000,000 |
| `local_strnrchr`     | near-end   |   3,179,125 | 92,000,000 |
| `stlsoft_C_strnrchr` | miss       |  36,397,666 | -1,000,000 |
| `local_strnrchr`     | miss       |  34,966,208 | -1,000,000 |

The short walk matches. On the long walk to index 3, `local_strnrchr` is about 8% slower. On the miss it is about 4% faster.


### `strnstrn` (total ns)

| Function             | Scenario   | Nanoseconds |     Anchor |
| -------------------- | ---------- | ----------- | ---------- |
| `stlsoft_C_strnstrn` | near-start |   3,394,084 |  8,000,000 |
| `strstr`             | near-start |  10,459,542 |  8,000,000 |
| `stlsoft_C_strnstrn` | near-end   |   5,457,875 | 84,000,000 |
| `strstr`             | near-end   |  36,866,708 | 84,000,000 |
| `stlsoft_C_strnstrn` | miss       |  10,954,917 | -1,000,000 |
| `strstr`             | miss       |  37,858,500 | -1,000,000 |

`stlsoft_C_strnstrn` is about 3.1× faster on the early needle, about 6.8× on the late needle, and about 3.5× on the miss.


## Summary

One row per platform. For every paired helper the cell is **baseline ÷ STLSoft**, from the total nanoseconds above, to two decimal places. Above 1, the STLSoft function was faster. `stlsoft_C_strnistrn` has no baseline, so that table is the total nanoseconds for the pass.


### `strnicmp`

Baseline is `strncasecmp`, and `_strnicmp` on both Windows cells.

| Platform      | differ-early | differ-late | equal |
| ------------- | ------------ | ----------- | ----- |
| local Mac     |        2.23× |       1.27× | 1.14× |
| linux-clang   |        2.39× |       0.10× | 0.11× |
| linux-gcc     |        1.86× |       0.10× | 0.09× |
| macos-clang   |        2.16× |       1.25× | 1.24× |
| macos-gcc     |        2.71× |       1.21× | 1.40× |
| windows-cl    |        2.84× |       0.88× | 0.86× |
| windows-mingw |        1.74× |       1.11× | 1.09× |


### `strnchr`

Baseline is `memchr`.

| Platform      | near-start | near-end |  miss |
| ------------- | ---------- | -------- | ----- |
| local Mac     |      1.00× |    0.99× | 1.00× |
| linux-clang   |      0.99× |    1.00× | 1.00× |
| linux-gcc     |      0.89× |    0.90× | 1.01× |
| macos-clang   |      1.01× |    1.12× | 1.09× |
| macos-gcc     |      0.94× |    1.04× | 1.10× |
| windows-cl    |      1.00× |    1.00× | 0.72× |
| windows-mingw |      1.11× |    1.00× | 0.83× |


### `strnistrn`

Total nanoseconds. No paired baseline.

| Platform      | near-start |    near-end |       miss |
| ------------- | ---------- | ----------- | ---------- |
| local Mac     |  4,170,750 |  30,920,458 | 32,696,042 |
| linux-clang   | 10,443,673 |  70,170,801 | 88,993,444 |
| linux-gcc     |  3,513,096 |  21,807,977 | 23,401,324 |
| macos-clang   |  9,103,375 |  61,779,041 | 65,838,750 |
| macos-gcc     |  9,386,750 |  62,101,083 | 67,250,583 |
| windows-cl    | 12,717,900 | 125,310,200 | 83,978,900 |
| windows-mingw |  5,942,800 |  30,763,200 | 39,626,000 |


### `strnpbrkn`

Baseline is `strpbrk`.

| Platform      | near-start | near-end |  miss |
| ------------- | ---------- | -------- | ----- |
| local Mac     |      3.85× |    3.93× | 5.21× |
| linux-clang   |      1.55× |    0.24× | 0.27× |
| linux-gcc     |      1.21× |    0.50× | 3.99× |
| macos-clang   |      4.07× |    4.65× | 5.02× |
| macos-gcc     |      4.05× |    4.38× | 5.67× |
| windows-cl    |      0.79× |    0.44× | 0.46× |
| windows-mingw |      2.96× |    1.58× | 1.63× |


### `strnrchr`

Baseline is `local_strnrchr`.

| Platform      | near-start | near-end |  miss |
| ------------- | ---------- | -------- | ----- |
| local Mac     |      1.00× |    1.00× | 1.01× |
| linux-clang   |      1.04× |    1.44× | 1.05× |
| linux-gcc     |      0.99× |    1.03× | 1.00× |
| macos-clang   |      1.08× |    0.99× | 0.96× |
| macos-gcc     |      0.95× |    1.00× | 0.90× |
| windows-cl    |      1.06× |    0.99× | 1.00× |
| windows-mingw |      1.00× |    1.00× | 0.97× |


### `strnstrn`

Baseline is `strstr`.

| Platform      | near-start | near-end |  miss |
| ------------- | ---------- | -------- | ----- |
| local Mac     |      2.39× |    7.19× | 7.67× |
| linux-clang   |      2.93× |    2.41× | 1.36× |
| linux-gcc     |      3.60× |    3.24× | 1.80× |
| macos-clang   |      3.08× |    6.75× | 3.46× |
| macos-gcc     |      3.07× |    6.87× | 3.33× |
| windows-cl    |      1.27× |    0.67× | 0.64× |
| windows-mingw |      1.32× |    0.52× | 0.41× |


## Directions so far

Local Mac plus `linux-gcc`, `linux-clang`, `macos-gcc`, `macos-clang`, `windows-cl`, and `windows-mingw`.

* **Anchors match** on every row of every run.
* **Early `strnicmp` favours `stlsoft_C_strnicmp`** on all seven runs, about 1.7–2.8×.
* **A 45-byte compare splits by C library.** Linux `strncasecmp` is about 9–11× faster. `windows-cl` `_strnicmp` is about 1.1–1.2× faster. The local Mac, both macOS cells, and `windows-mingw` favour `stlsoft_C_strnicmp` by about 1.1–1.4×.
* **`stlsoft_C_strnchr` stays close to `memchr`.** Most rows are within about 12%. The larger gaps are the misses on `windows-cl` (about 1.4× slower) and `windows-mingw` (about 1.2× slower).
* **`stlsoft_C_strnrchr` tracks `local_strnrchr`.** Linux Clang's short walk is the outlier: the local scan is about 1.4× slower there. The macOS long walks differ by up to about 12%.
* **`strnpbrkn` against `strpbrk` depends on the host.** The local Mac, both macOS cells, and `windows-mingw` favour `stlsoft_C_strnpbrkn` on every scenario. On the Apple cells the long scans are about 3.9–5.7×. On MinGW they are about 1.6×. Both Linux cells favour `stlsoft_C_strnpbrkn` on the early hit and favour `strpbrk` on the long scan. `windows-cl` favours `strpbrk` on all three.
* **Early `strnstrn` favours `stlsoft_C_strnstrn`** on all seven runs, about 1.3–3.6×. Late needle and miss favour it on the Mac, both macOS cells, and both Linux cells. They favour `strstr` on both Windows cells: about 1.5× on `windows-cl`, and about 1.9–2.5× on `windows-mingw`.


## Not yet done

* Record compiler banners for each cell, and the local `CMAKE_BUILD_TYPE`. The `macos-gcc` log does not say whether that job's `gcc` is GNU or Apple Clang.
* Write the settled performance claim from the seven runs above, once those banners are known.



<!-- ########################### end of file ########################### -->
