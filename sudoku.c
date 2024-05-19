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
   //Filas
   for (int i = 0 ; i < 9 ; i++){
      int arrayFilas[10] = {0};
      for (int j = 0 ; j < 9 ; j++){
         if (n->sudo[i][j] == 0) continue;
         if (n->sudo[i][j] < 1 || n->sudo[i][j] > 9) return 0;
         if (arrayFilas[n->sudo[i][j]] != 0) return 0;
         arrayFilas[n->sudo[i][j]] = 1;
      }
   }

   //Columnas
   for (int i = 0 ; i < 9 ; i++){
      int arrayColumnas[10] = {0};
      for (int j = 0 ; j < 9 ; j++){
         if (n->sudo[j][i] == 0) continue;
         if (n->sudo[j][i] < 1 || n->sudo[j][i] > 9) return 0;
         if (arrayColumnas[n->sudo[j][i]] != 0) return 0;
         arrayColumnas[n->sudo[j][i]] = 1;
      }
   }

   //Submatrices
   for (int k = 0 ; k < 9 ; k++){
      int arraySubmatrices[10] = {0};
      for (int p = 0 ; p < 9 ; p++){
         int i = 3*(k/3) + (p/3);
         int j = 3*(k%3) + (p%3);
         if (n->sudo[i][j] == 0) continue;
         if (n->sudo[i][j] < 1 || n->sudo[i][j] > 9) return 0;
         if (arraySubmatrices[n->sudo[i][j]] != 0) return 0;
         arraySubmatrices[n->sudo[i][j]] = 1;
      }
   }
   return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();
   int i,j, k;
   int primeraCasilla = 0;
   for (i = 0 ; i < 9 ; i++){
      for (j = 0 ; j < 9 ; j++){
         if (n->sudo[i][j] == 0 && primeraCasilla == 0){
            primeraCasilla = 1;
            for (k = 1 ; k < 10 ; k++){
               Node* adj = copy(n);
               adj->sudo[i][j] = k;
               if (is_valid(adj) && primeraCasilla == 1){
                  pushBack(list, adj);
               }
            }
         }
      }
   }
   return list;
}


int is_final(Node* n){
   if (n == NULL) return 0;
   for (int i = 0 ; i < 9 ; i++){
      for (int j = 0 ; j < 9 ; j++){
         if (n->sudo[i][j] == 0)
            return 0;
      }
   }
    return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S = createStack();
   cont = 0;
   push(S, initial);
   while (!is_empty(S)){
      Node* n = (Node *) top(S);
      pop(S);
      if (is_final(n)) return n;
      List* adj = get_adj_nodes(n);
      Node* aux = first(adj);
      while (aux != NULL){
         push(S, aux);
         aux = next(adj);
         if (is_final(aux))
         cont++;
      }
      free(n);
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