
#include "PathPlanning.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

PathPlanning::PathPlanning(Grid maze, int rows, int cols) {
  p = new PDList();
  m = new char*[rows];

  for (int i = 0; i < rows; i++) {
    m[i] = maze[i];
  }

}

PathPlanning::~PathPlanning() {
  delete p;
  delete m;
}

void PathPlanning::initialPosition(int x, int y) {
  p->addBack(new PositionDistance(x,y, 0));
}

PDList* PathPlanning::getReachablePositions() {
  int i = 0; //iterating var
  int x, y; //cordinates
  int distance = 0; //distance counter
  PDPtr pd;


  PDList* t(new PDList()); // temp list

  while (i < p->size()) {
    pd = p->get(i);
    if (pd && !(t->containsCoordinate(pd))) {
      distance = pd->getDistance()+1;
      x = pd->getX();
      y = pd->getY();

      if (m[y+1][x] == '.'
          && (!(t->containsCoordinateXY(x, y+1))))
            p->addBack(new PositionDistance(x, y+1, distance));

      if (m[y-1][x] == '.'
          && (!(t->containsCoordinateXY(x, y-1))))
            p->addBack(new PositionDistance(x, y-1, distance));

      if (m[y][x+1] == '.'
          && (!(t->containsCoordinateXY(x+1, y))))
            p->addBack(new PositionDistance(x+1, y, distance));

      if (m[y][x-1] == '.'
          && (!(t->containsCoordinateXY(x-1, y))))
            p->addBack(new PositionDistance(x-1, y, distance));

      t->addBack(pd);
    }
    i++;
  }

  PDList* p1 = new PDList(*p, 1);

  return p1;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(int toX, int toY) {
  PDList* p1 = new PDList();
  p1->addBack(p->get(0)); //initial coordinate
  PDPtr pd = p->getByCoordinate(toX, toY);

  int goalDistance = pd->getDistance();
  p1->addAt(pd, goalDistance);

  int i = p->size()-1;
  int sum1, sum2;

  while (i > 0) {
    sum1 = p->get(i)->getX() + p->get(i)->getY();
    sum2 = pd->getX() + pd->getY();
    if (p->get(i)->getDistance() == goalDistance-1 && std::abs(sum1-sum2) == 1 && goalDistance > 1) {
      p1->addAt(p->get(i), goalDistance-1);
      pd = p->get(i);
      goalDistance--;
    }
    i--;
  }

  PDList* p2 = new PDList(*p1, 0);

  p1->clear();
  delete p1;
  p->clear();

  return p2;
}
