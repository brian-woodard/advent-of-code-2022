use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;

fn main() {
   let file = File::open("../../input.txt").expect("File not found!");
   let reader = BufReader::new(file);
   let mut num_lines: u32 = 0;
   let mut num_total_contained: u32 = 0;
   let mut num_partial_contained: u32 = 0;
   let mut numbers: Vec<u32> = Vec::new();

   for line in reader.lines().filter_map(|result| result.ok()) {
      numbers.clear();
      let v: Vec<&str> = line.split_terminator(',').collect();
      let e1: Vec<&str> = v[0].split_terminator('-').collect();
      let e2: Vec<&str> = v[1].split_terminator('-').collect();

      for n in e1 {
         if let Ok(i) = n.parse::<u32>() {
            numbers.push(i);
         }
      }
      for n in e2 {
         if let Ok(i) = n.parse::<u32>() {
            numbers.push(i);
         }
      }

      if numbers[2] >= numbers[0] && numbers[3] <= numbers[1] {
         num_total_contained += 1;
      } else if numbers[0] >= numbers[2] && numbers[1] <= numbers[3] {
         num_total_contained += 1;
      }

      if numbers[0] >= numbers[2] && numbers[0] <= numbers[3] {
         num_partial_contained += 1;
      } else if numbers[1] >= numbers[2] && numbers[1] <= numbers[3] {
         num_partial_contained += 1;
      } else if numbers[2] >= numbers[0] && numbers[2] <= numbers[1] {
         num_partial_contained += 1;
      } else if numbers[3] >= numbers[0] && numbers[3] <= numbers[1] {
         num_partial_contained += 1;
      }

      num_lines += 1;
   }
   println!("Lines: {num_lines} total {num_total_contained} partial {num_partial_contained}");
}
