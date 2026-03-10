# host integration

The first release is not trying to fully solve embedding Tauri inside a directx or opengl host. That path is where complexity spikes fast.

What the repo does now:

- keeps the public c++ api separate from the frontend examples
- reserves an experimental header for host extension work
- avoids Windows-only assumptions in shared headers

What comes later:

- native host lifecycle contracts
- shared window ownership rules
- rendering surface coordination
- example integrations for Win32 and one graphics stack
