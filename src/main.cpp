#include <iostream>
#include <fstream>
//#include "../graph/q_golomb.c"
//#include "../graph/n_150_m_2351.c"
#include "../graph/chvatal.c"
#include "dotMaker.hpp"

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

void saveToFile(string fname, string s){
	cout << "Saving the clauses produced. " << endl;
	string file_name = DATA_FOLDER + fname + ".txt";
    ofstream file(file_name);
    if(file){
        file << s;
    }else{
	cout << "The saving failed. " << endl;	
    }
    file.close();
}

void createSAT(string fname){
	cout << "Starting the creation of the SAT clauses" << endl;

    string res = "c\n";
    res+="c starts with comments \n";
    res+="c\n";
    int nbVar = 2*orderG()*(orderG()-1);
    int nbClauses = 7*orderG()*(orderG()-1);
    res += "p cnf " + to_string(nbVar)
        + ' ' + to_string(nbClauses) + "\n";

    res += firstClauses();
    res += secondClauses();

    saveToFile(fname, res);
	cout << "End of the creation" << endl;
}

int main(int argc, char** argv){
	
	std::string name;
	if(argc > 1){
		name = argv[1];
	}else{
		name = DEFAULT_FILE_NAME;
	}
	createSAT(name);
	glucose_launcher(name, ".txt");
	construct_triangle_partition(name + GLUCOSE_RESULT, "test");
	write_graph(name);
	export_file_as_png(name);
	return 0;
}
