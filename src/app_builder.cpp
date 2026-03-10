#include "tauri_cpp/app_builder.hpp"

#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace tauri_cpp {

namespace {

auto escape_json(std::string_view value) -> std::string {
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

} // namespace

class app_builder::impl {
public:
  std::string app_id = "clock.tauri-cpp";
  window_options window;
  frontend_config frontend;
  std::unordered_map<std::string, command_handler> command_handlers;
  std::vector<startup_callback> startup_callbacks;
  std::shared_ptr<event_bus> events = std::make_shared<event_bus>();

  [[nodiscard]] auto validate() const -> command_response {
    if (app_id.empty())
      return command_response{
        .ok = false,
        .payload_json = {},
        .error_message = "app id is required",
      };

    if (frontend.dist_dir.empty())
      return command_response{
        .ok = false,
        .payload_json = {},
        .error_message = "frontend dist_dir is required",
      };

    if (frontend.entry_page.empty())
      return command_response{
        .ok = false,
        .payload_json = {},
        .error_message = "frontend entry_page is required",
      };

    return command_response{
      .ok = true,
      .payload_json = {},
      .error_message = {},
    };
  }
};

app_builder::app_builder() : impl_(std::make_unique<impl>()) {}

app_builder::~app_builder() = default;

app_builder::app_builder(const app_builder& other) : impl_(std::make_unique<impl>(*other.impl_)) {}

app_builder::app_builder(app_builder&&) noexcept = default;

auto app_builder::operator=(const app_builder& other) -> app_builder& {
  if (this == &other)
    return *this;

  impl_ = std::make_unique<impl>(*other.impl_);
  return *this;
}

auto app_builder::operator=(app_builder&&) noexcept -> app_builder& = default;

auto app_builder::set_app_id(std::string app_id) -> app_builder& {
  impl_->app_id = std::move(app_id);
  return *this;
}

auto app_builder::set_window(window_options options) -> app_builder& {
  impl_->window = std::move(options);
  return *this;
}

auto app_builder::set_frontend(frontend_config config) -> app_builder& {
  impl_->frontend = std::move(config);
  return *this;
}

auto app_builder::register_command(std::string command_name, command_handler handler) -> app_builder& {
  impl_->command_handlers.insert_or_assign(std::move(command_name), std::move(handler));
  return *this;
}

auto app_builder::register_startup_callback(startup_callback callback) -> app_builder& {
  impl_->startup_callbacks.push_back(std::move(callback));
  return *this;
}

auto app_builder::app_id() const -> std::string {
  return impl_->app_id;
}

auto app_builder::window() const -> window_options {
  return impl_->window;
}

auto app_builder::frontend() const -> frontend_config {
  return impl_->frontend;
}

auto app_builder::events() const -> std::shared_ptr<event_bus> {
  return impl_->events;
}

auto app_builder::dispatch_command(const command_request& request) const -> command_response {
  const auto it = impl_->command_handlers.find(request.command_name);
  if (it == impl_->command_handlers.end()) {
    return command_response{
      .ok = false,
      .payload_json = {},
      .error_message = "command not registered",
    };
  }

  return it->second(request);
}

auto app_builder::describe() const -> std::string {
  const auto valid = impl_->validate();

  std::ostringstream stream;
  stream << "{";
  stream << "\"app_id\":\"" << escape_json(impl_->app_id) << "\",";
  stream << "\"frontend_dist\":\"" << escape_json(impl_->frontend.dist_dir.string()) << "\",";
  stream << "\"entry_page\":\"" << escape_json(impl_->frontend.entry_page) << "\",";
  stream << "\"window\":{";
  stream << "\"title\":\"" << escape_json(impl_->window.title) << "\",";
  stream << "\"width\":" << impl_->window.width << ",";
  stream << "\"height\":" << impl_->window.height << ",";
  stream << "\"min_width\":" << impl_->window.min_width << ",";
  stream << "\"min_height\":" << impl_->window.min_height << ",";
  stream << "\"center\":" << (impl_->window.center ? "true" : "false") << ",";
  stream << "\"resizable\":" << (impl_->window.resizable ? "true" : "false") << ",";
  stream << "\"visible\":" << (impl_->window.visible ? "true" : "false");
  stream << "},";
  stream << "\"command_count\":" << impl_->command_handlers.size() << ",";
  stream << "\"startup_callback_count\":" << impl_->startup_callbacks.size() << ",";
  stream << "\"valid\":" << (valid.ok ? "true" : "false");
  stream << "}";
  return stream.str();
}

auto app_builder::run() const -> int {
  const auto valid = impl_->validate();
  if (!valid.ok)
    return 1;

  if (!std::filesystem::exists(impl_->frontend.dist_dir))
    return 1;

  for (const auto& callback : impl_->startup_callbacks)
    callback();

  impl_->events->emit(event_message{
    .topic = "app.started",
    .payload_json = describe(),
  });

  return 0;
}

} // namespace tauri_cpp
