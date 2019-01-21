#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char *argv[]) {
 pid_t childpid = 0;
 int i,j,k,n,nchar,l;
 if (argc !=3 ){ /* check for valid number of command-line arguments */
 fprintf(stderr, "Usage: %s processes\n", argv[0]);
 return 1;
}
   n = atoi(argv[1]);
   nchar=atoi(argv[2]);
   char **mybuf=malloc(n* sizeof(char*));
   for(j=0;j< (n);j++)
   mybuf[j]=malloc((nchar+1) * sizeof(char));
for(i=1;i<n;i++)
{
if(childpid=fork())
break;
}
//For reading characters
for(k=0;k<n;k++){
////printf("\nEnter character by character\n");

for(l=0;l<nchar;l++)
{
scanf(" %c",&mybuf[k][l]);
}
mybuf[k][l]='\0';
}
fprintf(stderr, "i=%d :%ld:%s\n",i,(long)getpid(),mybuf[i-1]);
return 0;
}
