import "./style.css";

const tauri_core = window.__TAURI__;

const app = document.querySelector("#app");

app.innerHTML = `
  <main class="min-h-screen bg-slate-950 text-slate-100">
    <section class="mx-auto flex min-h-screen max-w-5xl flex-col justify-center gap-8 px-6 py-16">
      <div>
        <p class="text-sm uppercase tracking-[0.3em] text-cyan-300">vite tailwind</p>
        <h1 class="mt-3 text-5xl font-black tracking-tight sm:text-7xl">tauri-cpp</h1>
        <p class="mt-4 max-w-2xl text-lg text-slate-300">
          a regular vite setup with tailwind only. no component layer, just a quick path to a
          styled desktop shell.
        </p>
      </div>
      <div class="flex flex-wrap gap-3">
        <button data-command="sync_echo" class="rounded-full bg-cyan-300 px-5 py-3 font-semibold text-slate-950">
          sync command
        </button>
        <button data-command="async_echo" class="rounded-full border border-slate-700 px-5 py-3 font-semibold">
          async command
        </button>
        <button id="smoke" class="rounded-full border border-slate-700 px-5 py-3 font-semibold">
          smoke test
        </button>
      </div>
      <pre id="output" class="overflow-auto rounded-3xl border border-slate-800 bg-slate-900/80 p-5 text-sm text-cyan-100">waiting for startup event</pre>
    </section>
  </main>
`;

const output = document.querySelector("#output");

const write_output = value => {
  output.textContent = typeof value === "string" ? value : JSON.stringify(value, null, 2);
};

document.querySelectorAll("[data-command]").forEach(button => {
  button.addEventListener("click", async () => {
    if (!tauri_core?.core?.invoke)
      return write_output("tauri runtime not found");

    const result = await tauri_core.core.invoke(button.dataset.command, {
      payloadJson: JSON.stringify({ source: "vite_tailwind" })
    });
    write_output(result);
  });
});

document.querySelector("#smoke")?.addEventListener("click", async () => {
  if (!tauri_core?.core?.invoke)
    return write_output("tauri runtime not found");

  const result = await tauri_core.core.invoke("smoke_test");
  write_output(result);
});

if (tauri_core?.event?.listen) {
  tauri_core.event.listen("demo:start", event => {
    write_output(event.payload);
  });
}
