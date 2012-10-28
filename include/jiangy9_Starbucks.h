#pragma once
#include <string>
#include "Starbucks.h"
#include "Resources.h"
#include <string>
#include "cinder/Rand.h"
using namespace std;

class node{
	public:
		node* left;
        node* right;
    	Entry* data;

		node();
        node(Entry* e);
};

class jiangy9_Starbucks : public Starbucks{
	public:
		node* insert(Entry* e, node* r, bool isXlevel);
		virtual void build(Entry* e, int n);
		double getDistance(double x, double y, node* r);
		node* checkOneSubtree(double x, double y, node* r, bool isXlevel);
		virtual Entry* getNearest(double x, double y);
		void mix(Entry* entries, int length);

	private:
		Entry* e;
		node* r;
		bool isXlevel;
		double x;
		double y;
};

