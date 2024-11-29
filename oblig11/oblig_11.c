#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

#define M 100 // Maks. antall ulike typer ressurser
#define N 100 // Maks. antall prosesser
int m;        // Antall ulike typer ressurser
int n;        // Antall prosesser
int E[M];     // Exists: Totalt antall av hver type ressurs
int A[M];     // Available: Antall tilgjengelige ressursforekomster
int C[N][M];  // Current: Antall ressurser hver prosess holder
int R[N][M];  // Request: Antall ressurser hver prosess trenger


// read_file(): Leser prosess- og ressursdata fra fil. Alle data må
// være ikke-negative heltall.
//
void read_file(char *filename)
{
   int i, j;
   FILE *p_file;
   
   // Åpner fil og sjekker for feil i åpning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   { 
      printf("Feil ved åpning av filen \"%s\"\n", filename); 
      exit(-1);
   }

   // Leser antall prosesser og ressurstyper
   fscanf(p_file, "%d %d", &m, &n);

   // Leser totalt antall ressurser av hver type
   for (i = 0; i < m; i++)
     fscanf(p_file, "%d", &E[i]);      
                            
   // Leser antall ressurser av hver type som hver prosess holder
   for (i = 0; i < n; i++)      
      for (j = 0; j < m; j++) 
         fscanf(p_file, "%d", &C[i][j]);
                            
   // Leser antall ressurser av hver type som hver prosess trenger
   for (i = 0; i < n; i++)      
      for (j = 0; j < m; j++) 
	fscanf(p_file, "%d", &R[i][j]);

   // Beregner antall tilgjengelige ressurser av hver type
   for (i = 0; i < m; i++) 
   {
      A[i] = E[i];
      for (j = 0; j < n; j++)    
         A[i] -= C[j][i];
   }
}


// safe(): Kjører Bankers for å sjekke om systemet er i safe tilstand
//
int safe()
{
  int work[M]; //Tilgjengelige ressurser
  int finish[N] = {0};
  int i, j, found;

  //Kopierer tilgjengelige ressurser til work
  for (i = 0; i < m; i++) {
    work[i] = A[i];
  }

  while (1) {
    found = FALSE;

    for (i = 0; i < n; i++) {
      if (!finish[i]) {
	int can_run = TRUE;

	//Sjekker om prossesen kan kjøre med tilgjengelige ressurser
	for (j = 0; j < m; j++) {
	  if (R[i][j] > work[j]) {
	    can_run = FALSE;
	    break;
	  }
	}

	if (can_run) {
	  finish[i] = TRUE;
	  found = TRUE;

	  //Returnere ressursene prosessen brukte
	  for (j = 0; j < m; j++) {
	    work[j] += C[i][j];
	  }

	  printf("p%d can run A = [", i + 1);
	  for (j = 0; j < m; j++) {
	    printf("%d", work[j]);
	    if (j < m - 1) printf(" ");
	  }
	  printf("]\n");
	}
      }
    }

    if (!found) break; //ingen flere prosesser kan kjøre
  }

  for (i = 0; i < n; i++) {
    if (!finish[i]) {
      printf("No more processes can run\n");
      return FALSE; //Systemet er usikker
    }
  }
  return TRUE; //Systemet er sikker
}


// main(): Leser filnavn med prosess- og ressursdata fra fil og kjører
// Bankers algoritme
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn data fra fil
   read_file(filename);
   
   // Simulerer Bankers
   if (safe())
     printf("Safe\n");
   else
     printf("Unsafe\n");
}
