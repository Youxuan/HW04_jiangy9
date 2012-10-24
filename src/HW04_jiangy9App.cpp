#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "jiangy9_Starbucks.h"
#include "Resources.h"
#include "cinder/gl/gl.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_jiangy9App : public AppBasic {
	public:
		void setup();
		void mouseDown( MouseEvent event );	
		void update();
		void draw();
		void readFromFile(Entry** entires, int* length); //read data from file

	private:
		Entry* entries; 
		int length; 
};

//read data from file and store data into an array
void HW04_jiangy9App::readFromFile(Entry** entries, int* length){
	ifstream fileInput("../resources/Test.csv");
	if(!fileInput)
		console() << "Cannot open folder!" << std::endl;

	string line;	
	//check how many items in that file
	while(!fileInput.eof()){	    
		getline(fileInput,line,'\n'); 
		*length++;
	}
	fileInput.close();
	console() << *length <<std::endl;
}

	//create array and assign value into array
	/**entries = new Entry[*length];
	for(int i=0;i<*length;i++){
		(*entries)[i].identifier = getline(getFirstLetter,256,',');
		 = getFirstLetter; //pointer or variable...
		
		double l_x;
		fileInput >> l_x;
		(*entries)[i].x = l_x; //get x coordinate
		
		char c2;
		fileInput.get(c2); //consume the comma
		
		double l_y;
		fileInput >> l_y;
		(*entries)[i].y = l_y; //get y coordinate*/


void HW04_jiangy9App::setup()
{
	entries = NULL;
	length = 0;
	//console() << "Lucy" << std::endl;
	//use this line to test if input is correct.
	readFromFile(&entries, &length);
	console() << &entries[0] << std::endl; //???????
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
