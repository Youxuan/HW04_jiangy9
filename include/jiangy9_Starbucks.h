#pragma once
#include <string>
#include "Starbucks.h"
#include "HW04_jiangy9.h"
#include "Resources.h"
#include <string>
using namespace std;

class jiangy9_Starbucks : public Starbucks{
	public:
		node* insert(Entry* e, node* r, bool isXlevel);
		virtual void build(Entry* e, int n);
		double distance(double x, double y, node* r);
		node* checkOneSubtree(double x, double y, node* r);
		virtual Entry* getNearest(double x, double y);

	private:
		Entry* e;
		node* r;
		bool isXlevel;
		double x;
		double y;
};

class node{
	public:
		node* left;
        node* right;
    	Entry* data;

		node();
        node(Entry* e);
};