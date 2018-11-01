// Graphe de K6 complet à 6 sommet
// X(G) = 6
/*
int graph[6][6] = {
  // 0  1  2  3  4  5 
    {0, 1, 1, 1, 1, 1}, //0
    {1, 0, 1, 1, 1, 1}, //1
    {1, 1, 0, 1, 1, 1}, //2
    {1, 1, 1, 0, 1, 1}, //3
    {1, 1, 1, 1, 0, 1}, //4
    {1, 1, 1, 1, 1, 0}, //5
};*/
#define SIZE 6


int graph[6][6] = {
  // 0  1  2  3  4  5  6
    {0, 1, 1, 1, 1, 0}, //0
    {1, 0, 1, 1, 1, 0}, //1
    {1, 1, 0, 1, 1, 1}, //2
    {1, 1, 1, 0, 1, 1}, //3
    {1, 1, 1, 1, 0, 1}, //4
    {0, 0, 1, 1, 1, 0}, //5
};//*/
int orderG(){
return SIZE;}

int sizeG(){
return 13;
}

int are_adjacent(int u, int v){
  if(0<= u && 0<=v && u<orderG() && v<orderG()){
      return graph[u][v];
  }
  return 0;
}
