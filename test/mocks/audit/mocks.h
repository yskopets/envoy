#pragma once

#include <memory>
#include <string>

#include "envoy/audit/audit_manager.h"
#include "envoy/audit/auditor.h"

#include "gmock/gmock.h"

namespace Envoy {
namespace Audit {

class MockAuditor : public Auditor {
public:
  MockAuditor();
  ~MockAuditor();

  // Audit::Auditor
  MOCK_METHOD1(observe, void(const ResourceChange& change));
};

class MockAuditManager : public AuditManager {
public:
  MockAuditManager();
  ~MockAuditManager();

  // Audit::Auditor
  MOCK_METHOD1(observe, void(const ResourceChange& change));
  // Audit::AuditManager
  MOCK_METHOD1(addSink, void(AuditSinkPtr&& sink));
};

} // namespace Audit
} // namespace Envoy
