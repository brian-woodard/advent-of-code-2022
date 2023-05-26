#include <iostream>
#include <fstream>
#include <sstream>

// The second column, you reason, must be what you should play in response: X for Rock, Y for Paper, 
// and Z for Scissors. Winning every time would be suspicious, so the responses must have been
// carefully chosen.

// The winner of the whole tournament is the player with the highest score. Your total score is the
// sum of your scores for each round. The score for a single round is the score for the shape you
// selected (1 for Rock, 2 for Paper, and 3 for Scissors) plus the score for the outcome of the
// round (0 if you lost, 3 if the round was a draw, and 6 if you won).

// Opponent
// A - Rock
// B - Paper
// C - Scissors

// Part 1
// Me
// X - Rock
// Y - Paper
// Z - Scissors

// A X - score 4 (1 + 3)
// A Y - score 8 (2 + 6)
// A Z - score 3 (3 + 0)

// B X - score 1 (1 + 0)
// B Y - score 5 (2 + 3)
// B Z - score 9 (3 + 6)

// C X - score 7 (1 + 6)
// C Y - score 2 (2 + 0)
// C Z - score 6 (3 + 3)

// Part 2
// Me
// X - Lose
// Y - Draw
// Z - Win

// A X - score 3 (3 + 0)
// A Y - score 4 (1 + 3)
// A Z - score 8 (2 + 6)

// B X - score 1 (1 + 0)
// B Y - score 5 (2 + 3)
// B Z - score 9 (3 + 6)

// C X - score 2 (2 + 0)
// C Y - score 6 (3 + 3)
// C Z - score 7 (1 + 6)

const int score_array[3][3] = 
{
   { 4, 8, 3 },
   { 1, 5, 9 },
   { 7, 2, 6 },
};

const int score2_array[3][3] = 
{
   { 3, 4, 8 },
   { 1, 5, 9 },
   { 2, 6, 7 },
};

int main()
{
   std::ifstream file("../input.txt");
   std::string   line;
   uint32_t      num_lines = 0;
   uint32_t      score = 0;
   uint32_t      score2 = 0;

   if (file.is_open())
   {
      std::cout << "Opened input.txt" << std::endl;

      while (!file.eof())
      {
         std::getline(file, line);

         if (line.length() == 0)
            break;

         std::stringstream stream;
         char opp_idx = 0;
         char my_idx = 0;

         stream.str(line);
         stream >> opp_idx >> my_idx;

         opp_idx -= 'A';
         my_idx -= 'X';

         num_lines++;

         score += score_array[opp_idx][my_idx];
         score2 += score2_array[opp_idx][my_idx];
      }
   }

   std::cout << "Read " << num_lines << " lines" << std::endl;
   std::cout << "Score: " << score << std::endl;
   std::cout << "Score Part 2: " << score2 << std::endl;

   file.close();
}
