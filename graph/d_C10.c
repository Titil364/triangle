int orderG(){
return 20;
}

int sizeG(){
return 30;
}

int are_adjacent(int u, int v){
if (0<= u && 0<=v && u<=10 && v<=10){
 if(0<= u && 0<=v && u<10 && v<10){
  return (((10+u-v)%10==1)||((10+v-u)%10==1));
 }	
 else return 0;
}

else return (u-v == -1 || u-v==1 || u-v == -10 +1 || u-v == 10 -1);
}
