
package main

import "core:fmt"
import "core:os"
import "core:strings"
import "core:strconv/decimal"

main :: proc() {
   data, ok := os.read_entire_file("../input.txt", context.allocator)

   calories: u64 = 0
   max_calories := [3]u64{0..=2 = 0}

   if !ok {
      // could not read file
      fmt.println("Failed to read file ../input.txt")
      return
   }

   it := string(data)
   for line in strings.split_lines_iterator(&it) {
      dec: decimal.Decimal

      ok := decimal.set(&dec, line)

      if ok {
         calories += decimal.rounded_integer(&dec)
      } else {
         if calories > max_calories[0] {
            max_calories[2] = max_calories[1]
            max_calories[1] = max_calories[0]
            max_calories[0] = calories
         } else if calories > max_calories[1] {
            max_calories[2] = max_calories[1]
            max_calories[1] = calories
         } else if calories > max_calories[2] {
            max_calories[2] = calories
         }
         calories = 0
      }
   }

   fmt.println("Most calories:     ", max_calories[0])
   fmt.println("2nd Most calories: ", max_calories[1])
   fmt.println("3rd Most calories: ", max_calories[2])
}