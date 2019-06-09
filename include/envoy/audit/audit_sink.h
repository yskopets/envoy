#pragma once

#include <functional>
#include <memory>

#include "envoy/audit/audit_common.h"
#include "envoy/common/pure.h"

namespace Envoy {
namespace Audit {

/**
 * A sink for Audit records.
 */
class AuditSink {
public:
  virtual ~AuditSink() {}

  virtual void log(const ResourceChange& change) PURE;
};

typedef std::unique_ptr<AuditSink> AuditSinkPtr;

} // namespace Audit
} // namespace Envoy
