int orderG(){
return 30;
}

int sizeG(){
return 75;
}

int are_adjacent(int u, int v){
if (0<= u && 0<=v && u<=orderG() && v<=orderG()){
 if(0<= u && 0<=v && u<15 && v<15){
  int i,j,index=0;
  int T[15];
  for(i=0;i<6;i++)
   for(j=i+1;j<6;j++)
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
