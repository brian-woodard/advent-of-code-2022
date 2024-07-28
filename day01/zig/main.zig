const std = @import("std");

pub fn main() !void {
    const out = std.io.getStdOut().writer();
    const input: []const u8 = "../input.txt";
    var in_file = try std.fs.cwd().openFile(input, .{});
    defer in_file.close();

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var calories: u32 = 0;
    var cur_calories: u32 = 0;
    var max_calories = [_]u32{0} ** 3;

    const buffer = try in_file.readToEndAlloc(arena.allocator(), 65536);

    try out.print("Read file {s} bytes {d} {d}\n", .{ input, arena.queryCapacity(), buffer.len });

    //var i: usize = 0;
    // while (i < 10) : (i += 1) {
    //     std.debug.print("{d}: {d}\n", .{ i, buffer[i] });
    // }

    var it = std.mem.split(u8, buffer, "\r\n");
    while (it.next()) |calories_str| {
        calories = std.fmt.parseInt(u32, calories_str, 10) catch 0;

        if (calories == 0) {
            if (cur_calories > max_calories[0]) {
                max_calories[2] = max_calories[1];
                max_calories[1] = max_calories[0];
                max_calories[0] = cur_calories;
            } else if (cur_calories > max_calories[1]) {
                max_calories[2] = max_calories[1];
                max_calories[1] = cur_calories;
            } else if (cur_calories > max_calories[2]) {
                max_calories[2] = cur_calories;
            }
            cur_calories = 0;
        } else {
            cur_calories += calories;
        }
    }

    try out.print("Most calories: {d}\n", .{max_calories[0]});
    try out.print("2nd Most calories: {d}\n", .{max_calories[1]});
    try out.print("3rd Most calories: {d}\n", .{max_calories[2]});

    try out.print("Total: {d}\n", .{max_calories[0] + max_calories[1] + max_calories[2]});
}
