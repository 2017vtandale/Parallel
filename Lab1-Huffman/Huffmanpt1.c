//Vishal Tandale pd 5
#include <stdio.h>
#include <math.h>

int main(){
  // printf("%s","bump");
  /*********Creating Tree**************/
  FILE* fin = fopen("decodeME.txt","r");
  char ch;
  char temp;
  char tree[2500];
  for(int i = 0; i<sizeof(tree);i++){
    tree[i] = '\0'; }

    int numBytes =(int)'0';
    int sizeof_File = 28;
    int pos = 1;
    numBytes = fread(&ch,sizeof(char),1,fin);
    numBytes = fread(&ch,sizeof(char),1,fin);
    numBytes = fread(&ch,sizeof(char),1,fin);
  for(int i = 0;i<sizeof_File;i++){
    numBytes = fread(&ch,sizeof(char),1,fin);
    numBytes = fread(&temp,sizeof(char),1,fin);
    pos = 1;

    while(temp!='\n'){
      pos = 2*pos + (temp - '0');
      tree[pos]='\e';
      numBytes = fread(&temp,sizeof(char),1,fin);
    }

    tree[pos] = ch;
  }
  /*********Creating Tree**************/
  /*********Decoding Message**************/
  pos = 1;
  numBytes = fread(&ch,sizeof(char),1,fin);
  double huffcount = 0;
  double asciicount = 0;
  double freqtable[127];
  double frequencies[127];
  int used[127];
  for(int i =0;i<127;i++){
    freqtable[i]=0;
    used[i] = -1;
    frequencies[i] =0;
  }
  int count=0;
  while(numBytes!=0){
    pos=1;
    while(1){
      huffcount+=1;
      pos = 2*pos + (ch - '0');
      numBytes = fread(&ch,sizeof(char),1,fin);
      if(tree[pos]-'\e'!=0){
        printf( "%c" , tree[pos] ) ;
        freqtable[tree[pos]]+=1;
        if(freqtable[tree[pos]]==1){
        used[count] = tree[pos];
        }
        count+=1;
        break;
      }
    }
  }
count-=1;
huffcount-=1;
freqtable[tree[pos]]-=1;
  printf("\n%d\n",count);
  double shannon =0;
  for(int i =0;i<127;i++){
    if(used[i]!=-1){
    printf("\n%d: %f",used[i],freqtable[used[i]]);
    // printf("%f\n",freqtable[used[i]]);
    frequencies[used[i]] = (double) freqtable[used[i]]/count;
    shannon+= -1*log(frequencies[used[i]])/log(2)*freqtable[used[i]];
  }}


  printf("\n%f\n",shannon+96);
  printf("\n%f\n",((count*8)-huffcount)/(count*8));
  return 0;
}
