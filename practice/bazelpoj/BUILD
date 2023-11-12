load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "runredlock",
    srcs = ["redlock_test.cpp"],
    deps = [
        "//db:redisapi",
        "//db:redlock",
        "//proto:addressbook_cc_proto",
    ],
    copts = ["--std=c++11", "-lpthread"]
)

cc_binary(
    name = "routine",
    srcs = [
      "routine.cpp"
    ],
    deps = [
      "//boost:boost_system"
    ],
    copts = ["--std=c++20", "-fcoroutines"],
    linkopts = [
          
    ]
)

cc_binary(
    name = "async_routine",
    srcs = [
      "async_routine.cpp"
    ],
    deps = [
    ],
    copts = ["--std=c++20", "-fcoroutines"],
    linkopts = [
      "-lpthread"
    ]
)

cc_binary(
    name = "awaitable_future",
    srcs = [
      "awaitable_future.cpp"
    ],
    deps = [
    ],
    copts = ["--std=c++20", "-fcoroutines"],
    linkopts = [
      "-lpthread"
    ]
)

cc_binary(
    name = "runlibco",
    srcs = [
      "runlibco.cpp"
    ],
    deps = [
      "//libco:colib",
      "//db:redisapi" 
    ],
    copts = ["--std=c++11"]
)



load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
refresh_compile_commands(
    name = "refresh_compile_commands",

    # Specify the targets of interest.
    # For example, specify a dict of targets and any flags required to build.
    targets = {
      "//:runredlock": "",
      "//:routine": "",
      "//:async_routine":""
    },
    # No need to add flags already in .bazelrc. They're automatically picked up.
    # If you don't need flags, a list of targets is also okay, as is a single target string.
    # Wildcard patterns, like //... for everything, *are* allowed here, just like a build.
      # As are additional targets (+) and subtractions (-), like in bazel query https://docs.bazel.build/versions/main/query.html#expressions
    # And if you're working on a header-only library, specify a test or binary target that compiles it.
)