#include "point.hpp"
#include <cmath>

// Default constructor
// Initializes the point to (0, 0, 0)

Point::Point()
{
  x = 0;
  y = 0;
  z = 0;
}

// Intializes the point to the given (x, y, z)
Point::Point(double x, double y, double z):
  x(x), y(y), z(z) {}

// Copy Constructor
Point::Point(const Point &P)
{
  x = P.get_x();
  y = P.get_y();
  z = P.get_z();
}

//Copy assignment operator
Point& Point::operator= (const Point& P)
{
  this->x = P.get_x();
  this->y = P.get_y();
  this->z = P.get_z();
  return *this;
}

// Destructor - Nothing to do here
Point::~Point()
{
}

// Mutators

void Point::set_x(const double x)
{
  this->x = x;
}

void Point::set_y(const double y)
{
  this->y = y;

}
void Point::set_z(const double z)
{
  this->z = z;
}


// Accessors
double Point::get_x() const {
  return x;
}

double Point::get_y() const {
  return y;
}

double Point::get_z() const {
  return z;
}


// Distance method

double Point::distance_to(const Point& target) const{

  double x_ = target.get_x();
  double y_ = target.get_y();
  double z_ = target.get_z();

  double dist = sqrt (
                    ( (x - x_) * (x - x_)) +
                    ( (y - y_) * (y - y_)) +
                    ( (z - z_) * (z - z_))
                      );

  return dist;
}
