#pragma once
#include <SFML/Graphics.hpp>

class GameEngine
{
private:
	sf::RenderWindow window;
	bool isRunning;
	sf::CircleShape player;
	sf::RectangleShape obstacle;
public:
	GameEngine();
	void Run();
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Render();
};

