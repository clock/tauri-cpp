#pragma once

#include <cstdint>
#include <string>

namespace tauri_cpp {

struct window_options {
  std::string title = "tauri-cpp";
  std::int32_t width = 1280;
  std::int32_t height = 720;
  std::int32_t min_width = 640;
  std::int32_t min_height = 480;
  bool center = true;
  bool resizable = true;
  bool visible = true;
};

} // namespace tauri_cpp
