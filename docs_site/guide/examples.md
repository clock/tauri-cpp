# examples

Start with `plain_html` unless you already know you want a richer frontend stack. It is the simplest example and the best first test. All three examples share the same general native path and differ mostly in frontend overhead and ergonomics.

| Example | Best for | Why you would pick it | Typical commands |
| --- | --- | --- | --- |
| `plain_html` | default starting point | Lowest overhead, static file copy build, easiest full-stack understanding | `npm run dev:plain_html`, `npm run run:plain_html`, `npm run package:plain_html` |
| `vite_tailwind` | utility-first styling without React | Regular Vite workflow with Tailwind and no component library | `npm run dev:vite_tailwind`, `npm run run:vite_tailwind`, `npm run package:vite_tailwind` |
| `react_shadcn` | component-heavy frontend work | Highest-level example with React and shadcn/ui style building blocks | `npm run dev:react_shadcn`, `npm run run:react_shadcn`, `npm run package:react_shadcn` |

## `plain_html`

This is the default recommendation. It uses plain html, css, and js, builds by copying static files, and is the best place to start if setup speed, low memory use, and bridge clarity matter more than framework comfort.

## `vite_tailwind`

This is the middle ground. It keeps the standard Vite app workflow and Tailwind styling without adding the extra weight of a component-heavy React stack.

## `react_shadcn`

This is the highest-level example in the repo. It uses React, Vite, and shadcn/ui style building blocks while keeping the same native demo surface as the other examples.

## Pick path

- Use `plain_html` if you are validating the native shell, perf, bootstrap path, or just need the best first test.
- Use `vite_tailwind` if you want a more typical frontend toolchain but still want a small moving surface.
- Use `react_shadcn` if your team already works in React and wants ready-made component patterns.

The Windows quickstart stays the same whichever example you choose. After that, use the example-specific `dev:*`, `run:*`, and `package:*` commands from the table above.

## Native control path

The actual native control path is:

`frontend -> Rust command -> rust/host bridge -> C++`

That is the model to keep in mind when you are deciding where code should live.
