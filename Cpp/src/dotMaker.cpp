#include <iostream>
#include <fstream>

const std::string DATA_FOLDER = "data/";
const std::string FILE_EXTENSION = ".dot";
const std::string IMG_EXTENSION = ".png";

void export_graph_as_png(std::string in, std::string out)
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
	std::string img_path = DATA_FOLDER + out  + IMG_EXTENSION;
	std::string transform = "dot -Tpng \""+path+"\" > \""+img_path+"\"";
	system(transform.c_str());
}

void export_graph_as_dot(std::string in, std::string out){

	ofstream 


}


int main(int argc, char** argv){
	return 0;
}




