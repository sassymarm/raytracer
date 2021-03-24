#pragma once

#include <stdio.h>
#include <assert.h>
#include <cmath>

class Color
{
private:
	double r, g, b;
	static const double EPSILON;
public:
	Color()
	{
		r = 0; g = 0; b = 0;
	}

	Color(double r, double g, double b) 
	{
		this->r = r; this->g = g; this->b = b;
	}

	double getR() {
		return r;
	}

	double getG()
	{
		return g;
	}

	double getB()
	{
		return b;
	}

	void print()
	{
		printf("r: %f, g: %f, b: %f, EPSILON: %f\n", r, g, b, EPSILON);
	}


	Color operator+(Color c)
	{
		Color a(r + c.r, g + c.g, b + c.b);
		return a;
	}

	Color operator-(Color c)
	{
		Color a(r - c.r, g - c.g, b - c.b);
		return a;
	}

	Color operator*(double d)
	{
		Color a(r * d, g * d, b * d);
		return a;
	}

	Color operator*(Color c)
	{
		Color a(r * c.r, g * c.g, b * c.b);
		return a;
	}

	void operator=(Color c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
	}

	bool operator==(Color c)
	{
		if (abs(r - c.r) < EPSILON &&
			  abs(g - c.g) < EPSILON &&
			  abs(b - c.b) < EPSILON)
			return true;
		else
			return false;
	}

	// RUN UNIT TESTS
	static void runTests()
	{
		printf("Running Color::runTests()\n");

		// Constructor
		Color c(-0.5, 0.4, 1.7);
		assert(c.getR() == -0.5);
		assert(c.getG() == 0.4);
		assert(c.getB() == 1.7);

		// Addition
		assert(Color(0.9, 0.6, 0.75) + Color(0.7, 0.1, 0.25) == Color(1.6, 0.7, 1.0));

		// Subtraction
		assert(Color(0.9, 0.6, 0.75) - Color(0.7, 0.1, 0.25) == Color(0.2, 0.5, 0.5));

		// Scalar Multiplication
		assert(Color(0.2, 0.3, 0.4) * 2 == Color(0.4, 0.6, 0.8));
		
		// Color Multiplication
		assert(Color(1, 0.2, 0.4) * Color(0.9, 1, 0.1) == Color(0.9, 0.2, 0.04));
	}
};

const double Color::EPSILON = 0.0001;
