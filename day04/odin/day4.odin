package main

import "core:fmt"
import "core:os"
import "core:strings"
import "core:strconv"

main :: proc() {
   num_lines: u32 = 0
   idx: u32 = 0
   num_total_contained: u32 = 0
   num_partial_contained: u32 = 0
   result: [4]uint
   data, ok := os.read_entire_file("../input.txt", context.allocator)

   if !ok {
      fmt.println("Failed to read file ../input.txt")
      return
   }

   it := string(data)
   for line in strings.split_lines_iterator(&it) {
      idx = 0
      for s1 in strings.split(line, ",") {
         for s2 in strings.split(s1, "-") {
            value, parse_ok := strconv.parse_uint(s2)
            if !parse_ok {
               fmt.println("Error parsing ", s2, value)
               return
            }
            result[idx] = value
            idx += 1
         }
      }

      if result[2] >= result[0] && result[3] <= result[1] {
         num_total_contained += 1
      } else if result[0] >= result[2] && result[1] <= result[3] {
         num_total_contained += 1
      }


      if result[0] >= result[2] && result[0] <= result[3] {
         num_partial_contained += 1
      } else if result[1] >= result[2] && result[1] <= result[3] {
         num_partial_contained += 1
      } else if result[2] >= result[0] && result[2] <= result[1] {
         num_partial_contained += 1
      } else if result[3] >= result[0] && result[3] <= result[1] {
         num_partial_contained += 1
      }

      num_lines += 1
   }

   fmt.println("Lines: ", num_lines, num_total_contained, num_partial_contained)
}
