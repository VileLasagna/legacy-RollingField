#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H


#include "Rect.h"


template <class T>
class BoundingBox: public Rect
{

public:
	
	BoundingBox () : mX(0), MX(0), mY(0), MY(0), mZ(0), MZ(0) {}
	BoundingBox (T minX, T maxX, T minY, T maxY, T minZ, T maxZ) :  mX(minX), MX(maxX), mY(minY), MY(maxY), mZ(minZ), MZ(maxZ) {}
	BoundingBox(const& Rect<T> ref) : mX(ref.minX), MX(ref.maxX), mY(ref.minY), MY (ref.maxY), mZ(0), MZ(0) {}

	T minZ() const {return mZ;}
	T maxZ() const {return MZ;}

	T depth() const {return MZ-mz;}


private:
	T mZ, MZ;

};


#endif //BOUNDING_BOX_H