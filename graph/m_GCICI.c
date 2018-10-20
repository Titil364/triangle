int orderG(){
  return 20402;
}

int sizeG(){
  return 40602;
}

int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=orderG() && v<=orderG()){
    if(0<=u && 0<=v && u<orderG() && v<orderG())
      return(
	     (
	      (
	       ((u-v)%101==1) || ((v-u)%101== 1)
	       )
	      &&
	      (v/101)==(u/101)
	      )
	     ||
	     (
	      (
	       (u/101-v/101)==1 || (v/101-u/101 ) == 1
	       )
	      &&
	      (v%101)==(u%101)
	      )
	     );
    return 0;
  }
  else return (u-v == -1 || u-v==1 || u-v == -orderG() +1 || u-v == orderG() -1);
}
