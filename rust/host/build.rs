fn main() {
    cxx_build::bridges(["src/bridge.rs"])
        .file("cpp/demo_bridge.cpp")
        .file("../../src/app_builder.cpp")
        .file("../../src/event_bus.cpp")
        .include("include")
        .include("../../include")
        .flag_if_supported("/std:c++20")
        .flag_if_supported("-std=c++20")
        .compile("tauri_cpp_host_bridge");

    println!("cargo:rerun-if-changed=src/bridge.rs");
    println!("cargo:rerun-if-changed=cpp/demo_bridge.cpp");
    println!("cargo:rerun-if-changed=include/tauri_cpp/rust_bridge.hpp");
    println!("cargo:rerun-if-changed=../../include/tauri_cpp/app_builder.hpp");
    println!("cargo:rerun-if-changed=../../include/tauri_cpp/command_context.hpp");
    println!("cargo:rerun-if-changed=../../include/tauri_cpp/event_bus.hpp");
    println!("cargo:rerun-if-changed=../../include/tauri_cpp/frontend_config.hpp");
    println!("cargo:rerun-if-changed=../../include/tauri_cpp/window_options.hpp");
    println!("cargo:rerun-if-changed=../../src/app_builder.cpp");
    println!("cargo:rerun-if-changed=../../src/event_bus.cpp");
}
