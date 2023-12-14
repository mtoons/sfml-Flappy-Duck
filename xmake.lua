---@diagnostic disable: undefined-global
-- TODO: Port this shit to zig build + real package mananger
add_rules("mode.debug", "mode.release")

if is_mode("release") then
    set_optimize("fastest")
    add_defines("RELEASE")
elseif is_mode("debug") then
    add_defines("DEBUG")
end

add_requires("sfml")

add_includedirs("include")

target("sfmlFlappyBird")
set_kind("binary")
add_files("src/*.cc")

add_packages("sfml")
