#include <stdio.h>
#include <stdlib.h>

struct prosess
{
   int nummer; 
   char status;
   float start_tid;
   float CPU_tid;
};

struct prosess *kopier(struct prosess p){
  struct prosess *ny_prosess = (struct prosess *) malloc(sizeof(struct prosess));

  ny_prosess->nummer = p.nummer;
  ny_prosess->status = p.status;
  ny_prosess->start_tid = p.start_tid;
  ny_prosess->CPU_tid = p.CPU_tid;

  return ny_prosess;
}

