#include "tauri_cpp/event_bus.hpp"

#include <algorithm>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace tauri_cpp {

class event_bus::impl {
public:
  auto subscribe(std::string topic, event_handler handler) -> std::size_t {
    std::scoped_lock lock(mutex_);

    const auto subscription_id = next_subscription_id_++;
    subscriptions_.emplace(subscription_id, subscription{
                                            .topic = std::move(topic),
                                            .handler = std::move(handler),
                                          });
    return subscription_id;
  }

  void unsubscribe(const std::size_t subscription_id) {
    std::scoped_lock lock(mutex_);
    subscriptions_.erase(subscription_id);
  }

  void emit(const event_message& message) const {
    std::vector<event_handler> handlers;

    {
      std::scoped_lock lock(mutex_);

      for (const auto& [subscription_id, subscription] : subscriptions_) {
        static_cast<void>(subscription_id);
        if (subscription.topic != message.topic)
          continue;

        handlers.push_back(subscription.handler);
      }
    }

    for (const auto& handler : handlers)
      handler(message);
  }

private:
  struct subscription {
    std::string topic;
    event_handler handler;
  };

  mutable std::mutex mutex_;
  std::size_t next_subscription_id_ = 1;
  std::unordered_map<std::size_t, subscription> subscriptions_;
};

event_bus::event_bus() : impl_(std::make_shared<impl>()) {}

event_bus::~event_bus() = default;

event_bus::event_bus(const event_bus&) = default;

event_bus::event_bus(event_bus&&) noexcept = default;

auto event_bus::operator=(const event_bus&) -> event_bus& = default;

auto event_bus::operator=(event_bus&&) noexcept -> event_bus& = default;

auto event_bus::subscribe(std::string topic, event_handler handler) -> std::size_t {
  return impl_->subscribe(std::move(topic), std::move(handler));
}

void event_bus::unsubscribe(const std::size_t subscription_id) {
  impl_->unsubscribe(subscription_id);
}

void event_bus::emit(event_message message) const {
  impl_->emit(message);
}

} // namespace tauri_cpp
