#pragma once


class Tuple
{
private:
  double x, y, z, w; // if w == 1 it's a point
  double EPSILON = 0.0001;

public:

  void setX(double x) { this->x = x; }
  void setY(double y) { this->y = y; }
  void setZ(double z) { this->z = z; }

  double getW() { return w; }
  double getX() { return x; }
  double getY() { return y; }
  double getZ() { return z; }


  Tuple() : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 }
  {

  }


  Tuple(double nx, double ny, double nz, double nw)
  {
    x = nx, y = ny, z = nz, w = nw;
  }

  Tuple(double nx, double ny, double nz)
  {
    x = nx; y = ny; z = nz; w = 0;
  }

  void set(double nx, double ny, double nz)
  {
    x = nx; y = ny; z = nz;
  }

  void set(double nx, double ny, double nz, double nw)
  {
    x = nx; y = ny; z = nz; w = nw;
  }

  bool operator==(Tuple b)
  {
    if (abs(x - b.x) < EPSILON &&
      abs(y - b.y) < EPSILON &&
      abs(z - b.z) < EPSILON &&
      abs(w - b.w) < EPSILON)
      return true;
    return false;
  }

  void printXYZ()
  {
    printf("%f, %f, %f\n", x, y, z);
  }

  void print()
  {
    std::cout << "x is: " << x << std::endl;
    std::cout << "y is: " << y << std::endl;
    std::cout << "z is: " << z << std::endl;
    std::cout << "w is: " << w << std::endl;
    if (w == 0)
      std::cout << "w is 0 so this is a vector" << std::endl;
    else
      std::cout << "w is not 0 so this is a point" << std::endl;
  }

  Tuple add(Tuple n)
  {
    return Tuple(x + n.x, y + n.y, z + n.z, w + n.w);
  }

  Tuple subtract(Tuple n)
  {
    return Tuple(x + n.x, y + n.y, z + n.z, w + n.w);
  }

  void negate()
  {
    x *= -1;
    y *= -1;
    z *= -1;
    w *= -1;
  }

  Tuple multiple(float s)
  {
    return Tuple(x * s, y * s, z * s, w * s);
  }

  Tuple divide(float s)
  {
    return Tuple(x / s, y / s, z / s, w / s);
  }

  double magnitude()
  {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
  }

  static Tuple normalize(Tuple t)
  {
    double m = t.magnitude();
    return Tuple(t.x / m, t.y / m, t.z / m, t.w / m);
  }

  Tuple normalize()
  {
    double m = magnitude();
    return Tuple(x / m, y / m, z / m, w / m);
  }

  double dot(Tuple n)
  {
    return (x * n.x + y * n.y + z * n.z + w * n.w);
  }

  Tuple cross(Tuple n)
  {
    return Tuple(y * n.z - z * n.y,
      z * n.x - x * n.z,
      x * n.y - y * n.x);
  }

  static Tuple cross(Tuple a, Tuple b)
  {
    return Tuple(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
  }



  static void runTests()
  {
    testNormalize();
    testDot();
    testCross();

  }


  static void testNormalize()
  {
    std::cout << "Running testNormalize()" << std::endl;
    assert(Tuple(4, 0, 0).normalize() == Tuple(1, 0, 0));
    assert(Tuple(1, 2, 3).normalize() == Tuple(0.26726, 0.53452, 0.80178));
  }

  static void testDot()
  {
    std::cout << "Running testDot()" << std::endl;
    Tuple t(1, 2, 3);
    double r = t.dot(Tuple(2, 3, 4));
    assert(r == 20);
  }

  static void testCross()
  {
    std::cout << "Running testCross()" << std::endl;
    Tuple a(1, 2, 3);
    Tuple b(2, 3, 4);

    Tuple c = Tuple::cross(a, b);
    assert(c == Tuple(-1, 2, -1));
    c = Tuple::cross(b, a);
    assert(c == Tuple(1, -2, 1));


  }
};