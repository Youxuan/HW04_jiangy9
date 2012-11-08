#pragma once
#include <string>
#include "Starbucks.h"
#include "Resources.h"
#include <string>
#include "cinder/Rand.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Circle.h"

using namespace std;
using namespace ci;
using namespace ci::app;

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
		void traversal(node* r, uint8_t* dataArray, Color8u color);
		double getDistance(double x, double y, node* r);
		node* checkOneSubtree(double x, double y, node* r, bool isXlevel);
		void mix(Entry* entries, int length);
		void setColor(Color8u newColor);
		void setArray(uint8_t* newDataArray);
		void highLight(Entry* e, Color8u color);
		
		
		virtual Entry* getNearest(double x, double y);
		virtual void build(Entry* e, int n);

	private:
		static const int windowWidth = 1024;
		static const int windowHeight = 1024;
		Entry* e;
		node* r;
		bool isXlevel;
		double x;
		double y;
		Color8u color;
		uint8_t* dataArray;
};

