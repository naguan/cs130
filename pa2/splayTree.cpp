#include "splayTree.h"

splayTree::splayTree(){ //constrcutor that sets the root t to NULL
	this->t == NULL;
}

node* splayTree::splay(node* x){ //splay the tree at node x
	while(x->getParent() != NULL){
		if(x->getParent()->getParent() == NULL) //condition for zig/zag
			singleRot(x);
		else if(x->getParent()->getParent()->getLeft() == x->getParent() && x->getParent()->getLeft() == x) //condition for zig-zig
			twoSingRot(x);
		else if(x->getParent()->getParent()->getRight() == x->getParent() && x->getParent()->getRight() == x) //condition for zag-zag
			twoSingRot(x);
		else //condition for zig-zag/zag-zig
			doubleRot(x);
	}
	return x;
}

void splayTree::singleRot(node* x){ //performs zig or zag depending on side of node 
	node* parent = x->getParent();
	if(x->getParent()->getLeft() == x){  //condition
		node* temp = x->getRight();
		x->setParent(NULL);
		x->setRight(parent);
		parent->setParent(x);
		parent->setLeft(temp);
		if(temp!=NULL) //sets parent of new child
			temp->setParent(parent);
	}else{
		node* temp = x->getLeft();
		x->setParent(NULL);
		x->setLeft(parent);
		parent->setParent(x);
		parent->setRight(temp);
		if(temp!=NULL) //sets parent of new child
			temp->setParent(parent);
	}
}


void splayTree::twoSingRot(node* x){ //performs zig-zig or zag-zag depending on side of node 
	node* parent = x->getParent();
	node* gParent = x->getParent()->getParent();
	if(parent->left == x){ //condition
		node* temp1 = x->getRight();
		node* temp2 = parent->getRight();
		x->setParent(gParent->getParent());
		x->setRight(parent);
		parent->setParent(x);
		parent->setLeft(temp1);
		parent->setRight(gParent);
		gParent->setParent(parent);
		gParent->setLeft(temp2);
		if(x->getParent() != NULL){ //sets the parents new child
			if(x->getParent()->getLeft() == gParent)
				x->getParent()->setLeft(x);
			else
				x->getParent()->setRight(x);
		}
		if(temp1 != NULL) //sets parent of new child
			temp1->setParent(parent);
		if(temp2 != NULL) //sets parent of new child
			temp2->setParent(gParent);
	}else{
		node* temp1 = parent->getLeft();
		node* temp2 = x->getLeft();
		x->setParent(gParent->getParent());
		x->setLeft(parent);
		parent->setParent(x);
		parent->setLeft(gParent);
		parent->setRight(temp2);
		gParent->setParent(parent);
		gParent->setRight(temp1);
		if(x->getParent() != NULL){ //sets the parents new child
			if(x->getParent()->getLeft() == gParent)
				x->getParent()->setLeft(x);
			else
				x->getParent()->setRight(x);
		}
		if(temp1 != NULL) //sets parent of new child
			temp1->setParent(gParent);
		if(temp2 != NULL) //sets parent of new child
			temp2->setParent(parent);
	}
}
void splayTree::doubleRot(node* x){ //performs zig-zag/zag-zig
	node* parent = x->getParent();
	node* gParent = parent->getParent();
	if(parent->left == x){ //condition
		node* temp1 = x->getLeft();
		node* temp2 = x->getRight();
		x->setParent(gParent->getParent());
		x->setLeft(gParent);
		x->setRight(parent);
		parent->setParent(x);
		parent->setLeft(temp2);
		gParent->setParent(x);
		gParent->setRight(temp1);
		if(x->getParent() != NULL){ //sets new child of the parent of x
			if(x->getParent()->getLeft() == gParent)
				x->getParent()->setLeft(x);
			else
				x->getParent()->setRight(x);
		}
		if(temp1 != NULL) //sets new parent of x as the parent of the gParent
			temp1->setParent(gParent);
		if(temp2 != NULL) //sets new parent of x as the parent of the gParent
			temp2->setParent(parent);
	}else{
		node* temp1 = x->getLeft();
		node* temp2 = x->getRight();
		x->setParent(gParent->getParent());
		x->setLeft(parent);
		x->setRight(gParent);
		parent->setParent(x);
		parent->setRight(temp1);
		gParent->setParent(x);
		gParent->setLeft(temp2); 
		if(x->getParent() != NULL){ //sets new child of the parent of x
			if(x->getParent()->getLeft() == gParent)
				x->getParent()->setLeft(x);
			else
				x->getParent()->setRight(x);
		}
		if(temp1 != NULL) //sets new parent of x as the parent of the gParent
			temp1->setParent(parent);
		if(temp2 != NULL) //sets new parent of x as the parent of the gParent
			temp2->setParent(gParent);
	}
}
node* splayTree::access(int i){ //find the node with key i
	node* prevTemp; //keeps track of last non-null node
	node* temp = this->t; //pointer for root
	while (temp != NULL){ //locates the value by traversing down tree
		if(temp->getKey() < i){ //traverse down right
			prevTemp = temp;
			temp = temp->getRight();
		}else if(temp->getKey() > i){ //traverse down left
			prevTemp = temp;
			temp = temp->getLeft();
		}else{ //found the node with key i; splay then return
			this->t = this->splay(temp); 
			return this->t;
		}
	}
	this->t = this->splay(prevTemp); //not found, splay the last non-null node
	return NULL;
}

