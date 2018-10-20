int orderG(){
return 18;
}

int sizeG(){
return 30;
}

int are_adjacent(int u, int v){
if (0<= u && 0<=v && u<=orderG() && v<=orderG()){
 if(0<= u && 0<=v && u<orderG() && v<orderG()){
  if(u/3==v/3)
   return 1; 
  if(u/3==v%3 && v/3==u%3)
   return 1;
  }
 return 0;
}

else return (u-v == -1 || u-v==1 || u-v == -orderG() +1 || u-v == orderG() -1);
}
