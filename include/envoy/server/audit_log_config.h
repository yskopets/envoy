#pragma once

#include <string>

#include "envoy/audit/audit_sink.h"
#include "envoy/server/instance.h"

#include "common/protobuf/protobuf.h"

namespace Envoy {
namespace Server {
namespace Configuration {

/**
 * Implemented for each Audit::AuditSink and registered via Registry::registerFactory() or
 * the convenience class RegisterFactory.
 */
class AuditSinkFactory {
public:
  virtual ~AuditSinkFactory() {}

  /**
   * Create a particular Audit::AuditSink implementation. If the implementation is unable to produce
   * an Audit::AuditSink with the provided parameters, it should throw an EnvoyException. The returned
   * pointer should always be valid.
   * @param config supplies the custom proto configuration for the Audit::AuditSink
   * @param server supplies the server instance
   */
  virtual Audit::AuditSinkPtr createAuditSink(const Protobuf::Message& config, Instance& server) PURE;

  /**
   * @return ProtobufTypes::MessagePtr create empty config proto message for v2. The filter
   *         config, which arrives in an opaque google.protobuf.Struct message, will be converted to
   *         JSON and then parsed into this empty proto.
   */
  virtual ProtobufTypes::MessagePtr createEmptyConfigProto() PURE;

  /**
   * Returns the identifying name for a particular implementation of Audit::AuditSink produced by the
   * factory.
   */
  virtual std::string name() const PURE;
};

} // namespace Configuration
} // namespace Server
} // namespace Envoy
