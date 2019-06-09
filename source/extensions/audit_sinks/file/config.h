#pragma once

#include "envoy/server/audit_log_config.h"

namespace Envoy {
namespace Extensions {
namespace AuditSinks {
namespace File {

/**
 * Config registration for the file audit log. @see AuditSinkFactory.
 */
class AuditLogFileFactory : public Server::Configuration::AuditSinkFactory {
public:
  Audit::AuditSinkPtr
  createAuditSink(const Protobuf::Message& config, Server::Instance& server) override;

  ProtobufTypes::MessagePtr createEmptyConfigProto() override;

  std::string name() const override;
};

} // namespace File
} // namespace AuditSinks
} // namespace Extensions
} // namespace Envoy
