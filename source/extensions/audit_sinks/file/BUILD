licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "audit_log_file_lib",
    srcs = ["audit_log_file_impl.cc"],
    hdrs = ["audit_log_file_impl.h"],
    deps = [
        "//include/envoy/access_log:access_log_interface",
        "//include/envoy/audit:audit_sink_interface",
        "@envoy_api//envoy/data/audit/v2:audit_log_cc",
    ],
)

envoy_cc_library(
    name = "config",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    deps = [
        ":audit_log_file_lib",
        "//include/envoy/registry",
        "//include/envoy/server:audit_log_config_interface",
        "//source/common/protobuf",
        "//source/extensions/audit_sinks:well_known_names",
        "@envoy_api//envoy/config/audit/v2:audit_log_file_cc",
    ],
)
