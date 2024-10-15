#include <SFML/Graphics.hpp>

#include "FPSCounter.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 200, 200 ), "SFML works!" );
	FPSCounter fpsCounter;

	sf::Clock clock;
	sf::Time elapsed = clock.getElapsedTime();
	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed )
				window.close();
		}

		window.clear();

		fpsCounter.update( elapsed );
		fpsCounter.render( window, sf::Vector2f(10, 50) );

		window.display();

		elapsed = clock.getElapsedTime();
		clock.restart();
	}

	return 0;
}