licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "address_interface",
    hdrs = ["address.h"],
    deps = [
        ":io_handle_interface",
        "//include/envoy/api:os_sys_calls_interface",
    ],
)

envoy_cc_library(
    name = "connection_interface",
    hdrs = ["connection.h"],
    external_deps = ["abseil_int128"],
    deps = [
        ":address_interface",
        ":filter_interface",
        ":listen_socket_interface",
        "//include/envoy/buffer:buffer_interface",
        "//include/envoy/event:deferred_deletable",
        "//include/envoy/ssl:connection_interface",
        "//include/envoy/stream_info:stream_info_interface",
    ],
)

envoy_cc_library(
    name = "connection_handler_interface",
    hdrs = ["connection_handler.h"],
    deps = [
        ":listen_socket_interface",
        ":listener_interface",
        "//include/envoy/ssl:context_interface",
    ],
)

envoy_cc_library(
    name = "dns_interface",
    hdrs = ["dns.h"],
    deps = ["//include/envoy/network:address_interface"],
)

envoy_cc_library(
    name = "drain_decision_interface",
    hdrs = ["drain_decision.h"],
)

envoy_cc_library(
    name = "filter_interface",
    hdrs = ["filter.h"],
    deps = [
        ":listen_socket_interface",
        ":transport_socket_interface",
        "//include/envoy/buffer:buffer_interface",
        "//include/envoy/upstream:host_description_interface",
    ],
)

envoy_cc_library(
    name = "hash_policy_interface",
    hdrs = ["hash_policy.h"],
    external_deps = ["abseil_optional"],
    deps = [
        ":address_interface",
    ],
)

envoy_cc_library(
    name = "io_handle_interface",
    hdrs = ["io_handle.h"],
    deps = [
        "//include/envoy/api:io_error_interface",
        "//source/common/common:assert_lib",
    ],
)

envoy_cc_library(
    name = "listen_socket_interface",
    hdrs = ["listen_socket.h"],
    deps = [
        ":address_interface",
        ":io_handle_interface",
        "@envoy_api//envoy/api/v2/core:pkg_cc_proto",
    ],
)

envoy_cc_library(
    name = "transport_socket_interface",
    hdrs = ["transport_socket.h"],
    deps = [
        ":io_handle_interface",
        "//include/envoy/buffer:buffer_interface",
        "//include/envoy/ssl:connection_interface",
    ],
)

envoy_cc_library(
    name = "connection_balancer_interface",
    hdrs = ["connection_balancer.h"],
    deps = [
        ":listen_socket_interface",
    ],
)

envoy_cc_library(
    name = "listener_interface",
    hdrs = ["listener.h"],
    deps = [
        ":connection_balancer_interface",
        ":connection_interface",
        ":listen_socket_interface",
        "//include/envoy/stats:stats_interface",
        "@envoy_api//envoy/api/v2:pkg_cc_proto",
    ],
)

envoy_cc_library(
    name = "resolver_interface",
    hdrs = ["resolver.h"],
    deps = [
        ":address_interface",
        "@envoy_api//envoy/api/v2/core:pkg_cc_proto",
    ],
)
