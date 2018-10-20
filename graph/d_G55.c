int orderG(){
  return 110;
}

int sizeG(){
  return 990+110;
}

int are_adjacent(int u, int v){
  if (0<= u && 0<=v && u<=orderG() && v<=orderG()){
    if(0<= u && 0<=v && u<orderG() && v<orderG()){
      int i,j,index=0;
      int T[orderG()];
      for(i=0;i<11;i++)
	for(j=i+1;j<11;j++)
	  {
	    T[index]= (1 << i) + (1 << j);
	    index++;
	  }
      return (!(T[u] & T[v]));
    }	
    else return 0;
  }
else return (u-v == -1 || u-v==1 || u-v == -110 +1 || u-v == 110 -1);
}
