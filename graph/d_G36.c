int orderG(){
  return 72;
}

int sizeG(){
  return 666;
}

int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=36 && v<=36){
    if(0<=u && 0<=v && u<orderG() && v<orderG()){
      if (u>v)
	return (u-v)%12;
      else
	return (v-u)%12;
    }
    return 0;
  }
  else return (u-v == -1 || u-v==1 || u-v == -36 +1 || u-v == 36 -1);
}
