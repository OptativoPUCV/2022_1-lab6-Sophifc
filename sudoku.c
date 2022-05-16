#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  Node * nodo = createNode();
  nodo = copy(n);
  int k;

  for(int i = 0 ; i < 9; i++){
    for(int j = 0; j < 9; j++){
      k = j + 1;
      while(k < 9){
        if(n->sudo[i][j] != 0 && nodo->sudo[i][k] != 0){
          if(n->sudo[i][j] == nodo->sudo[i][k]){
            return 0;
          }
        }
        k++;
      }
    }
  }
  
  
  for(int j = 0; j < 9 ; j++){
    for(int i = 0; i < 9 ; i++){
      k= i + 1;
      while(k < 9){
        if(n->sudo[i][j] != 0 && nodo->sudo[k][j] != 0){
          if(n->sudo[i][j] == nodo->sudo[k][j]){
            return 0;
          }
        }
      k++;
    }
  }
}

  
  for(k=0;k < 9;k++){ 
    for(int p = 0 ; p < 9 ; p++){
      int i = 3 * (k/3) + (p/3);
      int j = 3 * (k%3) + (p%3);
      //int l = 0;
    for(int l=0;l < 9;l++){
      int i2 = (3*(k/3) + (l/3));
      int j2 = (3*(k%3) + (l%3));
      if(i2 != i && j2 != j){
        if(n->sudo[i][j] != 0 && n->sudo[i2][j2] != 0){
          if(n->sudo[i][j] == nodo->sudo[i2][j2]){
            return 0;
          }
        } 
      }
    }
  }
}
  
 return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int valido;
  
  for (int i=0; i<9; i++){
    for(int k=0; k<9; k++){

      if(n->sudo[i][k]==0){
        
        for(int c=0;c<9;c++){
          Node* ad=createNode();
          n->sudo[i][k]++;
          ad=copy(n);
          valido=is_valid(ad);
          if(valido==1){
            pushBack(list,ad);
          }
        }
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for(int i=0 ;i < 9; i++){
    for(int j=0 ;j < 9; j++){
      if(n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila, initial);
  while(!is_empty(pila)){
    
    Node* nodo= top(pila);
    pop(pila);
     if(is_final(nodo) == 1){
       return nodo;
      }
     List* lista = get_adj_nodes(nodo);
     Node* ad = first(lista);
    
     while(ad){
        push(pila,ad);
        ad=next(lista);
     }
     free(nodo);
  }
  return NULL;
  
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/