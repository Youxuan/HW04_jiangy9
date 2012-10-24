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

node* jiangy9_Starbucks::insert(Entry* e, node* r, bool isXlevel){
	if( r == NULL)
        return new node(e);
	if (((r->data->x-e->x)<=0.00001)||(((e->x-r->data->x)<=0.00001))&&((r->data->y-e->y)<=0.00001)||(((e->y-r->data->y)<=0.00001)))
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

void jiangy9_Starbucks::build(Entry* e, int n){
	r = new node(e);
	for(int i=1;i<n;i++){
		insert(&e[i],r,true); 
	}
}

double jiangy9_Starbucks::distance(double x, double y, node* r){
	return sqrt((x-r->data->x)*(x-r->data->x)+(y-r->data->y)*(y-r->data->y));
}
