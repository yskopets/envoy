#pragma once

#include "envoy/audit/audit_common.h"
#include "envoy/common/pure.h"

#include "common/protobuf/protobuf.h"

namespace Envoy {
namespace Audit {

class Auditor {
public:
  virtual ~Auditor() {}

  virtual void observe(const ResourceChange& change) PURE;
};

class RequestedChange {
public:
  virtual ~RequestedChange() {}

  virtual void accept() PURE;
};

class RemoveResource : public virtual ResourceChange, public virtual RequestedChange {
public:
  RemoveResource(const std::string& type_name, const std::string& resource_name)
      : type_name_(type_name), resource_name_(resource_name) {}

  // Audit::OngoingChange
  void accept() override { accepted_ = true; }
  // Audit::ResourceChange
  bool accepted() const override { return accepted_; }
  const std::string& operation() const override { return operation_; }
  const std::string& resourceType() const override { return type_name_; }
  const std::string& resourceName() const override { return resource_name_; }
  const Protobuf::Message* resource() const override { return nullptr; }
  const std::string& version() const override { return version_; }

private:
  const std::string operation_{"delete"};
  const std::string& type_name_;
  const std::string& resource_name_;
  const std::string version_{""};
  bool accepted_{false};
};

class ApplyResource : public virtual ResourceChange, public virtual RequestedChange {
public:
  ApplyResource(const Protobuf::Message& resource, const std::string& resource_name,
                const std::string& version)
      : resource_(resource), resource_name_(resource_name), version_(version) {}

  // Audit::RequestedChange
  void accept() override { accepted_ = true; }
  // Audit::ResourceChange
  bool accepted() const override { return accepted_; }
  const std::string& operation() const override { return operation_; }
  const std::string& resourceType() const override {
    return resource_.GetDescriptor()->full_name();
  }
  const std::string& resourceName() const override { return resource_name_; }
  const Protobuf::Message* resource() const override { return &resource_; }
  const std::string& version() const override { return version_; }

private:
  const std::string operation_{"apply"};
  const Protobuf::Message& resource_;
  const std::string& resource_name_;
  const std::string& version_;
  bool accepted_{false};
};

} // namespace Audit
} // namespace Envoy
