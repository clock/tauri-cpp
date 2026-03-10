#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <string>

namespace tauri_cpp {

struct event_message {
  std::string topic;
  std::string payload_json;
};

using event_handler = std::function<void(const event_message&)>;

class event_bus {
public:
  event_bus();
  ~event_bus();

  event_bus(const event_bus&);
  event_bus(event_bus&&) noexcept;
  auto operator=(const event_bus&) -> event_bus&;
  auto operator=(event_bus&&) noexcept -> event_bus&;

  auto subscribe(std::string topic, event_handler handler) -> std::size_t;
  void unsubscribe(std::size_t subscription_id);
  void emit(event_message message) const;

private:
  class impl;
  std::shared_ptr<impl> impl_;
};

} // namespace tauri_cpp
