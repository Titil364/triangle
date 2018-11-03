#include <iostream>
#include <fstream>
#include <assert.h>


/********************************************************************
*                                                                 *
* ****  **   **  ****  ****  ****  ****    ****  ****  ****  **** *
*  **   * * * *  *  *  *  *  *  *   **     *  *  *  *  **    *  * *
*  **   * * * *  ***   *  *  ***    **     ****  ***   **    **** *
* ****  *  *  *  *     ****  *  *   **     *  *  *  *  ****  *  * *
*                                                                 *
*********************************************************************/

//#include "../graph/q_golomb.c" //UNSAT
//#include "../graph/chvatal.c" //UNSAT
//#include "../graph/d_C10.c" //UNSAT
//#include "../graph/p_sierp3.c" //SAT
//#include "../graph/p_sierp33.c" //SAT
//#include "../graph/sierp33.c" //SAT
//#include "../graph/G33.c" //SAT
//#include "../graph/G36.c" //SAT
//#include "../graph/G40.c" //GLUCOSE TOO LONG
//#include "../graph/G60.c" //KILL
//#include "../graph/d_G30.c" //UNSAT
//#include "../graph/p_petersen.c" //UNSAT
//#include "../graph/p_moser.c" //UNSAT
//#include "../graph/n_15_m_24.c" //SAT
//#include "../graph/n_15_m_32.c" //SAT
//#include "../graph/n_15_m_64.c" //SAT
//#include "../graph/n_30_m_69.c" //SAT
//#include "../graph/n_30_m_108.c" //SAT
//#include "../graph/n_30_m_221.c" //SAT 
//#include "../graph/n_45_m_124.c" //SAT
//#include "../graph/n_45_m_234.c" //SAT
//#include "../graph/n_45_m_524.c" //SAT
//#include "../graph/n_90_m_479.c" //SAT
#include "../graph/n_90_m_2030.c" //SAT
//#include "../graph/n_150_m_2351.c" //SAT
//#include "../graph/K6.c" //SAT
//#include "../graph/K6-2.c" //SAT
//#include "../graph/K4.c" //UNSAT
//#include "../graph/K4-1.c" //UNSAT
//#include "../graph/K4-2.c" //UNSAT
//#include "../graph/K4-3.c" //UNSAT
//#include "../graph/K5.c" //UNSAT
//#include "../graph/K3.c" //SAT
//#include "../graph/m_G70.c" //BAD ALLOC
//#include "../graph/G55.c" //Glucose run 2 hours and can't find
//#include "../graph/d_10K2.c" //UNSAT
//#include "../graph/p_m5.c" //UNSAT
//#include "../graph/p_m11.c" //UNSAT
//#include "../graph/p_m23.c" //UNSAT
//#include "../graph/p_m47.c" //UNSAT
//#include "../graph/p_m95.c" //UNSAT
//#include "../graph/q_GXXIXXI.c" //UNSAT
//#include "../graph/q_kneser62.c" //UNSAT
//#include "../graph/q_kneser72.c" //UNSAT
//#include "../graph/p_kneser83.c" //UNSAT


/********************************************************************
*                                                                 *
* ****  **   **  ****  ****  ****  ****    ****  ****  ****  **** *
*  **   * * * *  *  *  *  *  *  *   **     *  *  *  *  **    *  * *
*  **   * * * *  ***   *  *  ***    **     ****  ***   **    **** *
* ****  *  *  *  *     ****  *  *   **     *  *  *  *  ****  *  * *
*                                                                 *
*********************************************************************/


#include "dotMaker.hpp"

std::vector< std::string> HELP = {"help", "HELP", "h", "H"};


using namespace std;

