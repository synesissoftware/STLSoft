# COMSTL tests — documented skips

The following `include/comstl/` components are intentionally not covered by automated tests in this tree because they require complex external setup that is not available in the standard CI/unit-test environment.

| Component | Reason |
|-----------|--------|
| `speech/sapi_util.hpp` | Requires Windows SAPI runtime and `sapi.h` headers (`COMSTL_SPEECH_SAPI_UTIL_USE_MS_SAPI_HEADERS`). |
| `typelib/functions.hpp` | Requires a registered or on-disk type library (`.tlb`) to exercise meaningfully. |
| `typelib/TypeInfo_resource_scope.hpp` | Depends on typelib loading; same constraint as `typelib/functions.hpp`. |
| `util/thread_marshal.hpp` | Requires cross-apartment marshaling with a registered proxy/stub; not feasible as a pure in-memory unit test. |
| `conversion/method_cast.hpp` | Requires a live `IDispatch` vtable with callable DISPIDs; covered indirectly only where `IDispatch` is available (not guaranteed in CI). |
| `collections/collection_sequence.hpp` | Requires a custom `IEnumXXXX` implementation with a non-trivial collection protocol. |
| `collections/enumeration_policies.hpp` | Policy header only; exercised via `enumerator_sequence` where a mock enumerator is provided. |
| `interface/interface_cast.hpp` | Obsolete shim; use `conversion/interface_cast.hpp` (tested). |
| `interface/interface_traits.hpp` | Obsolete shim; use `util/interface_traits.hpp` (tested). |
| `error/errorinfo_desc.hpp` | Thin descriptor wrapper around `errorinfo_functions.h` (tested). |
| `error/bad_interface_cast.hpp` | Exception typedef only; behaviour covered by `conversion/interface_cast` tests. |
| `error/exceptions.hpp` | Aggregate include; constituents tested individually. |
| `exception/bad_interface_cast.hpp` | Exception typedef only. |
| `exception/throw_policies.hpp` | Policy templates; no standalone runtime surface. |
| `exception/policy/HRESULT_to_string_translation_policy.hpp` | Policy template; depends on project-wide exception configuration. |
| `functional/com_predicate_adaptors.hpp` | Predicate adaptor templates; no standalone runtime surface beyond included functionals. |
| `functional/functionals.hpp` | Umbrella include for `interface_functionals.hpp` and `type_functionals.hpp` (both tested). |
| `auto/dispatch_functions.h` | Exercised indirectly via `VARIANT_functions` tests that create `IDispatch` instances when the SynesisValue component is present. |
