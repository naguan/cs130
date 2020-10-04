#include "hashTable1.h"

hashTable::hashTable(int size){ 
	std::srand(std::time(nullptr));
	this->size = size + 1;
	table.resize(this->size);
	for(int i = 0; i < 4; i++){
		this->arr[i] = std::rand() % (this->size) ; //creates random coefficients for hash
	}
/*
	arr[0] = 162; //least sig
	arr[1] = 210;
	arr[2] = 89;
	arr[3] = 10; //most sig
*/
}

void hashTable::insert(std::string ip){
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
		std::cerr <<"Error: could not delete "<<  ip << " because it does not exist." << std::endl;
	}else{
		for(std::string it : table[hash(ip)]){ 
			if(it == ip){
				table[hash(ip)].remove(ip);
				this->deleted++;     
				return;     
			}
		}
	}
	return;
}
int hashTable::hash(std::string ip){ //hashs ip by placing the 4 parts of ip into array
	std::string temp = "";
	int num[4];
	int iterator = 0;
	int sum = 0;
	for(int i = 0; i<ip.length(); i++){ //<=
		if(isdigit(ip[i])){
			temp += ip[i];
		}else{
			num[iterator] = (stoi(temp) * this->arr[iterator]); //multiplies number by coefficiet
			iterator++;
			temp = "";
		}
	}
	num[iterator] = (stoi(temp) * this->arr[iterator]);
	iterator++;
	temp = "";
	for(int j = 0; j < 4; j++){ //add all four values together
		sum += num[j];
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
	for(std::list<std::string> it : table){
		if(it.empty()){
			emptyCount++;
		} 
		if(it.size() == 1){
			justOneCount++;
		}
	}
	std::cout << arr[3] << " " << arr[2] << " " << arr[1] << " " << arr[0] << std::endl; //0 --> least sig, 3 most sig
	std::cout << inserted << std::endl;
	std::cout << deleted << std::endl;
	std::cout << emptyCount << std::endl;
	std::cout << justOneCount << std::endl;
	std::cout << this->maxCollision << " " << this->maxLocation << std::endl;
}
