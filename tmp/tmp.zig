const std = @import("std");

/// A high-performance standard I/O wrapper built for Competitive Programming
/// in Zig 0.16.0. It leverages the injected `std.Io` backend and the built-in Arena.
pub const CpIO = struct {
    allocator: std.mem.Allocator,
    in_reader: *std.Io.Reader,
    out_writer: *std.Io.Writer,

    /// Initializes buffered stdin and stdout using the application's injected I/O.
    pub fn init(init_args: std.process.Init) !CpIO {
        const io = init_args.io;
        
        const alloc = init_args.arena.allocator();
        
        const in_buf = try alloc.alloc(u8, 65536); // 64KB read buffer
        const reader_impl = try alloc.create(std.Io.File.Reader);
        reader_impl.* = std.Io.File.stdin().reader(io, in_buf);

        const out_buf = try alloc.alloc(u8, 65536); // 64KB write buffer
        const writer_impl = try alloc.create(std.Io.File.Writer);
        writer_impl.* = std.Io.File.stdout().writer(io, out_buf);

        return .{
            .allocator = alloc,
            .in_reader = &reader_impl.interface,
            .out_writer = &writer_impl.interface,
        };
    }

    /// Flushes the standard output buffer. MUST be called before program exits!
    pub fn flush(self: *CpIO) !void {
        try self.out_writer.flush();
    }

    /// Prints formatted data to stdout
    pub fn print(self: *CpIO, comptime fmt: []const u8, args: anytype) !void {
        try self.out_writer.print(fmt, args);
    }

    /// Reads the next whitespace-separated token. 
    /// The returned string slice lives in the Arena, making it fast and safe to hold onto.
    pub fn next(self: *CpIO) !?[]const u8 {
        var list = std.ArrayListUnmanaged(u8){};
        
        var byte: u8 = undefined;
        while (true) {
            byte = self.in_reader.readByte() catch |err| switch (err) {
                error.EndOfStream => return null,
                else => return err,
            };
            if (!std.ascii.isWhitespace(byte)) {
                try list.append(self.allocator, byte);
                break;
            }
        }
        
        while (true) {
            byte = self.in_reader.readByte() catch |err| switch (err) {
                error.EndOfStream => break,
                else => return err,
            };
            if (std.ascii.isWhitespace(byte)) break;
            try list.append(self.allocator, byte);
        }
        
        return list.items;
    }

    /// Reads and parses the next token as an integer
    pub fn nextInt(self: *CpIO, comptime T: type) !T {
        const token = (try self.next()) orelse return error.EndOfInput;
        return try std.fmt.parseInt(T, token, 10);
    }

    /// Reads and parses the next token as a float
    pub fn nextFloat(self: *CpIO, comptime T: type) !T {
        const token = (try self.next()) orelse return error.EndOfInput;
        return try std.fmt.parseFloat(T, token);
    }
};

pub fn solve(n: u32) !void {

}

pub fn main(init: std.process.Init) !void {
    var io = try CpIO.init(init);

    defer io.flush() catch {};

    const t = try io.nextInt(u32);
    
    for (0..t) |_| {
        const n = try io.nextInt(u32);
        solve(n);
    }
}

