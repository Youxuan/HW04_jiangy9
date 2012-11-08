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
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "Circle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_jiangy9App : public AppBasic {
	public:
		void setup();
		void mouseDown( MouseEvent event );	
		void update();
		void draw();
		void prepareSettings(Settings* settings);
		void readFromFile(Entry** entries, int* length); 

	private:
		static const int windowWidth = 1024;
		static const int windowHeight = 1024;
		Entry* entries; 
		int length;
		jiangy9_Starbucks foo;
		Surface* mySurface;
		int click;
		double x;
		double y;
		Circle* circle;
};

void HW04_jiangy9App::prepareSettings(Settings* settings){
	settings->setWindowSize(windowWidth, windowHeight);
}

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

void HW04_jiangy9App::setup()
{
	mySurface = new Surface(windowWidth, windowHeight, true);
	*mySurface = loadImage("../resources/USA_Map.png");
	
	foo.setColor(Color8u(237,28,36));
	uint8_t* dataArray = (*mySurface).getData();
	foo.setArray(dataArray);

	entries = NULL;
	length = 0;
	click = 0;
	circle = new Circle();
	x = 0.0;
	y = 0.0;
	
	readFromFile(&entries, &length);
	foo.build(entries, length);
	delete [] entries;

	

	//console() << foo.getNearest(0.5,0.5)->identifier << std::endl;
}

void HW04_jiangy9App::mouseDown( MouseEvent event )
{
	if(event.isLeftDown()){
		//circle->setCircle((*mySurface).getData(), 10.0f, x, y, Color8u(0,0,0));
		
		x = (double)event.getX();
		y = (double)event.getY();

		circle->setCircle((*mySurface).getData(), 10.0f, (float)(foo.getNearest(x,y)->x), (float)(foo.getNearest(x,y)->y), Color8u(0,0,0));
		console() << x << " " << y << std::endl;
		

		click++;
	}
}

void HW04_jiangy9App::update()
{
	if(click%2==1){
		//foo.highLight(foo.getNearest(x,y), Color8u(255,255,255));
		circle->draw();
	}
	
}

void HW04_jiangy9App::draw()
{
	//draw map of the U.S.	
	gl::draw(*mySurface);
	   
}

CINDER_APP_BASIC( HW04_jiangy9App, RendererGl )
