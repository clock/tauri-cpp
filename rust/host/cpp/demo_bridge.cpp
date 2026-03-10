#include "tauri_cpp/rust_bridge.hpp"

#include <filesystem>
#include <string>

#include "tauri_cpp/app_builder.hpp"

namespace tauri_cpp::bridge {

namespace {

auto make_demo_builder(const std::string& app_id,
                       const std::string& frontend_dist,
                       const std::string& entry_page) -> tauri_cpp::app_builder {
  tauri_cpp::app_builder builder;
  builder.set_app_id(app_id);
  builder.set_frontend(tauri_cpp::frontend_config{
    .dist_dir = std::filesystem::path(frontend_dist),
    .entry_page = entry_page,
  });
  builder.register_command("sync_echo", [](const tauri_cpp::command_request& request) {
    return tauri_cpp::command_response{
      .ok = true,
      .payload_json = request.payload_json,
      .error_message = {},
    };
  });
  builder.register_command("async_echo", [](const tauri_cpp::command_request& request) {
    return tauri_cpp::command_response{
      .ok = true,
      .payload_json = request.payload_json,
      .error_message = {},
    };
  });
  builder.register_command("system_info", [](const tauri_cpp::command_request&) {
    return tauri_cpp::command_response{
      .ok = true,
      .payload_json = "{\"platform\":\"native\",\"bridge\":\"cxx\"}",
      .error_message = {},
    };
  });
  return builder;
}

auto escape_json(const std::string& value) -> std::string {
  std::string escaped;
  escaped.reserve(value.size());

  for (const auto ch : value) {
    switch (ch) {
    case '\\':
      escaped += "\\\\";
      break;
    case '"':
      escaped += "\\\"";
      break;
    case '\n':
      escaped += "\\n";
      break;
    case '\r':
      escaped += "\\r";
      break;
    case '\t':
      escaped += "\\t";
      break;
    default:
      escaped += ch;
      break;
    }
  }

  return escaped;
}

auto response_json(const tauri_cpp::command_response& response) -> std::string {
  return std::string("{\"ok\":")
    + (response.ok ? "true" : "false")
    + ",\"payload_json\":\""
    + escape_json(response.payload_json)
    + "\",\"error_message\":\""
    + escape_json(response.error_message)
    + "\"}";
}

} // namespace

auto describe_demo_app(const rust::Str app_id,
                       const rust::Str frontend_dist,
                       const rust::Str entry_page) -> rust::String {
  const auto builder = make_demo_builder(std::string(app_id),
                                         std::string(frontend_dist),
                                         std::string(entry_page));
  return rust::String(builder.describe());
}

auto invoke_demo_command(const rust::Str command_name, const rust::Str payload_json) -> rust::String {
  const auto builder = make_demo_builder("clock.tauri_cpp.demo", ".", "index.html");
  const auto response = builder.dispatch_command(tauri_cpp::command_request{
    .command_name = std::string(command_name),
    .payload_json = std::string(payload_json),
  });

  return rust::String(response_json(response));
}

} // namespace tauri_cpp::bridge
