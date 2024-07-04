
#include <stdio.h>
#include <assert.h>
#include "Utility.h"

#define NUM_KNOTS 10

struct Vector2
{
   bool operator==(const Vector2& That)
   {
      return (this->X == That.X &&
              this->Y == That.Y);
   }

   bool operator!=(const Vector2& That)
   {
      return (this->X != That.X ||
              this->Y != That.Y);
   }

   Vector2 operator-(const Vector2 That)
   {
      Vector2 result = { this->X - That.X,
                         this->Y - That.Y };
      return result;
   }

   int X;
   int Y;
};

uint32_t Vector2HashTable(Vector2 Key)
{
   // TODO: Better hash function
   uint32_t hash = (Key.X * 31) + Key.Y;

   return hash;
}

void Vector2HashPrint(uint32_t Index, Vector2 Key, bool Value)
{
   printf("Bucket %d: Key (%d, %d) Value %s\n", Index, Key.X, Key.Y, Value ? "true" : "false");
}

void MoveTail(Vector2* Head, Vector2* Tail)
{
   Vector2 delta = *Head - *Tail;

   assert((delta.X <= 2) && delta.X >= -2);
   assert((delta.Y <= 2) && delta.Y >= -2);

   if (delta.X == 2)
   {
      Tail->X++;
      //Tail->Y += delta.Y;
      if (delta.Y >= 1)
         Tail->Y++;
      else if (delta.Y <= -1)
         Tail->Y--;
   }
   else if (delta.X == -2)
   {
      Tail->X--;
      //Tail->Y += delta.Y;
      if (delta.Y >= 1)
         Tail->Y++;
      else if (delta.Y <= -1)
         Tail->Y--;
   }
   else if (delta.Y == 2)
   {
      Tail->Y++;
      //Tail->X += delta.X;
      if (delta.X >= 1)
         Tail->X++;
      else if (delta.X <= -1)
         Tail->X--;
   }
   else if (delta.Y == -2)
   {
      Tail->Y--;
      //Tail->X += delta.X;
      if (delta.X >= 1)
         Tail->X++;
      else if (delta.X <= -1)
         Tail->X--;
   }
}

void SimulateKnots(Vector2* Pos, HashTable<Vector2, bool>* PosTable, int NumKnots)
{
   PosTable[0][Pos[0]] = true;

   for (int k = 1; k < NumKnots; k++)
   {
      MoveTail(&Pos[k-1], &Pos[k]);
      PosTable[k][Pos[k]] = true;
   }
}

void PrintPath(HashTable<Vector2, bool>& PosTable, Vector2 Min, Vector2 Max)
{
   printf("\n");
   for (int y = Max.Y; y >= Min.Y; y--)
   {
      for (int x = Min.X; x <= Max.X; x++)
      {
         Vector2 pos = { x, y };
         if (PosTable.At(pos))
            printf("#");
         else
            printf(".");
      }
      printf("\n");
   }
   printf("\n");
}

