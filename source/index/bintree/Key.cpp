#include "../../headers/indexBintree.h"
#include "../../headers/indexQuadtree.h"

int Key::computeLevel(BinTreeInterval *interval) {
	double dx=interval->getWidth();
	//int level = BinaryPower.exponent(dx) + 1;
	int level=DoubleBits::exponent(dx)+1;
	return level;
}

Key::Key(BinTreeInterval *interval){
	pt=0.0;
	level=0;
	interval=NULL;
	computeKey(interval);
}

double Key::getPoint() {
	return pt;
}

int Key::getLevel() {
	return level;
}

BinTreeInterval* Key::getInterval() {
	return interval;
}

/**
* return a square envelope containing the argument envelope,
* whose extent is a power of two and which is based at a power of 2
*/
void Key::computeKey(BinTreeInterval *itemInterval) {
	level=computeLevel(itemInterval);
	interval=new BinTreeInterval();
	computeInterval(level,itemInterval);
	// MD - would be nice to have a non-iterative form of this algorithm
	while (!interval->contains(itemInterval)) {
		level+=1;
		computeInterval(level,itemInterval);
	}
}

void Key::computeInterval(int level,BinTreeInterval *itemInterval){
	double size=DoubleBits::powerOf2(level);
	//double size = pow2.power(level);
	pt=floor(itemInterval->getMin()/size)*size;
	interval->init(pt,pt+size);
}
