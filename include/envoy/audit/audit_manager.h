#pragma once

#include <memory>

#include "envoy/audit/auditor.h"
#include "envoy/audit/audit_sink.h"

#include "envoy/common/pure.h"

namespace Envoy {
namespace Audit {

/**
 * TODO(yskopets)
 */
class AuditManager : public virtual Auditor {
public:
  virtual ~AuditManager() {}

  /**
   * TODO(yskopets)
   */ 
  virtual void addSink(AuditSinkPtr&& sink) PURE;
};

typedef std::unique_ptr<AuditManager> AuditManagerPtr;

} // namespace Audit
} // namespace Envoy
