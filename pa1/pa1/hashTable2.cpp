#include "hashTable2.h"
#include <bitset>
#include <sstream>
hashTable::hashTable(int size){ 
	std::srand(std::time(nullptr));
	int temp = 0;
	bool prime = true;
	bool no = true;
	this->origSize = size;
	while(no){
		size++;
		prime = true;
		for(int i = 2; i<=size/2; i++){
			if(size%i == 0){
				prime = false;
				i = size; //breaks out of for loop
			}
		}
		if(prime){
			this->size = size;
			no = false;
		}
	}
	table.resize(this->size);
	for(int i = 0; i < 31; i++){
		this->randCoeffs.push_back(std::rand() % (this->size) ); //creates random coefficients for hash
	}
}

void hashTable::insert(std::string ip){ //inserts into table
	if(existsInTable(ip)){
		std::cerr << ip<<" already exists." << std::endl;
	}else{

		table[hash(ip)].push_front(ip);
		this->inserted++; 
		if(this->maxCollision == -1 && this->maxLocation == -1){ //overwrites initial conditions on the variables
			this->maxCollision = table[hash(ip)].size();
			this->maxLocation = hash(ip);
		}
		if(table[hash(ip)].size() > this->maxCollision){ //checks to see size of vector > current max val
			this->maxCollision = table[hash(ip)].size();
			this->maxLocation = hash(ip);
		}
		if((table[hash(ip)].size() == this->maxCollision) && (hash(ip)>=this->maxLocation) ){ //if list same size, update location val
			this->maxLocation = hash(ip);

		}
	}
	return;
}

void hashTable::lookup(std::string ip){  //looks up ip
	for(std::string it : table[hash(ip)] ){
		if(it == ip){
			std::cout << ip << ": found." << std::endl;
			return;
		}
	}
	std::cout << ip << ": not found."<< std::endl;
	return;
}

void hashTable::del(std::string ip){ //checks to see if ip in table, if it is, remove it
	if(!existsInTable(ip)){
		std::cerr <<"Error: could not delete "<<ip << " because it does not exist." << std::endl;
	}else{
		for(std::string it : table[hash(ip)]){ 
			if(it == ip){
				if(this->maxCollision == -1 && this->maxLocation == -1){ //overwrites initial conditions on the variables
					this->maxCollision = table[hash(ip)].size();
					this->maxLocation = hash(ip);
				}
				if(table[hash(ip)].size() > this->maxCollision && hash(ip) > this->maxLocation){ //checks to see size of vector > current max val
					this->maxCollision = table[hash(ip)].size();
					this->maxLocation = hash(ip);
					std::cout << maxLocation << std::endl;
				}
				if((table[hash(ip)].size() == this->maxCollision) && (hash(ip) > this->maxLocation) ){ //if list same size, update location val
					this->maxLocation = hash(ip);
					std::cout << maxLocation << std::endl;
				}
				table[hash(ip)].remove(ip);
				this->deleted++;
				return;       
			}
		}
		
	}
	return;
}

int hashTable::hash(std::string ip){ //hashs ip
	std::string temp = "";
	std::string binaryStr = this->converter(ip);
	std::vector<std::string> t;
	int tempInt = 0;
	int sum = 0;
	int logSize = log2(origSize);
	for(int i = 31; i > -1; i--){
		if(logSize > temp.length()){
			temp = binaryStr[i] + temp;
		}
		else{
			t.push_back(temp);
			temp.clear();
			temp += binaryStr[i];
		}
	}
	t.push_back(temp);
	this->groupingSize = t.size();
	for(int j = 0; j < t.size(); j++){
		tempInt = std::stoi(t[j], nullptr, 2);
		sum += this->randCoeffs[j] * tempInt;
	}
	return (sum % this->size);
	
	
	
}

bool hashTable::existsInTable(std::string ip){ //same thing as lookup essentially but returns a bool
	for( std::string it : table[hash(ip)] ){
		if(it == ip){
			return true;
		}
	}
	return false;

}

void hashTable::stat(){ //prints out all the stuff
	int iterator = 0;
	int emptyCount = 0;
	int justOneCount = 0;
	int maxLocation = 0;
	for(int i = 0; i<this->groupingSize; i++){
			std::cout<<this->randCoeffs[i]<< ' ';
	}
	std::cout<<std::endl;
	for(std::list<std::string> it : table){
		if(it.empty()){
			emptyCount++;
		} 
		if(it.size() == 1){
			justOneCount++;
		}
	}
	std::cout << inserted << std::endl;
	std::cout << deleted << std::endl;
	std::cout << emptyCount << std::endl;
	std::cout << justOneCount << std::endl;
	std::cout << this->maxCollision << " " << this->maxLocation << std::endl;
}

std::string hashTable::converter(std::string ip){ //converts the ip string to 32bit string
	int input;
	std::vector<int> eightBitBin;	
	std::stringstream ss(ip);
	while (ss >> input) {
		if (ss.peek() == '.') {
			ss.ignore();
		}
		eightBitBin.push_back(input);
	}
	std::bitset<8> firstBits(eightBitBin[0]);
	std::bitset<8> secondBits(eightBitBin[1]);
	std::bitset<8> thirdBits(eightBitBin[2]);
	std::bitset<8> fourthBits(eightBitBin[3]);

	return firstBits.to_string() + secondBits.to_string() + thirdBits.to_string() + fourthBits.to_string();
	
}
