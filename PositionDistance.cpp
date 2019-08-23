
#include "PositionDistance.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

PositionDistance::PositionDistance(int x, int y, int d){
  this->x = x;
  this->y = y;
  this->d = d;
}
PositionDistance::~PositionDistance(){
  // delete this;
}


int PositionDistance::getX() {
   return this->x;
}

int PositionDistance::getY() {
   return this->y;
}

int PositionDistance::getDistance() {
   return this->d;
}

void PositionDistance::printMe(){
  std::cout << "(" << this->x << "," << this->y << "," << this->d << ")" << std::endl;
}
