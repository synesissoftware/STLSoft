# ATLSTL unit tests — deferred components

## util/module_scope.hpp

`atlstl::module_scope` scopes initialisation and termination of an ATL
`CComModule` / `_Module` instance via `module_type::Init()` and `Term()`.
Meaningful unit coverage requires a full ATL module object map, a valid
`HINSTANCE`, and typically a registered type library — infrastructure that
belongs in a component test rather than a leaf unit test.

## window/* (about_dialog, enhanced_window, window)

GUI/HWND-heavy window components are intentionally excluded from the unit-test
suite. Cover these with component or manual GUI tests.

## automation/multiple_dispatch.hpp (full runtime coverage)

The dispid striping algorithm is covered by
`test.unit.atlstl.automation.multiple_dispatch`. End-to-end
`GetIDsOfNames()` / `Invoke()` routing through real dual interfaces still
requires a MIDL-generated type library and is deferred to a future component
test.


# ############################## end of file ############################# #
