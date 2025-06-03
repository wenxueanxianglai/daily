add_rules("mode.debug", "mode.release")
set_languages("c++20")
add_requires("fmt") 
add_requires("gtest", {system = false })

target("v1_array")
    set_kind("binary")
    add_files("array.cpp")
    add_packages("fmt", "gtest")

target("v1_linked_list")
    set_kind("binary")
    add_files("linked_list.cpp")
    add_packages("fmt", "gtest")

target("v1_list")
    set_kind("binary")
    add_files("my_list.cpp")
    add_packages("fmt", "gtest")

target("v1_stack")
    set_kind("binary")
    add_files("stack.cpp")
    add_packages("fmt", "gtest")

target("v1_linkedlist_stack")
    set_kind("binary")
    add_files("linkedlist_stack.cpp")
    add_packages("fmt", "gtest")