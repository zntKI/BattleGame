#include <SFML/Graphics.hpp>

#include "FPSCounter.hpp"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 800 ), "SFML works!" );
	window.setFramerateLimit( 60 );

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
		fpsCounter.render( window );

		window.display();

		elapsed = clock.getElapsedTime();
		clock.restart();
	}

	return 0;
}