load("@envoy_api//bazel:api_build_system.bzl", "api_go_proto_library", "api_proto_library_internal")

licenses(["notice"])  # Apache 2

api_proto_library_internal(
    name = "audit_log_service",
    srcs = ["audit_log_service.proto"],
    visibility = [
        "//envoy/config/bootstrap/v2:__pkg__",
    ],
    deps = [
        "//envoy/api/v2/core:grpc_service",
    ],
)

api_go_proto_library(
    name = "audit_log_service",
    proto = ":audit_log_service",
    deps = [
        "//envoy/api/v2/core:grpc_service_go_proto",
    ],
)

api_proto_library_internal(
    name = "audit_log_file",
    srcs = ["audit_log_file.proto"],
    visibility = [
        "//envoy/config/bootstrap/v2:__pkg__",
    ],
)

api_go_proto_library(
    name = "audit_log_file",
    proto = ":audit_log_file",
    deps = [
    ],
)

api_proto_library_internal(
    name = "audit",
    srcs = ["audit.proto"],
    visibility = [
        "//envoy/config/bootstrap/v2:__pkg__",
    ],
    deps = [
    ],
)

api_go_proto_library(
    name = "audit",
    proto = ":audit",
    deps = [
    ],
)
