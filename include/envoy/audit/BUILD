licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "audit_common_interface",
    hdrs = ["audit_common.h"],
    deps = [
        "//source/common/protobuf",
    ],
)

envoy_cc_library(
    name = "auditor_interface",
    hdrs = ["auditor.h"],
    deps = [
        ":audit_common_interface",
    ],
)

envoy_cc_library(
    name = "audit_sink_interface",
    hdrs = ["audit_sink.h"],
    deps = [
        ":audit_common_interface",
    ],
)

envoy_cc_library(
    name = "audit_manager_interface",
    hdrs = ["audit_manager.h"],
    deps = [
        ":auditor_interface",
        ":audit_sink_interface",
    ],
)
