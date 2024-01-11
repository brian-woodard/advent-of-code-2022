
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <sys/stat.h>

struct TBuffer
{
   uint8_t* Data;
   uint32_t Count;
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

const int START_PACKET_SIZE = 4;
const int START_MESSAGE_SIZE = 14;

bool StartOf(char* Data, int Size)
{
   bool result = true;

   for (int i = 0; i < Size; i++)
   {
      if (Data[i] == 0)
      {
         result = false;
         break;
      }

      for (int j = i+1; j < Size; j++)
      {
         if (Data[i] == Data[j])
         {
            result = false;
            break;
         }
      }

      if (!result)
         break;
   }

   return result;
}

int main()
{
   TBuffer file = ReadEntireFile("../input.txt");
   char start_of_packet[START_MESSAGE_SIZE] = {};
   int byte_offset = 0;

   if (file.Count)
   {
      int idx = 0;

      for (int i = 0; i < file.Count; i++)
      {
         start_of_packet[idx] = file.Data[i];

         if (StartOf(start_of_packet, START_MESSAGE_SIZE))
         {
            byte_offset = i++;
            break;
         }

         idx = (idx + 1) % START_MESSAGE_SIZE;
      }

      printf("Marker found at byte offset %d\n", byte_offset+1);
   }
}
