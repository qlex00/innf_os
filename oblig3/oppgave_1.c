#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int palindrom(char *s1){
    int len  = strlen(s1);
    char *s2 = (char *) malloc((len + 1) * sizeof(char));
    
    /*kopierer tegnene fra s1 til s2 i omvendt rekkefølge*/
    for(int i = 0; i < len; i++){
        s2[i] = s1[len - 1 - i];
    }
    s2[len] = '\0';

    int lik = strcmp(s1, s2);
    free(s2);
    return(lik == 0);
}