void PrintState(Vector2* Pos)
{
   //const int min_x = 0;
   //const int max_x = 5;
   //const int min_y = 0;
   //const int max_y = 4;

   // test2.txt
   // min (-11, -5) max (14, 15)

   const int min_x = -11;
   const int max_x = 14;
   const int min_y = -5;
   const int max_y = 15;

   const int tot_x = max_x-min_x+1;
   const int tot_y = max_y-min_y+1;

   char area[tot_x * tot_y];

   const char knot[NUM_KNOTS] = { 'H', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

   memset(area, '.', sizeof(area));

   for (int i = NUM_KNOTS-1; i >= 0; i--)
   {
      int tx = Pos[i].X - min_x;
      int ty = Pos[i].Y - min_y;
      int idx = (ty * tot_x) + tx;
      area[idx] = knot[i];
   }

   printf("\n");
   for (int y = max_y; y >= min_y; y--)
   {
      for (int x = min_x; x <= max_x; x++)
      {
         int tx = x - min_x;
         int ty = y - min_y;
         int idx = (ty * tot_x) + tx;
         printf("%c", area[idx]);
      }
      printf("\n");
   }
   printf("\n");
}

int main()
{
   HashTable<Vector2, bool> pos_table[NUM_KNOTS];
   TBuffer                  file = ReadEntireFile("../input.txt");
   Vector2                  pos[NUM_KNOTS];
   uint32_t                 total_moves = 0;
   Vector2                  min = { 10000, 10000 };
   Vector2                  max = { -10000, -10000 };

   for (int i = 0; i < NUM_KNOTS; i++)
   {
      pos[i] = { 0, 0 };
      pos_table[i].SetHashTableFn(Vector2HashTable);
      pos_table[i].SetPrintFn(Vector2HashPrint);
      pos_table[i][pos[i]] = true;
   }

   if (file.Count)
   {
      for (int i = 0; i < file.Count; i++)
      {
         if (file.Data[i] == 'R')
         {
            int num_moves = 0;

            i += 2;

            while (i < file.Count && file.Data[i] != '\n')
            {
               num_moves *= 10;
               num_moves += file.Data[i++] - '0';
            }

            //printf("== R %d ==\n", num_moves);
            
            for (int j = 0; j < num_moves; j++)
            {
               pos[0].X++;

               SimulateKnots((Vector2*)&pos, (HashTable<Vector2, bool>*)&pos_table, NUM_KNOTS);

               if (pos[0].X > max.X)
                  max.X = pos[0].X;
               if (pos[0].Y > max.Y)
                  max.Y = pos[0].Y;
               if (pos[0].X < min.X)
                  min.X = pos[0].X;
               if (pos[0].Y < min.Y)
                  min.Y = pos[0].Y;

               //PrintState(pos);

               total_moves++;
            }
         }
         else if (file.Data[i] == 'U')
         {
            int num_moves = 0;

            i += 2;

            while (i < file.Count && file.Data[i] != '\n')
            {
               num_moves *= 10;
               num_moves += file.Data[i++] - '0';
            }

            //printf("== U %d ==\n", num_moves);
            
            for (int j = 0; j < num_moves; j++)
            {
               pos[0].Y++;

               SimulateKnots((Vector2*)&pos, (HashTable<Vector2, bool>*)&pos_table, NUM_KNOTS);

               if (pos[0].X > max.X)
                  max.X = pos[0].X;
               if (pos[0].Y > max.Y)
                  max.Y = pos[0].Y;
               if (pos[0].X < min.X)
                  min.X = pos[0].X;
               if (pos[0].Y < min.Y)
                  min.Y = pos[0].Y;

               //PrintState(pos);

               total_moves++;
            }
         }
         else if (file.Data[i] == 'L')
         {
            int num_moves = 0;

            i += 2;

            while (i < file.Count && file.Data[i] != '\n')
            {
               num_moves *= 10;
               num_moves += file.Data[i++] - '0';
            }

            //printf("== L %d ==\n", num_moves);
            
            for (int j = 0; j < num_moves; j++)
            {
               pos[0].X--;

               SimulateKnots((Vector2*)&pos, (HashTable<Vector2, bool>*)&pos_table, NUM_KNOTS);

               if (pos[0].X > max.X)
                  max.X = pos[0].X;
               if (pos[0].Y > max.Y)
                  max.Y = pos[0].Y;
               if (pos[0].X < min.X)
                  min.X = pos[0].X;
               if (pos[0].Y < min.Y)
                  min.Y = pos[0].Y;

               //PrintState(pos);

               total_moves++;
            }
         }
         else if (file.Data[i] == 'D')
         {
            int num_moves = 0;

            i += 2;

            while (i < file.Count && file.Data[i] != '\n')
            {
               num_moves *= 10;
               num_moves += file.Data[i++] - '0';
            }

            //printf("== D %d ==\n", num_moves);
            
            for (int j = 0; j < num_moves; j++)
            {
               pos[0].Y--;

               SimulateKnots((Vector2*)&pos, (HashTable<Vector2, bool>*)&pos_table, NUM_KNOTS);

               if (pos[0].X > max.X)
                  max.X = pos[0].X;
               if (pos[0].Y > max.Y)
                  max.Y = pos[0].Y;
               if (pos[0].X < min.X)
                  min.X = pos[0].X;
               if (pos[0].Y < min.Y)
                  min.Y = pos[0].Y;

               //PrintState(pos);

               total_moves++;
            }
         }
      }
   }

   printf("Final head position (%d, %d), total moves %d\n", pos[0].X, pos[0].Y, total_moves);
   printf("Head table size: %d (unique head positions)\n", pos_table[0].Size());

   for (int i = 0; i < NUM_KNOTS; i++)
   {
      printf("Table %d size: %d\n", i+1, pos_table[i].Size());
   }

   printf("Tail table size: %d (unique tail positions)\n", pos_table[NUM_KNOTS-1].Size());

   printf("min (%d, %d) max (%d, %d)\n", min.X, min.Y, max.X, max.Y);

   //PrintPath(pos_table[NUM_KNOTS-1], min, max);

   printf("load factor: %f\n", pos_table[0].LoadFactor());
   //pos_table[0].Print();

   delete [] file.Data;
}
