#include <SFML/Graphics.hpp>

#include "sceneManager.hpp"
#include "menuScene.hpp"
#include "gameScene.hpp"

int main()
{
	srand( time( 0 ) );

	sf::RenderWindow window( sf::VideoMode( 1280, 720 ), "SFML works!" );
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