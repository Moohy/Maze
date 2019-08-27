
#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>


PDList::PDList() {
  length = 200; // default value if not initilaized
  this->positions = new PDPtr[length];
  numPositions = 0;
}

PDList::PDList(int length){
  this->length = length;
  this->positions = new PDPtr[length];
  numPositions = 0;
}

PDList::PDList(PDList &other, int skip) {
  length = other.size();
  this->positions = new PDPtr[length];
  if(other.size() == skip)
    throw std::runtime_error("An empty list will result");
  else
    for (int i = skip; i < other.size(); ++i) {
      this->positions[i-skip] = new PositionDistance(*(other.positions[i]));
    }
  numPositions = other.size()-skip;
}

PDList::~PDList() {
  for (int i = 0; i < numPositions; i++) {
    delete *(positions+i);
  }
  delete[] positions;
}

void PDList::growArray(){
  length *= 2;
  PDPtr p[length];
  for (int i = 0; i < this->size(); ++i) {
    *(p+i) = this->get(i);
  }
  this->positions = p;
}

int PDList::size() {
   return numPositions;
}

int PDList::getLength(){
  return length;
}

PDPtr PDList::get(int i) {
  if (i >= this->size() || i < 0)
    throw std::runtime_error("Invalid index get(i)");

   return *(this->positions+i);
}

void PDList::addBack(PDPtr position) {
  if (this->containsCoordinate(position))
    return void();

  if(this->size() >= this->length)
    growArray();

  *(this->positions+numPositions)=position;
  numPositions++;
}

void PDList::addAt(PDPtr position, int i) {
  if (i >= this->getLength() || i < 0)
    throw std::runtime_error("Invalid add index addAt(x, i)");

  *(this->positions+i)=position;
  numPositions++;
}

PDPtr PDList::getByCoordinate(int x, int y) {
  for (int i = numPositions-1; i >= 0; i--) {
    if (x == (*(this->positions+i))->getX()
        && y == (*(this->positions+i))->getY())
      return *(this->positions+i);
  }
  return nullptr;
}

bool PDList::containsCoordinateXY(int x, int y) {
  for (int i = 0; i < this->size(); ++i) {
    if (x == (*(positions+i))->getX()
        && y == (*(positions+i))->getY())
      return true;
  }
  return false;
}

bool PDList::containsCoordinate(PDPtr position) {
  for (int i = 0; i < numPositions; i++) {
    if (position->getX() == (*(this->positions+i))->getX()
        && position->getY() == (*(this->positions+i))->getY())
      return true;
  }
   return false;
}

void PDList::clear() {
  PDList::~PDList();
}
