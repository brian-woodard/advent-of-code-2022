
package main

import "core:fmt"
import "core:os"
import "core:strings"

main :: proc() {
   data, ok := os.read_entire_file("../input.txt", context.allocator)

   score_array := [3][3]u32{
      {4, 8, 3},
      {1, 5, 9},
      {7, 2, 6}
   }

   score2_array := [3][3]u32{
      {3, 4, 8},
      {1, 5, 9},
      {2, 6, 7}
   }

   if !ok {
      fmt.println("Failed to read file")
      return
   }

   score: u32 = 0
   score2: u32 = 0

   it := string(data)
   for line in strings.split_lines_iterator(&it) {
      opp_idx: u32 = u32(line[0]) - u32('A')
      my_idx: u32 = u32(line[2]) - u32('X')
      score += score_array[opp_idx][my_idx]
      score2 += score2_array[opp_idx][my_idx]
   }

   fmt.println("Score: ", score)
   fmt.println("Score2: ", score2)
}