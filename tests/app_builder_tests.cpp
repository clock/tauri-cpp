#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <filesystem>
#include <memory>
#include <string>

#include <doctest/doctest.h>

#include "tauri_cpp/app_builder.hpp"

TEST_CASE("app_builder dispatches registered commands") {
  tauri_cpp::app_builder builder;
  builder.set_frontend({.dist_dir = std::filesystem::current_path(), .entry_page = "index.html"});
  builder.register_command("ping", [](const tauri_cpp::command_request& request) {
    return tauri_cpp::command_response{
      .ok = true,
      .payload_json = request.payload_json,
      .error_message = {},
    };
  });

  const auto response = builder.dispatch_command({
    .command_name = "ping",
    .payload_json = "{\"value\":1}",
  });

  CHECK(response.ok);
  CHECK(response.payload_json == "{\"value\":1}");
}

TEST_CASE("app_builder run validates frontend path") {
  tauri_cpp::app_builder builder;
  builder.set_frontend({.dist_dir = "missing_directory", .entry_page = "index.html"});

  CHECK(builder.run() == 1);
}

TEST_CASE("event_bus emits to matching subscribers") {
  tauri_cpp::event_bus bus;
  auto message_count = 0;
  std::string payload;

  const auto subscription_id = bus.subscribe("demo.ready", [&](const tauri_cpp::event_message& message) {
    ++message_count;
    payload = message.payload_json;
  });

  bus.emit({
    .topic = "demo.ready",
    .payload_json = "{\"ok\":true}",
  });

  bus.unsubscribe(subscription_id);
  bus.emit({
    .topic = "demo.ready",
    .payload_json = "{\"ok\":false}",
  });

  CHECK(message_count == 1);
  CHECK(payload == "{\"ok\":true}");
}
