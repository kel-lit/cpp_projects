#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template <typename T>
void debug(T msg){

	std::cout << msg << std::endl;
}

int main(int argc, char* argv[]){

	if (argc != 2){
		std::cout << "Please provide a single path to .bmp image." << std::endl;
		return 1;
	}

	std::string file_path = argv[1];
	std::ifstream image;

	image.open(file_path, std::ios::binary);

	if (!image.is_open()){
		debug("Failed to open file. Aborting.");
		return 1;
	}

	std::vector<char> byte_array;

	char byte;
	while(image.get(byte)){
		byte_array.push_back(byte);
	}

	return 0;

}