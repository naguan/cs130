#include "splayTree.h"

int main(){
	int i = 0;
	std::string line;
	std::string temp;
	std::string space = " ";
	splayTree* tree = new splayTree();
	while(std::getline(std::cin, line)){
		if(line == "print"){
			tree->print();
		}
		else{
			i = line.find(space);
			temp = line.substr(0, i);
			if(temp == "insert"){
				line = line.substr(i+1, line.length()-i);
				tree->insert(std::stoi(line));
				
			}
			if(temp == "find"){
				line = line.substr(i+1, line.length()-i);
				tree->find(std::stoi(line));
			}
			if(temp == "delete"){
				line = line.substr(i+1, line.length()-i);
				tree->del(std::stoi(line));
			}
		}
	}
	delete tree;
	return 0;
}