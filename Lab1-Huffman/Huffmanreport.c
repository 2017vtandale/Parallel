//Vishal Tandale pd 5
#include <stdio.h>
#include <math.h>
// #include <stdlib.h>

int main(){
  //printf("At the Top\n");
  char ch;
  char temp;
  char tree[2500];
  int dig1;
  int dig2;
  int size[3];
  int sizeof_File;
  char filename[1035];
  int numBytes;
  int count;
  double huffcount = 0;
  double asciicount = 0;
  double freqtable[127];
  double frequencies[127];
  int used[127];
  // printf("%s","bump");
  /*********Creating Tree**************/
  for(int i = 1;i<=1;i++){
    printf("Start Code\n");
    dig2 =  i%10;
    dig1 = i/10;

    //char *filename = (char*) malloc(1024);
    snprintf(filename,8,"a%d%d.txt",dig1,dig2);
    printf("Got to make filename: %s\n",filename);
    FILE* fin = fopen(filename,"r");
    sizeof_File = 0;

    for(int i = 0; i<sizeof(tree);i++){
      tree[i] = '\0'; }

    numBytes =(int)'0';
    numBytes = fread(&ch,sizeof(char),1,fin);
    count = 0;
    //printf("Filled Empty Tree\n");
    while(ch!='\n'){
      //printf("%c",ch);
      size[count] = ch-'0';
      count++;
      //printf("%d\n",count);
      numBytes = fread(&ch,sizeof(char),1,fin);
    }
    printf("Count: %d\n", count);
    //for(int z =0;z<3;z++){
    //printf("Fill Size: %d\n",size[z]);}
    count--;
    for(int x = 0;x<=count;x++){
      //printf("%d\n", size[x]);
      sizeof_File += size[x]*pow(10,count-x);
      }
    //sizeof_File--;
    printf("Size: %d\n",sizeof_File);

    int pos = 1;

    for(int i = 0;i<sizeof_File;i++){
      numBytes = fread(&ch,sizeof(char),1,fin);
      numBytes = fread(&temp,sizeof(char),1,fin);
      pos = 1;}

    while(temp!='\n'){
      pos = 2*pos + (temp - '0');
      tree[pos]='\e';
      numBytes = fread(&temp,sizeof(char),1,fin);
    }

      tree[pos] = ch;
      printf("Creating New Tree\n");
    /*********Creating Tree**************/
    /*********Decoding Message**************/
    pos = 1;
    numBytes = fread(&ch,sizeof(char),1,fin);

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
          //printf( "%c" , tree[pos] ) ;
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
    double shannon =0;
    for(int i =0;i<127;i++){
      if(used[i]!=-1){
        //printf("\n%d: %f",used[i],freqtable[used[i]]);
        // printf("%f\n",freqtable[used[i]]);
        frequencies[used[i]] = (double) freqtable[used[i]]/count;
        shannon+= -1*log(frequencies[used[i]])/log(2)*freqtable[used[i]];
    }
  }


    printf("\n%s\t%f\n",filename,shannon);

}
return 0;
}
