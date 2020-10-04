#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

struct node{ //struct that makes nodes for the tree
	node *left, *right, *parent;
	int key; 
	node(int i){
		this->key = i;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
	}
	//getters
	int getKey(){
		return this->key;
	}
	node* getLeft(){
		return this->left;
	}
	node* getRight(){
		return this->right;
	}
	node* getParent(){
		return this->parent;
	}
	//setters
	void setLeft(node* n){
		this->left = n;
	}
	void setRight(node * n){
		this->right = n;
	}
	void setParent(node* n){
		this->parent = n;
	}
};
class splayTree{
	private:
		node* t;
	public:
		splayTree();

		void find(int i); //finds the node with key i
		void insert(int i); //inserts node with key i
		void del(int i); //deletes node with key i
		
		node* splay(node* x); //splays tree at node x
		void singleRot(node* x); //zig/zag operation at node x
		void twoSingRot(node* x); //zig-zig/zag-zag at node x
		void doubleRot(node* x); //zig-zag/zag-zig at node x
		
		node* access(int i); //accesses the node with key i, splays that node or the last known node
		node* join(node* t1, node* t2); //joins two subtrees together; t1 -> left, t2, -> right
		node* split(int i, node* t); //splits the subtree into two by returning one and passing the other by ref

		void print(); //prints splay tree
		void printAtH(node* t, int h); //prints the nodes at level H
		int getHeight(node*t); //gets height of tree

};