/*
 * @file Point/point.hpp
 * @author Shah Anwaar Khalid
 *
 * This class represents a point in three dimensional space
 * Co ordinates are double precision floating point.
 */

#ifndef POINT_H
#define POINT_H

class Point
{

  public:

  //! Constructors
    Point();
    Point(double x, double y, double z);

  //! Copy constructor
    Point(const Point&);

  //! Copy assignment operator
    Point& operator = (const Point &);

   //! Destructor 
    ~Point();

   //! Mutator methods
    void set_x(const double);
    void set_y(const double);
    void set_z(const double);

   //! Accessor methods
    double get_x() const;
    double get_y() const;
    double get_z() const;


   //! Computes the distance to a point.
    double distance_to(const Point&) const;

  private:
    double x;
    double y;
    double z;
};
#endif
