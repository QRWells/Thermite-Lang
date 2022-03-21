add_defines("SRC")

add_requires("fmt", "llvm")

target("Thermite-Lang")
    set_default(true)
    set_kind("binary")

    add_files("$(curdir)/src/**.cc")

    add_packages("fmt", "llvm")
target_end()