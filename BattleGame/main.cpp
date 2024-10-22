#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "sceneManager.hpp"
#include "FPSCounter.hpp"
#include "button.hpp"
#include "spriteObject.hpp"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 1280, 720 ), "SFML works!" );
	window.setFramerateLimit( 60 );

	SceneManager sceneManager;

	Scene scene1( "scene01" );

	//FPSCounter fpsCounter( "fpsCounter", "FPS: ", sf::Vector2f( 0.f, 10.0f ), sf::Vector2f( 1.f, 1.0f ), Utils::getDefaultFont(), sf::Color::Green, 24 );
	//scene1.addGameObject( fpsCounter );

	// Setup to test parent-child relation
	//TextObject textRed( "textRed", "First", sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 1.f, 1.0f ), Utils::getDefaultFont(), sf::Color::Red, 24 );
	//TextObject textGreen( "textGreen", "Second", textRed.getGlobalPosition() + sf::Vector2f( 50.f, 50.f ), sf::Vector2f( 1.f, 1.0f ), Utils::getDefaultFont(), sf::Color::Green, 24 );
	//textGreen.attachToParent( textRed );
	//TextObject textBlue( "textBlue", "Third", textGreen.getGlobalPosition() + sf::Vector2f( 50.f, 50.f ), sf::Vector2f( 1.f, 1.0f ), Utils::getDefaultFont(), sf::Color::Blue, 24 );
	//textBlue.attachToParent( textGreen );
	//scene1.addGameObject( textRed );
	//scene1.addGameObject( textGreen );
	//scene1.addGameObject( textBlue );
	//
	//textRed.move( sf::Vector2f( 50.f, 50.f ) );
	//textGreen.move( sf::Vector2f( 200.f, 0.f ) );
	//textBlue.move( sf::Vector2f( 0.f, 100.f ) );

	Scene scene2( "scene02" );

	SpriteObject bg( "bg", "Assets/Sprites/Bgs/bg_castle.png", sf::Vector2f(0.f, 0.f), sf::Vector2f( 1/3.f, 1/3.f ) );
	scene2.addGameObject( bg );

	// Setup to test button functionality
	Button button( "btn", sf::Vector2f( 200.f, 100.f ), sf::Color::Red, sf::Vector2f( 300.f, 300.f ), sf::Vector2f( 1.f, 1.f ) );
	scene1.addGameObject( button );
	TextObject btnText( "btnText", "Play", button.getGlobalPosition() );
	btnText.attachToParent( button );

	button.setButtonAction( [ &sceneManager, &scene2 ]() {
		sceneManager.stackScene( scene2.getIdentifier() );
		} );

	scene1.addGameObject( btnText );

	sceneManager.addScene( scene1 );
	sceneManager.addScene( scene2 );

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed )
				window.close();
			else
				sceneManager.handleEvent( event, window );
		}

		window.clear();

		sceneManager.update();
		sceneManager.render( window );

		window.display();
	}

	return 0;
}

inline void setupMainMenuScene() {

}