/**
	\brief Create the variable of X(u, v, parite) where v is the \"parite\" neighbour of u 
	\param u a vertex
	\param v a vertex
	\param parite an integer 1 or 2
	\return The variable Xuvparite converted in integer
 
 */
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
    string res = "c Begin first Clauses \n";
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

                } else {
                    res += "-" + to_string(replaceVar(u, v, 1)) + " 0\n";
                    res += "-" + to_string(replaceVar(u, v, 2)) + " 0\n";
                }
            }
        }
    }
	res += "c End of first Clauses \n";
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
    string res = "c Begin second Clauses \n";
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
	res += "c End of second Clauses \n";
    return res;
}

/**
	\brief computes the third clauses :
        *a vertex cannot appear in more than one triangle;
	 and return a string corresponding to that clauses
	\return string 
 */
string thirdClauses(){
    string res = "c Begin third Clauses \n";
    for(int u=0; u<orderG();u++){
	for(int v=0;v<orderG();v++){
	    if(u != v && are_adjacent(u, v)){
		for(int w=0;w<orderG();w++){
		    if(w != u && w != v
			&& are_adjacent(w, u)){
			if(are_adjacent(w, v)){
				for(int k= 1; k<=2; k++){
                                    res += "-" + to_string(replaceVar(u, w, k))
                                        + " -" + to_string(replaceVar(u, v, k)) + " 0\n";
				}
				
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
	res += "c End Third Clauses \n";
    return res;
}


string fourthClauses(){
	string res = "c Begin Fourth Clauses \n";
	for(int u=0; u<orderG();u++){
		for(int v=0;v<orderG();v++){
			if(u != v && are_adjacent(u, v)){
				for(int w=0;w<orderG();w++){
					if(w != u && w != v && are_adjacent(u, w)){
						if(are_adjacent(v, w)){
							for(int z=0; z<orderG(); z++){
								if(z!=u && z!=v && z!=w){
									res +=  " -" + to_string(replaceVar(v, z, 2))
									+	" -" + to_string(replaceVar(u, v, 1))
									+	" -" + to_string(replaceVar(u, w, 2)) + " 0\n";

									res +=  " -" + to_string(replaceVar(v, z, 1))
									+	" -" + to_string(replaceVar(u, v, 1))
									+	" -" + to_string(replaceVar(u, w, 2)) + " 0\n";

									res +=  " -" + to_string(replaceVar(w, z, 2))
									+	" -" + to_string(replaceVar(u, v, 1))
									+	" -" + to_string(replaceVar(u, w, 2)) + " 0\n";

									res +=  " -" + to_string(replaceVar(v, z, 1))
									+	" -" + to_string(replaceVar(u, v, 1))
									+	" -" + to_string(replaceVar(u, w, 2)) + " 0\n";

									res +=  " -" + to_string(replaceVar(u, z, 2))
									+	" -" + to_string(replaceVar(u, v, 1))
									+	" -" + to_string(replaceVar(u, w, 2)) + " 0\n";

									res +=  " -" + to_string(replaceVar(u, z, 1))
									+	" -" + to_string(replaceVar(u, v, 1))
									+	" -" + to_string(replaceVar(u, w, 2)) + " 0\n";
								}
							}
						}
					} 
				}
			}
		}
	}
	res += "c End Fourth Clauses \n";
	return res;
}
int saveToFile(string fname, string s){
	cout << "Saving the clauses produced. " << endl;
	string file_name = DATA_FOLDER + fname + "_CNF";
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
	cout << "Starting creating the clauses. " << endl;

    string res = "c\n";
    res+="c clauses corresponding to " + fname +"\n";
    res+="c\n";
    int nbVar = 2*orderG()*orderG();
    int nbClauses = 2 * orderG()
        + 3*orderG()*(orderG()-1)
        + 2*orderG()*(orderG()-1)*(orderG()-2)
	+ orderG()%3*orderG();
    res += "p cnf " + to_string(nbVar)
        + ' ' + to_string(nbClauses) + "\n";

    res += firstClauses();
    res += secondClauses();
    res += thirdClauses();
    res += fourthClauses();

    saveToFile(fname, res);
	cout << "End of the creation. " << endl<<endl;
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

void mainProgram(std::string name){

	createSAT(name);
	glucose_launcher(name, "_CNF");
	std::vector<struct xuv*> partition;
	construct_triangle_partition(name + GLUCOSE_RESULT, partition);
	write_graph(name, partition);
	export_file_as_png(name);
}

int main(int argc, char** argv){
	std::string name;

	std::cout << "***********************************************************" << std::endl;
	std::cout << "*   Reduction From Partition Into Triangle to CNF-SAT     *" << std::endl;
	std::cout << "*   By Luc-Etienne Pommé, Cyril Govin                     *" << std::endl;
	std::cout << "***********************************************************" << std::endl << std::endl;
	if(argc > 1){
		name = argv[1];
		int i = 0;
		bool help = false;
		while(name.at(i) == '-' || name.at(i) == '\0'){
			i++;
		}
		std::string h = name.substr(i);
		if(i != 0){
			for(std::vector< std::string>::iterator it = HELP.begin();
				it != HELP.end(); ++it){
				if(!h.compare(*it)){
					help = true;
				}
			}
		
			if(help){
				
				std::cout << "How to launch : bin/main outputFileName [--big]" <<std::endl;
				std::cout << "OPTIONS: " <<std::endl;
				std::cout << "		--big Only write the partition into triangle in the .dot file.  " <<std::endl;
				std::cout << "DESCRIPTION: " <<std::endl;
				std::cout << "		The program use a graph included in main.cpp and writes 4 files in the folder  data/ :" <<std::endl<<std::endl;
				std::cout << "			DIMACS format file containing the graph traduced in CNF clauses (extension: _CNF) " <<std::endl;
			
				std::cout << "			GLUCOSE answer file, using the previous file glucose is called to write a file (extension: _SAT)" <<std::endl;
				std::cout << "			DOT format file, created using orderG() and are_adjavent(int u, int v) for the graph and the GLUCOSE's answer file to" <<std::endl;
				std::cout << "				color the edges of the partition into triangle (if found)" <<std::endl;
				std::cout << "			PNG format file, using the previous DOT FILE and Graphviz's \"dot\" program to extract a the graph with the partition into an image. " <<std::endl<<std::endl;
				std::cout <<"		It can only use one graph at a time. You need to change the include located in the begining of main.cpp between the commented \"import area\""<<std::endl;
				std::cout << "		to change the graph you want to test. "<<std::endl;
				std::cout << "		You can import your own graph but make sure your file is written in c or cpp and that it contains at least the three following functions : " <<std::endl;
				std::cout << "			orderG() which returns the order of the graph, the number of verteces  " <<std::endl;
				std::cout << "			sizeG() which returns the size of the graph, the number of edges. .  " <<std::endl;
				std::cout << "			are_adjacent(int u, int v) which returns 1 if the verteces u and v are adjacent, else returns 0. " <<std::endl<<std::endl;
				std::cout << "		Don't forget to add it in the dedicated \"import area\" section. " <<std::endl;
				std::cout << "		For more details about the function, please read the comments. "<<std::endl; 
				std::cout << "		" <<std::endl;

			}else{
				std::cout << "ERROR - Unknown parameter -"<<h <<". "  <<std::endl;
				std::cout << "Please use -h or --help if you need assistance. " <<std::endl;
				std::cout << " " <<std::endl;
			}
		}else{
			if(argc > 2){
				i = 0;
				std::string big = argv[2];
				while(big.at(i) == '-' || big.at(i) == '\0'){
					i++;
				}
				std::string bg = big.substr(i);
				if(!bg.compare("big")){
					BIG_GRAPH = true;
				}else{
					std::cout << "ERROR - Unknown parameter -"<< bg <<". "  <<std::endl;
					std::cout << "Please use -h or --help if you need assistance. " <<std::endl;
					std::cout << " " <<std::endl;

				}
				
			}	
				mainProgram(name);
		}
	}else{
		name = DEFAULT_FILE_NAME;
		mainProgram(name);
	}


	//Test
//    assert(testVarReplacement());
	return 0;
}
