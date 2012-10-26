#pragma once
#include "jiangy9_Starbucks.h"
#include <math.h>

node::node(){
	left = NULL;
	right = NULL;
	data = NULL;
}

node::node(Entry* e){
	left = right = NULL;
	data = e;
}

//add one new Starbucks object into K-d tree
node* jiangy9_Starbucks::insert(Entry* e, node* r, bool isXlevel){
	if( r == NULL)
        return new node(e);
	if((abs(r->data->x-e->x)<=0.00001)&&(abs(r->data->y-e->y)<=0.00001))
        return r;

	//decide which side to go in K-d tree
	if(isXlevel){
		if(e->x < r->data->x)
			r->left = insert(e,r->left,!isXlevel);
		else
			r->right = insert(e,r->right,!isXlevel);
	}
	else{
		if(e->y < r->data->y)
			r->left = insert(e,r->left,!isXlevel);
		else
			r->right = insert(e,r->right,!isXlevel);
	}

	return r;
}

//build the entire K-d tree
void jiangy9_Starbucks::build(Entry* e, int n){
	r = new node(e);
	for(int i=1;i<n;i++){
		insert(&e[i],r,true); 
	}
}

//calculate distance between given location and Starbucks in current node
double jiangy9_Starbucks::getDistance(double x, double y, node* r){
	return sqrt((x-r->data->x)*(x-r->data->x)+(y-r->data->y)*(y-r->data->y));
}

//check half of the entire K-d tree
node* jiangy9_Starbucks::checkOneSubtree(double x, double y, node* r, bool isXlevel){
	if(r==NULL)    
		return r;

	if((abs(r->data->x-x)<=0.00001)&&(abs(r->data->y-y)<=0.00001)) 
		return r;

	node* foundLeft = NULL;
	node* foundRight = NULL;
	//decide which side to go in K-d tree
	if(isXlevel){
		if(r->data->x < x)
			foundLeft = checkOneSubtree(x,y,r->left,!isXlevel);
		if(foundLeft == NULL)
			foundRight = checkOneSubtree(x,y,r->right,!isXlevel);
	}
	else{
		if(r->data->y < y)
			foundLeft = checkOneSubtree(x,y,r->left,!isXlevel);
		if(foundLeft == NULL)
			foundRight = checkOneSubtree(x,y,r->right,!isXlevel);
	}

	if(foundLeft == NULL && foundRight == NULL)
		return r;

	//check if we should check another side depends on "which side is NULL!!!"
	if(isXlevel){
		if(foundLeft==NULL){
			if(getDistance(x,y,foundRight) > getDistance(x,y,r))
				foundRight = r;
			//check root and foundLeft, which one is more close, compare that one to ...
			if(abs(x-foundRight->data->x) > getDistance(x,y,foundRight))
				foundLeft = checkOneSubtree(x,y,r->left,!isXlevel);
		}
		if(foundRight==NULL){
			if(getDistance(x,y,foundLeft) > getDistance(x,y,r))
				foundLeft = r;
			if(abs(x-foundLeft->data->x) > getDistance(x,y,foundLeft))
				foundRight = checkOneSubtree(x,y,r->right,!isXlevel);
		}
	}
	else{
		if(foundLeft==NULL){
			if(getDistance(x,y,foundRight) > getDistance(x,y,r))
				foundRight = r;
			if(abs(y-foundRight->data->y) > getDistance(x,y,foundRight))
				foundLeft = checkOneSubtree(x,y,r->left,!isXlevel);
		}
		if(foundRight==NULL){
			if(getDistance(x,y,foundLeft) > getDistance(x,y,r))
				foundLeft = r;
			if(abs(y-foundLeft->data->y) > getDistance(x,y,foundLeft))
				foundRight = checkOneSubtree(x,y,r->right,!isXlevel);
		}
	}

	
	if(foundLeft == NULL && foundRight != NULL){
		if(getDistance(x,y,r) > getDistance(x,y,foundRight))
			return foundRight;
		else
			return r;
	}
	else if(foundLeft != NULL && foundRight == NULL){
		if(getDistance(x,y,r) > getDistance(x,y,foundLeft))
			return foundLeft;
		else
			return r;
	}
	else{
		double shortestDistance = min(getDistance(x,y,r),min(getDistance(x,y,foundRight),getDistance(x,y,foundLeft)));
		if(shortestDistance == getDistance(x,y,r))
			return r;
		else if(shortestDistance == getDistance(x,y,foundRight))
			return foundRight;
		else
			return foundLeft;
	}
}

Entry* jiangy9_Starbucks::getNearest(double x, double y){
	return checkOneSubtree(x,y,r,true)->data;
}