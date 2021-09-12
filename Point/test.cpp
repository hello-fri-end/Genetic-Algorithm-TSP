#include "point.hpp"
#include<iostream>
using namespace std;

int main()
{
  Point X;
  cout<<X.get_x()<<X.get_y()<<X.get_z()<<endl;

  Point Y(1, 2, 3);
  cout<<Y.get_x()<<Y.get_y()<<Y.get_z()<<endl;

  cout<< X.distance_to(Y)<<endl;
}
