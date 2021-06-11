#include "Sortalgorithm.h"

// init bubblesort with position 0
BubbleSort::BubbleSort() {
	iterator = 0;
}

// sort array once per function-call and draw the change
// also increment iterator once per call and set to 0 if >= size -1
void BubbleSort::sort(rect *r, sf::RectangleShape* rect, sf::RenderWindow* window, int size) {

	for (int i = 0; i < size; i++) {
		rect->setFillColor(sf::Color(sf::Color::Red));
		if (i == iterator) rect->setFillColor(sf::Color(sf::Color::Blue));
		rect->setPosition(r[i].posx, 600);
		rect->setSize(sf::Vector2f(2, r[i].height));
		rect->setRotation(180);
		window->draw(*rect);
	}

	int taller;

	if (r[iterator].height > r[iterator + 1].height) {
		taller = r[iterator].height;
		r[iterator].height = r[iterator + 1].height;
		r[iterator + 1].height = taller;
	}

	iterator++;

	if (iterator >= size - 1) iterator = 0;

	return;
}