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

class OngoingChange {
public:
  virtual ~OngoingChange() {}  

  virtual void complete() PURE;  
};

class RemoveResource : public virtual ResourceChange, public virtual OngoingChange {
public:
  RemoveResource(const std::string& type_name, const std::string& resource_name,
  const std::string& version) 
  : type_name_(type_name), resource_name_(resource_name), version_(version) {}

  // Audit::OngoingChange
  void complete() override { complete_ = true; }
  // Audit::ResourceChange
  bool completed() const override { return complete_; }
  const std::string& operation() const override { return operation_; }
  const std::string& resourceType() const override { return type_name_; }
  const std::string& resourceName() const override { return resource_name_; }
  const Protobuf::Message* resource() const override { return nullptr; }
  const std::string& version() const override { return version_; }

private:
  const std::string operation_{"Remove"};
  const std::string& type_name_;
  const std::string& resource_name_;
  const std::string& version_;
  bool complete_{false};
};

class AddOrUpdateResource : public virtual ResourceChange, public virtual OngoingChange {
public:
  AddOrUpdateResource(const Protobuf::Message& resource, const std::string& resource_name,
  const std::string& version) 
  : resource_(resource), resource_name_(resource_name), version_(version) {}

  // Audit::OngoingChange
  void complete() override { complete_ = true; }
  // Audit::ResourceChange
  bool completed() const override { return complete_; }
  const std::string& operation() const override { return operation_; }
  const std::string& resourceType() const override { return resource_.GetDescriptor()->full_name(); }
  const std::string& resourceName() const override { return resource_name_; }
  const Protobuf::Message* resource() const override { return &resource_; }
  const std::string& version() const override { return version_; }

private:
  const std::string operation_{"AddOrUpdate"};
  const Protobuf::Message& resource_;
  const std::string& resource_name_;
  const std::string& version_;
  bool complete_{false};
};

} // namespace Audit
} // namespace Envoy
