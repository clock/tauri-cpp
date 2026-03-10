# host integration

Standalone is the stable path. Native host attachment is kept experimental on purpose.

## What exists now

- the public C++ API stays separate from the frontend examples
- an experimental header exists for host extension work
- shared headers avoid locking the repo into Windows-only assumptions

## What is intentionally deferred

- native host lifecycle contracts
- shared window ownership rules
- rendering surface coordination
- example integrations for Win32 and a graphics stack

The repo does not claim that DirectX, OpenGL, or other host attachment work is solved. That work comes later, after the standalone desktop flow is solid.
