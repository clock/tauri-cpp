#pragma once

#include <filesystem>
#include <string>

namespace tauri_cpp {

struct frontend_config {
  std::filesystem::path dist_dir;
  std::string entry_page = "index.html";
};

} // namespace tauri_cpp
