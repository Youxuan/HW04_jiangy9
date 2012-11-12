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
		void keyDown( KeyEvent event );
		void update();
		void draw();
		void prepareSettings(Settings* settings);
		void readFromFile(int* length, LucyEntry** lucyEntry); 
		void readPopulation(population** old_pop, int* old_pop_length, population** new_pop, int* new_pop_length);
		void calculatePopulation(population* old_pop, int old_pop_length, population* new_pop, int new_pop_length, LucyEntry* lucyEntry, jiangy9_Starbucks foo, int length);
		void paintPopulation(LucyEntry* lucyEntry, int length, uint8_t* dataArray2);
		void paintCencus(population* old_pop, int old_pop_length, population* new_pop, int new_pop_length, uint8_t* dataArray3);

	private:
		static const int windowWidth = 1024;
		static const int windowHeight = 1024;
		Entry* entries; 
		int length;
		jiangy9_Starbucks foo;
		Surface* mySurface1;
		Surface* mySurface2;
		Surface* mySurface3;
		int click;
		double x;
		double y;
		int press;
		uint8_t* dataArray1;
		uint8_t* dataArray2;
		uint8_t* dataArray3;
		double target_x;
		double target_y;

		population* old_pop;
		int old_pop_length;
		population* new_pop;
		int new_pop_length;

		int pressO;

		LucyEntry* lucyEntry;
};

void paintCencus(population* old_pop, int old_pop_length, population* new_pop, int new_pop_length, uint8_t* dataArray3){
	int new_max = 37452;
	for(int i=0; i<=new_pop_length; i++){
		double percentage = new_pop[i].pop_number/new_max;
		double x = new_pop[i].pop_x * 1024;
		double y = (1-new_pop[i].pop_y) * 1024;
		for(int yy=0; yy<=1024; yy++){
				for(int xx=0;xx<=1024; xx++){
					if ((xx-x)*(xx-x) + (yy-y)*(yy-y) <= 3.0f*3.0f){
						dataArray3[4*(xx + yy * 1024)] = (int)(237*percentage);
						dataArray3[4*(xx + yy * 1024)+1] = (int)(28*percentage);
						dataArray3[4*(xx + yy * 1024)+2] = (int)(36*percentage);
						dataArray3[4*(xx + yy * 1024)+3] = 255;
					}
				}
			}
	}

}

