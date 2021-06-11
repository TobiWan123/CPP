#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "Sortalgorithm.h";

bool init = false;
int size = 200;
rect *rectData;

// sf::Time delay = sf::seconds(1.0f);

int main()
{
    sf::RenderWindow window(sf::VideoMode(size, 600), "Sortalgorithm-Visualization");
    sf::RectangleShape rect(sf::Vector2f(2, 100.0f));

    // change implementaition for different Sort-Visualization
    // MergeSort merges = new MergeSort();
    BubbleSort* bubble = new BubbleSort();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!init) {
            init = true;
            rectData = initRect(size);
        }

        bubble->sort(rectData, &rect, &window, size); 

        window.display();
        window.clear();
    }

    return 0;
}