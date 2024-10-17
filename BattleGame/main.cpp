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
	TextObject textRed( "textRed", "First", sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 1.f, 1.0f ), nullptr, Utils::getDefaultFont(), sf::Color::Red, 24 );
	TextObject textGreen( "textGreen", "Second", sf::Vector2f( 50.f, 50.f ), sf::Vector2f( 1.f, 1.0f ), &textRed, Utils::getDefaultFont(), sf::Color::Green, 24 );
	TextObject textBlue( "textBlue", "Third", sf::Vector2f( 100.f, 100.f ), sf::Vector2f( 1.f, 1.0f ), &textGreen, Utils::getDefaultFont(), sf::Color::Blue, 24 );
	scene1.addGameObject( textRed );
	scene1.addGameObject( textGreen );
	scene1.addGameObject( textBlue );

	// Setup to test parent-child relation
	textRed.move( sf::Vector2f( 50.f, 50.f ) );
	textGreen.move( sf::Vector2f( 200.f, 0.f ) );
	textBlue.move( sf::Vector2f( 0.f, 100.f ) );

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