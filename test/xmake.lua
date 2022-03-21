add_defines("TEST")

target("Lexer-Test")
    set_kind("binary")
    set_group("test")

    add_files("$(curdir)/test/Lexer-Test/**.cc");
    add_files("$(curdir)/src/**.cc")
    remove_files("$(curdir)/src/main.cc")

    add_packages("fmt", "llvm")
target_end()

target("Parser-Test")
    set_kind("binary")
    set_group("test")

    add_files("$(curdir)/test/Parser-Test/**.cc");
    add_files("$(curdir)/src/**.cc")
    remove_files("$(curdir)/src/main.cc")

    add_packages("fmt", "llvm")
target_end()
