#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "tauri_cpp/command_context.hpp"
#include "tauri_cpp/event_bus.hpp"
#include "tauri_cpp/frontend_config.hpp"
#include "tauri_cpp/window_options.hpp"

namespace tauri_cpp {

class app_builder {
public:
  app_builder();
  ~app_builder();

  app_builder(const app_builder&);
  app_builder(app_builder&&) noexcept;
  auto operator=(const app_builder&) -> app_builder&;
  auto operator=(app_builder&&) noexcept -> app_builder&;

  auto set_app_id(std::string app_id) -> app_builder&;
  auto set_window(window_options options) -> app_builder&;
  auto set_frontend(frontend_config config) -> app_builder&;
  auto register_command(std::string command_name, command_handler handler) -> app_builder&;
  auto register_startup_callback(startup_callback callback) -> app_builder&;

  [[nodiscard]] auto app_id() const -> std::string;
  [[nodiscard]] auto window() const -> window_options;
  [[nodiscard]] auto frontend() const -> frontend_config;
  [[nodiscard]] auto events() const -> std::shared_ptr<event_bus>;

  [[nodiscard]] auto dispatch_command(const command_request& request) const -> command_response;
  [[nodiscard]] auto describe() const -> std::string;
  auto run() const -> int;

private:
  class impl;
  std::unique_ptr<impl> impl_;
};

} // namespace tauri_cpp
