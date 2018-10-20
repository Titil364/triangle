int orderG(){
return 40;
}

int sizeG(){
return 50;
}

int are_adjacent(int u, int v){
if (0<= u && 0<=v && u<=20 && v<=20){
if(0<= u && 0<=v && u<orderG() && v<orderG()){
  return (u+v==19);
 }	
 else return 0;
}

else return (u-v == -1 || u-v==1 || u-v == -20 +1 || u-v == 20 -1);
}
