#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	const std::string identifier;

	sf::Vector2f globalPosition;
	sf::Vector2f localPosition;
	sf::Vector2f scale;

	GameObject* parent;
	std::map<std::string, GameObject*> children;

public:
	GameObject( const std::string& identifier,
		const sf::Vector2f& position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f& scale = sf::Vector2f( 1.f, 1.f ) );
	GameObject( const GameObject& other );

	virtual ~GameObject();

protected:
	/// <summary>
	/// sets the local postion of the game object after hierarchy modification
	/// </summary>
	/// <param name="position"> -> the new local position</param>
	virtual void setPosition( sf::Vector2f position );

public:
	std::string getIdentifier() const;
	sf::Vector2f getLocalPosition() const;
	sf::Vector2f getGlobalPosition() const;
	sf::Vector2f getScale() const;
	GameObject* getParent() const;
	void setParent( GameObject* parent );

	void addChild( GameObject& child );
	void removeChild( const std::string childIdentifier );
	void attachToParent( GameObject& parent );
	void detachFromParent();

	virtual void handleEvent( const sf::Event& event, sf::RenderWindow& window );
	virtual void update();
	virtual void render( sf::RenderWindow& window );

	/// <summary>
	/// adds the given displacement to the local and global postion of the game object<para/>
	/// also does the same down the line in its children hierarchy
	/// </summary>
	/// <param name="position"> -> the desired displacement</param>
	virtual void move( sf::Vector2f position );
	virtual void setScale( sf::Vector2f scale );
};