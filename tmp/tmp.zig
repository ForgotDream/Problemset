const std = @import("std");

const stdout = std.Io.getStdOut().writer();

pub fn main() void {
    try stdout.print("hello, world", .{});
}
