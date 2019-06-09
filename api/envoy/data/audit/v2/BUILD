load("@envoy_api//bazel:api_build_system.bzl", "api_go_proto_library", "api_proto_library_internal")

licenses(["notice"])  # Apache 2

api_proto_library_internal(
    name = "audit_log",
    srcs = ["audit_log.proto"],
    visibility = [
        "//envoy/service/audit/v2:__pkg__",
    ],
    deps = [
        "//envoy/api/v2/core:base",
    ],
)

api_go_proto_library(
    name = "audit_log",
    proto = ":audit_log",
    deps = [
        "//envoy/api/v2/core:base_go_proto",
    ],
)
