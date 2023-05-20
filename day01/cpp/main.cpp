#include <iostream>
#include <fstream>

int main()
{
   std::ifstream file("../input.txt");
   std::string   line;
   uint32_t      num_lines = 0;
   uint32_t      calories = 0;
   uint32_t      max_calories[3] = {};

   if (file.is_open())
   {
      std::cout << "Opened input.txt" << std::endl;

      while (!file.eof())
      {
         std::getline(file, line);

         num_lines++;

         try
         {
            calories += std::stoi(line);
         }
         catch(std::invalid_argument const& e)
         {
            // blank line check if new max
            if (calories > max_calories[0])
            {
               max_calories[2] = max_calories[1];
               max_calories[1] = max_calories[0];
               max_calories[0] = calories;
            }
            else if (calories > max_calories[1])
            {
               max_calories[2] = max_calories[1];
               max_calories[1] = calories;
            }
            else if (calories > max_calories[2])
            {
               max_calories[2] = calories;
            }

            calories = 0;

            continue;
         }
      }
   }

   std::cout << "Read " << num_lines << " lines" << std::endl;

   std::cout << "Most calories:     " << max_calories[0] << std::endl;
   std::cout << "2nd Most calories: " << max_calories[1] << std::endl;
   std::cout << "3rd Most calories: " << max_calories[2] << std::endl;

   std::cout << "Total: " << (max_calories[0] + max_calories[1] + max_calories[2]) << std::endl;

   file.close();
}
