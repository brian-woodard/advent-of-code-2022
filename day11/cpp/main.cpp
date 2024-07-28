#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string.h>
#include "Utility.h"

enum TOperationType
{
   OP_ADDITION,
   OP_SUBTRACTION,
   OP_MULTIPLICATION,
   OP_DIVISION,
   OP_COUNT
};

enum TOperandEnum
{
   OPERAND_ITEM_VALUE,
   OPERAND_INT_LITERAL,
   OPERAND_COUNT
};

enum TTestType
{
   TEST_DIVISBLE,
   TEST_COUNT
};

struct TOperand
{
   TOperandEnum Operand;
   int32_t      Value;
};

struct TOperation
{
   TOperationType Operation;
   TOperand       Operand[2];
};

struct TTest
{
   TTestType Test;
   int32_t   Value;
   int32_t   ThrowTo[2];
};

struct TMonkey
{
   int32_t          Monkey;
   std::vector<int> Items;
   TOperation       Operation;
   TTest            Test;
};

int main()
{
   TBuffer file = ReadEntireFile("../test.txt");
   TMonkey monkey = {};

   if (file.Count)
   {
      int pos = 0;

      while (pos < file.Count)
      {
         if (file.Data[pos] == 'M')
         {
            if (strncmp((char*)&file.Data[pos], "Monkey ", 7) == 0)
            {
               pos += 7;

               int32_t id = file.Data[pos++] - '0';

               while (file.Data[pos] != ':')
               {
                  id = id * 10;
                  id += file.Data[pos++] - '0';
               }
               printf("found monkey %d\n", id);

               monkey.Monkey = id;
               monkey.Items.clear();
            }
         }
         else if (file.Data[pos] == 'S')
         {
            if (strncmp((char*)&file.Data[pos], "Starting items: ", 16) == 0)
            {
               pos += 16;

               int32_t item = file.Data[pos] - '0';

               while (file.Data[pos] != '\n')
               {
                  pos++;

                  while (file.Data[pos] != ',' && file.Data[pos] != '\n')
                  {
                     item = item * 10;
                     item += file.Data[pos++] - '0';
                  }
                  monkey.Items.push_back(item);
                  item = 0;

                  while (!isdigit(file.Data[pos]))
                  {
                     if (file.Data[pos] == '\n')
                        break;
                     pos++;
                  }

                  item = file.Data[pos] - '0';
               }

               printf("items: %llu => { ", monkey.Items.size());
               for (auto item : monkey.Items)
               {
                  printf("%d ", item);
               }
               printf("}\n");
            }
         }

         pos++;
      }
   }

   delete [] file.Data;
}
