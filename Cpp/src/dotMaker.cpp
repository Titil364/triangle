#include <iostream>
#include <fstream>
#include <unistd.h>

const std::string DATA_FOLDER = "data/";
const std::string FILE_EXTENSION = ".dot";
const std::string IMG_EXTENSION = ".png";

const std::string FILE_NAME = "test";

/**
	\brief Export the file given as a .png (the file must be a .dot) 
	\param in Name of the file to export
 */
void export_file_as_png(std::string in)
{
	std::string path = DATA_FOLDER + in + FILE_EXTENSION;
	static const std::string command = "mkdir data";

	// Test if the folder can be accessed
	if(access("data",X_OK))
	{
		system(command.c_str());
		// sleeps 100ms to make sure the system has created the folder, else it may bug
		usleep(100000);
	}
	std::string img_path = DATA_FOLDER + in  + IMG_EXTENSION;
	std::string transform = "dot -Tpng \""+path+"\" > \""+img_path+"\"";
	system(transform.c_str());
}

/**
	\brief  
	\param SAT_ANSWER The name of the file used to know if the formula is satisfiable
 */
int construct_triangle_partition(std::string SAT_ANSWER, std::string out){

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
		std::cout << line <<std::endl;
		
	}else{
		std::cout << "ERROR : Cannot open the SAT_ANSWER file. ";
		return 1;
	}
	
	SAT_FILE.close();
	return 0;
}


int main(int argc, char** argv){
	std::string name;
	if(argc > 1){
		name = argv[1];
	}else{
		name = "test2";
	}
		construct_triangle_partition(name, "test");
	return 0;
}




