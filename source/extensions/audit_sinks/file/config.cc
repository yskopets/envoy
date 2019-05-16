#include "extensions/audit_sinks/file/config.h"

#include <memory>

#include "envoy/config/audit/v2/audit_log_file.pb.validate.h"
#include "envoy/registry/registry.h"

#include "common/protobuf/protobuf.h"

#include "extensions/audit_sinks/file/audit_log_file_impl.h"
#include "extensions/audit_sinks/well_known_names.h"

namespace Envoy {
namespace Extensions {
namespace AuditSinks {
namespace File {

Audit::AuditSinkPtr
AuditLogFileFactory::createAuditSink(const Protobuf::Message& config, 
                                        Server::Instance& server) {
  const auto& fal_config =
      MessageUtil::downcastAndValidate<const envoy::config::audit::v2::AuditLogFile&>(config);

  return std::make_unique<AuditLogFile>(fal_config.path(), server.accessLogManager());
}

ProtobufTypes::MessagePtr AuditLogFileFactory::createEmptyConfigProto() {
  return ProtobufTypes::MessagePtr{new envoy::config::audit::v2::AuditLogFile()};
}

std::string AuditLogFileFactory::name() const { return AuditSinkNames::get().File; }

/**
 * Static registration for the file audit log. @see RegisterFactory.
 */
REGISTER_FACTORY(AuditLogFileFactory, Server::Configuration::AuditSinkFactory);

} // namespace File
} // namespace AuditSinks
} // namespace Extensions
} // namespace Envoy
