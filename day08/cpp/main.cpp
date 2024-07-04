
#include <stdio.h>
#include "Utility.h"

int main()
{
   TBuffer  file = ReadEntireFile("../input.txt");
   int      rows = 0;
   int      cols = 0;
   uint8_t* grid = nullptr;
   int      num_visible = 0;

   if (file.Count)
   {
      int idx = 0;
      
      grid = new uint8_t[file.Count+1];

      for (int i = 0; i < file.Count; i++)
      {
         //printf("%c", file.Data[i]);

         if (file.Data[i] == '\n')
         {
            rows++;

            if (cols == 0)
               cols = i;
         }
         else
         {
            grid[idx++] = file.Data[i];
         }
      }

      grid[idx] = 0;
   }

   printf("Input is a %d x %d grid\n", cols, rows);
   //printf("grid: %s\n", grid);

   int scenic_score = 0;

   for (int y = 1; y < rows-1; y++)
   {
      for (int x = 1; x < cols-1; x++)
      {
         int  curr_idx = (y * cols) + x;

#if 0
         bool is_visible = false;

         // check left
         if (!is_visible)
         {
            is_visible = true;
            for (int x1 = x-1; x1 >= 0; x1--)
            {
               int idx = (y * cols) + x1;
               if (grid[idx] >= grid[curr_idx])
               {
                  is_visible = false;
                  break;
               }
            }
         }

         // check right
         if (!is_visible)
         {
            is_visible = true;
            for (int x1 = x+1; x1 < cols; x1++)
            {
               int idx = (y * cols) + x1;
               if (grid[idx] >= grid[curr_idx])
               {
                  is_visible = false;
                  break;
               }
            }
         }

         // check top
         if (!is_visible)
         {
            is_visible = true;
            for (int y1 = y-1; y1 >= 0; y1--)
            {
               int idx = (y1 * cols) + x;
               if (grid[idx] >= grid[curr_idx])
               {
                  is_visible = false;
                  break;
               }
            }
         }

         // check bottom
         if (!is_visible)
         {
            is_visible = true;
            for (int y1 = y+1; y1 < rows; y1++)
            {
               int idx = (y1 * cols) + x;
               if (grid[idx] >= grid[curr_idx])
               {
                  is_visible = false;
                  break;
               }
            }
         }

         if (is_visible)
         {
            num_visible++;
         }
#else
         int score[4] = {};

         // check left
         for (int x1 = x-1; x1 >= 0; x1--)
         {
            int idx = (y * cols) + x1;
            if (grid[idx] >= grid[curr_idx] || x1 == 0)
            {
               score[0] = x-x1;
               break;
            }
         }

         // check right
         for (int x1 = x+1; x1 < cols; x1++)
         {
            int idx = (y * cols) + x1;
            if (grid[idx] >= grid[curr_idx] || x1 == cols-1)
            {
               score[1] = x1-x;
               break;
            }
         }

         // check top
         for (int y1 = y-1; y1 >= 0; y1--)
         {
            int idx = (y1 * cols) + x;
            if (grid[idx] >= grid[curr_idx] || y1 == 0)
            {
               score[2] = y-y1;
               break;
            }
         }

         // check bottom
         for (int y1 = y+1; y1 < rows; y1++)
         {
            int idx = (y1 * cols) + x;
            if (grid[idx] >= grid[curr_idx] || y1 == rows-1)
            {
               score[3] = y1-y;
               break;
            }
         }

         int total_score = score[0] * score[1] * score[2] * score[3];

         if (total_score > scenic_score)
            scenic_score = total_score;
#endif
      }
   }

   num_visible += (cols + rows - 2) * 2;

   printf("number of visible trees: %d\n", num_visible);
   printf("scenic score: %d\n", scenic_score);

   delete [] grid;
   delete [] file.Data;
}
