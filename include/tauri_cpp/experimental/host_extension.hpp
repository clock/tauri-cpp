#pragma once

#include <string>

namespace tauri_cpp::experimental {

enum class host_mode {
  standalone,
  native_host
};

struct host_extension_options {
  host_mode mode = host_mode::standalone;
  std::string backend_name;
};

} // namespace tauri_cpp::experimental
