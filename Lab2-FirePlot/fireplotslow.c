#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int W;
int H;
double P;
void PrintPlot(char* Plot[][W]){
   for(int x = 0;x<H;x++){
      for(int i =0;i<W;i++){
         printf("%s",Plot[x][i]);
      }
      printf("\n");
   }
}
char* RandomizePlot(){
   char* Plot[H][W];
   int par;
   for(int x = 0;x<H;x++){
      for(int i =0;i<W;i++){
         par = ((double)rand() / (double)RAND_MAX)<P;
         Plot[x][i] = "_";
         if(par==1){
            Plot[x][i]="T";
         }
      }
   }
   return Plot;
}
 int main(){
    W=30;
    H = 40;
    P = .7;
    PrintPlot(RandomizePlot());


 }
