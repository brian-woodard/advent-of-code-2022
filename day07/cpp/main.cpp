
#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include <sys/stat.h>

#define MAX_DIR_SIZE          256
#define MAX_DISK_SPACE        70000000
#define DISK_SPACE_FOR_UPDATE 30000000

struct TBuffer
{
   uint8_t* Data;
   uint32_t Count;
};

struct TDirectory
{
   TDirectory* Prev;
   TDirectory* Children;
   uint64_t    Size;
   uint64_t    NumChildren;
   uint8_t     DirName[256];
};

TBuffer ReadEntireFile(const char* FileName)
{
   TBuffer Result = {};

   FILE *File = fopen(FileName, "rb");
   if (File)
   {
      struct stat Stat;
      stat(FileName, &Stat);

      Result.Data = new uint8_t[Stat.st_size];
      Result.Count = Stat.st_size;

      if (Result.Data)
      {
         if (fread(Result.Data, Result.Count, 1, File) != 1)
         {
            fprintf(stderr, "ERROR: Unable to read \"%s\".\n", FileName);
            delete [] Result.Data;
         }
      }

      fclose(File);
   }
   else
   {
      fprintf(stderr, "ERROR: Unable to open \"%s\".\n", FileName);
   }

   return Result;
}

uint64_t CalculateSizes(TDirectory* Directory)
{
   uint64_t size = Directory->Size;

   for (int i = 0; i < Directory->NumChildren; i++)
   {
      size += CalculateSizes(&Directory->Children[i]);
   }

   Directory->Size = size;

   return size;
}

uint64_t SmallDirSize(TDirectory* Directory)
{
   uint64_t size = 0;

   for (int i = 0; i < Directory->NumChildren; i++)
   {
      size += SmallDirSize(&Directory->Children[i]);
   }

   if (Directory->Size <= 100000)
   {
      size += Directory->Size;
   }

   return size;
}

void PrintDirectory(TDirectory* Directory)
{
   printf(" DirName     = %s\n", Directory->DirName);
   printf(" Directory   = %p\n", Directory);
   printf(" Prev        = %p\n", Directory->Prev);
   printf(" Children    = %p\n", Directory->Children);
   printf(" Size        = %ld\n", Directory->Size);
   printf(" NumChildren = %ld\n\n", Directory->NumChildren);

   for (int i = 0; i < Directory->NumChildren; i++)
   {
      PrintDirectory(&Directory->Children[i]);
   }
}

void FindSmallestDir(TDirectory* Directory, int64_t MinimumSize, int64_t* CurrMaximumSize, TDirectory** DirToDelete)
{
   for (int i = 0; i < Directory->NumChildren; i++)
   {
      FindSmallestDir(&Directory->Children[i], MinimumSize, CurrMaximumSize, DirToDelete);
   }

   if (Directory->Size >= MinimumSize && Directory->Size < *CurrMaximumSize)
   {
      *CurrMaximumSize = Directory->Size;
      *DirToDelete = Directory;
   }
}

void Cleanup(TDirectory* Directory)
{
   for (int i = 0; i < Directory->NumChildren; i++)
   {
      Cleanup(&Directory->Children[i]);
   }

   delete [] Directory->Children;
}

