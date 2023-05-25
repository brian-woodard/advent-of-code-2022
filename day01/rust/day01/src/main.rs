
use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;
  
fn main() {

    let numbers: Vec<i32> = load_from_file("../../input.txt");
    let mut calories: i32 = 0;
    let mut max_calories: [i32; 3] = [0; 3];

    for n in numbers {
        if n != -1 {
            calories += n;
        } else {
            if calories > max_calories[0] {
                max_calories[2] = max_calories[1];
                max_calories[1] = max_calories[0];
                max_calories[0] = calories;
            } else if calories > max_calories[1] {
                max_calories[2] = max_calories[1];
                max_calories[1] = calories;
            } else if calories > max_calories[2] {
                max_calories[2] = calories;
            }
            calories = 0;
        }
    }

    println!("Most calories:     {}", max_calories[0]);
    println!("2nd Most calories: {}", max_calories[1]);
    println!("3rd Most calories: {}", max_calories[2]);
}

fn load_from_file(file_path: &str) -> Vec<i32> {
    let file = File::open(file_path).expect("file wasn't found.");
    let reader = BufReader::new(file);
    let mut numbers: Vec<i32> = Vec::new();

    for line in reader.lines() {
        if let Ok(i) = line.unwrap().parse::<i32>() {
            numbers.push(i);
        } else {
            numbers.push(-1);
        }
    }

    numbers.push(-1);

    return numbers
}