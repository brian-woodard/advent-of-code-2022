package main

import "core:fmt"
import "core:os"
import "core:strings"

main :: proc() {
   num_lines: u32 = 0
   score: u32 = 0
   lines_array: [3]string
   data, ok := os.read_entire_file("../input.txt", context.allocator)

   if !ok {
      fmt.println("Failed to read file ../input.txt")
      return
   }

   it := string(data)
   for line in strings.split_lines_iterator(&it) {
      idx: u32 = num_lines % 3
      lines_array[idx] = line

      if idx == 2 {
         found := false

         for c1 in lines_array[0] {
            for c2 in lines_array[1] {
               if c1 == c2 {
                  for c3 in lines_array[2] {
                     if c1 == c3 {
                        found = true

                        if c1 >= 'a' && c1 <= 'z' {
                           score += (u32(c1) - u32('a')) + 1
                        }
                        else {
                           score += (u32(c1) - u32('A')) + 27
                        }

                        break
                     }
                  }
               }

               if found {
                  break
               }
            }

            if found {
               break
            }
         }
      }

      num_lines += 1
   }

   fmt.println("Lines: ", num_lines, score)

/*
   num_lines: u32 = 0
   score: u32 = 0
   data, ok := os.read_entire_file("../input.txt", context.allocator)

   if !ok {
      // could not read file
      fmt.println("Failed to read file ../input.txt")
      return
   }

   it := string(data)
   for line in strings.split_lines_iterator(&it) {
      found := false
      midpoint := len(line)/2
      fmt.println("Mid: ", midpoint)
      num_lines += 1

      // for c in line {
      //    fmt.println("Char: ", c)
      // }

      for i in 0..<midpoint {
         for j in midpoint..<len(line) {
            if line[i] == line[j] {
               fmt.println("Found: ", line[i])
               found = true

               if line[i] >= 'a' && line[i] <= 'z' {
                  score += (u32(line[i]) - u32('a')) + 1
               }
               else {
                  score += (u32(line[i]) - u32('A')) + 27
               }

               break
            }
         }

         if found {
            break
         }
      }
   }

   fmt.println("Lines ", num_lines, score)
*/
}
