#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
		sf::Texture texture;
		if (!texture.loadFromFile("picture.png"))
		{
			std::cout << "Error" << std::endl;
			return 1;
		}

	sf::Sprite sprite;
	sprite.setTexture(texture);
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

		window.draw(sprite);
        // end the current frame
        window.display();
    }

    return 0;
}
