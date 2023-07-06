#include <iostream>
#include <fstream>

int main()
{
   std::ifstream file("../input1.txt");
   std::string   line;
   std::string   lines[3];
   uint32_t      num_lines = 0;
   uint32_t      score = 0;

   if (file.is_open())
   {
      std::cout << "Opened input.txt" << std::endl;

      while (!file.eof())
      {
         std::getline(file, line);

         lines[num_lines%3] = line;

         if (num_lines%3 == 2)
         {
            bool found = false;

            for (int i = 0; i < lines[0].length(); i++)
            {
               for (int j = 0; j < lines[1].length(); j++)
               {
                  if (lines[0][i] == lines[1][j])
                  {
                     for (int k = 0; k < lines[2].length(); k++)
                     {
                        if (lines[0][i] == lines[2][k])
                        {
                           char c = lines[0][i];
                           if (c >= 'a' && c <= 'z')
                              score += (c - 'a') + 1;
                           else
                              score += (c - 'A') + 27;

                           found = true;
                           break;
                        }
                     }

                     if (found)
                        break;
                  }
               }

               if (found)
                  break;
            }
         }

         num_lines++;

#if 0
         if (line.length() > 0 && (line.length() % 2) == 0)
         {
            int  midpoint = line.length() / 2;
            bool found = false;

            for (int i = 0; i < midpoint; i++)
            {
               for (int j = midpoint; j < line.length(); j++)
               {
                  if (line[i] == line[j])
                  {
                     char c = line[i];
                     if (c >= 'a' && c <= 'z')
                        score += (c - 'a') + 1;
                     else
                        score += (c - 'A') + 27;

                     found = true;

                     break;
                  }
               }

               if (found)
                  break;
            }
         }
#endif
      }
   }

   std::cout << "Read " << num_lines << " lines" << std::endl;

   std::cout << "Score: " << score << std::endl;

   file.close();
}
