#pragma once

#include <string>

#include "rust/cxx.h"

namespace tauri_cpp::bridge {

auto describe_demo_app(rust::Str app_id, rust::Str frontend_dist, rust::Str entry_page)
  -> rust::String;

auto invoke_demo_command(rust::Str command_name, rust::Str payload_json) -> rust::String;

} // namespace tauri_cpp::bridge
