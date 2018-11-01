// Graphe de K4
// X(G) = 6
#define SIZE 4
/*
int graph[SIZE][SIZE] = {
  // 0  1  2  3  4  5
    {0, 1, 1, 1, 1}, //0
    {1, 0, 1, 1, 1}, //1
    {1, 1, 0, 1, 1}, //2
    {1, 1, 1, 0, 1}, //3
    {1, 1, 1, 1, 0}, //4
};//*/


int graph[SIZE][SIZE] = {
  // 0  1  2  3  4  5
    {0, 1, 1, 1}, //0
    {1, 0, 1, 1}, //1
    {1, 1, 0, 1}, //2
    {1, 1, 1, 0}, //3
};//*/


int orderG(){
return SIZE;}

int sizeG(){
return 6;
}

int are_adjacent(int u, int v){
  if(0<= u && 0<=v && u<orderG() && v<orderG()){
      return graph[u][v];
  }
  return 0;
}
