#include <SFML/Graphics.hpp>

#include "sceneManager.hpp"
#include "menuScene.hpp"
#include "gameScene.hpp"

int main(int argc, char* argv[])
{
	srand( time( 0 ) );

	int width = argc > 1 ? std::stoi( argv[ 1 ] ) : 1280;
	int height = argc > 2 ? std::stoi( argv[ 2 ] ) : 720;
	Utils::setScreenDimensions( width, height );

	sf::RenderWindow window( sf::VideoMode( width, height ), "Battle Game" );
	window.setFramerateLimit( 60 );

#pragma region SETUP_SCENE_GENERAL

	SceneManager sceneManager( window );

	MenuScene menuScene( "menuScene", sceneManager, "Assets/configs/scenes.json", "Assets/configs/high_scores.cmgt" );
	sceneManager.addScene( menuScene );
	GameScene gameScene( "gameScene", sceneManager, "Assets/configs/scenes.json", "Assets/configs/high_scores.cmgt" );
	sceneManager.addScene( gameScene );

	sceneManager.stackScene( menuScene.getIdentifier() );

#pragma endregion

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed )
				window.close();
			else if ( event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::R ) {

				//sceneManager.clearScenes();

				// TODO: Figure out!

			}
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