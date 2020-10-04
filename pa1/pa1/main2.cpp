#include "hashTable2.h"


int main(){
	int size;
	std::string line;
	std::string temp = "";
	std::string ip = "";
	getline(std::cin, line);
	size = stoi(line);
	hashTable h(size); 
	while(getline(std::cin,line)){
		for(int i = 0; i < line.length(); i++){
			if(isalpha(line[i])){
				temp += line[i];
			}else if(isdigit(line[i]) || line[i] == '.'){
				ip += line[i];

			}else{
        			//if there is a space in the line --> do nothing
			}
		}
		if(temp == "insert"){
			h.insert(ip);
		}else if(temp == "lookup"){
			h.lookup(ip);
		}else if(temp == "delete"){
			h.del(ip);
		}else if(temp == "stat"){
			h.stat();
		}else{ 
			std::cerr << "Invalid input in txt file" << std::endl;
        	//any other output
        }
        temp = "";
        ip = "";
	}
}
