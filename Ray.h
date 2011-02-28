////////////////////////////////////////////////////////////////////////////////////////////////
//class Ray:
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef RAY_H
#define RAY_H

#include "Event.h"
#include "Position.h"
#include <vector>
using namespace std;

class Position;

class Ray {


 public:
  Ray();
  vector<double> getEField(Event *event,Position pos); // Get E field from the shower at a particular location pos
  
  protected:
  
  private:

};

#endif //RAY_H
