use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;

fn main() {
   let file = File::open("../../input.txt").expect("file wasn't found.");
   let reader = BufReader::new(file);
   let mut num_lines: u32 = 0;
   let mut score: u32 = 0;
   let mut lines_array: [Vec<char>; 3] = [vec![], vec![], vec![]];

   for line in reader.lines().filter_map(|result| result.ok()) {
      let mut found = false;
      let mut i = 0;
      let mut j;
      let mut k;
      let idx: usize = (num_lines%3) as usize;
      lines_array[idx] = line.chars().collect();

      if idx == 2 {
         while i < lines_array[0].len() {
            j = 0;
            while j < lines_array[1].len() {
               k = 0;
               if lines_array[0][i] == lines_array[1][j] {
                  while k < lines_array[2].len() {
                     if lines_array[1][j] == lines_array[2][k] {
                        let this_score: usize;

                        if lines_array[1][j] >= 'a' && lines_array[1][j] <= 'z' {
                           this_score = (lines_array[1][j] as usize - 'a' as usize) + 1;
                        }
                        else {
                           this_score = (lines_array[1][j] as usize - 'A' as usize) + 27;
                        }
         
                        score += this_score as u32;

                        found = true;
                        break;
                     }
                     k += 1;
                  }
               }

               if found {
                  break;
               }

               j += 1;
            }

            if found {
               break;
            }

            i += 1;
         }
      }

      num_lines += 1;
   }

   /*
   for line in reader.lines().filter_map(|result| result.ok()) {
      let char_vec: Vec<char> = line.chars().collect();
      let mut found = false;
      let midpoint = char_vec.len()/2;
      let mut i = 0;
      let mut j = midpoint;

      //println!("Line: {} length {} midpoint {}", line, line.len(), midpoint);
      num_lines += 1;

      while i < midpoint {
         while j < char_vec.len() {
            if char_vec[i] == char_vec[j] {
               let this_score: usize;

               if char_vec[i] >= 'a' && char_vec[i] <= 'z' {
                  this_score = (char_vec[i] as usize - 'a' as usize) + 1;
               }
               else {
                  this_score = (char_vec[i] as usize - 'A' as usize) + 27;
               }

               //println!("Found match {} score {}", char_vec[i], this_score);
               score += this_score as u32;
               found = true;
               break;
            }
            j += 1;
         }

         if found {
            break;
         }

         i += 1;
         j = midpoint
      }
   }
   */

   println!("Read {} lines, score {}", num_lines, score);
}
