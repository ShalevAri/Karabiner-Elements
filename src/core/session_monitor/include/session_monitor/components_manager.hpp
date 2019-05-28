#pragma once

// `krbn::session_monitor::components_manager` can be used safely in a multi-threaded environment.

#include "monitor/version_monitor.hpp"
#include "session_monitor_receiver_client.hpp"
#include <pqrs/osx/session.hpp>

namespace krbn {
namespace session_monitor {
class components_manager final : public pqrs::dispatcher::extra::dispatcher_client {
public:
  components_manager(const components_manager&) = delete;

  components_manager(std::weak_ptr<version_monitor> weak_version_monitor) : dispatcher_client(),
                                                                            on_console_(false) {
    client_ = std::make_unique<session_monitor_receiver_client>();

    client_->connected.connect([this] {
      send_to_receiver();
    });

    session_monitor_ = std::make_unique<pqrs::osx::session::monitor>(weak_dispatcher_);

    session_monitor_->on_console_changed.connect([this](auto&& on_console) {
      logger::get_logger()->info("on_console_changed: {0}", on_console);

      on_console_ = on_console;
      send_to_receiver();
    });
  }

  virtual ~components_manager(void) {
    detach_from_dispatcher([this] {
      session_monitor_ = nullptr;
      client_ = nullptr;
    });
  }

  void async_start(void) {
    enqueue_to_dispatcher([this] {
      if (client_) {
        client_->async_start();
      }

      if (session_monitor_) {
        session_monitor_->async_start(std::chrono::milliseconds(3000));
      }
    });
  }

private:
  void send_to_receiver(void) const {
    if (client_) {
      client_->async_console_user_id_changed(getuid(), on_console_);
    }
  }

  bool on_console_;
  std::unique_ptr<session_monitor_receiver_client> client_;
  std::unique_ptr<pqrs::osx::session::monitor> session_monitor_;
};
} // namespace session_monitor
} // namespace krbn