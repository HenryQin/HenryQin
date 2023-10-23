load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_import");

cc_library(
    name = "colib",
    srcs = [
        "co_epoll.cpp",
        "co_hook_sys_call.cpp",
        "co_routine.cpp",
        "coctx.cpp",
        "coctx_swap.S",
        "co_comm.cpp"
    ],
    hdrs = [
        "co_closure.h",
        "co_comm.h",
        "co_epoll.h",
        "co_routine_inner.h",
        "co_routine_specific.h",
        "coctx.h",
        'co_routine.h',
    ],
    includes = ['.'],
    deps = [
    ],
    copts = [
        "-DLINUX",
        "-D_PTHREADS",
        "-DTIXML_USE_STL",
        "--std=c++11",
    ],
    linkopts = [
        "-ldl",
        "-lpthread",
    ],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "example_specific",
    srcs = [
        "example_specific.cpp"
    ],
    deps = [
        ":colib"
    ],
    copts = [
        "--std=c++11"
    ]
)