// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <assert.h>
#include <stdio.h>

#include "tuple.h"
#include "color.h"
#include "canvas.h"
#include "matrix.h"

#define TEST



struct projectile
{
  Tuple position, velocity;
  projectile() 
  {
  }
};

struct environment
{
  Tuple gravity, wind;
};

projectile tick(environment env, projectile proj)
{
  proj.position = proj.position.add(proj.velocity);
  proj.velocity = proj.velocity.add(env.gravity).add(env.wind);
  return proj;
}

int main()
{
  Tuple::runTests();
  Color::runTests();
  Canvas::runTests();
  Matrix::runTests();
  
  double width = 110;
  double height = 110;
  Canvas c(width, height);
  
  projectile p;
  p.position = Tuple(0,1,0);
  p.velocity = Tuple(1, 1, 0).normalize();

  environment e;
  e.gravity = Tuple(0, -0.1, 0);
  e.wind = Tuple(-0.01, 0, 0);

  double scale = 10;
  float rvalue = 1;
  while (p.position.getY() > 0)
  {
    //p.position.printXYZ();
    c.writePixel(p.position.getX()*scale, height - p.position.getY()*scale, Color(rvalue, 0, 0));
    
    p = tick(e, p);
    
  }
  c.saveToFile("C:\\Users\\Marm\\Desktop\\test.ppm");

}
