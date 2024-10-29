#include <SFML/Graphics.hpp>

#include "sceneManager.hpp"
#include "FPSCounter.hpp"
#include "button.hpp"
#include "spriteObject.hpp"
#include "animationSpriteObject.hpp"
#include "gameScene.hpp"

//FPSCounter fpsCounter( "fpsCounter", "FPS: ", sf::Vector2f( 0.f, 10.0f ), sf::Vector2f( 1.f, 1.0f ), Utils::getDefaultFont(), sf::Color::Green, 24 );
//TextObject textRed( "textRed", "First", sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 1.f, 1.0f ), Utils::getDefaultFont(), sf::Color::Red, 24 );
//SpriteObject bg( "bg", "Assets/Sprites/Bgs/bg_castle.png", sf::Vector2f(0.f, 0.f), sf::Vector2f( 1/3.f, 1/3.f ) );
//Button button( "btn", sf::Vector2f( 200.f, 100.f ), sf::Color::Red, sf::Vector2f( 300.f, 300.f ), sf::Vector2f( 1.f, 1.f ) );

int main()
{
	srand( time( 0 ) );

	sf::RenderWindow window( sf::VideoMode( 1280, 720 ), "SFML works!" );
	window.setFramerateLimit( 60 );

#pragma region SETUP_SCENE_GENERAL

	SceneManager sceneManager("Assets/configs/scenes.json");

	GameScene gameScene( "gameScene" );
	sceneManager.addScene( gameScene );

	/*Scene scene1( "sceneMenu" );
	Scene scene2( "sceneGameplay" );

	sceneManager.addScene( scene1 );
	sceneManager.addScene( scene2 );*/

#pragma endregion

//#pragma region SETUP_SCENE_MENU
//
//	// Game title
//
//	SpriteObject titlePanel( "titlePanel", "Assets/Sprites/UI/title_panel.png", sf::Vector2f( window.getSize().x / 2.f, window.getSize().y / 5.f ), sf::Vector2f( 3.f, 3.f ), sf::Vector2f( 0.5f, 0.5f ) );
//	scene1.addGameObject( titlePanel );
//	TextObject gameTitleText( "gameTitleText", "Game_Title", titlePanel.getGlobalPosition() - sf::Vector2f( 0.f, 20.f ), sf::Vector2f( 0.5f, 0.5f ), Utils::getDefaultFont(), sf::Color::Yellow, 50 );
//	gameTitleText.attachToParent( titlePanel );
//	scene1.addGameObject( gameTitleText );
//
//
//	// Container for buttons
//
//	GameObject btnContainer( "btnContainer", sf::Vector2f( window.getSize().x / 2.f, window.getSize().y * 2 / 3.f ) );
//	scene1.addGameObject( btnContainer );
//
//	// General btn vars
//
//	sf::Vector2f btnOffset( 0.f, 150.f );
//
//
//	// Play button
//
//	Button buttonPlay( "btnPlay", "Assets/Sprites/UI/btn.png", 1, 3, btnContainer.getGlobalPosition() - btnOffset, sf::Vector2f( 3.f, 3.f ), sf::Vector2f( 0.5f, 0.5f ) );
//	scene1.addGameObject( buttonPlay );
//	TextObject btnPlayText( "btnPlayText", "Play", buttonPlay.getGlobalPosition(), sf::Vector2f( 0.5f, 0.5f ) );
//	btnPlayText.attachToParent( buttonPlay );
//
//	buttonPlay.setButtonAction( [ &sceneManager, &scene2 ]() {
//		sceneManager.stackScene( scene2.getIdentifier() );
//		} );
//
//	buttonPlay.attachToParent( btnContainer );
//
//	scene1.addGameObject( btnPlayText );
//
//
//	// Erase button
//
//	Button buttonErase( "btnErase", "Assets/Sprites/UI/btn.png", 1, 3, btnContainer.getGlobalPosition(), sf::Vector2f( 3.f, 3.f ), sf::Vector2f( 0.5f, 0.5f ) );
//	scene1.addGameObject( buttonErase );
//	TextObject btnEraseText( "btnEraseText", "Erase", buttonErase.getGlobalPosition(), sf::Vector2f( 0.5f, 0.5f ) );
//	btnEraseText.attachToParent( buttonErase );
//
//	buttonErase.attachToParent( btnContainer );
//
//	scene1.addGameObject( btnEraseText );
//
//
//	// Quit button
//
//	Button buttonQuit( "btnQuit", "Assets/Sprites/UI/btn.png", 1, 3, btnContainer.getGlobalPosition() + btnOffset, sf::Vector2f( 3.f, 3.f ), sf::Vector2f( 0.5f, 0.5f ) );
//	scene1.addGameObject( buttonQuit );
//	TextObject btnQuitText( "btnQuitText", "Quit", buttonQuit.getGlobalPosition(), sf::Vector2f( 0.5f, 0.5f ) );
//	btnQuitText.attachToParent( buttonQuit );
//
//	buttonQuit.setButtonAction( [ &window ]() {
//		window.close();
//		} );
//
//	buttonQuit.attachToParent( btnContainer );
//
//	scene1.addGameObject( btnQuitText );
//
//	/*sf::RectangleShape verticalLine( sf::Vector2f( 3.f, window.getSize().y ) );
//	verticalLine.setOrigin( verticalLine.getSize() / 2.f );
//	verticalLine.setPosition( sf::Vector2f( window.getSize().x / 2.f, window.getSize().y / 2.f ) );
//
//	sf::RectangleShape horizontalLine( sf::Vector2f( window.getSize().x, 3.f ) );
//	horizontalLine.setOrigin( horizontalLine.getSize() / 2.f );
//	horizontalLine.setPosition( sf::Vector2f( window.getSize().x / 2.f, window.getSize().y / 2.f ) );*/
//
//#pragma endregion
//
//#pragma region SETUP_SCENE_GAMEPLAY
//
//	// BG setup
//	SpriteObject bg( "bg", "Assets/Sprites/Bgs/bg_dry.png", sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 1 / 3.f, 1 / 3.f ), sf::Vector2f( 0.f, 0.f ) );
//	scene2.addGameObject( bg );
//
//
//
//	// Player setup
//	AnimationSpriteObject character( "char", "Assets/Sprites/Characters/FireWizard/idle.png", 1, 7, 1.f, sf::Vector2f( window.getSize().x / 4.f, window.getSize().y / 2.f ), sf::Vector2f( 3.f, 3.f ), sf::Vector2f( 0.4f, 0.75f ) );
//	scene2.addGameObject( character );
//	/*AnimationSpriteObject fireBall( "fireBall", "Assets/Sprites/Characters/FireWizard/charge.png", 1, 12, .1f,
//		character.getGlobalPosition() + sf::Vector2f( character.getSpriteSize().x / 2.f, 0.f ), sf::Vector2f(3.f, 3.f), sf::Vector2f(1.f, 0.5f));
//	scene2.addGameObject( fireBall );
//	fireBall.attachToParent( character );*/
//	SpriteObject healthBarChar( "healthBarChar", "Assets/Sprites/UI/health_bar.png",
//		character.getGlobalPosition() - sf::Vector2f( 0.f, character.getSpriteSize().y / 3.f ), sf::Vector2f( 1.f, 1.f ), sf::Vector2f( .5f, .5f ) );
//	scene2.addGameObject( healthBarChar );
//	healthBarChar.attachToParent( character );
//	// TODO: Make it an animation sprite with all three colors - green, orange and red (sprite sheet with three different sprites); make them change accordingly depending on the health percentage
//	SpriteObject healthBarFillChar( "healthBarFillChar", "Assets/Sprites/UI/health_bar_fill.png",
//		healthBarChar.getGlobalPosition() - sf::Vector2f( healthBarChar.getSpriteSize().x / 2.f, 0.f ), sf::Vector2f( 1.f, 1.f ), sf::Vector2f( 0.f, .5f ) );
//	scene2.addGameObject( healthBarFillChar );
//	//healthBarFillChar.attachToParent( healthBarChar );
//
//	// Enemy setup
//	AnimationSpriteObject enemy( "enemy", "Assets/Sprites/Characters/WandererMagican/idle_flipped.png", 1, 8, .9f, sf::Vector2f( window.getSize().x * 3 / 4.f, window.getSize().y / 2.f ), sf::Vector2f( 3.f, 3.f ), sf::Vector2f( 0.5f, 0.75f ) );
//	scene2.addGameObject( enemy );
//	SpriteObject healthBarEnemy( "healthBarEnemy", "Assets/Sprites/UI/health_bar.png",
//		enemy.getGlobalPosition() - sf::Vector2f( 0.f, enemy.getSpriteSize().y / 3.f ), sf::Vector2f( 1.f, 1.f ), sf::Vector2f( .5f, .5f ) );
//	scene2.addGameObject( healthBarEnemy );
//	healthBarEnemy.attachToParent( enemy );
//	// TODO: Make it an animation sprite with all three colors - green, orange and red (sprite sheet with three different sprites); make them change accordingly depending on the health percentage
//	SpriteObject healthBarFillEnemy( "healthBarFillEnemy", "Assets/Sprites/UI/health_bar_fill.png",
//		healthBarEnemy.getGlobalPosition() + sf::Vector2f( healthBarEnemy.getSpriteSize().x / 2.f, 0.f ), sf::Vector2f( 1.f, 1.f ), sf::Vector2f( 1.f, .5f ) );
//	scene2.addGameObject( healthBarFillEnemy );
//	healthBarFillEnemy.attachToParent( healthBarEnemy );
//
//
//
//	// UI setup
//	SpriteObject optionsPanel( "optionsPanel", "Assets/Sprites/UI/text_area_flipped.png", sf::Vector2f( 0.f, window.getSize().y * 1.f ), sf::Vector2f( 4.f, 5.f ), sf::Vector2f( 0.f, 1.f ) );
//	scene2.addGameObject( optionsPanel );
//
//	GameObject optionContainer( "optionContainer", optionsPanel.getGlobalPosition() + sf::Vector2f( optionsPanel.getSpriteSize().x / 2.f, -( optionsPanel.getSpriteSize().y / 2.f ) ) );
//	scene2.addGameObject( optionContainer );
//	optionContainer.attachToParent( optionsPanel );
//
//	sf::Vector2f actionButtonsOffset( 100.f, 0.f );
//
//	Button buttonAttack( "btnAttack", "Assets/Sprites/UI/btn2.png", 1, 3, optionContainer.getGlobalPosition() - actionButtonsOffset, sf::Vector2f( 2.5f, 2.5f ), sf::Vector2f( 0.5f, 0.5f ) );
//	scene2.addGameObject( buttonAttack );
//	TextObject buttonAttackText( "buttonAttackText", "Attack", buttonAttack.getGlobalPosition(), sf::Vector2f( 0.5f, 0.5f ) );
//	scene2.addGameObject( buttonAttackText );
//	buttonAttackText.attachToParent( buttonAttack );
//
//	buttonAttack.attachToParent( optionContainer );
//
//	Button btnRecover( "btnRecover", "Assets/Sprites/UI/btn2.png", 1, 3, optionContainer.getGlobalPosition() + actionButtonsOffset, sf::Vector2f( 2.5f, 2.5f ), sf::Vector2f( 0.5f, 0.5f ) );
//	scene2.addGameObject( btnRecover );
//	TextObject buttonRecoverText( "buttonRecoverText", "Recover", btnRecover.getGlobalPosition(), sf::Vector2f( 0.5f, 0.5f ) );
//	scene2.addGameObject( buttonRecoverText );
//	buttonRecoverText.attachToParent( btnRecover );
//
//	btnRecover.attachToParent( optionContainer );
//
//
//	SpriteObject textArea( "textArea", "Assets/Sprites/UI/text_area.png", sf::Vector2f( window.getSize().x * 1.f, window.getSize().y * 1.f ), sf::Vector2f( 5.f, 5.f ), sf::Vector2f( 1.f, 1.f ) );
//	scene2.addGameObject( textArea );
//
//
//	// Quit button
//
//	Button buttonQuitGame( "buttonQuitGame", "Assets/Sprites/UI/btn.png", 1, 3, sf::Vector2f(window.getSize().x * 1.f, 0.f), sf::Vector2f(2.f, 2.f), sf::Vector2f(1.f, 0.f));
//	scene2.addGameObject( buttonQuitGame );
//	TextObject btnQuitGameText( "btnQuitGameText", "Quit", buttonQuitGame.getGlobalPosition() + sf::Vector2f( -(buttonQuitGame.getSpriteSize().x / 2.f), buttonQuitGame.getSpriteSize().y / 2.f ), sf::Vector2f(0.5f, 0.5f));
//	btnQuitGameText.attachToParent( buttonQuitGame );
//
//	buttonQuitGame.setButtonAction( [ &sceneManager ]() {
//		sceneManager.popScene();
//		} );
//
//	scene2.addGameObject( btnQuitGameText );
//
//#pragma endregion
//
//#pragma region SETUP_FPS_COUNTER
//
//	FPSCounter fpsCounter( "fpsCounter", "FPS: ", sf::Vector2f( 0.f, 10.0f ), sf::Vector2f( 0.f, 0.f ), Utils::getDefaultFont(), sf::Color::Red, 24 );
//	scene1.addGameObject( fpsCounter );
//	scene2.addGameObject( fpsCounter );
//
//#pragma endregion

	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed )
				window.close();
			else if ( event.type == sf::Event::KeyPressed && 
				event.key.code == sf::Keyboard::R) {
				
				//sceneManager.clearScenes();

				// TODO: Figure out!

			}
			else
				sceneManager.handleEvent( event, window );
		}

		window.clear();

		sceneManager.update();
		sceneManager.render( window );
		/*window.draw( verticalLine );
		window.draw( horizontalLine );*/

		window.display();
	}

	return 0;
}

