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
	foo.setColor(Color8u(237,28,36));
	uint8_t* dataArray = (*mySurface).getData();
	//set every pixel on surface transparent in order to display the map
	for(int x=0;x<windowWidth;x++){
		for(int y=0;y<windowHeight;y++)
			dataArray[4*(x + y * windowWidth)+3] = 0;
	}

	foo.setArray(dataArray);
	Rand::randomize();
	entries = NULL;
	length = 0; //length is from 0 to 7654(real length is 1 to 7655)
	
	readFromFile(&entries, &length);
	foo.build(entries, length);
	delete [] entries;

	

	//console() << foo.getNearest(0.5,0.5)->identifier << std::endl;
}

void HW04_jiangy9App::mouseDown( MouseEvent event )
{
}

void HW04_jiangy9App::update()
{
	
}

void HW04_jiangy9App::draw()
{
	//draw map of the U.S.
	gl::Texture myTexture( loadImage( loadResource( RES_MAP ) ) );
	gl::draw(myTexture);
	gl::draw(*mySurface);
	   
}

CINDER_APP_BASIC( HW04_jiangy9App, RendererGl )
