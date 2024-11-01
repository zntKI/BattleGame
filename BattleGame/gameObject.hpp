#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
private:
	bool shouldDestroy;
	bool shouldLateDestroy;

protected:
	const std::string identifier;

	sf::Vector2f globalPosition;
	sf::Vector2f localPosition;

	GameObject* parent;
	std::map<std::string, GameObject*> children;

public:
	GameObject( const std::string& identifier, const GameObject* parent,
		const sf::Vector2f position = sf::Vector2f( 0.f, 0.f ) );
	GameObject( const GameObject& other );

	virtual ~GameObject();

protected:
	/// <summary>
	/// sets the local postion of the game object after hierarchy modification
	/// </summary>
	/// <param name="position"> -> the new local position</param>
	virtual void setPosition( sf::Vector2f position );

public:
	virtual void finishInit();

	std::string getIdentifier() const;
	sf::Vector2f getLocalPosition() const;
	sf::Vector2f getGlobalPosition() const;
	GameObject* getParent() const;
	void setParent( GameObject* parent );

	void addChild( GameObject* child );
	void addChild( GameObject& child );
	void removeChild( const std::string childIdentifier );
	void attachToParent( GameObject* parent );
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
	virtual void move( const sf::Vector2f& position );

	void lateDestroy();
	bool isLateDestroy() const;

	void destroy();
	bool isDestroy() const;
};