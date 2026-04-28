#include "GameEngine.h"
#include <thread>
#include <chrono>

GameEngine::GameEngine()
	: window(sf::VideoMode(800, 600), "My Game Engine")
	, isRunning(true)
	, player(50.f)
	, obstacle(sf::Vector2f(100.f, 100.f))
{
	window.setFramerateLimit(60);

	player.setFillColor(sf::Color::Red);
	player.setPosition(400.f, 300.f);

	obstacle.setFillColor(sf::Color::Blue);
	obstacle.setPosition(600.f, 400.f);
}

void GameEngine::Run()
{
	sf::Clock clock;

	while (isRunning)
	{
		sf::Time deltaTime = clock.restart();
		ProcessInput(deltaTime.asSeconds());
		Update(deltaTime.asSeconds());
		Render();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void GameEngine::ProcessInput(float deltaTime)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		///*if (event.type == sf::Event::Closed)
		//{
		//	isRunning = false;
		//	window.close();
		//}*/
		
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				isRunning = false;
				window.close();
				break;
			}
			case sf::Event::Resized:
			{
				window.setView(sf::View(sf::FloatRect(0, 0,
													static_cast<float>(event.size.width),
													static_cast<float>(event.size.height))));
				break;
			}
			case sf::Event::LostFocus:
			case sf::Event::GainedFocus:
			case sf::Event::KeyPressed:
			case sf::Event::MouseButtonPressed:
				break;
			default:
				break;
		}
	} // Окончание обработки событий
	
	const float speed = 200.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player.move(-speed * deltaTime, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player.move(speed * deltaTime, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player.move(0.f, -speed * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		player.move(0.f, speed * deltaTime);
}

void GameEngine::Update(float deltaTime)
{
	sf::Vector2f position = player.getPosition();
	float radius = player.getRadius();
	sf::Vector2u windowSize = window.getSize();
	

	if (position.x < radius) 
		player.setPosition(radius, position.y);
	if (position.x > windowSize.x - radius)
		player.setPosition(windowSize.x - radius, position.y);
	if (position.y < radius)
		player.setPosition(position.x, radius);
	if (position.y > windowSize.y - radius)
		player.setPosition(position.x, windowSize.y - radius);
	
	if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
		player.setFillColor(sf::Color::Yellow);
	else
		player.setFillColor(sf::Color::Red);
}

void GameEngine::Render()
{
	window.clear(sf::Color::Black);
	window.draw(player);
	window.draw(obstacle);
	window.display();
}