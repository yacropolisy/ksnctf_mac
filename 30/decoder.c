#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[], char *envp[]) {
 int   i, ii, A, B, D, E, F;
 char c;
 while ((i = getchar()) != EOF) {
       ii = getchar();
       D = (i & 0x0f);
       E = (ii & 0xf0) >> 4;
       F = (ii & 0x0f);
       A = D^E;
       B = F;
   printf("\\x%X%X", A, B);
 }
 exit(EXIT_SUCCESS);
}
