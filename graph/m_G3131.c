int orderG(){
return 1922;
}

int sizeG(){
return 3782;
}

int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=961 && v<=961){
    if(0<=u && 0<=v && u<orderG() && v<orderG())
      return(
	     (
	      (
	       ((u-v)%31==1) || ((v-u)%31== 1)
	       )
	      &&
	      (v/31)==(u/31)
	      )
	     ||
	     (
	      (
	       (u/31-v/31)==1 || (v/31-u/31 ) == 1
	       )
	      &&
	      (v%31)==(u%31)
	      )
	     );
    return 0;
  }
else return (u-v == -1 || u-v==1 || u-v == -961 +1 || u-v == 961 -1);
}
