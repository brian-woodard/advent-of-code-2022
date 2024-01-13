use std::fs;

//const START_PACKET_SIZE: usize = 4;
const START_MESSAGE_SIZE: usize = 14;

fn read_entire_file(file: &str) -> Result<Vec<u8>, Box<dyn std::error::Error>> {
   let buffer = fs::read(file)?;
   Ok(buffer)
}

fn main() {
   let data = read_entire_file("../../input.txt");

   match data {
      Ok(data) => handle_data(&data),
      Err(error) => println!("Got an error: {}", error),
   }
}

fn handle_data(data: &Vec<u8>) {
   let mut start_of_packet : [u8; START_MESSAGE_SIZE] = [0; START_MESSAGE_SIZE];
   let mut idx : usize = 0;
   let mut byte_offset = 0;

   for byte in data {
      start_of_packet[idx] = *byte;

      if start_of(&start_of_packet) {
         byte_offset = byte_offset + 1;
         break;
      }

      idx = (idx + 1) % START_MESSAGE_SIZE;
      byte_offset = byte_offset + 1;
   }

   println!("Marker found at byte offset {byte_offset}");
}

fn start_of(data: &[u8; START_MESSAGE_SIZE]) -> bool {
   let mut result = true;

   for i in 0..START_MESSAGE_SIZE {
      if data[i] == 0 {
         result = false;
         break;
      }

      for j in i+1..START_MESSAGE_SIZE {
         if data[i] == data[j] {
            result = false;
            break;
         }
      }

      if !result {
         break;
      }
   }

   result
}