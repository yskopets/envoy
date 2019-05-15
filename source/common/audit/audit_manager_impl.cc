#include "common/audit/audit_manager_impl.h"

namespace Envoy {
namespace Audit {

// Audit::Auditor
void AuditManagerImpl::observe(const ResourceChange& change) {
  // TODO(yskopets)  
  if (change.completed()) {
    for (const auto& sink : sinks_) {
      sink->log(change);
    }
  }
}

// Audit::AuditManager
void AuditManagerImpl::addSink(AuditSinkPtr&& sink) {
  sinks_.emplace_back(std::move(sink));
}

} // namespace Audit
} // namespace Envoy
