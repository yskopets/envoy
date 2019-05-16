load("@envoy_api//bazel:api_build_system.bzl", "api_go_grpc_library", "api_proto_library_internal")

licenses(["notice"])  # Apache 2

api_proto_library_internal(
    name = "audit_log_service",
    srcs = ["audit_log_service.proto"],
    has_services = 1,
    deps = [
        "//envoy/api/v2/core:base",
        "//envoy/api/v2/core:grpc_service",
        "//envoy/data/audit/v2:audit_log",
    ],
)

api_go_grpc_library(
    name = "audit_log_service",
    proto = ":audit_log_service",
    deps = [
        "//envoy/api/v2/core:base_go_proto",
        "//envoy/data/audit/v2:audit_log_go_proto",
    ],
)