int main()
{
   TDirectory* root = nullptr;
   TDirectory* curr = nullptr;
   uint64_t    start_index = 0;
   uint64_t    end_index = 0;
   uint64_t    commands = 0;
   TBuffer     file = ReadEntireFile("../input.txt");

   // parse input
   while (end_index < file.Count)
   {
      if (file.Data[end_index++] == '\n')
      {
         commands++;

         if (file.Data[start_index] == '$')
         {
            start_index += 2;
            if (file.Data[start_index] == 'c' && file.Data[start_index+1] == 'd')
            {
               start_index += 3;
               if (!root)
               {
                  if (file.Data[start_index] == '/' && (end_index - start_index - 1) == 1)
                  {
                     root = new TDirectory;

                     root->Prev = nullptr;
                     root->Children = nullptr;
                     root->Size = 0;
                     root->NumChildren = 0;

                     memset(root->DirName, 0, sizeof(root->DirName));

                     root->DirName[0] = file.Data[start_index];

                     curr = root;
                  }
                  else
                  {
                     printf("Error: root does not exist, expect first 'cd' command to '/'\n");
                     break;
                  }
               }
               else if (file.Data[start_index] == '.' && file.Data[start_index+1] == '.')
               {
                  if (curr->Prev)
                  {
                     curr = curr->Prev;
                  }
                  else
                  {
                     printf("Error no prev directory on line %d\n", commands);
                     break;
                  }
               }
               else
               {
                  bool found = false;

                  // loop over children and change current directory to the directory specified
                  for (int i = 0; i < curr->NumChildren; i++)
                  {
                     if (memcmp(&curr->Children[i].DirName, &file.Data[start_index], (end_index - start_index - 1)) == 0)
                     {
                        found = true;
                        curr->Children[i].Prev = curr;
                        curr = &curr->Children[i];
                        break;
                     }
                  }

                  if (!found)
                  {
                     printf("Error unknown directory on line %d\n", commands);
                     break;
                  }
               }
            }
            else if (file.Data[start_index] == 'l' && file.Data[start_index+1] == 's')
            {
               // list command, do nothing
            }
            else
            {
               printf("Error unknown command on line %d\n", commands);
               break;
            }
         }
         else if (file.Data[start_index] == 'd' &&
                  file.Data[start_index+1] == 'i' &&
                  file.Data[start_index+2] == 'r')
         {
            TDirectory* curr_children = curr->Children;

            start_index += 4;

            curr->NumChildren++;
            curr->Children = new TDirectory[curr->NumChildren];

            for (int i = 0; i < curr->NumChildren; i++)
            {
               if (i == curr->NumChildren - 1)
               {
                  curr->Children[i].Prev = nullptr;
                  curr->Children[i].Children = nullptr;
                  curr->Children[i].Size = 0;
                  curr->Children[i].NumChildren = 0;

                  memset(curr->Children[i].DirName, 0, sizeof(curr->Children[i].DirName));

                  for (int j = 0; j < end_index - start_index - 1; j++)
                  {
                     curr->Children[i].DirName[j] = file.Data[start_index + j];
                  }
               }
               else
               {
                  memcpy(&curr->Children[i], &curr_children[i], sizeof(TDirectory));
               }
            }

            if (curr_children)
               delete [] curr_children;
         }
         else if (file.Data[start_index] >= '0' && file.Data[start_index] <= '9')
         {
            int i;
            int size = 0;
            int base10 = 1;

            for (i = start_index; i < end_index; i++)
            {
               if (file.Data[i] == ' ')
                  break;
            }

            for (int j = i-1; j >= start_index; j--)
            {
               size += (file.Data[j] - '0') * base10;
               base10 *= 10;
            }

            curr->Size += size;
         }
         else
         {
            printf("Error parsing line %d\n", commands);
         }

         start_index = end_index;
      }
   }

   printf("processed %d commands\n", commands);

   if (root)
   {
      uint64_t free_space;
      int64_t  space_needed;;

      printf("root = %p\n", root);

      root->Size = CalculateSizes(root);

      PrintDirectory(root);

      // part 1
      uint64_t size = SmallDirSize(root);
      printf("size = %ld\n", size);

      // part 2
      free_space = MAX_DISK_SPACE - root->Size;
      printf("free size = %ld\n", free_space);

      space_needed = DISK_SPACE_FOR_UPDATE - (int64_t)free_space;
      if (space_needed > 0)
      {
         TDirectory* directory_to_delete = nullptr;
         int64_t     curr_max_size       = MAX_DISK_SPACE;

         printf("space needed = %d\n", space_needed);
         FindSmallestDir(root, space_needed, &curr_max_size, &directory_to_delete);

         printf("delete directory %s to free %d space\n",
                directory_to_delete->DirName,
                directory_to_delete->Size);
      }

      Cleanup(root);

      delete root;
   }

   delete [] file.Data;
}
