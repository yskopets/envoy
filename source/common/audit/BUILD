licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "audit_manager_lib",
    srcs = ["audit_manager_impl.cc"],
    hdrs = ["audit_manager_impl.h"],
    deps = [
        "//include/envoy/audit:audit_manager_interface",
    ],
)
