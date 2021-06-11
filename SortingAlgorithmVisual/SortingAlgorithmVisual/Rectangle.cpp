#include "Rectangle.h"
#include <stdlib.h>

// build unsorted array with random rectangles(heights)
rect * initRect(int size) {;
	rect *r = new rect[size];
	for (int i = 0; i < size; i++) {
		r[i].posx = i;
		r[i].height = 1 + rand() % 500; 
 	}

	return r;
}