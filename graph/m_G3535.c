int orderG(){
  return 2450;
}

int sizeG(){
  return 4830;
}

int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=1225 && v<=1225){
    if(0<=u && 0<=v && u<orderG() && v<orderG())
      return(
	     (
	      (
	       ((u-v)%35==1) || ((v-u)%35== 1)
	       )
	      &&
	      (v/35)==(u/35)
	      )
	     ||
	     (
	      (
	       (u/35-v/35)==1 || (v/35-u/35 ) == 1
	       )
	      &&
	      (v%35)==(u%35)
	      )
	     );
    return 0;
  }
  else return (u-v == -1 || u-v==1 || u-v == -1225 +1 || u-v == 1225 -1);
}
