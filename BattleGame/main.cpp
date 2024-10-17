#include <SFML/Graphics.hpp>

#include "sceneManager.hpp"
#include "FPSCounter.hpp"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 800 ), "SFML works!" );
	window.setFramerateLimit( 60 );

	SceneManager sceneManager;

	Scene scene1( "scene01" );

	FPSCounter fpsCounter( "fpsCounter", "FPS: ", sf::Vector2f( 0.f, 10.0f ), sf::Vector2f( 1.f, 1.0f ), nullptr, Utils::getDefaultFont(), sf::Color::Green, 24 );
	scene1.addGameObject( fpsCounter );

	sceneManager.addScene( scene1 );

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed )
				window.close();
		}

		window.clear();

		sceneManager.update();
		sceneManager.render( window );

		window.display();
	}

	return 0;
}