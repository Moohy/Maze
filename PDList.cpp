
#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>


PDList::PDList() {
  numPositions = 0;
}

PDList::PDList(PDList &p, int skip) {
  for (int i = skip; i < p.size(); ++i) {
    *(positions+i-skip) = new PositionDistance(p.get(i)->getX(), p.get(i)->getY(), p.get(i)->getDistance());
  }
  numPositions = p.size()-skip;
}

PDList::~PDList() {
  for (int i = 0; i < numPositions; i++) {
    delete positions[i];
  }
}

int PDList::size() {
   return numPositions;
}

PDPtr PDList::get(int i) {
  if (i > this->size()) {
    return NULL;
  }
   return *(this->positions+i);
}

void PDList::addBack(PDPtr position) {
  if (this->containsCoordinate(position)) {
    return void();
  }
  *(this->positions+numPositions)=position;
  numPositions++;
}

void PDList::addAt(PDPtr position, int i) {
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

void PDList::print() {
  PDPtr p;
  for (int i = 0; i < numPositions; i++) {
    p=this->get(i);
    printf("(%d, %d, %d)\n",p->getX(), p->getY(), p->getDistance());
  }
}

void PDList::clear() {
  this->PDList::~PDList();
}
