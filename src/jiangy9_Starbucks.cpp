#pragma once
#include "jiangy9_Starbucks.h"
#include <math.h>
#include "cinder/Rand.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Circle.h"
#include "cinder/Rand.h"

using namespace std;
using namespace ci;
using namespace ci::app;

LucyEntry::LucyEntry(){
	identifier = "";
	x = 0.0;
	y = 0.0;
	pop_old = 0.0;
	pop_new = 0.0;
}

node::node(){
	left = NULL;
	right = NULL;
	data = NULL;
}

node::node(Entry* e){
	left = right = NULL;
	data = e;
}

population::population(){
	pop_number = 0.0;
	pop_x = 0.0;
	pop_y = 0.0;
	id = 0;
}

void jiangy9_Starbucks::setColor(){
	color.r = Rand::randInt(0,256);
	color.g = Rand::randInt(0,256);
	color.b = Rand::randInt(0,256);
}

void jiangy9_Starbucks::setArray(uint8_t* newDataArray){
	dataArray = newDataArray;
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
	LucyEntry* newEntries = new LucyEntry[n];

	for(int i=0;i<n;i++)
		newEntries[i] = ((LucyEntry*)e)[i];
	e = newEntries;

	mix((LucyEntry*)e, n);
	r = new node(e);
	for(int i=1;i<n;i++){
		insert(&e[i],r,true); 
	}

	traversal(r, dataArray);
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
		if(r->data->x > x)
			foundLeft = checkOneSubtree(x,y,r->left,!isXlevel);
		if(foundLeft == NULL)
			foundRight = checkOneSubtree(x,y,r->right,!isXlevel);
	}
	else{
		if(r->data->y > y)
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
			if(abs(x-foundRight->data->x) < getDistance(x,y,foundRight))
				foundLeft = checkOneSubtree(x,y,r->left,!isXlevel);
		}
		if(foundRight==NULL){
			if(getDistance(x,y,foundLeft) > getDistance(x,y,r))
				foundLeft = r;
			if(abs(x-foundLeft->data->x) < getDistance(x,y,foundLeft))
				foundRight = checkOneSubtree(x,y,r->right,!isXlevel);
		}
	}
	else{
		if(foundLeft==NULL){
			if(getDistance(x,y,foundRight) > getDistance(x,y,r))
				foundRight = r;
			if(abs(y-foundRight->data->y) < getDistance(x,y,foundRight))
				foundLeft = checkOneSubtree(x,y,r->left,!isXlevel);
		}
		if(foundRight==NULL){
			if(getDistance(x,y,foundLeft) > getDistance(x,y,r))
				foundLeft = r;
			if(abs(y-foundLeft->data->y) < getDistance(x,y,foundLeft))
				foundRight = checkOneSubtree(x,y,r->right,!isXlevel);
		}
	}

	//decide which one should be returned
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

void jiangy9_Starbucks::mix(LucyEntry* entries, int length){
	int pick = 0;
	for(int i=0;i<length-1;i++){
		pick = cinder::Rand::randInt(i+1,length);
		LucyEntry temp = entries[i];
		entries[i] = entries[pick];
		entries[pick] = temp;
	}
}

void jiangy9_Starbucks::traversal(node* r, uint8_t* dataArray){
	if(r==NULL)
		return;
	else{
		traversal(r->left,dataArray);
		setColor();
	    for(int y=0; y<=windowHeight; y++){
			for(int x=0;x<=windowWidth; x++){
				if ((x-((r->data->x)*windowWidth))*(x-((r->data->x)*windowWidth)) + (y-((1-(r->data->y))*windowHeight))*(y-((1-(r->data->y))*windowHeight)) <= 3.0f*3.0f){
					dataArray[4*(x + y * windowWidth)] = color.r;
					dataArray[4*(x + y * windowWidth)+1] = color.g;
					dataArray[4*(x + y * windowWidth)+2] = color.b;
					dataArray[4*(x + y * windowWidth)+3] = 255;
				}
			}
		}

		traversal(r->right,dataArray);
	}
}

void jiangy9_Starbucks::paintPopulation(node* r, uint8_t* dataArray2){

	if(r==NULL)
		return;
	else{
		paintPopulation(r->left,dataArray);
		double percentage = 0.0;
		double x = 0.0;
		double y = 0.0;
		if(((LucyEntry*)(r->data))->pop_old!=0){
			//console() << ((LucyEntry*)(r->data))->identifier << std::endl;
			percentage = (((LucyEntry*)(r->data))->pop_new - ((LucyEntry*)(r->data))->pop_old) / ((LucyEntry*)(r->data))->pop_old;
			//console() << percentage << std::endl;

			x = ((LucyEntry*)(r->data))->x * windowWidth;
			y = (1-((LucyEntry*)(r->data))->y) * windowHeight;

			for(int yy=0; yy<=windowHeight; yy++){
				for(int xx=0;xx<=windowWidth; xx++){
					if ((xx-x)*(xx-x) + (yy-y)*(yy-y) <= 3.0f*3.0f){
						dataArray2[4*(xx + yy * windowWidth)] = (int)(237*percentage);
						dataArray2[4*(xx + yy * windowWidth)+1] = (int)(28*percentage);
						dataArray2[4*(xx + yy * windowWidth)+2] = (int)(36*percentage);
						dataArray2[4*(xx + yy * windowWidth)+3] = 255;
					}
				}
			}

		}
		/*
		else{
			x = ((LucyEntry*)(r->data))->x * windowWidth;
			y = (1-((LucyEntry*)(r->data))->y) * windowHeight;

			for(int yy=0; yy<=windowHeight; yy++){
				for(int xx=0;xx<=windowWidth; xx++){
					if ((xx-x)*(xx-x) + (yy-y)*(yy-y) <= 9.0f*9.0f){
						dataArray2[4*(xx + yy * windowWidth)] = 0;
						dataArray2[4*(xx + yy * windowWidth)+1] = 0;
						dataArray2[4*(xx + yy * windowWidth)+2] = 0;
						dataArray2[4*(xx + yy * windowWidth)+3] = 255;
					}
				}
			}

		}
		*/

		paintPopulation(r->right,dataArray);
	}

}

void jiangy9_Starbucks::paint(uint8_t* dataArray2){
	paintPopulation(r, dataArray2);
}