#include "extensions/audit_sinks/file/audit_log_file_impl.h"

#include "envoy/data/audit/v2/audit_log.pb.h"

namespace Envoy {
namespace Extensions {
namespace AuditSinks {
namespace File {

using AuditRecord = envoy::data::audit::v2::AuditRecord; 

AuditLogFile::AuditLogFile(const std::string& audit_log_path,
                           LogFileManager& log_file_manager) {
  log_file_ = log_file_manager.createAccessLog(audit_log_path);
}

void AuditLogFile::log(const Audit::ResourceChange& change) {
  std::string json;

  if (change.resource() != nullptr) {
    const auto status = Protobuf::util::MessageToJsonString(*change.resource(), &json);
    RELEASE_ASSERT(status.ok(), "");
  }

  AuditRecord audit_record;
  audit_record.set_operation(change.operation());
  audit_record.set_type_url(change.resourceType());
  audit_record.set_resource_name(change.resourceName());
  audit_record.set_resource(json);
  audit_record.set_version(change.version());

  json.clear();
  const auto status = Protobuf::util::MessageToJsonString(audit_record, &json);
  RELEASE_ASSERT(status.ok(), "");

  log_file_->write(fmt::format("{}\n", json));
}

} // namespace File
} // namespace AuditSinks
} // namespace Extensions
} // namespace Envoy
