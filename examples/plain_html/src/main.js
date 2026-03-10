const tauri_core = window.__TAURI__;
const output = document.querySelector("#output");

const write_output = value => {
  output.textContent = typeof value === "string" ? value : JSON.stringify(value, null, 2);
};

const invoke = async (command, payload_json = "{}") => {
  if (!tauri_core?.core?.invoke) {
    write_output("tauri runtime not found");
    return;
  }

  const result = await tauri_core.core.invoke(command, { payloadJson: payload_json });
  write_output(result);
};

document.querySelector("#sync_button")?.addEventListener("click", () => {
  void invoke("sync_echo", "{\"source\":\"plain_html\"}");
});

document.querySelector("#async_button")?.addEventListener("click", () => {
  void invoke("async_echo", "{\"source\":\"plain_html\"}");
});

document.querySelector("#smoke_button")?.addEventListener("click", async () => {
  if (!tauri_core?.core?.invoke)
    return;

  const result = await tauri_core.core.invoke("smoke_test");
  write_output(result);
});

if (tauri_core?.event?.listen) {
  tauri_core.event.listen("demo:start", event => {
    write_output(event.payload);
  });
}
