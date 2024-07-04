
#include <stdio.h>
#include <assert.h>
#include "Utility.h"

const uint32_t signal_cycle[] = { 20, 60, 100, 140, 180, 220 };

void DrawPixel(char* Screen, int Pixel, int Value)
{
   int pixel = Pixel % 40;

   if (pixel == Value-1 ||
       pixel == Value ||
       pixel == Value+1)
   {
      Screen[Pixel] = '#';
   }
}

int main()
{
   TBuffer  file = ReadEntireFile("../input.txt");
   int32_t  reg_x = 1;
   uint32_t cycles = 0;
   int      idx = 0;
   int32_t  signal_strength = 0;
   char     screen[6][40];

   memset(screen, '.', sizeof(screen));

   if (file.Count)
   {
      for (int i = 0; i < file.Count; i++)
      {
         if (file.Data[i] == 'a' &&
             file.Data[i+1] == 'd' &&
             file.Data[i+2] == 'd' &&
             file.Data[i+3] == 'x')
         {
            int value = 0;
            bool negative = false;

            i += 5;

            if (file.Data[i] == '-')
            {
               negative = true;
               i++;
            }

            while (i < file.Count && file.Data[i] != '\n')
            {
               value *= 10;
               value += file.Data[i++] - '0';
            }

            if (negative) value *= -1;

            // addx takes two cycles, check if we hit a signal cycle during add
            if (cycles+1 == signal_cycle[idx] || cycles+2 == signal_cycle[idx])
            {
               signal_strength += (signal_cycle[idx] * reg_x);
               printf("1: idx %d (%d * %d) signal strength %d\n", idx, reg_x, signal_cycle[idx], signal_strength);
               if (idx < ArrayCount(signal_cycle))
                  idx++;
            }

            DrawPixel((char*)screen, cycles, reg_x);
            DrawPixel((char*)screen, cycles+1, reg_x);
            
            cycles += 2;
            reg_x += value;
         }
         else if (file.Data[i] == 'n' &&
                  file.Data[i+1] == 'o' &&
                  file.Data[i+2] == 'o' &&
                  file.Data[i+3] == 'p')
         {
            while (file.Data[i] != '\n')
            {
               i++;
            }

            DrawPixel((char*)screen, cycles, reg_x);

            cycles++;

            if (cycles == signal_cycle[idx])
            {
               signal_strength += (signal_cycle[idx] * reg_x);
               printf("2: idx %d (%d * %d) signal strength %d\n", idx, reg_x, signal_cycle[idx], signal_strength);
               if (idx < ArrayCount(signal_cycle))
                  idx++;
            }
         }

         //printf("cycle %d reg x %d\n", cycles, reg_x);
      }
   }

   printf("\n");
   for (int y = 0; y < 6; y++)
   {
      for (int x = 0; x < 40; x++)
      {
         printf("%c", screen[y][x]);
      }
      printf("\n");
   }
   printf("\n");

   delete [] file.Data;
}
