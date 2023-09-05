#include <iostream>
#include <fstream>
#include <vector>

const int NUM_POSITIONS = 9;

void print_crates(std::vector<uint8_t> Crates[])
{
   uint32_t depth = 0;

   printf("\n");
   for (int i = 0; i < NUM_POSITIONS; i++)
   {
      if (Crates[i].size() > depth)
         depth = Crates[i].size();
   }

   for (int y = depth-1; y >= 0; y--)
   {
      for (int x = 0; x < NUM_POSITIONS; x++)
      {
         if (Crates[x].size() > y)
            printf("[%c] ", Crates[x][y]);
         else
            printf("    ");
      }
      printf("\n");
   }
   printf("\n");
}

void execute_command(const std::string& Command, std::vector<uint8_t> Crates[])
{
   size_t move_pos = Command.find("move");
   size_t from_pos = Command.find("from");
   size_t to_pos = Command.find("to");

   if (move_pos != std::string::npos &&
       from_pos != std::string::npos &&
       to_pos != std::string::npos)
   {
      int qty = std::atoi(Command.substr(move_pos+4, from_pos).c_str());
      int from = std::atoi(Command.substr(from_pos+4, to_pos).c_str()) - 1;
      int to = std::atoi(Command.substr(to_pos+2).c_str()) - 1;

      //printf("move %d from %d to %d\n", qty, from, to);

      for (int i = 0; i < qty; i++)
      {
         Crates[to].push_back(Crates[from].back());
         Crates[from].pop_back();
      }
   }
}

void execute_command_9001(const std::string& Command, std::vector<uint8_t> Crates[])
{
   size_t move_pos = Command.find("move");
   size_t from_pos = Command.find("from");
   size_t to_pos = Command.find("to");

   if (move_pos != std::string::npos &&
       from_pos != std::string::npos &&
       to_pos != std::string::npos)
   {
      int qty = std::atoi(Command.substr(move_pos+4, from_pos).c_str());
      int from = std::atoi(Command.substr(from_pos+4, to_pos).c_str()) - 1;
      int to = std::atoi(Command.substr(to_pos+2).c_str()) - 1;
      int idx = Crates[from].size() - qty;

      //printf("move %d from %d to %d\n", qty, from, to);

      for (int i = 0; i < qty; i++, idx++)
      {
         Crates[to].push_back(Crates[from][idx]);
      }

      for (int i = 0; i < qty; i++)
      {
         Crates[from].pop_back();
      }
   }
}

int main()
{
   std::ifstream            file("../input.txt");
   std::string              line;
   std::vector<std::string> initial;
   std::vector<uint8_t>     crates[NUM_POSITIONS];
   uint32_t                 num_lines = 0;
   uint32_t                 num_commands = 0;
   bool                     read_initial = true;

   if (file.is_open())
   {
      while (!file.eof())
      {
         std::getline(file, line);

         if (line.length() && read_initial)
         {
            initial.push_back(line);
         }
         else if (read_initial)
         {
            read_initial = false;

            for (int i = initial.size()-2; i >= 0; i--)
            {
               if (initial[i][1] != ' ')
                  crates[0].push_back(initial[i][1]);
               if (initial[i][5] != ' ')
                  crates[1].push_back(initial[i][5]);
               if (initial[i][9] != ' ')
                  crates[2].push_back(initial[i][9]);
               if (initial[i][13] != ' ')
                  crates[3].push_back(initial[i][13]);
               if (initial[i][17] != ' ')
                  crates[4].push_back(initial[i][17]);
               if (initial[i][21] != ' ')
                  crates[5].push_back(initial[i][21]);
               if (initial[i][25] != ' ')
                  crates[6].push_back(initial[i][25]);
               if (initial[i][29] != ' ')
                  crates[7].push_back(initial[i][29]);
               if (initial[i][33] != ' ')
                  crates[8].push_back(initial[i][33]);
            }

            print_crates(crates);
         }

         if (line.length() && !read_initial)
         {
            execute_command_9001(line, crates);
            num_commands++;
         }

         num_lines++;
      }
   }

   print_crates(crates);

   std::cout << "Read " << num_lines << std::endl;

   for (int i = 0; i < NUM_POSITIONS; i++)
   {
      printf("%c", crates[i].back());
   }
   printf("\n");

   file.close();
}
