#pragma once

#include <functional>
#include <string>

namespace tauri_cpp {

struct command_request {
  std::string command_name;
  std::string payload_json;
};

struct command_response {
  bool ok = true;
  std::string payload_json;
  std::string error_message;
};

using command_handler = std::function<command_response(const command_request&)>;
using startup_callback = std::function<void()>;

} // namespace tauri_cpp
