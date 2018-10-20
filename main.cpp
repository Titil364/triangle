#include <iostream>
#include <fstream>
#include "./graph/d_G33.c"

using namespace std;

int replaceVar(int u, int v, int parite){
    int tab = (parite-1)*orderG(); // In which "tab" do we have to count the variables
    // u on columns & v on lines in first and second "tab"
    int add = v*orderG() + u;
    return tab + add;
}

string firstClauses(){
    string res = "";
    for(int u=0; u<orderG();u++){
        for(int v=0;v<orderG();v++){
            if(v!=u && are_adjacent(u, v)){
                res += to_string(replaceVar(u, v, 1)) + " 0\n";
                res += to_string(replaceVar(u, v, 2)) + " 0\n";
                res += to_string(replaceVar(-u, v, 1)) + ' ' + to_string(replaceVar(u, v, 2)) + " 0\n";
            }
        }
    }
    return res;
}

string secondClauses(){
    string res = "";
    for(int u=0; u<orderG();u++){
        for(int v=0;v<orderG();v++){
            if(v!=u && are_adjacent(u, v)){
                res += to_string(replaceVar(-u, v, 1)) + ' ' + to_string(replaceVar(v, u, 1)) + " 0\n";
                res += to_string(replaceVar(-u, v, 1)) + ' ' + to_string(replaceVar(v, u, 2)) + " 0\n";
                res += to_string(replaceVar(-u, v, 2)) + ' ' + to_string(replaceVar(v, u, 1)) + " 0\n";
                res += to_string(replaceVar(-u, v, 2)) + ' ' + to_string(replaceVar(v, u, 2)) + " 0\n";
            }
        }
    }
    return res;
}

void saveToFile(string s){
    ofstream file;
    file.open("./sort/cnfSat00.txt");
    if(file.is_open()){
        file << s;
    }
    file.close();
}

int main(){
    string res = "c\n";
    res+="c starts with comments \n";
    res+="c\n";
    int nbVar = 2*orderG()*(orderG()-1);
    int nbClauses = 7*orderG()*(orderG()-1);
    res += "p cnf " + to_string(nbVar)
        + ' ' + to_string(nbClauses) + "\n";

    res += firstClauses();
    res += secondClauses();

    saveToFile(res);
    return 0;
}
