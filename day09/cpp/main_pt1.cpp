
#include <stdio.h>
#include "Utility.h"

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

   if (delta.X == 2)
   {
      Tail->X++;
      Tail->Y += delta.Y;
   }
   else if (delta.X == -2)
   {
      Tail->X--;
      Tail->Y += delta.Y;
   }
   else if (delta.Y == 2)
   {
      Tail->Y++;
      Tail->X += delta.X;
   }
   else if (delta.Y == -2)
   {
      Tail->Y--;
      Tail->X += delta.X;
   }
}

int main()
{
   HashTable<Vector2, bool> head_table;
   HashTable<Vector2, bool> tail_table;
   TBuffer                  file = ReadEntireFile("../input.txt");
   Vector2                  head_pos = { 0, 0 };
   Vector2                  tail_pos = { 0, 0 };
   uint32_t                 total_moves = 0;

   head_table.SetHashTableFn(Vector2HashTable);
   head_table.SetPrintFn(Vector2HashPrint);

   tail_table.SetHashTableFn(Vector2HashTable);
   tail_table.SetPrintFn(Vector2HashPrint);

   if (file.Count)
   {
      head_table[head_pos] = true;
      tail_table[tail_pos] = true;

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
            
            for (int j = 0; j < num_moves; j++)
            {
               head_pos.X++;
               head_table[head_pos] = true;

               MoveTail(&head_pos, &tail_pos);
               tail_table[tail_pos] = true;

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
            
            for (int j = 0; j < num_moves; j++)
            {
               head_pos.Y++;
               head_table[head_pos] = true;

               MoveTail(&head_pos, &tail_pos);
               tail_table[tail_pos] = true;

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
            
            for (int j = 0; j < num_moves; j++)
            {
               head_pos.X--;
               head_table[head_pos] = true;

               MoveTail(&head_pos, &tail_pos);
               tail_table[tail_pos] = true;

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
            
            for (int j = 0; j < num_moves; j++)
            {
               head_pos.Y--;
               head_table[head_pos] = true;

               MoveTail(&head_pos, &tail_pos);
               tail_table[tail_pos] = true;

               total_moves++;
            }
         }
      }
   }

   printf("Final head position (%d, %d), total moves %d\n", head_pos.X, head_pos.Y, total_moves);
   printf("Head table size: %d (unique head positions)\n", head_table.Size());
   //head_table.Print();
   printf("Tail table size: %d (unique tail positions)\n", tail_table.Size());
   //tail_table.Print();

   delete [] file.Data;
}
