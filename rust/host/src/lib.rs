mod bridge;

use std::path::{Path, PathBuf};
use std::time::Duration;

use anyhow::Context;
use serde::{Deserialize, Serialize};
use tauri::{Emitter, WebviewWindow};

#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct SerializableCommandResult {
    pub ok: bool,
    pub payload_json: String,
    pub error_message: String,
}

#[derive(Clone, Debug)]
pub struct HostConfig {
    pub app_id: String,
    pub frontend_dist: PathBuf,
    pub entry_page: String,
}

#[derive(Clone, Serialize)]
pub struct StartupEvent {
    pub app_id: String,
    pub frontend_dist: String,
    pub entry_page: String,
    pub manifest_json: String,
}

impl HostConfig {
    pub fn new(app_id: impl Into<String>, frontend_dist: impl Into<PathBuf>) -> Self {
        Self {
            app_id: app_id.into(),
            frontend_dist: frontend_dist.into(),
            entry_page: String::from("index.html"),
        }
    }

    pub fn entry_page(mut self, entry_page: impl Into<String>) -> Self {
        self.entry_page = entry_page.into();
        self
    }
}

pub fn validate_frontend(frontend_dist: &Path) -> anyhow::Result<()> {
    if !frontend_dist.exists() {
        anyhow::bail!("frontend dist directory does not exist: {}", frontend_dist.display());
    }

    Ok(())
}

pub fn describe_demo_app(config: &HostConfig) -> anyhow::Result<String> {
    validate_frontend(&config.frontend_dist)?;

    Ok(bridge::ffi::describe_demo_app(
        &config.app_id,
        &config.frontend_dist.to_string_lossy(),
        &config.entry_page,
    ))
}

pub fn invoke_sync_demo(command_name: &str, payload_json: &str) -> SerializableCommandResult {
    serde_json::from_str(&bridge::ffi::invoke_demo_command(command_name, payload_json))
        .unwrap_or_else(|error| SerializableCommandResult {
            ok: false,
            payload_json: String::new(),
            error_message: error.to_string(),
        })
}

pub async fn invoke_async_demo(command_name: &str, payload_json: &str) -> SerializableCommandResult {
    tokio::time::sleep(Duration::from_millis(30)).await;
    serde_json::from_str(&bridge::ffi::invoke_demo_command(command_name, payload_json))
        .unwrap_or_else(|error| SerializableCommandResult {
            ok: false,
            payload_json: String::new(),
            error_message: error.to_string(),
        })
}

pub fn emit_startup(window: &WebviewWindow, config: &HostConfig) -> anyhow::Result<()> {
    let manifest_json = describe_demo_app(config)?;

    window
        .emit(
            "demo:start",
            StartupEvent {
                app_id: config.app_id.clone(),
                frontend_dist: config.frontend_dist.to_string_lossy().into_owned(),
                entry_page: config.entry_page.clone(),
                manifest_json,
            },
        )
        .context("failed to emit startup event")
}
