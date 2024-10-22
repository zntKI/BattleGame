#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "sceneManager.hpp"
#include "FPSCounter.hpp"
#include "button.hpp"
#include "spriteObject.hpp"
#include "animationSpriteObject.hpp"

//FPSCounter fpsCounter( "fpsCounter", "FPS: ", sf::Vector2f( 0.f, 10.0f ), sf::Vector2f( 1.f, 1.0f ), Utils::getDefaultFont(), sf::Color::Green, 24 );
//TextObject textRed( "textRed", "First", sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 1.f, 1.0f ), Utils::getDefaultFont(), sf::Color::Red, 24 );
//SpriteObject bg( "bg", "Assets/Sprites/Bgs/bg_castle.png", sf::Vector2f(0.f, 0.f), sf::Vector2f( 1/3.f, 1/3.f ) );
//Button button( "btn", sf::Vector2f( 200.f, 100.f ), sf::Color::Red, sf::Vector2f( 300.f, 300.f ), sf::Vector2f( 1.f, 1.f ) );

int main()
{
	sf::RenderWindow window( sf::VideoMode( 1280, 720 ), "SFML works!" );
	window.setFramerateLimit( 60 );

#pragma region SETUP_SCENE_GENERAL

	SceneManager sceneManager;

	Scene scene1( "sceneMenu" );
	Scene scene2( "sceneGameplay" );

	sceneManager.addScene( scene1 );
	sceneManager.addScene( scene2 );

#pragma endregion

#pragma region SETUP_SCENE_MENU

	// Container for buttons

	GameObject btnContainer( "btnContainer", sf::Vector2f( window.getSize().x / 2.f, window.getSize().y / 2.f ) );
	scene1.addGameObject( btnContainer );

	// General btn vars

	sf::Vector2f btnSize( 200.f, 100.f );
	sf::Vector2f btnOffset( 0.f, btnSize.y + 50.f );


	// Play button

	Button buttonPlay( "btnPlay", btnSize, sf::Color::Red, btnContainer.getGlobalPosition() - btnOffset );
	scene1.addGameObject( buttonPlay );
	TextObject btnPlayText( "btnPlayText", "Play", buttonPlay.getGlobalPosition(), sf::Vector2f( 0.5f, 0.5f ) );
	btnPlayText.attachToParent( buttonPlay );

	buttonPlay.setButtonAction( [ &sceneManager, &scene2 ]() {
		sceneManager.stackScene( scene2.getIdentifier() );
		} );

	buttonPlay.attachToParent( btnContainer );

	scene1.addGameObject( btnPlayText );


	// Erase button

	Button buttonErase( "btnErase", btnSize, sf::Color::Red, btnContainer.getGlobalPosition() );
	scene1.addGameObject( buttonErase );
	TextObject btnEraseText( "btnEraseText", "Erase", buttonErase.getGlobalPosition(), sf::Vector2f( 0.5f, 0.5f ) );
	btnEraseText.attachToParent( buttonErase );

	buttonErase.attachToParent( btnContainer );

	scene1.addGameObject( btnEraseText );


	// Quit button

	Button buttonQuit( "btnQuit", btnSize, sf::Color::Red, btnContainer.getGlobalPosition() + btnOffset );
	scene1.addGameObject( buttonQuit );
	TextObject btnQuitText( "btnQuitText", "Quit", buttonQuit.getGlobalPosition(), sf::Vector2f( 0.5f, 0.5f ) );
	btnQuitText.attachToParent( buttonQuit );

	buttonQuit.setButtonAction( [ &window ]() {
		window.close();
		} );

	buttonQuit.attachToParent( btnContainer );

	scene1.addGameObject( btnQuitText );

#pragma endregion

#pragma region SETUP_SCENE_GAMEPLAY

	SpriteObject bg( "bg", "Assets/Sprites/Bgs/bg_castle.png", sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 1 / 3.f, 1 / 3.f ) );
	scene2.addGameObject( bg );

	// TODO: implement scale changing down the children line in game objects as it is with position!
	AnimationSpriteObject character( "char", "Assets/Sprites/Characters/FireWizard/idle.png", 1, 7, .1f, sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 2.f, 2.f ) );
	scene2.addGameObject( character );

#pragma endregion

#pragma region SETUP_FPS_COUNTER

	FPSCounter fpsCounter( "fpsCounter", "FPS: ", sf::Vector2f( 0.f, 10.0f ), sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 1.f, 1.f ), Utils::getDefaultFont(), sf::Color::Red, 24 );
	scene1.addGameObject( fpsCounter );
	scene2.addGameObject( fpsCounter );

#pragma endregion

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