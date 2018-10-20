int orderG(){
return 882;
}

int sizeG(){
return 1722;
}

int are_adjacent(int u, int v){
if (0<= u && 0<=v && u<=orderG() && v<=orderG()){
    if(0<=u && 0<=v && u<orderG() && v<orderG())
        return(
                (
                 (
                  ((u-v)%21==1) || ((v-u)%21== 1)
                 )
                 &&
                 (v/21)==(u/21)
                )
                ||
                (
                 (
                  (u/21-v/21)==1 || (v/21-u/21 ) == 1
                 )
                 &&
                 (v%21)==(u%21)
                 )
              );
    return 0;
 }
 else return (u-v == -1 || u-v==1 || u-v == -orderG() +1 || u-v == orderG() -1);
}
