#pragma once

#include <list>

#include "envoy/audit/audit_manager.h"

namespace Envoy {
namespace Audit {

class AuditManagerImpl : public AuditManager {
public:
  // Audit::Auditor
  void observe(const ResourceChange& change) override;

  // Audit::Manager
  void addSink(AuditSinkPtr&& sink) override;

private:
  std::list<Audit::AuditSinkPtr> sinks_;
};

} // namespace Audit
} // namespace Envoy
