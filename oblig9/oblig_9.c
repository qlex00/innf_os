#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur som lagrer data om en page frame
struct page_frame
{
   int id;   // Page-ID/-number
   int load; // Tidspunkt da pagen ble lagt inn i RAM
   int last; // Tidspunkt da pagen siste ble referert til
   int R;    // Referenced bit
   int M;    // Modified bit
};

// Globale variabler
int T = 300;           // Systemtid, settes til passende verdi
int N;                 // Antall prosesser
struct page_frame *PF; // Peker til array med page frames

// read_file(): Leser data for N page frames fra fil. Pages skal
// ligge sortert på ankomsttid. Alle data må være ikke-negative
// heltall. Alle tider oppgis i hele tidsenheter. Filformat:
//
//    N
//    id load last R M
//    id load last R M
//    id load last R M
//    ...
//
void read_file(char *filename)
{
   int i;
   FILE *p_file;
   
   // Åpner fil og sjekker for feil i åpning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   { 
      printf("Feil ved åpning av filen \"%s\"\n", filename); 
      exit(-1);
   }

   // Leser antall page frames
   fscanf(p_file, "%d", &N);

   // Oppretter array med plass til alle pages
   PF = (struct page_frame *) malloc(N * sizeof(struct page_frame));

   // Leser inn en og en page frame.
   for (i = 0; i < N; i++)
      fscanf(p_file, "%d %d %d %d %d", &PF[i].id, &PF[i].load,
	      &PF[i].last, &PF[i].R, &PF[i].M);
   fclose(p_file);
}

//first_in_first_out(): Simulering av page replacement med FIFO
//
void first_in_first_out()
{
  printf("First-In-First-Out\n");
  
  struct page_frame *fifo_page = &PF[0];

  for (int i = 1; i < N; i++) {
    if (PF[i].load < fifo_page->load){
      fifo_page = &PF[i];
    }
  }
  printf("Page: %d Loaded: %d Last ref: %d R: %d M: %d\n", fifo_page->id, fifo_page->load, fifo_page->last, fifo_page->R, fifo_page->M);
}

//least_recently_used(): Simulering av page replacement med LRU
//
void least_recently_used()
{
  printf("Least recently used\n");
  
  struct page_frame *lru_page = &PF[0];

  for(int i = 1; i < N; i++) {
    if(PF[i].last < lru_page->last){
      lru_page = &PF[i];
    }
  }
  printf("Page: %d Loaded: %d Last ref: %d R: %d M: %d\n", lru_page->id, lru_page->load, lru_page->last, lru_page->R, lru_page->M);
  
}

//second_chance(): Simulering av page replacement med Second Chance
//
void second_chance()
{
  printf("Second chance\n");
  
  int index = 0;
  while(1) {
    if (PF[index].R == 0){
      printf("Page: %d Loaded: %d Last ref: %d R: %d M: %d\n",
	     PF[index].id, PF[index].load, PF[index].last, PF[index].R, PF[index].M);
      break;
    }else{
      PF[index].R = 0;
      index = (index + 1) % N;
    }
  }
}

// main(): Leser filnavn med page frame data, leser inndata fra fil og
// kjører tre ulike page replacement algoritmer
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn prosessdataene
   read_file(filename);

   // Simulerer page replacement
   first_in_first_out();
   least_recently_used();
   second_chance();
}
