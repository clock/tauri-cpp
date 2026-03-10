use std::env;
use std::fs;
use std::path::PathBuf;

use tauri::Manager;
use tauri_cpp_host::{HostConfig, SerializableCommandResult, invoke_async_demo, invoke_sync_demo};

fn host_config() -> HostConfig {
    HostConfig::new(
        "clock.tauri-cpp.react-shadcn",
        PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("..").join("dist"),
    )
}

#[tauri::command]
fn sync_echo(payload_json: String) -> Result<SerializableCommandResult, String> {
    Ok(invoke_sync_demo("sync_echo", &payload_json))
}

#[tauri::command]
async fn async_echo(payload_json: String) -> Result<SerializableCommandResult, String> {
    Ok(invoke_async_demo("async_echo", &payload_json).await)
}

#[tauri::command]
fn system_info(payload_json: Option<String>) -> Result<SerializableCommandResult, String> {
    let payload = payload_json.unwrap_or_else(|| String::from("{}"));
    Ok(invoke_sync_demo("system_info", &payload))
}

#[tauri::command]
fn smoke_test() -> Result<String, String> {
    serde_json::to_string_pretty(&serde_json::json!({
        "sync": invoke_sync_demo("sync_echo", "{\"mode\":\"smoke\"}"),
        "system": invoke_sync_demo("system_info", "{}")
    }))
    .map_err(|error| error.to_string())
}

pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_dialog::init())
        .plugin(tauri_plugin_shell::init())
        .setup(|app| {
            let config = host_config();
            let window = app.get_webview_window("main").ok_or("missing main window")?;

            tauri_cpp_host::emit_startup(&window, &config).map_err(|error| error.to_string())?;

            if env::args().any(|arg| arg == "--smoke-test") {
                let payload = smoke_test()?;
                window.hide().map_err(|error| error.to_string())?;
                fs::write("smoke-test-result.json", payload).map_err(|error| error.to_string())?;
                app.handle().exit(0);
            }

            Ok(())
        })
        .invoke_handler(tauri::generate_handler![
            sync_echo,
            async_echo,
            system_info,
            smoke_test
        ])
        .run(tauri::generate_context!())
        .expect("failed to run react_shadcn app");
}
