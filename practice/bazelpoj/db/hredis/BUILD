load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_import")

cc_import(
      name = "hredis",
      hdrs = glob(["include/*.h", "include/adapters/*.h"]),
      static_library = "lib/libhiredis.a",
      visibility = ["//visibility:public"],
      linkopts = ["-fPIC"]
)

cc_library(
    name = "hredis_lib",
    srcs = [],
    hdrs = glob(["include/**/*.h"]),
    linkopts = ["-Llib"],
    visibility = ["//visibility:public"],
)


cc_binary (
    name = "test",
    srcs = ["test.cpp"],
    deps = [":hredis"],
    copts = ["--std=c++11" , "-Werror"],
    linkstatic = 1,
)