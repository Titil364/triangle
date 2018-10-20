int orderG(){
  return 2*78;
}  

int sizeG(){
  return 2145+orderG();
}


int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=orderG() && v<=orderG()){
    if(0<= u && 0<=v && u<orderG() && v<orderG()){
      int i,j,index=0;
      int T[orderG()];
      for(i=0;i<13;i++)
	for(j=i+1;j<13;j++)
	  {
	    T[index]= (1 << i) + (1 << j);
	    index++;
	  }
      return (!(T[u] & T[v]));
    }	
    else return 0;
  }
  else return (u-v == -1 || u-v==1 || u-v == -orderG() +1 || u-v == orderG() -1);
}
