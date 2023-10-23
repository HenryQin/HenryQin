load("@rules_proto//proto:defs.bzl", "proto_library")


cc_proto_library(
    name = "addressbook_cc_proto",
    deps = [":addressbook_proto"],
)

proto_library(
    name = "addressbook_proto",
    srcs = ["addressbook.proto"],
)

package(default_visibility = ["//visibility:public"]) 