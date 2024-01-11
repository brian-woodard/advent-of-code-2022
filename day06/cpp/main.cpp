
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

const int MARKER_SIZE = 4;

bool StartOfPacket(char* Marker)
{
   bool result = false;

   result = (Marker[0] != Marker[1]) &&
            (Marker[0] != Marker[2]) &&
            (Marker[0] != Marker[3]) &&
            (Marker[1] != Marker[2]) &&
            (Marker[1] != Marker[3]) &&
            (Marker[2] != Marker[3]) &&
            (Marker[0] != 0) &&
            (Marker[1] != 0) &&
            (Marker[2] != 0) &&
            (Marker[3] != 0);

   return result;
}

int main()
{
   TBuffer file = ReadEntireFile("../input.txt");
   char marker[MARKER_SIZE] = {};
   int byte_offset = 0;

   if (file.Count)
   {
      int marker_idx = 0;

      for (int i = 0; i < file.Count; i++)
      {
         marker[marker_idx] = file.Data[i];

         if (StartOfPacket(marker))
         {
            byte_offset = i++;
            break;
         }

         marker_idx = (marker_idx + 1) % MARKER_SIZE;
      }
   }

   printf("Marker found at byte offset %d\n", byte_offset+1);
}
