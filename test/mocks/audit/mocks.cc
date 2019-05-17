#include "test/mocks/audit/mocks.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::_;
using testing::Return;
using testing::ReturnRef;

namespace Envoy {
namespace Audit {

MockAuditor::MockAuditor() {}
MockAuditor::~MockAuditor() {}

} // namespace Audit
} // namespace Envoy
