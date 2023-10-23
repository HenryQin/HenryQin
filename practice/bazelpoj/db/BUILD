load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")


cc_library(
    name = "redisapi",
    srcs = ["redisapi.cpp"],
    hdrs = ["redisapi.h"],
    deps = ["//db/hredis:hredis"],
    copts = ['-std=c++11'],
    visibility = ["//visibility:public"],
    linkstatic = 1
)

cc_library(
    name = "redlock",
    srcs = ["redlock.cpp"],
    hdrs = ["redlock.h"],
    deps = [":redisapi"],
    includes = ["."],
    copts = ['-std=c++11', "-lpthread"],
    visibility = ["//visibility:public"]
)