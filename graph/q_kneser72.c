int orderG(){
return 42;
}

int sizeG(){
return 147;
}

int are_adjacent(int u, int v){
if (0<= u && 0<=v && u<=orderG() && v<=orderG()){
    if(0<= u && 0<=v && u<21 && v<21){
        int i,j,index=0;
        int T[21];
        for(i=0;i<7;i++)
            for(j=i+1;j<7;j++)
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
