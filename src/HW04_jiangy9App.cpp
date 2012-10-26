#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "jiangy9_Starbucks.h"
#include "Resources.h"
#include "cinder/gl/gl.h"
#include <iostream>
#include <fstream>
#include <string>
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_jiangy9App : public AppBasic {
	public:
		void setup();
		void mouseDown( MouseEvent event );	
		void update();
		void draw();
		void readFromFile(Entry** entries, int* length); 
		void mix(Entry* entries, int length);

	private:
		Entry* entries; 
		int length;
		jiangy9_Starbucks foo;
		//Rand myrand;
};

//read data from file and store data into an array
void HW04_jiangy9App::readFromFile(Entry** entries, int* length){
	ifstream fileInput_1("../resources/Starbucks_2006.csv");
	if(!fileInput_1)
		console() << "Cannot open folder!" << std::endl;

	//check how many items in that file
	string line;
	while(!fileInput_1.eof()){	    
		getline(fileInput_1,line,',');
		double l_x;
		fileInput_1 >> l_x;
		char comma;
		fileInput_1.get(comma);
		double l_y;
		fileInput_1 >> l_y;

		*length += 1;
	}
	fileInput_1.close();
	*length -= 1;
	console() << *length << std::endl;

	//read data from file into array
	ifstream fileInput_2("../resources/Starbucks_2006.csv");
	*entries = new Entry[*length];
	for(int i=0;i<*length;i++){
		getline(fileInput_2,line,',');
		(*entries)[i].identifier = line;

		//console() << (*entries)[i].identifier << std::endl;
		
		double l_x;
		fileInput_2 >> l_x;
		(*entries)[i].x = l_x;

		//console() << (*entries)[i].x << std::endl;

		char comma;
		fileInput_2.get(comma);

		double l_y;
		fileInput_2 >> l_y;
		(*entries)[i].y = l_y;

		//console() << (*entries)[i].y << std::endl;
	}
	fileInput_2.close();
}

void HW04_jiangy9App::mix(Entry* entries, int length){ //Does it really provide random number?
	int pick = 0;
	for(int i=0;i<length-1;i++){
		pick = Rand::randInt(i+1,length);
		Entry temp = entries[i];
		entries[i] = entries[pick];
		entries[pick] = temp;
	}
}

void HW04_jiangy9App::setup()
{
	Rand::randomize();
	entries = NULL;
	length = 0; //length is from 0 to 7654(real length is 1 to 7655)
	readFromFile(&entries, &length);
	mix(entries,length);
	foo.build(entries, length);
	console() << foo.getNearest(0.12345,0.23456)->identifier << std::endl;
}

void HW04_jiangy9App::mouseDown( MouseEvent event )
{
}

void HW04_jiangy9App::update()
{
}

void HW04_jiangy9App::draw()
{
	
	   
}

CINDER_APP_BASIC( HW04_jiangy9App, RendererGl )
