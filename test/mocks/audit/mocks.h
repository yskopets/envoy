#pragma once

#include <memory>
#include <string>

#include "envoy/audit/auditor.h"
#include "envoy/audit/audit_manager.h"

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

} // namespace Audit
} // namespace Envoy
