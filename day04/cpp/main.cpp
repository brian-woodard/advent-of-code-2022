#include <iostream>
#include <fstream>

int main()
{
   std::ifstream file("../input.txt");
   std::string   line;
   uint32_t      num_lines = 0;
   uint32_t      num_total_contained = 0;
   uint32_t      num_partial_contained = 0;

   if (file.is_open())
   {
      while (!file.eof())
      {
         std::getline(file, line);

         size_t comma = line.find(',');
         size_t hash1 = line.find('-');
         size_t hash2 = line.find('-', comma);

         if (comma != std::string::npos &&
             hash1 != std::string::npos &&
             hash2 != std::string::npos)
         {
            int e1n1 = std::atoi(line.substr(0,       hash1).c_str());
            int e1n2 = std::atoi(line.substr(hash1+1, comma).c_str());
            int e2n1 = std::atoi(line.substr(comma+1, hash2).c_str());
            int e2n2 = std::atoi(line.substr(hash2+1).c_str());

            if (e2n1 >= e1n1 && e2n2 <= e1n2)
               num_total_contained++;
            else if (e1n1 >= e2n1 && e1n2 <= e2n2)
               num_total_contained++;


            if (e1n1 >= e2n1 && e1n1 <= e2n2)
               num_partial_contained++;
            else if (e1n2 >= e2n1 && e1n2 <= e2n2)
               num_partial_contained++;
            else if (e2n1 >= e1n1 && e2n1 <= e1n2)
               num_partial_contained++;
            else if (e2n2 >= e1n1 && e2n2 <= e1n2)
               num_partial_contained++;
         }

         num_lines++;
      }
   }

   std::cout << "Read " << num_lines
             << " lines, num total contained " << num_total_contained
             << " num partial contained " << num_partial_contained << std::endl;

   file.close();
}
