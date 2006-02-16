/**********************************************************************
 * $Id$
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: noding/IntersectionAdder.java rev. 1.4 (JTS-1.7)
 *
 **********************************************************************/

#include "geos/noding.h"

namespace geos {

/*private*/
bool
IntersectionAdder::isTrivialIntersection(const SegmentString* e0,
		int segIndex0, const SegmentString* e1, int segIndex1)
{
	if (e0 != e1) return false;

	if (li.getIntersectionNum() != 1) return false;

	if (isAdjacentSegments(segIndex0, segIndex1)) return true;

	if (! e0->isClosed()) return false;

	int maxSegIndex = e0->size() - 1;
	if ( (segIndex0 == 0 && segIndex1 == maxSegIndex)
		||  (segIndex1 == 0 && segIndex0 == maxSegIndex) )
	{
		return true;
	}
	return false;
 
}

/*public*/
void
IntersectionAdder::processIntersections(
		SegmentString* e0,  int segIndex0,
		SegmentString* e1,  int segIndex1)
{
	// don't bother intersecting a segment with itself
	if (e0 == e1 && segIndex0 == segIndex1) return;

	numTests++;


	const Coordinate& p00 = e0->getCoordinate(segIndex0);
	const Coordinate& p01 = e0->getCoordinate(segIndex0 + 1);
	const Coordinate& p10 = e1->getCoordinate(segIndex1);
	const Coordinate& p11 = e1->getCoordinate(segIndex1 + 1);

	li.computeIntersection(p00, p01, p10, p11);
//if (li.hasIntersection() && li.isProper()) Debug.println(li);

	// No intersection, nothing to do
	if (! li.hasIntersection()) return;

	//intersectionFound = true;
	numIntersections++;

	if (li.isInteriorIntersection())
	{

		numInteriorIntersections++;
		hasInterior=true;
	}

	// if the segments are adjacent they have at least
	// one trivial intersection,
	// the shared endpoint.  Don't bother adding it if it 
	// is the only intersection.
	if (! isTrivialIntersection(e0, segIndex0, e1, segIndex1))
	{
		hasIntersectionVar = true;
		e0->addIntersections(&li, segIndex0, 0);
		e1->addIntersections(&li, segIndex1, 1);
		if (li.isProper()) {
			numProperIntersections++;
			//Debug.println(li.toString()); 
			//Debug.println(li.getIntersection(0));
//properIntersectionPoint = (Coordinate) li.getIntersection(0).clone();
			hasProper = true;
			hasProperInterior = true;
		}
	}
}

} // namespace geos

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/02/16 08:19:07  strk
 * Missed from last commit
 *
 **********************************************************************/
