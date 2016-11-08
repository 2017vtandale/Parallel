//Vishal Tandale Pd.5 11/3/16 Phase 3 finished
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	char symbol ;
	//
	int frequency ;
	//
	struct Node* left ;
	struct Node* right ;
	//
} TreeNode;
//

void condenseNodes(struct Node* tree, int n){
  int min1 = 0;
  int min2 = 0;
  struct Node temp1;
  struct Node temp2;
  for(int i =1;i<n;i++){
    printf("%d:%d\n",i,tree[i].frequency);
    if(tree[i].frequency<tree[min2].frequency){
      min2=i;
    }
    if(tree[i].frequency<tree[min1].frequency){
      min2 = min1;
      min1 =i;
    }
  }
  printf("%d,%d\n\n\n",min1,min2);
  temp1 = tree[n-1];
  temp2 = tree[n-2];
  tree[n-1] = tree[min1];
  tree[n-2] = tree[min2];
  tree[min1] = temp1;
  tree[min2] = temp2;
  tree[n-2].left = &tree[n-1];
  tree[n-2].frequency = tree[n-2].frequency+tree[n-1].frequency;
}

struct Node* condenseTrees(struct Node* tree, int count){
  for(int i=0;i<count-2;i++)
  {
    condenseNodes(tree, count-i);
  }
  return tree;
}




int main(){
  struct Node tree[156];
  int Frequency[156];
  for(int i =0;i<sizeof(Frequency);i++){
    Frequency[i]=0;
  }
  FILE* fin = fopen("test.txt","r");
  /****Get Frequency******/
  char ch;
  int numBytes;
  numBytes = fread(&ch,sizeof(char),1,fin);
  while(numBytes!=0){
    Frequency[ch]+=1;
    numBytes = fread(&ch,sizeof(char),1,fin);
  }
  // for(int i =0;i<sizeof(Frequency);i++){
  //   if(Frequency[i]>0){
  //     printf("%c Frequency: %d\n", i, Frequency[i]);
  //   }
  // }

/****Get Frequency******/
/****Build Tree********/
int count = 0;
for(int i =0;i<156;i++){
  if(Frequency[i]>0){

    TreeNode* ptr = (TreeNode*) malloc(sizeof(TreeNode));
    ptr -> frequency = Frequency[i];
    ptr -> symbol = i;
    tree[count]= *ptr;
    //printf("%c Frequency: %d\n", tree[count].symbol, tree[count].frequency);
    count+=1;
  }
}
/****Build Tree********/
  condenseTrees(tree, count);
  return 0;

}
