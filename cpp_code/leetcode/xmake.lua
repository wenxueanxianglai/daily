add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"})

add_rules("mode.debug", "mode.release")


add_requires("fmt") 
add_requires("gtest", {system = false})

function add_test_target(target_name, cpp_file)
    target(target_name)
        set_kind("binary")
        add_files(cpp_file)
        add_packages("fmt", "gtest")
end

add_test_target("test_two_sum", "1_two_sum.cpp")