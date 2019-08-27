
#include "PositionDistance.h"

#include <cstdio>
#include <cstdlib>

PositionDistance::PositionDistance(int x, int y, int d){
  this->x = x;
  this->y = y;
  this->d = d;
}

PositionDistance::PositionDistance(PositionDistance &other){
  this->x = other.x;
  this->y = other.y;
  this->d = other.d;
}

PositionDistance::~PositionDistance(){

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