node* splayTree::split(int i, node* t){ //returns right tree, t passed back is left tree
	if(this->access(i) == NULL) //splays the tree at i or the last non-null node
		t = this->t;
	node* temp;
	if(t->getKey() < i){ //splits the tree depending on i and the root key value
		temp = t->getRight();
		if(temp != NULL){
			temp->setParent(NULL);
		}
		t->setRight(NULL);
		this->t = t;
		return temp;
	}else{
		temp = t;
		t = t->getLeft();
		if(t != NULL){
			t->setParent(NULL);
		}
		temp->setLeft(NULL);
		this->t = t;
		return temp;
	}
}

node* splayTree::join(node* t1, node* t2){ //t1 = left, t2 = right
	int max;
	node* temp;
	if(t1 == NULL){ //returns t2 if t1 NULL
		return t2;
	} //else find max of t1 and splay it at max
	else{
		max = t1->getKey();
		this->t = t1;
		temp = t1;
		while(temp->getRight() != NULL){ //finds max value of left subtree since all right subtree values > i
			if(temp->getRight()->getKey() > max){
				max = temp->getRight()->getKey();
			}
			temp = temp->getRight();
		}
		this->t = access(max); //splay at max
		if(t1->getRight() == NULL) 
			t1->setRight(t2);
		else{ //ensures we don't overwrite any children that are important
			temp = this->t;
			while(temp->getRight() != NULL)
				temp = temp->getRight();
			temp->setRight(t2);
		}
	}
	if(t2 != NULL) //resets parent pointers
		t2->setParent(this->t);
	return this->t;
}

void splayTree::find(int i){ //accesses the tree and splays it at i if found, else splay it at last non-null node
	if(this->access(i) == NULL){
		std::cerr << "item " << i << " not found"<< std::endl;
	}else{
		std::cout << "item " << i << " found"<< std::endl;
	}
}

void splayTree::insert(int i){ //inserts a new node into tree
	if( this->t == NULL ){ //if tree empty, make a new root
			this->t = new node(i);
			std::cout << "item " << i << " inserted"<< std::endl;
	}else{
		if(this->access(i) == NULL){ //check to see if in tree; ==NULL -> not in tree
			node *temp = new node(i); //make a new root
			node *n = split(i, this->t); //splits the current tree
			temp->setLeft(this->t); //makes the tree with new root
			if(this->t != NULL) //reset parents
				this->t->setParent(temp);
			temp->setRight(n);
			if(n != NULL) 
				n->setParent(temp);
			this->t = temp; //points root pointer back to root
			std::cout << "item " << i << " inserted"<< std::endl;
		}else{
			std::cout << "item " << i << " not inserted; already present" << std::endl;
		}
	}	
}
void splayTree::del(int i){ //deletes node with key i 
	node* temp = access(i); //splays at i
	if(this->t->getKey() != i){ //not found
		std::cerr << "item " << i << " not deleted; not present"<< std::endl;
	}else{
		if(this->t->getLeft() != NULL) //deletes parental connection
			this->t->getLeft()->setParent(NULL);
		if(this->t->getRight() != NULL) //deletes parental connection
			this->t->getRight()->setParent(NULL);
		this->t = this->join(this->t->getLeft(), this->t->getRight()); //joins the left/right subtrees since root is deleted
		std::cout << "item " << i << " deleted" << std::endl;
	}	
	delete temp;
}

void splayTree::print(){ //prints the tree in BFS order
	for(int i = 0; i < this->getHeight(this->t); i++){
		printAtH(this->t, i);
		std::cout << std::endl;
	}
}
void splayTree::printAtH(node* t, int h){ //prints the keys at level h
	if(t == NULL)
		return;
	if(h == 0)
		std::cout<< t->getKey() << " ";
	else if(h > 0){
		printAtH(t->getLeft(), h-1);
		printAtH(t->getRight(), h-1);
	}
}
int splayTree::getHeight(node* t){ //finds the height of the given tree
	if(t == NULL){
		return 0;
	}
	else{
		if(getHeight(t->getRight())>getHeight(t->getLeft()))
			return (getHeight(t->getRight())+1); 
		else
			return (getHeight(t->getLeft())+1);
	}
}