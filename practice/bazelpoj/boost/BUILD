load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_import")

cc_import(
      name = "import_boost_system",
      hdrs = glob(["include/boost/**"]),
      static_library = "lib/libboost_system.a",
      visibility = ["//visibility:public"],
      alwayslink = 1
)


cc_library(
      name = "boost_system",
      srcs = [],
      hdrs = [],
      includes = ["include"],
      deps = [":import_boost_system"],
      visibility = ["//visibility:public"]
)