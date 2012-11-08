#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Circle{
	public:
		Circle();
		void draw();
		void setCircle(uint8_t* dataArray_new, float radius_new, float center_x_new, float center_y_new, Color8u color_new);

	private:
		static const int windowWidth = 1024;
		static const int windowHeight = 1024;
		float radius, center_x, center_y;
		Color8u color;
		uint8_t* dataArray;
};