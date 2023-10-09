use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;

const NUM_POSITIONS: usize = 9;

fn main() {
   let file = File::open("../../input.txt").expect("File not found!");
   let reader = BufReader::new(file);
   let mut num_lines: u32 = 0;
   let mut read_initial = true;
   let mut initial: Vec<Vec<char>> = Vec::new();
   let mut crates : [Vec<char>; NUM_POSITIONS] = [Vec::new(), Vec::new(), Vec::new(),
                                                  Vec::new(), Vec::new(), Vec::new(),
                                                  Vec::new(), Vec::new(), Vec::new()];

   for line in reader.lines().filter_map(|result| result.ok()) {
      num_lines += 1;
      let chars: Vec<char> = line.chars().collect();

      if read_initial && chars.len() > 0 {
         initial.push(chars);
      } else if read_initial {
         read_initial = false;

         for i in (0..initial.len()).rev() {
            if initial[i][1] != ' ' && initial[i][1] != '1' {
               crates[0].push(initial[i][1]);
            }
            if initial[i][5] != ' ' && initial[i][5] != '2' {
               crates[1].push(initial[i][5]);
            }
            if initial[i][9] != ' ' && initial[i][9] != '3' {
               crates[2].push(initial[i][9]);
            }
            if initial[i][13] != ' ' && initial[i][13] != '4' {
               crates[3].push(initial[i][13]);
            }
            if initial[i][17] != ' ' && initial[i][17] != '5' {
               crates[4].push(initial[i][17]);
            }
            if initial[i][21] != ' ' && initial[i][21] != '6' {
               crates[5].push(initial[i][21]);
            }
            if initial[i][25] != ' ' && initial[i][25] != '7' {
               crates[6].push(initial[i][25]);
            }
            if initial[i][29] != ' ' && initial[i][29] != '8' {
               crates[7].push(initial[i][29]);
            }
            if initial[i][33] != ' ' && initial[i][33] != '9' {
               crates[8].push(initial[i][33]);
            }
         }

         print_crates(&crates);
      } else if chars.len() > 0 && !read_initial {
         execute_command_9001(&line, &mut crates);
      }
   }

   println!("Read {num_lines} lines");

   for c in &crates {
      if c.len() == 0 {
         print!(" ");
      } else {
         match c.get(c.len()-1) {
            Some(value) => print!("{value}"),
            None => println!("Error!"),
      }
      }
   }
   println!();

   print_crates(&crates);
}

fn print_crates(crates : &[Vec<char>; NUM_POSITIONS]) {
   let mut depth: usize = 0;

   println!();

   for i in 0..NUM_POSITIONS {
      if crates[i].len() > depth {
         depth = crates[i].len();
      }
   }

   for y in (0..depth).rev() {
      for x in 0..NUM_POSITIONS {
         if crates[x].len() > y {
            print!("[{}] ", crates[x][y]);
         } else {
            print!("    ");
         }
      }
      println!();
   }

   println!();
}

fn execute_command(command : &String, crates : &mut [Vec<char>; NUM_POSITIONS]) {
   let cmds: Vec<&str> = command.split(' ').collect();
   let qty: usize = cmds[1].parse::<usize>().expect("Can't parse!");
   let from: usize = cmds[3].parse::<usize>().expect("Can't parse!")-1;
   let to: usize = cmds[5].parse::<usize>().expect("Can't parse!")-1;

   //println!("move {qty} from {from} to {to}");

   for _i in 0..qty {
      let item = crates[from].pop().expect("No item in vector!");
      crates[to].push(item);
   }
}

fn execute_command_9001(command : &String, crates : &mut [Vec<char>; NUM_POSITIONS]) {
   let cmds: Vec<&str> = command.split(' ').collect();
   let qty: usize = cmds[1].parse::<usize>().expect("Can't parse!");
   let from: usize = cmds[3].parse::<usize>().expect("Can't parse!")-1;
   let to: usize = cmds[5].parse::<usize>().expect("Can't parse!")-1;
   let mut idx = crates[from].len() - qty;

   //println!("move {qty} from {from} to {to}");

   for _i in 0..qty {
      let item = crates[from][idx];
      crates[to].push(item);
      idx += 1;
   }

   for _i in 0..qty {
      crates[from].pop();
   }
}