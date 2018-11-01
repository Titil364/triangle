// Graphe de K3
// X(G) = 3
#define SIZE 3

int graph[SIZE][SIZE] = {
  // 0  1  2  
    {0, 1, 1}, //0
    {1, 0, 1}, //1
    {1, 1, 0}, //2
};//*/


int orderG(){
return SIZE;}

int sizeG(){
return 3;
}

int are_adjacent(int u, int v){
  if(0<= u && 0<=v && u<orderG() && v<orderG()){
      return graph[u][v];
  }
  return 0;
}
