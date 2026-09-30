# TEMPORARY (file_lines.perf): boot_probe.c is a pure-C breadcrumb TU so a
# silent MinGW death before C++ main still leaves file_lines.perf.trace.txt.
# Remove SIS:AUTO_GENERATED so this edit is not overwritten; restore the
# stock one-liner once the crash is located.
define_example_program(test.performance.platformstl.file_lines main.cpp)
target_sources(test.performance.platformstl.file_lines PRIVATE boot_probe.c)
