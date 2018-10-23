#ifndef DOTMAKER_HPP
#define DOTMAKER_HPP


#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>

const bool DEBUG = false;

const std::string DATA_FOLDER = "data/";
const std::string FILE_EXTENSION = ".dot";
const std::string IMG_EXTENSION = ".png";

const std::string DEFAULT_FILE_NAME = "chvatal";

const std::string GLUCOSE = "glucose/simp/glucose";
const std::string GLUCOSE_FOLDER = "glucose/simp/";
const std::string GLUCOSE_RESULT = "_SAT";

struct variables{
int u;
int v;
int parite;
};

/**
	\brief Export the file given as a .png (the file must be a .dot)
	\param in Name of the file to export
 */
void export_file_as_png(std::string in)
{
	//child
	if(fork() == 0){
		std::string path = DATA_FOLDER + in + FILE_EXTENSION;
		static const std::string command = "mkdir data";

		// Test if the folder can be accessed
		if(access(DATA_FOLDER.c_str(),X_OK) != 0)
		{
			system(command.c_str());
			// sleeps 100ms to make sure the system has created the folder, else it may bug
			usleep(100000);
		}
		std::string img_path = DATA_FOLDER + in  + IMG_EXTENSION;
		std::string transform = "dot -Tpng \""+path+"\" > \""+img_path+"\"";

		execl("/usr/bin/dot", "dot", "-Tpng", path.c_str(), "-o", img_path.c_str());
	}else{//parent
		std::cout << "Creating the png in background by my child. " << std::endl;
	}
}

/**
	\brief Display on the screen the value of the vector (must be a string vector)
	\param v A String vector
 */
void display_string_vector(std::vector< std::string> v){
	for(std::vector< std::string>::iterator it = v.begin(); it!=v.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

/**
	\brief Transform a variable n into a triplet u,v,n (n=[1-2])
	\param n The variable returned by glucose, and var, a structure that represents
	the equivalent of n, using u, v and the number 1 or 2
 */
variables reverse_var(int n, struct variables var){
    if(n > orderG()*orderG()){
        var.parite = 2;
    } else {
        var.parite = 1;
    }
    int tab = n-(var.parite-1)*orderG()*orderG();
    var.v = tab/orderG();
    var.u = tab-var.v*orderG();
    return var;
}

/**
	\brief
	\param SAT_ANSWER The name of the file used to know if the formula is satisfiable
 */
int construct_triangle_partition(std::string SAT_ANSWER/*, std::string out*/){

	std::cout << std::endl << "Starting the construction of the graph" << std::endl;
	std::string line;
	std::string SAT_ANSWER_PATH = DATA_FOLDER + SAT_ANSWER;
	std::ifstream SAT_FILE(SAT_ANSWER_PATH.c_str());
	const std::string UNSAT = "UNSAT";

	if(SAT_FILE){
		std::getline(SAT_FILE, line);
		if(UNSAT.compare(line) == 0){
			std::cout << "The formula is UNSAT. Please choose an other one. " << std::endl;
			return 2;
		}

		size_t i = 0;
		std::vector< std::string> Tvariables;
		std::vector< std::string> Fvariables;
		std::vector< std::string> variables;
		std::string delimiter(" "), token;
		while((i = line.find(delimiter)) != std::string::npos){
			token = line.substr(0, i);
			//Token displayer
			//std::cout << token << std::endl;
			if(token.at(0) == '-'){
				Fvariables.push_back(token.substr(1, token.length()));
			}else{
				Tvariables.push_back(token);
			}
			variables.push_back(token);
			line.erase(0, i + delimiter.length());
		}

		if(DEBUG){
			std::cout << "Positive variables : " << std::endl;
			display_string_vector(Tvariables);
			std::cout << "Negative variables : " << std::endl;
			display_string_vector(Fvariables);
			std::cout << "All variables : " << std::endl;
			display_string_vector(variables);
			//Il faut détecter qui est le voisin de qui
			std::cout << line <<std::endl;
		}

	}else{
		std::cout << "ERROR : Cannot open the SAT_ANSWER file. ";
		return 1;
	}

	SAT_FILE.close();
	return 0;
}

/**
	\brief Display the currect directory on the screen
 */
int write_graph(std::string fname){
	std::cout << "Starting creating the .dot file. " <<std::endl;
	if(graph == NULL){
		std::cout << "The variable graph doesn't exist. " <<std::endl;
		return 1;
	}

	std::ofstream oGraph(DATA_FOLDER + fname + FILE_EXTENSION);

	if(oGraph){
		std::string line;
		line = "strict graph{ \n";
		oGraph << line;
		for(int i = 0; i < orderG(); i++){

			for(int y = i+1; y < orderG(); y++){
				if(graph[i][y] == 1){
					line = std::to_string(i)+" -- "+ std::to_string(y) ;
					if(false){
						line += "[color=deeppink]";
					}
					line += "; \n";
					oGraph << line;
				}
				line.clear();
			}
		}
		line = "}";
		oGraph << line;
	}
	oGraph.close();
	return 0;
}

/**
	\brief Display the currect directory on the screen
 */
void display_current_directory(){
	std::cout << "Current directory " << get_current_dir_name() << std::endl << std::flush;
}
/**
	\brief Launch glucose with the "in" file (must be in DATA_FOLDER)
	\param in Name of the file
	\param extension The extension of the file (facultative)
 */
int glucose_launcher(std::string in, std::string extension)
{

	static const std::string command = GLUCOSE + " "+ DATA_FOLDER + in + extension + " " + DATA_FOLDER + in + GLUCOSE_RESULT;


	std::cout << "Lauching : " + command << std::endl;
	// Test if the folder can be accessed
	if(access(GLUCOSE_FOLDER.c_str(), X_OK) == 0)
	{
		system(command.c_str());
		// sleeps 100ms to make sure the system has created the file
		usleep(100000);
		std::cout << "Lanching success. " << std::endl;
		return 0;
	}
		std::cout << "Lanching failed. " << std::endl;
	//Erreur
	return 1;
}



#endif
