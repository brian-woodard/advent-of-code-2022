
use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;

fn main() {
    let file = File::open("../../input.txt").expect("file wasn't found.");
    let reader = BufReader::new(file);
    let mut score: u32 = 0;
    let mut score2: u32 = 0;

    let score_array: [[u32; 3]; 3] = [
        [ 4, 8, 3 ],
        [ 1, 5, 9 ],
        [ 7, 2, 6 ]
    ];

    let score2_array: [[u32; 3]; 3] = [
        [ 3, 4, 8 ],
        [ 1, 5, 9 ],
        [ 2, 6, 7 ]
    ];

    for line in reader.lines() {
       let parse_str = line.unwrap();
       let chars: Vec<char> = parse_str.chars().collect();
       let opp_idx: usize = chars[0] as usize - 'A' as usize;
       let my_idx: usize = chars[2] as usize - 'X' as usize;
       score = score + score_array[opp_idx][my_idx];
       score2 += score2_array[opp_idx][my_idx];
    }

    println!("Score: {}", score);
    println!("Score2: {}", score2);
}
