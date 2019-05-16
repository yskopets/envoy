#pragma once

#include "envoy/access_log/access_log.h"
#include "envoy/audit/audit_sink.h"

namespace Envoy {
namespace Extensions {
namespace AuditSinks {
namespace File {

using LogFileManager = AccessLog::AccessLogManager;
using LogFileSharedPtr = AccessLog::AccessLogFileSharedPtr;

/**
 * Audit Log sink that writes log entries to a file.
 */
class AuditLogFile : public Audit::AuditSink {
public:
  AuditLogFile(const std::string& audit_log_path, LogFileManager& log_file_manager);

  // Audit::AuditSink
  void log(const Audit::ResourceChange& change) override;

private:
  LogFileSharedPtr log_file_;
};

} // namespace File
} // namespace AuditSinks
} // namespace Extensions
} // namespace Envoy
