#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string.h>
#include <ctype.h>
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
   TEST_DIVISIBLE,
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
   int32_t               Monkey;
   std::vector<uint64_t> Items;
   TOperation            Operation;
   TTest                 Test;
   int32_t               ItemsInspected;
};

int main()
{
   TBuffer file = ReadEntireFile("../input.txt");
   TMonkey monkey = {};
   std::vector<TMonkey> monkeys;

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
               //printf("found monkey %d\n", id);

               monkey.Monkey = id;
               monkey.ItemsInspected = 0;
               monkey.Items.clear();
            }
         }
         else if (file.Data[pos] == 'S')
         {
            if (strncmp((char*)&file.Data[pos], "Starting items: ", 16) == 0)
            {
               pos += 16;

               uint64_t item = file.Data[pos] - '0';

               while (file.Data[pos] != '\n' && file.Data[pos] != '\r')
               {
                  pos++;

                  while (file.Data[pos] != ',' && file.Data[pos] != '\n' && file.Data[pos] != '\r')
                  {
                     item = item * 10;
                     item += file.Data[pos++] - '0';
                  }
                  monkey.Items.push_back(item);
                  item = 0;

                  while (!isdigit(file.Data[pos]))
                  {
                     if (file.Data[pos] == '\n' || file.Data[pos] == '\r')
                        break;
                     pos++;
                  }

                  item = file.Data[pos] - '0';
               }

               // printf("items: %llu => { ", monkey.Items.size());
               // for (auto item : monkey.Items)
               // {
               //    printf("%d ", item);
               // }
               // printf("}\n");
            }
         }
         else if (file.Data[pos] == 'O')
         {
            if (strncmp((char*)&file.Data[pos], "Operation: ", 11) == 0)
            {
               pos += 11;

               if (strncmp((char*)&file.Data[pos], "new = old ", 10) == 0)
               {
                  pos += 10;

                  //printf("operation: item_value ");

                  monkey.Operation.Operand[0].Operand = OPERAND_ITEM_VALUE;
                  if (file.Data[pos] == '+')
                  {
                     //printf("plus ");
                     monkey.Operation.Operation = OP_ADDITION;
                     pos++;
                  }
                  else if (file.Data[pos] == '-')
                  {
                     //printf("minus ");
                     monkey.Operation.Operation = OP_SUBTRACTION;
                     pos++;
                  }
                  else if (file.Data[pos] == '*')
                  {
                     //printf("times ");
                     monkey.Operation.Operation = OP_MULTIPLICATION;
                     pos++;
                  }
                  else if (file.Data[pos] == '/')
                  {
                     //printf("divided by ");
                     monkey.Operation.Operation = OP_DIVISION;
                     pos++;
                  }
                  else
                  {
                     printf("Unknown operation found on Monkey %d\n", monkey.Monkey);
                     return 1;
                  }

                  pos++;

                  if (isdigit(file.Data[pos]))
                  {
                     int32_t int_literal = file.Data[pos++] - '0';
                     while (isdigit(file.Data[pos]))
                     {
                        int_literal = int_literal * 10;
                        int_literal += file.Data[pos++] - '0';
                     }
                     monkey.Operation.Operand[1].Operand = OPERAND_INT_LITERAL;
                     monkey.Operation.Operand[1].Value = int_literal;
                     //printf("%d", int_literal);
                  }
                  else if (strncmp((char*)&file.Data[pos], "old", 3) == 0)
                  {
                     //printf("item_value");
                     pos += 3;
                     monkey.Operation.Operand[1].Operand = OPERAND_ITEM_VALUE;
                  }

                  //printf("\n");
               }
               else
               {
                  printf("Unknown operation found on Monkey %d\n", monkey.Monkey);
                  return 1;
               }
            }
         }
         else if (file.Data[pos] == 'T')
         {
            if (strncmp((char*)&file.Data[pos], "Test: ", 6) == 0)
            {
               pos += 6;

               if (strncmp((char*)&file.Data[pos], "divisible by ", 13) == 0)
               {
                  pos += 13;

                  monkey.Test.Test = TEST_DIVISIBLE;

                  int32_t test_value = file.Data[pos++] - '0';
                  while (isdigit(file.Data[pos]))
                  {
                     test_value = test_value * 10;
                     test_value += file.Data[pos++] - '0';
                  }
                  monkey.Test.Value = test_value;

                  while (isspace(file.Data[pos]))
                  {
                     pos++;
                  }

                  if (strncmp((char*)&file.Data[pos], "If true: throw to monkey ", 25) == 0)
                  {
                     pos += 25;

                     int32_t throw_to = file.Data[pos++] - '0';
                     while (isdigit(file.Data[pos]))
                     {
                        throw_to = throw_to * 10;
                        throw_to += file.Data[pos++] - '0';
                     }
                     monkey.Test.ThrowTo[0] = throw_to;
                  }
                  else
                  {
                     printf("Unknown test found on Monkey %d\n", monkey.Monkey);
                     return 1;
                  }

                  while (isspace(file.Data[pos]))
                  {
                     pos++;
                  }

                  if (strncmp((char*)&file.Data[pos], "If false: throw to monkey ", 26) == 0)
                  {
                     pos += 26;

                     int32_t throw_to = file.Data[pos++] - '0';
                     while (isdigit(file.Data[pos]))
                     {
                        throw_to = throw_to * 10;
                        throw_to += file.Data[pos++] - '0';
                     }
                     monkey.Test.ThrowTo[1] = throw_to;

                     //printf("test: divisible by %d (%d %d)\n", monkey.Test.Value, monkey.Test.ThrowTo[0], monkey.Test.ThrowTo[1]);
                     monkeys.push_back(monkey);
                  }
                  else
                  {
                     printf("Unknown test found on Monkey %d\n", monkey.Monkey);
                     return 1;
                  }
               }
               else
               {
                  printf("Unknown test found on Monkey %d\n", monkey.Monkey);
                  return 1;
               }
            }
         }

         pos++;
      }
   }

   printf("Read %llu monkeys from file\n", monkeys.size());

   // for (auto& m : monkeys)
   // {
   //    printf("monkey %d\n", m.Monkey);
   //    printf("items: %d\n", m.Items.size());
   //    printf("op value %d\n", m.Operation.Operand[1].Value);
   //    printf("test %d (%d %d)\n", m.Test.Value, m.Test.ThrowTo[0], m.Test.ThrowTo[1]);
   // }

   // run over each monkey for some amount of rounds
   for (int round = 0; round < 20; round++)
   {
      //printf("== Round %d ==================================================\n", round+1);
      for (int m = 0; m < monkeys.size(); m++)
      {
         for (int i = 0; i < monkeys[m].Items.size(); i++)
         {
            monkeys[m].ItemsInspected++;

            //printf("r %d m %d i %d inspected %d item %llu -> ", round+1, m, i, monkeys[m].ItemsInspected, monkeys[m].Items[i]);

            switch (monkeys[m].Operation.Operation)
            {
               case OP_ADDITION:
                  if (monkeys[m].Operation.Operand[1].Operand == OPERAND_INT_LITERAL)
                     monkeys[m].Items[i] = monkeys[m].Items[i] + monkeys[m].Operation.Operand[1].Value;
                  else
                     monkeys[m].Items[i] = monkeys[m].Items[i] + monkeys[m].Items[i];
                  break;
               case OP_SUBTRACTION:
                  if (monkeys[m].Operation.Operand[1].Operand == OPERAND_INT_LITERAL)
                     monkeys[m].Items[i] = monkeys[m].Items[i] - monkeys[m].Operation.Operand[1].Value;
                  else
                     monkeys[m].Items[i] = monkeys[m].Items[i] - monkeys[m].Items[i];
                  break;
               case OP_MULTIPLICATION:
                  if (monkeys[m].Operation.Operand[1].Operand == OPERAND_INT_LITERAL)
                     monkeys[m].Items[i] = monkeys[m].Items[i] * monkeys[m].Operation.Operand[1].Value;
                  else
                     monkeys[m].Items[i] = monkeys[m].Items[i] * monkeys[m].Items[i];
                  break;
               case OP_DIVISION:
                  if (monkeys[m].Operation.Operand[1].Operand == OPERAND_INT_LITERAL)
                     monkeys[m].Items[i] = monkeys[m].Items[i] / monkeys[m].Operation.Operand[1].Value;
                  else
                     monkeys[m].Items[i] = monkeys[m].Items[i] / monkeys[m].Items[i];
                  break;
               default:
                  break;
            }

            //printf("%llu -> ", monkeys[m].Items[i]);

            monkeys[m].Items[i] /= 3;

            //printf("%llu", monkeys[m].Items[i]);

            switch (monkeys[m].Test.Test)
            {
               case TEST_DIVISIBLE:
               {
                  TMonkey& true_monkey = monkeys[monkeys[m].Test.ThrowTo[0]];
                  TMonkey& false_monkey = monkeys[monkeys[m].Test.ThrowTo[1]];
                  if (monkeys[m].Items[i] % monkeys[m].Test.Value == 0)
                  {
                     true_monkey.Items.push_back(monkeys[m].Items[i]);
                     //printf(" throw to %d", monkeys[m].Test.ThrowTo[0]);
                  }
                  else
                  {
                     false_monkey.Items.push_back(monkeys[m].Items[i]);
                     //printf(" throw to %d", monkeys[m].Test.ThrowTo[1]);
                  }

                  break;
               }
               default:
                  break;
            }

            //printf("\n");
         }

         // monkey inspected and threw all  items
         monkeys[m].Items.clear();
      }

      //printf("\n");
   }

   int32_t max[2] = { 0 };

   // print item list of all monkeys
   for (int m = 0; m < monkeys.size(); m++)
   {
      printf("Monkey %d (inspected %d items): ", monkeys[m].Monkey, monkeys[m].ItemsInspected);
      for (int i = 0; i < monkeys[m].Items.size(); i++)
      {
         printf("%d", monkeys[m].Items[i]);
         if (i + 1 < monkeys[m].Items.size())
            printf(", ");
      }
      printf("\n");

      if (monkeys[m].ItemsInspected > max[0])
      {
         max[1] = max[0];
         max[0] = monkeys[m].ItemsInspected;
      }
      else if (monkeys[m].ItemsInspected > max[1])
      {
         max[1] = monkeys[m].ItemsInspected;
      }
   }

   printf("result %d (%d %d)\n", max[0] * max[1], max[0], max[1]);

   delete [] file.Data;
}
