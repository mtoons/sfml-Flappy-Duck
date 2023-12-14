const std = @import("std");
fn linkSFML(b: *std.build.Builder, exe: *std.build.Step.Compile, link_static: bool) void {
    const SFML_LIB_NAMES: []const []const u8 = &.{
        "audio",
        "graphics",
        "network",
        "system",
        "window",
    };

    for (SFML_LIB_NAMES) |libname| {
        const lib_name_2 = b.fmt("sfml-{s}{s}", .{ libname, if (link_static) "-s" else "" });
        exe.linkSystemLibrary(lib_name_2);
    }
}

pub fn build(b: *std.build.Builder) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "default",
        .target = target,
        .optimize = optimize,
    });
    exe.linkLibC();
    exe.linkLibCpp();
    // Add your .addIncludeDir or .linkLibrary here

    const build_sfml = b.addSystemCommand(
        &[_][]const u8{
            "make",
            "-C",
            "./lib/SFML-2.6.1",
        },
    );
    _ = build_sfml;

    // const make_step = b.step("sfml", "Build sfml");
    // make_step.dependOn(&build_sfml.step);
    //
    // // NOTE: you need to run `zig build sfml` before build/run will work
    // exe.addIncludePath(.{ .path = "lib/SFML-2.6.1/bin" });
    // exe.addIncludePath(.{ .path = "lib/SFML-2.6.1/src" });
    // exe.linkSystemLibrary(.{ .path = "sfml" });

    exe.addIncludePath(std.build.LazyPath{ .path = "lib/SFML-2.6.1/include" });
    exe.addLibraryPath(std.build.LazyPath{ .path = "lib/SFML-2.6.1/lib" });
    exe.addLibraryPath(std.build.LazyPath{ .path = "lib/SFML-2.6.1/bin" });
    linkSFML(b, exe, false);

    // exe.addLibraryPath(std.build.LazyPath{ .path = "lib/SFML-2.6.1/bin" });
    // exe.linkSystemLibrary("sfml-main");
    // exe.linkSystemLibrary("sfml-system-s");
    // exe.linkSystemLibrary("sfml-graphics-s");
    // exe.linkSystemLibrary("sfml-window-s");
    // exe.linkSystemLibrary("sfml-audio-s");
    // exe.linkSystemLibrary("sfml-network-s");

    // exe.linkSystemLibrary("FLAC");
    // exe.linkSystemLibrary("freetype");
    // exe.linkSystemLibrary("ogg");
    // exe.linkSystemLibrary("openal32");
    // exe.linkSystemLibrary("vorbis");
    // exe.linkSystemLibrary("vorbisenc");
    // exe.linkSystemLibrary("vorbisfile");
    // exe.linkSystemLibrary("sfml-main");
    // exe.linkSystemLibrary("sfml-system");
    // exe.linkSystemLibrary("sfml-graphics");
    // exe.linkSystemLibrary("sfml-window");
    // exe.linkSystemLibrary("sfml-audio");
    // exe.linkSystemLibrary("sfml-network");
    //
    // exe.linkSystemLibrary("sfml-graphics-s");
    // exe.linkSystemLibrary("sfml-window-s");
    // exe.linkSystemLibrary("sfml-system-s");
    // exe.linkSystemLibrary("sfml-audio-s");
    // exe.linkSystemLibrary("sfml-network-s");
    //
    // exe.linkSystemLibrary("sfml-main-d");
    // exe.linkSystemLibrary("sfml-graphics-d");
    // exe.linkSystemLibrary("sfml-window-d");
    // exe.linkSystemLibrary("sfml-system-d");
    // exe.linkSystemLibrary("sfml-audio-d");
    // exe.linkSystemLibrary("sfml-network-d");
    //
    // exe.linkSystemLibrary("sfml-graphics-s-d");
    // exe.linkSystemLibrary("sfml-window-s-d");
    // exe.linkSystemLibrary("sfml-system-s-d");
    // exe.linkSystemLibrary("sfml-audio-s-d");
    // exe.linkSystemLibrary("sfml-network-s-d");

    // exe.linkSystemLibrary("openal32");
    // exe.linkSystemLibrary("sfml-audio-2");
    // exe.linkSystemLibrary("sfml-audio-d-2");
    // exe.linkSystemLibrary("sfml-graphics-2");
    // exe.linkSystemLibrary("sfml-graphics-d-2");
    // exe.linkSystemLibrary("sfml-network-2");
    // exe.linkSystemLibrary("sfml-network-d-2");
    // exe.linkSystemLibrary("sfml-system-2");
    // exe.linkSystemLibrary("sfml-system-d-2");
    // exe.linkSystemLibrary("sfml-window-2");
    // exe.linkSystemLibrary("sfml-window-d-2");

    exe.addIncludePath(.{ .path = "include" });
    exe.addCSourceFiles(.{
        .files = &.{
            "src/main.cc",
            "src/player.cc",
            "src/pipe.cc",
        },
        .flags = &.{
            "-std=c++20",
            "-L lib/sfml",
            // "-MJ compile_commands.json", // don't work at time of writting
        },
    });

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
