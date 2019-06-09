#pragma once

#include <string>

#include "common/singleton/const_singleton.h"

namespace Envoy {
namespace Extensions {
namespace AuditSinks {

/**
 * Well-known Audit sink names.
 */
class AuditSinkNameValues {
public:
  // File sink
  const std::string File = "envoy.audit_sinks.file";
  // AuditLogService sink
  const std::string AuditLogService = "envoy.audit_sinks.audit_log_service";
};

typedef ConstSingleton<AuditSinkNameValues> AuditSinkNames;

} // namespace AuditSinks
} // namespace Extensions
} // namespace Envoy