void HW04_jiangy9App::paintPopulation(LucyEntry* lucyEntry, int length, uint8_t* dataArray2){
	double percentage = 0.0;
	double x = 0.0;
	double y = 0.0;

	for(int i=0; i<=length; i++){
		if(lucyEntry[i].pop_old!=0){
			percentage = (lucyEntry[i].pop_new - lucyEntry[i].pop_old) / lucyEntry[i].pop_old;
			console() << percentage << std::endl;

			x = lucyEntry[i].x * windowWidth;
			y = (1 - lucyEntry[i].y) * windowHeight;

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
		else{
			x = lucyEntry[i].x * windowWidth;
			y = (1 - lucyEntry[i].y) * windowHeight;
			for(int yy=0; yy<=windowHeight; yy++){
				for(int xx=0;xx<=windowWidth; xx++){
					if ((xx-x)*(xx-x) + (yy-y)*(yy-y) <= 3.0f*3.0f){
						dataArray2[4*(xx + yy * windowWidth)] = 237;
						dataArray2[4*(xx + yy * windowWidth)+1] = 28;
						dataArray2[4*(xx + yy * windowWidth)+2] = 36;
						dataArray2[4*(xx + yy * windowWidth)+3] = 255;
					}
				}
			}
		}

	}
}

void HW04_jiangy9App::calculatePopulation(population* old_pop, int old_pop_length, population* new_pop, int new_pop_length, LucyEntry* lucyEntry, jiangy9_Starbucks foo, int length){
	/*
	for(int i=0; i<=new_pop_length; i++){
        ((LucyEntry*)(foo.getNearest(new_pop[i].pop_x, new_pop[i].pop_y)))->pop_new += new_pop[i].pop_number;
    }

    for(int i=0; i<=old_pop_length; i++){
        ((LucyEntry*)(foo.getNearest(old_pop[i].pop_x, old_pop[i].pop_y)))->pop_old += old_pop[i].pop_number;
    }
	*/


	for(int i=0;i<=new_pop_length;i++){
		Entry* neareast = foo.getNearest(new_pop[i].pop_x, new_pop[i].pop_y);
		for(int j=0;j<=length;j++){
			if((lucyEntry[j]).identifier.compare(neareast->identifier)==0){
				(lucyEntry[j]).pop_new += new_pop[i].pop_number;
			}
		} 
	}

	for(int i=0;i<=old_pop_length;i++){
		Entry* neareast2 = foo.getNearest(old_pop[i].pop_x, old_pop[i].pop_y);
		for(int j=0;j<=length;j++){
			if((lucyEntry[j]).identifier.compare(neareast2->identifier)==0){
				(lucyEntry[j]).pop_old += old_pop[i].pop_number;
			}
		} 
	}



}

void HW04_jiangy9App::readPopulation(population** old_pop, int* old_pop_length, population** new_pop, int* new_pop_length){
	
	ifstream fileInput_1("../resources/Census_2000.csv"); //Census_2000.csv
	if(!fileInput_1)
		console() << "Cannot open folder!" << std::endl;

	int number;
	char comma;
	double coordinates;
	while(!fileInput_1.eof()){
		fileInput_1 >> number;
		fileInput_1.get(comma);
		fileInput_1 >> number;
		fileInput_1.get(comma);
		fileInput_1 >> number;
		fileInput_1.get(comma);
		fileInput_1 >> number;
		fileInput_1.get(comma);
		fileInput_1 >> number;
		fileInput_1.get(comma);
		fileInput_1 >> coordinates;
		fileInput_1.get(comma);
		fileInput_1 >> coordinates;

		*old_pop_length += 1;
	}
	fileInput_1.close();
	*old_pop_length -= 1;
	//console() << *old_pop_length << std::endl;

	ifstream fileInput_2("../resources/Census_2000.csv");
	*old_pop = new population[(*old_pop_length)+1];
	for(int i=0;i<=*old_pop_length;i++){
		fileInput_2 >> number;
		fileInput_2.get(comma);
		fileInput_2 >> number;
		fileInput_2.get(comma);
		fileInput_2 >> number;
		fileInput_2.get(comma);
		fileInput_2 >> number;
		(*old_pop)[i].id = number;
		fileInput_2.get(comma);

		int number1;
		fileInput_2 >> number1;
		(*old_pop)[i].pop_number = number1;
		fileInput_2.get(comma);
		double coordinates_x;
		fileInput_2 >> coordinates_x;
		(*old_pop)[i].pop_x = coordinates_x;
		fileInput_2.get(comma);
		double coordinates_y;
		fileInput_2 >> coordinates_y;
		(*old_pop)[i].pop_y = coordinates_y;
	}
	fileInput_2.close();
	

	//get number of items in new census data
	ifstream fileInput_3("../resources/Census_2010.csv"); //Census_2010.csv
	if(!fileInput_3)
		console() << "Cannot open folder!" << std::endl;
	while(!fileInput_3.eof()){
		fileInput_3 >> number;
		fileInput_3.get(comma);
		fileInput_3 >> number;
		fileInput_3.get(comma);
		fileInput_3 >> number;
		fileInput_3.get(comma);
		fileInput_3 >> number;
		fileInput_3.get(comma);
		fileInput_3 >> number;
		fileInput_3.get(comma);
		fileInput_3 >> coordinates;
		fileInput_3.get(comma);
		fileInput_3 >> coordinates;

		*new_pop_length += 1;
	}
	fileInput_3.close();
	*new_pop_length -= 1;
	//console() << *new_pop_length << std::endl;
	
	ifstream fileInput_4("../resources/Census_2010.csv");
	*new_pop = new population[(*new_pop_length+1)];
	for(int i=0;i<=*new_pop_length;i++){
		fileInput_4 >> number;
		fileInput_4.get(comma);
		fileInput_4 >> number;
		fileInput_4.get(comma);
		fileInput_4 >> number;
		fileInput_4.get(comma);
		fileInput_4 >> number;
		(*new_pop)[i].id = number;
		fileInput_4.get(comma);
		
		int number2;
		fileInput_4 >> number2;
		(*new_pop)[i].pop_number = number2;

		fileInput_4.get(comma);

		double coordinates_xx;
		fileInput_4 >> coordinates_xx;
		(*new_pop)[i].pop_x = coordinates_xx;

		fileInput_4.get(comma);

		double coordinates_yy;
		fileInput_4 >> coordinates_yy;
		(*new_pop)[i].pop_y = coordinates_yy;
	}
	fileInput_4.close();
	

}

void HW04_jiangy9App::prepareSettings(Settings* settings){
	settings->setWindowSize(windowWidth, windowHeight);
}

//read data from file and store data into an array
void HW04_jiangy9App::readFromFile(int* length, LucyEntry** lucyEntry){
	ifstream fileInput_1("../resources/Starbucks_2006.csv");
	if(!fileInput_1)
		console() << "Cannot open folder!" << std::endl;

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

	ifstream fileInput_2("../resources/Starbucks_2006.csv");
	*lucyEntry = new LucyEntry[(*length)+1];

	for(int i=0;i<=*length;i++){
		getline(fileInput_2,line,',');
		(*lucyEntry)[i].identifier = line;
		double l_x;
		fileInput_2 >> l_x;
		(*lucyEntry)[i].x = l_x;
		char comma;
		fileInput_2.get(comma);
		double l_y;
		fileInput_2 >> l_y;
		(*lucyEntry)[i].y = l_y;
	}
	fileInput_2.close();
	
}

void HW04_jiangy9App::setup()
{
	mySurface1 = new Surface(windowWidth, windowHeight, true);
	*mySurface1 = loadImage("../resources/USA_Map.png");

	mySurface2 = new Surface(windowWidth, windowHeight, true);
	*mySurface2 = loadImage("../resources/USA_Map.png");

	mySurface3 = new Surface(windowWidth, windowHeight, true);
	*mySurface3 = loadImage("../resources/USA_Map.png");
	
	uint8_t* dataArray1 = (*mySurface1).getData();
	uint8_t* dataArray2 = (*mySurface2).getData();
	uint8_t* dataArray3 = (*mySurface3).getData();
	foo.setArray(dataArray1);

	length = 0;
	click = 0;
	x = 0.0;
	y = 0.0;
	target_x = 0.0;
	target_y = 0.0;
	press = 0;
	pressO = 0;

	entries = NULL;
	lucyEntry = NULL;
	
	old_pop = NULL;
	old_pop_length = 0;
	new_pop = NULL;
    new_pop_length = 0;

	readFromFile(&length, &lucyEntry);
	foo.build(lucyEntry, length+1);	

	readPopulation(&old_pop, &old_pop_length, &new_pop, &new_pop_length);
	//paintCencus(old_pop, old_pop_length, new_pop, new_pop_length, dataArray3);
	calculatePopulation(old_pop, old_pop_length, new_pop, new_pop_length, lucyEntry, foo, length);

	paintPopulation(lucyEntry, length, dataArray2);

	//foo.paint(dataArray2);
}

void HW04_jiangy9App::mouseDown( MouseEvent event )
{
	if(event.isLeftDown()){		
		x = (double)event.getX()/windowWidth;
		y = 1-((double)event.getY()/windowHeight);
		click++;
		
	}
}

void HW04_jiangy9App::keyDown( KeyEvent event ){
	if(event.getChar()=='p')
		press++;
	if(event.getChar()=='o')
		pressO++;
}

void HW04_jiangy9App::update()
{
	dataArray1 = (*mySurface1).getData();
	if(click!=0){
		Circle* circle1 = new Circle();
		circle1->setCircle((*mySurface1).getData(), 5.0f, (float)(foo.getNearest(x,y)->x), (float)(foo.getNearest(x,y)->y), Color8u(0,0,0));
		circle1->draw();
	}	
	
}

void HW04_jiangy9App::draw()
{	
	gl::enableAlphaBlending();
	if(press%2==0 && pressO%2==0)
		gl::draw(*mySurface1);
	else if(press%2==1)
		gl::draw(*mySurface2);
	else
		gl::draw(*mySurface3);
	
	   
}

CINDER_APP_BASIC( HW04_jiangy9App, RendererGl )
