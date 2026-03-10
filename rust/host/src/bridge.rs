#[cxx::bridge(namespace = "tauri_cpp::bridge")]
pub mod ffi {
    unsafe extern "C++" {
        include!("tauri_cpp/rust_bridge.hpp");

        fn describe_demo_app(app_id: &str, frontend_dist: &str, entry_page: &str) -> String;
        fn invoke_demo_command(command_name: &str, payload_json: &str) -> String;
    }
}
