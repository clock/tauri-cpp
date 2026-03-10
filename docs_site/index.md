---
layout: home

hero:
  name: tauri-cpp
  text: Windows-first Tauri + C++ starter
  tagline: Build standalone desktop apps first, keep the native bridge thin, and stay friendly to Visual Studio on Windows.
  actions:
    - theme: brand
      text: Windows Quickstart
      link: /guide/quickstart
    - theme: alt
      text: Pick an Example
      link: /guide/examples

features:
  - title: Low-friction setup
    details: Bootstrap scripts, committed Visual Studio tasks, and clear first-run steps aimed at outside Windows users.
  - title: Thin native/web bridge
    details: A small C++ surface and a shared Rust bridge keep the Tauri layer narrow instead of turning it into another framework.
  - title: Visual Studio friendly
    details: The repo keeps a direct F5 path for debug sessions while still staying portable enough for later Linux and macOS work.
---

## Stable path vs experimental path

`tauri-cpp` is built around one stable target: standalone desktop apps that ship static frontend files in a Tauri webview. DirectX, OpenGL, and other native host attachment paths stay explicitly experimental until the standalone route is solid.

## Choose an example

<div class="home-panels">
  <section class="home-panel">
    <h2>Choose <code>plain_html</code> by default</h2>
    <p>It is the lightest setup in the repo and the best first stop if you care more about startup clarity, low overhead, and understanding the full stack than about framework comfort.</p>
    <ul>
      <li><strong><code>plain_html</code></strong> for the lowest overhead starter</li>
      <li><strong><code>vite_tailwind</code></strong> for a normal Vite app with utility-first styling</li>
      <li><strong><code>react_shadcn</code></strong> for a higher-level component stack</li>
    </ul>
  </section>
  <section class="home-panel">
    <h2>What ships here</h2>
    <p>The repo includes a small C++ API, a shared Rust host crate using <code>cxx</code>, three frontend examples, Windows-first bootstrap scripts, and a GitHub Pages docs site.</p>
    <p>Use the docs to start with Windows setup, then move into examples, integration guidance, architecture notes, and the API overview.</p>
  </section>
  <section class="home-panel">
    <h2>Start the right way</h2>
    <p>For a working flow today, start from one of the example apps, keep the command bridge small, and wire heavier native work behind C++ instead of trying to expose your whole engine to the webview.</p>
    <p><a href="./guide/quickstart">Open the quickstart</a> or <a href="./guide/existing-projects">see the integration path</a>.</p>
  </section>
</div>
