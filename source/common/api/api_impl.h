#pragma once

#include <chrono>
#include <string>

#include "envoy/api/api.h"
#include "envoy/event/timer.h"
#include "envoy/filesystem/filesystem.h"
#include "envoy/thread/thread.h"

namespace Envoy {
namespace Api {

/**
 * Implementation of Api::Api
 */
class Impl : public Api {
public:
  Impl(Thread::ThreadFactory& thread_factory, Stats::Store&, Event::TimeSystem& time_system,
       Filesystem::Instance& file_system, Audit::Auditor& auditor);

  // Api::Api
  Event::DispatcherPtr allocateDispatcher() override;
  Event::DispatcherPtr allocateDispatcher(Buffer::WatermarkFactoryPtr&& watermark_factory) override;
  Thread::ThreadFactory& threadFactory() override { return thread_factory_; }
  Filesystem::Instance& fileSystem() override { return file_system_; }
  TimeSource& timeSource() override { return time_system_; }
  Audit::Auditor& auditor() override { return auditor_; }

private:
  Thread::ThreadFactory& thread_factory_;
  Event::TimeSystem& time_system_;
  Filesystem::Instance& file_system_;
  Audit::Auditor& auditor_;
};

} // namespace Api
} // namespace Envoy
