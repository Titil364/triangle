int orderG(){
  return 80;
}

int sizeG(){
  return 780;
}

int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=40 && v<=40){
    if(0<=u && 0<=v && u<orderG() && v<orderG()){
      if (u>v)
	return (u-v)%8;
      else
	return (v-u)%8;
    }
    return 0;
  }
  else return (u-v == -1 || u-v==1 || u-v == -40 +1 || u-v == 40 -1);
}
