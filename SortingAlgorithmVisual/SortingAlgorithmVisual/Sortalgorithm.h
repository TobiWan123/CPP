#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"

class BubbleSort {
private:
	
public:
	int iterator;

	BubbleSort();

	void sort(rect* r, sf::RectangleShape* rect, sf::RenderWindow* window, int size);  // function parameter [] is same as * for passing and returning array by reference
};

class MergeSort {
private:
	
public:
	MergeSort();

	void sort(rect* r, sf::RectangleShape* rect, sf::RenderWindow* window, int size);
};