#pragma once
#include <string>
#include "Starbucks.h"
#include "HW04_jiangy9.h"
#include "Resources.h"
#include <string>
using namespace std;

class jiangy9_Starbucks : public Starbucks{
	public:
		virtual node* insert(Entry* e, node* r, bool isXlevel);
		virtual void build(Entry* e, int n);
		virtual double distance(double x, double y, node* r);
		virtual node* getNearest(double x, double y, node* r);

	private:
		Entry* e;
		node* r;
		bool isXlevel;
		double x;
		double y;
};