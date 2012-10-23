#include "HW04_jiangy9.h"

node::node(){
	left = NULL;
	right = NULL;
	data = NULL;
}

node::node(Entry* e){
	left = right = NULL;
	data = e;
}