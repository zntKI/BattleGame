#include "gameObject.hpp"

GameObject::GameObject()
{
	font.loadFromFile( "Assets/Roboto-Regular.ttf" );
	text.setFont( font );
	text.setString( "FPS: " );
	text.setCharacterSize( 24 );
	text.setFillColor( sf::Color::Green );
}

GameObject::~GameObject()
{
}

void GameObject::render( sf::RenderWindow& window, sf::Vector2f pos )
{
	text.setPosition( pos );
	window.draw( text );
}
