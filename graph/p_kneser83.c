int orderG(){
return 112;
}

int sizeG(){
return 392;
}

int are_adjacent(int u, int v){
if (0<= u && 0<=v && u<=orderG() && v<=orderG()){
    if(0<= u && 0<=v && u<56 && v<56){
        int i,j,k,index=0;
        int T[56];
        for(i=0;i<8;i++)
            for(j=i+1;j<8;j++)
                for(k=j+1;k<8;k++)
                {
                    T[index]= (1 << i) + (1 << j)+(1<<k);
                    index++;
                }
        return (!(T[u] & T[v]));
    }	
    else return 0;
}


else return (u-v == -1 || u-v==1 || u-v == -orderG() +1 || u-v == orderG() -1);
}
