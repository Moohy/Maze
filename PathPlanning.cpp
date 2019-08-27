/*
*
*   I have thought of some algrothims regarding getPath function but the best
*   one that comes to my mind is starting from goal and go backward scince
*   I will only only compare with distance-1.
*
*   Where if i start from the initial position I will have to create other lists
*   and then compare each of them to get the cheapest path.

*   In term of space the algorithm doeas not consume more than the worst case
*   which is if all the maze are dots except the walls
*
*   For getReachablePositions function, the algorithm was given and I have been
*   thinking of good implementation of the function and use less checking of
*   the existing positions but I couldn't find anyother solution than looping
*   through the list each time to look for position contain same coordinate.
*   This is absolutely a disadvantage since I loop the main list 4 time in
*   checking for neighbour positions.
*
*
*/
#include "PathPlanning.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

/*
*
*   I have created a main list that will have the the worst case of the maze
*   length which is (rows-2)*(cols-2) ignoring the walls.
*
*   I have added a function on the PDList class that can make dynamic list
*   called "growArray". and this can be done by giving no argument to PDList
*   constructor.
*
*   Also, a 2d array has been initilaized and a loop will just copy the maze
*
*/
PathPlanning::PathPlanning(Grid maze, int rows, int cols) {
  p = new PDList((rows-2)*(cols-2));
  m = new char*[rows];

  for (int i = 0; i < rows; i++) {
    m[i] = maze[i];
  }
}

PathPlanning::~PathPlanning() {
  delete[] m;
  m = NULL;
}

void PathPlanning::initialPosition(int x, int y) {
  if (m[y][x] != '.')
    throw std::runtime_error("Initial point should be '.'");
  p->addBack(new PositionDistance(x,y, 0));
}

/*
*
*   This function will get all reachable positions that are reachable in
*   the given maze from the initial position
*
*   The way it works, it goes in a loop and checks up down right left positiions
*   from its parent. If they are dots and not included in the temp list, then
*   add them to the main list and add their parent to the temp list
*
*   Before returning the main list we have to have a list not containing zero
*   position. Also, we need to have a deep copy so we don't lost the main list
*
*/
PDList* PathPlanning::getReachablePositions() {
  int i = 0; // iterating var
  int x, y; // cordinates
  int distance = 0; // distance counter
  PDPtr pd; // PositionDistance pointer

  PDList* t(new PDList(p->getLength())); // temp list

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

  // deep copy and skipping the initial position that has zero distance
  PDList* p1 = new PDList(*p, 1);

  return p1;
}

/*
*
*   This function will get the cheapest path to the goal position
*
*   The way it works, it adds the initial postions from the main list to
*   temp list called p1. Then the function searches for the goal position in
*   the main list by a custom function in PDList that searches for positions by
*   giving coordinates to its arguments. and then adds it to p1 list in an
*   index equals to its distance
*
*   The way it does the search for the cheapest path is, it goes backward from
*   goal position to the initial position by calculating the sum of coordinates
*   of position that has distance-1 and the sum of goal coordinates.
*   If the difference is 1 then it's  a parent to goal position "leads directly
*   to goal position". Then add it ti the list at index of distance-1.
*
*   The function will keep doing this until the distance is 1.
*
*   Then it will deep copy p1 and delete p1 and return p2.
*
*/
PDList* PathPlanning::getPath(int toX, int toY) {
  // in case the maze has only one position and one goal which is the initial
  if (p->size() == 1)
    return p;


  PDList* p1 = new PDList(p->size());
  p1->addBack(p->get(0)); //initial coordinate which has zero distance
  PDPtr pd = p->getByCoordinate(toX, toY); //final distination "goal"

  if (pd == nullptr)
    return NULL;

  int goalDistance = pd->getDistance();
  p1->addAt(pd, goalDistance);
  int i = p->size()-1;
  int sum1, sum2;


  while (i > 0) {
    sum1 = p->get(i)->getX() + p->get(i)->getY();
    sum2 = pd->getX() + pd->getY();
    if (p->get(i)->getDistance() == goalDistance-1
          && std::abs(sum1-sum2) == 1
          && goalDistance > 1) {
      p1->addAt(p->get(i), goalDistance-1);
      pd = p->get(i);
      goalDistance--;
    }
    i--;
  }

  PDList* p2 = new PDList(*p1);
  p1->clear();

  return p2;
}
