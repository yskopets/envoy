#pragma once

#include "envoy/common/pure.h"

#include "common/protobuf/protobuf.h"

namespace Envoy {
namespace Audit {

class Event {
public:
  virtual ~Event() {}
};

class ResourceChange : public virtual Event {
public:
  virtual bool accepted() const PURE;
  // TODO(yskopets) Enum ???
  virtual const std::string& operation() const PURE;
  virtual const std::string& resourceType() const PURE;
  virtual const std::string& resourceName() const PURE;
  virtual const Protobuf::Message* resource() const PURE;
  virtual const std::string& version() const PURE;
};

} // namespace Audit
} // namespace Envoy
