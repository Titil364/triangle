int orderG(){
  return 140;
}

int sizeG(){
  return 2415;
}

int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=70 && v<=70){
    if(0<=u && 0<=v && u<orderG() && v<orderG()){
      if (u>v)
	return (u-v)%14;
      else
	return (v-u)%14;
    }
    return 0;
  }
  else return (u-v == -1 || u-v==1 || u-v == -orderG() +1 || u-v == orderG() -1);
}
