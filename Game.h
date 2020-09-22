#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Base.h"

int main(int argc, char* argv[]);

class Game
{
public:
	Game()
	{
		window.create(sf::VideoMode(800, 600), "15 Puzzle");
		window.setVerticalSyncEnabled(true);

		texture.loadFromFile("assets/numbers.png");
		font.loadFromFile("assets/Montserrat-Regular.otf");
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);
		text.setString("Space - to restart");
		text.setPosition({ static_cast<float>(window.getSize().x - 250.0f), 100.0f });

		level.Load(texture, font, { { 32, 32 }, {2.0f, 2.0f }, { 10.0f, 10.0f } });
	}

	~Game()
	{
		window.close();
	}


private:
	friend int ::main(int argc, char* argv[]);

	void Run()
	{
		sf::Time pastTime;
		sf::Time deltaTime;
		sf::Clock clock;
		sf::Event e;

		while (running)
		{
			sf::Time time = clock.getElapsedTime();
			deltaTime = time - pastTime;
			pastTime = time;

			while (window.pollEvent(e))
			{
				OnEvent(e);
			}

			OnUpdate(deltaTime.asSeconds());

			window.clear(sf::Color(
				static_cast<sf::Uint8>(0.1f * 255.0f),
				static_cast<sf::Uint8>(0.1f * 255.0f),
				static_cast<sf::Uint8>(0.1f * 255.0f)));

			OnRender();
			OnGUI();

			window.display();
		}
	}

	void OnUpdate(float deltaTime)
	{
		level.Update(deltaTime);
	}

	void OnRender()
	{
		level.Render(window);
	}

	void OnEvent(sf::Event& e)
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			OnWindowClose(e);
		case sf::Event::KeyReleased:
			if (e.key.code == sf::Keyboard::Space)
				level.Restart();
			if (e.key.code == sf::Keyboard::Escape)
				running = false;
		}

		level.OnEvent(e);
	}

	void OnGUI()
	{
		window.draw(text);

		level.OnGUI(window);
	}

	void OnWindowClose(sf::Event& e)
	{
		running = false;
	}

private:
	sf::RenderWindow window;
	bool running = true;
	sf::Texture texture;
	sf::Font font;
	sf::Text text;
	Level level;

	std::string restartText = "Space - to restart";
};
