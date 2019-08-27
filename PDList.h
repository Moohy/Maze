
#ifndef COSC_ASS_ONE_POSITION_LIST
#define COSC_ASS_ONE_POSITION_LIST

#include "PositionDistance.h"
#include "Types.h"

class PDList {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Create a New Empty List
   PDList();

   // Clean-up the list
   ~PDList();

   // Number of items in the list
   int size();

   // Get a pointer to the position-distance at index i
   PDPtr get(int i);

   // Add a position-distance (as a pointer) to the list
   //    This class now has control over the pointer
   //    And should delete the pointer if the position-distance is removed from the list
   void addBack(PDPtr position);

   // Checks if the list contains a position-distance with the same co-ordinate
   //    as the given position.
   bool containsCoordinate(PDPtr position);

   // Remove everything from the list
   // Don't forget to clean-up the memory!
   void clear();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

    // constructor will create positions array of size length
    PDList(int length);

    // deep copy
    PDList(PDList &other, int skip=0);

    // grow array if list is initilaized without giving length integers
    void growArray();

    // add a position at index i
    // This will overwrite any position on index i with the new one
    void addAt(PDPtr position, int i);

    // searches for position by giving coordinate
    // returns true if found, otherwise false.
    bool containsCoordinateXY(int x, int y);

    // get position by giving coordinate
    // returns PDPtr if found, nullptr otherwise
    PDPtr getByCoordinate(int x, int y);

    // will return the length of the list
    int getLength();


   /* This is a suggestion of what you could use. */
   /* You can change this code.                   */
private:
  int       length;
  PDPtr*    positions;
  int       numPositions;


};

#endif // COSC_ASS_ONE_POSITION_LIST
