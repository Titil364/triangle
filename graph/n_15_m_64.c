
int orderG(){
return 15;}

int sizeG(){
return 64;
}

int graph[15][15] = {
{0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0},
{1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1},
{0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
{1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
{1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0},
{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1},
{0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
{0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1},
{0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
{0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1},
{0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
{0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0},
{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0}
};


int are_adjacent(int u, int v){
  if(0<= u && 0<=v && u<orderG() && v<orderG()){
      return graph[u][v];
  }
  return 0;
}
