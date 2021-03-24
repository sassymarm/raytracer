#pragma once

#include <vector>
#include <assert.h>
#include <string>
#include <sstream>
#include "color.h"


class Canvas
{
private:
	Color* pixels;
	int width;
	int height;
public:
	Canvas(int width, int height)
	{
		this->width = width;
		this->height = height;
		//printf("sizeof Color = %d", sizeof(double));
		pixels = (Color*)malloc(sizeof(Color) * width * height);
		for (int i = 0; i < width * height; ++i)
		{
			pixels[i] = Color(0,0,0);
		}
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	Color getPixel(int i)
	{
		return pixels[i];
	}

	Color getPixel(int w, int h)
	{
		return pixels[w + width * h];
	}

	void writePixel(int w, int h, Color c)
	{
		pixels[w + h * width] = c;
	}

	void saveToFile(std::string path)
	{
		FILE* p; 
		if (0 != fopen_s(&p, path.c_str(), "w"))
			return; // error
		
		#define COUNT 100000
		char buf[COUNT];
		for (int i = 0; i < COUNT; ++i)
			buf[i] = '\n';


		std::stringstream ss;
		ss << "P3\n" << width << " " << height << "\n255\n";
		for (int i = 0; i < width * height; ++i)
		{
			Color c = pixels[i];
			int red = (int)(c.getR() * 255);
			int green = (int)(c.getG() * 255);
			int blue = (int)(c.getB() * 255);
			ss << red << " " << green << " " << blue << "\n";
		}
		std::string s = ss.str();
		sprintf_s(buf, s.size()+1, s.c_str());
		
		fwrite(buf, sizeof(char), COUNT, p);

		/*
		for (int i = 0; i < width * height; ++i)
		{
			Color c = pixels[i];
			int red = c.getR() * 255;
			int green = c.getG() * 255;
			int blue = c.getB() * 255;
			sprintf_s(buf, 256, "%d %d %d ", red, green, blue);
			fwrite(buf, sizeof(char), 256, p);
		}
		*/
	}

	// RUN UNIT TESTS
	static void runTests()
	{
		// Initialization
		printf("Running Canvas::runTest()\n");
		Canvas c(10, 20);
		assert(c.getWidth() == 10);
		assert(c.getHeight() == 20);
		for (int i = 0; i < c.getWidth() * c.getHeight(); ++i)
		{
			assert(c.getPixel(0) == Color(0, 0, 0));
		}

		// Writing pixels
		c.writePixel(2, 3, Color(1, 0, 0));
		assert(c.getPixel(2, 3) == Color(1, 0, 0));
	}
};