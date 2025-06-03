add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"})

add_rules("mode.debug", "mode.release")
-- set_languages("c++20")
-- add_requires("fmt") 
-- add_requires("gtest", {system = false })

includes("src/v1")

-- target("v1_array")
--     set_kind("binary")
--     add_files("src/v1/array.cpp")
--     add_packages("fmt", "gtest")

-- target("v1_linked_list")
--     set_kind("binary")
--     add_files("src/v1/linked_list.cpp")
--     add_packages("fmt", "gtest")