#include <iostream>
#include <fstream>
#include <assert.h>
//#include "../graph/q_golomb.c"
//#include "../graph/n_150_m_2351.c"
//#include "../graph/chvatal.c"
//#include "../graph/SixVertex.c"
//#include "../graph/n_15_m_24.c"
//#include "../graph/n_15_m_64.c"
//#include "../graph/n_15_m_32.c"
//#include "../graph/d_C10.c"
#include "../graph/p_sierp3.c"
#include "dotMaker.hpp"

using namespace std;

int replaceVar(int u, int v, int parite){
    int tab = (parite-1)*orderG()*orderG(); // In which "tab" do we have to count the variables
    // u on columns & v on lines in first and second "tab"
    int add = v*orderG() + u;
    return tab + add;
}

/**
	\brief computes the first clauses :
        *every vertex has a left neighbor
        *every vertex has a right neighbor
        *those two vertices are different;
	and return a string corresponding to that clauses
	\param
 */
string firstClauses(){
    string res = "";
    for(int u=0; u<orderG();u++){
        for(int v=0;v<orderG();v++){
            if(v!=u && are_adjacent(u, v)){
                res += to_string(replaceVar(u, v, 1)) + " ";
                //res += to_string(u) + "," +  to_string(v) + "," + to_string(1) + "   ";
            }
        }
        res += " 0\n";
        for(int v=0;v<orderG();v++){
            if(v!=u && are_adjacent(u, v)){
                res += to_string(replaceVar(u, v, 2)) + " ";
                //res += to_string(u) + "," +  to_string(v) + "," + to_string(2) + "   ";
            }
        }
        res += " 0\n";
        for(int v=0;v<orderG();v++){
            if(v!=u){
                if(are_adjacent(u, v)){
                    res += "-" + to_string(replaceVar(u, v, 1)) + " -" + to_string(replaceVar(u, v, 2)) + " 0\n";
                    /*res += "-" + to_string(u) + "," +  to_string(v) + "," + to_string(1) + "   -"
                    + to_string(u) + "," +  to_string(v) + "," + to_string(2) + " 0\n";*/
                } else {
                    res += "-" + to_string(replaceVar(u, v, 1)) + " 0\n";
                    res += "-" + to_string(replaceVar(u, v, 2)) + " 0\n";
                    /*res += "-" + to_string(u) + "," +  to_string(v) + "," + to_string(1) + " 0\n";
                    res += "-" + to_string(u) + "," +  to_string(v) + "," + to_string(2) + " 0\n";*/
                }
            }
        }
    }
    return res;
}

/**
	\brief computes the second clauses :
        *if u is v left or right neighbor then,
            v is u left or right neighbor;
	and return a string corresponding to that clauses
	\param
 */
string secondClauses(){
    string res = "";
    for(int u=0; u<orderG();u++){
        for(int v=0;v<orderG();v++){
            if(v!=u && are_adjacent(u, v)){
                res += "-" + to_string(replaceVar(u, v, 1))
                    + ' ' + to_string(replaceVar(v, u, 1))
                    + ' ' + to_string(replaceVar(v, u, 2)) + " 0\n";
                res += "-" + to_string(replaceVar(u, v, 2))
                    + ' ' + to_string(replaceVar(v, u, 1))
                    + ' ' + to_string(replaceVar(v, u, 2)) + " 0\n";
                /*res += "-" + to_string(u) + "," +  to_string(v) + "," + to_string(1)
                    + "   " + to_string(v) + "," +  to_string(u) + "," + to_string(1)
                    + "   " + to_string(v) + "," +  to_string(u) + "," + to_string(2) + " 0\n";
                res += "-" + to_string(u) + "," +  to_string(v) + "," + to_string(2)
                    + "   " + to_string(v) + "," +  to_string(u) + "," + to_string(1)
                    + "   " + to_string(v) + "," +  to_string(u) + "," + to_string(2) + " 0\n";*/
            }
        }
    }
    return res;
}

/**
	\brief computes the third clauses :
        *a vertex cannot appear in more than one triangle;
	 and return a string corresponding to that clauses
	\param
 */
string thirdClauses(){
    string res = "";
        for(int k= 1; k<=2; k++){
            for(int u=0; u<orderG();u++){
                for(int v=0;v<orderG();v++){
                    if(u != v && are_adjacent(u, v)){
                        for(int w=0;w<orderG();w++){
                            if(w != u && w != v
                                && are_adjacent(w, u)){
                                if(are_adjacent(w, v)){
                                    res += "-" + to_string(replaceVar(u, w, k))
                                        + " -" + to_string(replaceVar(u, v, k)) + " 0\n";
                                    /*res += "-" + to_string(u) + "," +  to_string(w) + "," + to_string(k)
                                        + "   -" + to_string(u) + "," +  to_string(v) + "," + to_string(k) + " 0\n";*/
                                } else {
                                    res += "-" + to_string(replaceVar(u,v,1))
                                        + " -" + to_string(replaceVar(u,w,2)) + " 0\n";
                                    res += "-" + to_string(replaceVar(u,v,2))
                                        + " -" + to_string(replaceVar(u,w,1)) + " 0\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    return res;
}

int saveToFile(string fname, string s){
	cout << "Saving the clauses produced. " << endl;
	string file_name = DATA_FOLDER + fname + ".txt";
	ofstream file(file_name);
    if(file){
        file << s;
    }else{
	cout << "The saving failed. " << endl;
    	return 1;
    }
    file.close();
	return 0;
}

void createSAT(string fname){
	cout << "Starting the creation of the SAT clauses" << endl;

    string res = "c\n";
    res+="c clauses corresponding to " + fname +"\n";
    res+="c\n";
    int nbVar = 2*orderG()*(orderG()-1);
    int nbClauses = 2 * orderG()
        + 3*orderG()*(orderG()-1)
        + 2*orderG()*(orderG()-1)*(orderG()-2);
    res += "p cnf " + to_string(nbVar)
        + ' ' + to_string(nbClauses) + "\n";

    res += firstClauses();
    res += secondClauses();
    res += thirdClauses();

    saveToFile(fname, res);
	cout << "End of the creation" << endl;
}

bool testVarReplacement(){
    struct xuv var;
    var.u = orderG();
    var.v = 5;
    var.parite = 2;
    struct xuv var2;
    var2.u = orderG();
    var2.v = 5;
    var2.parite = 2;
    int n = replaceVar(var.u, var.v, var.parite);
    reverse_var(n, &var2);
    cout << var.u << " " << var.v << " " << var.parite << "\n";
    cout << var2.u << " " << var2.v << " " << var2.parite << "\n";
    return (var.u == var2.u
                && var.v == var2.v
                && var.parite == var2.parite);
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
	std::vector<struct xuv*> partition;
	construct_triangle_partition(name + GLUCOSE_RESULT, partition/*, "test"*/);
	write_graph(name, partition);
	export_file_as_png(name);

	//Test
//    assert(testVarReplacement());
	return 0;
}
