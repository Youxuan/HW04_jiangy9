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

	private:
		string line;
};

void HW04_jiangy9App::setup()
{
	//console() << "Lucy" << std::endl;
	//use this line to test if input is correct.
	
	

}

void HW04_jiangy9App::mouseDown( MouseEvent event )
{
}

void HW04_jiangy9App::update()
{
}

void HW04_jiangy9App::draw()
{
	ifstream myfile("Lucy.txt");
	if (myfile.is_open()){
		while(myfile.good()){
			getline(myfile,line);
			console() << line << std::endl;
		}
		myfile.close();
	}
	   
}

CINDER_APP_BASIC( HW04_jiangy9App, RendererGl )
