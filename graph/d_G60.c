int orderG(){
  return 120;
}

int sizeG(){
  return 58*30+120;
}

int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=60 && v<=60){
    if(0<=u && 0<=v && u<orderG() && v<orderG()){
      if (u>v)
	return (u-v)%30;
      else
	return (v-u)%30;
    }
    return 0;
  }
  else return (u-v == -1 || u-v==1 || u-v == -orderG() +1 || u-v == orderG() -1);
}
