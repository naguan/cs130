#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <time.h>
#include <array>
#include <ctime>
#include <cmath>
#include <cstdlib>
class hashTable{
    private:
        std::vector<std::list<std::string>> table; //vector that will contain the lists
        std::vector<int> randCoeffs; //vector of rand coeffs
        int size; //size of table
        int maxLocation=-1; //max location for the max collisions
        int maxCollision=-1; //max collisions for the entire table
        int inserted = 0; //num of inserted ip addrs
        int deleted = 0; //num of deleted ip addrs
        int groupingSize = 0; //group of bin
	  int origSize;

     public:
        hashTable(int size); //constructor
        bool existsInTable(std::string ip);//checks to see if ip is in table
        void insert(std::string ip);//inserts ip
        void del(std::string ip);//deletes ip
        void lookup(std::string ip);//look up ip to see if in table
        void stat(); //prints out the variables of the hash table
        int hash(std::string ip);//hash func
        std::string converter(std::string ip);//converts ip addr to 32 bit binary
};