//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <string>
//
//int main() {
//    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Scrollable Fight Screen" );
//
//    // Load a font
//    sf::Font font;
//    if ( !font.loadFromFile( "Assets/Roboto-Regular.ttf" ) ) {
//        return -1;
//    }
//
//    // Create the background rectangle for the text area
//    sf::RectangleShape textAreaBackground( sf::Vector2f( 600.f, 100.f ) );
//    textAreaBackground.setFillColor( sf::Color( 200, 200, 200 ) );  // Light grey background
//    textAreaBackground.setPosition( 100.f, 400.f );  // Position the background
//
//    // Create the text for the fight messages
//    sf::Text fightText;
//    fightText.setFont( font );
//    fightText.setCharacterSize( 18 );
//    fightText.setFillColor( sf::Color::Black );
//    fightText.setPosition( textAreaBackground.getPosition().x + 10.f, textAreaBackground.getPosition().y + 10.f );
//
//    // A list of fight messages (for demonstration)
//    std::vector<std::string> fightMessages = {
//        "Player attacks with a sword!",
//        "Enemy blocks the attack.",
//        "Player prepares for a special move.",
//        "Enemy strikes back!",
//        "Player dodges the attack.",
//        "Player uses a healing potion.",
//        "Enemy stumbles.",
//        "Player lands a critical hit!",
//        "Enemy is defeated.",
//        "Player wins the battle!"
//    };
//
//    const int maxVisibleLines = 4;  // Number of visible lines in the text area
//    int scrollOffset = 0;  // Keeps track of the current scrolling position
//
//    // Function to update visible text based on the scroll offset
//    auto updateVisibleText = [ & ]() {
//        std::string visibleText;
//        int start = scrollOffset;
//        int end = std::min( static_cast< int >( fightMessages.size() ), scrollOffset + maxVisibleLines );
//
//        for ( int i = start; i < end; ++i ) {
//            visibleText += fightMessages[ i ] + "\n";
//        }
//
//        fightText.setString( visibleText );
//    };
//
//    updateVisibleText();
//
//    while ( window.isOpen() ) {
//        sf::Event event;
//        while ( window.pollEvent( event ) ) {
//            if ( event.type == sf::Event::Closed )
//                window.close();
//
//            // Scroll up (e.g., mouse wheel or up arrow)
//            if ( event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta > 0 ) {
//                if ( scrollOffset > 0 ) {
//                    scrollOffset--;
//                    updateVisibleText();
//                }
//            }
//
//            // Scroll down (e.g., mouse wheel or down arrow)
//            if ( event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta < 0 ) {
//                if ( scrollOffset < fightMessages.size() - maxVisibleLines ) {
//                    scrollOffset++;
//                    updateVisibleText();
//                }
//            }
//
//            // Scroll with keyboard (optional)
//            if ( event.type == sf::Event::KeyPressed ) {
//                if ( event.key.code == sf::Keyboard::Up ) {
//                    if ( scrollOffset > 0 ) {
//                        scrollOffset--;
//                        updateVisibleText();
//                    }
//                }
//                else if ( event.key.code == sf::Keyboard::Down ) {
//                    if ( scrollOffset < fightMessages.size() - maxVisibleLines ) {
//                        scrollOffset++;
//                        updateVisibleText();
//                    }
//                }
//            }
//        }
//
//        // Draw the scene
//        window.clear( sf::Color::White );
//        window.draw( textAreaBackground );  // Draw the background of the text area
//        window.draw( fightText );           // Draw the fight messages text
//        window.display();
//    }
//
//    return 0;
//}