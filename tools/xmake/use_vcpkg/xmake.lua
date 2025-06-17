add_rules("mode.debug", "mode.release")

-- 设置语言标准
set_languages("c++17")

-- 使用 vcpkg 安装 boost 和 fmt
--add_requires("vcpkg::boost", {alias = "boost"})
add_requires("vcpkg::fmt", {alias = "fmt", system = false})
--add_requires("vcpkg::protobuf", {alias = "protobuf", system = false})
add_requires("vcpkg::protobuf", {system = false})

rule("protobuf_cpp")
    set_extensions(".proto")
    after_load(function (target) 
       target:data_set("outdir", "proto/generated") 
    end)
    
    on_buildcmd_file(function (target, batchcmds, sourcefile_proto, opt)
        import("core.project.depend")
        import("lib.detect.find_tool")

        local proto_file = path.filename(sourcefile_proto)
        local fileconfig = path.directory(path.absolute(sourcefile_proto))
        print("fileconfig: ", fileconfig)
        local outputdir = path.absolute(target:data("outdir"))
        print("out_dir : ", outputdir)
  

        local protoc_path = path.join(os.getenv("VCPKG_ROOT"), "installed", "x64-linux", "tools", "protobuf")
        local protoc = find_tool("protoc", {paths= protoc_path})
        if not protoc then
            raise("protoc not found")
        end
        batchcmds:mkdir(outputdir)
        
        batchcmds:execv(protoc.program, {"--cpp_out=".. outputdir,  "--proto_path=".. fileconfig, proto_file })
    end)

target("use_vcpkg")
    set_kind("binary")
    add_rules("protobuf_cpp", {outdir="proto/generated"})
    add_files("proto/*.proto")
    add_files("src/*.cpp")
    add_packages("vcpkg::protobuf", "fmt")



--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

