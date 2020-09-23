#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Base.h"

int main(int argc, char* argv[]);
// Cоздаем класс игры
class Game
{
public:
	Game()
	{
		//Открываем окошко игры, подргужаем файл с числами, шрифт, цвет выбираем шрифта и размер
		window.create(sf::VideoMode(500, 500), "15 Puzzle");
		window.setVerticalSyncEnabled(true);

		texture.loadFromFile("assets/numbers.png");
		font.loadFromFile("assets/Montserrat-Regular.otf");
		text.setFont(font);
		text.setFillColor(sf::Color::Green);
		text.setCharacterSize(20);
		text.setString("F2 - to restart");
		text.setPosition({ static_cast<float>(100), 30.0f });

		level.Load(texture, font, { { 32, 32 }, {2.0f, 2.0f }, { 10.0f, 10.0f } });
	}
	// Деструктор
	~Game()
	{
		window.close();
	}


private:
	friend int ::main(int argc, char* argv[]);

	void Run()
	{
		// Обработка времени
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
			
			//Цввет окошка

			window.clear(sf::Color(
				static_cast<sf::Uint8>(0.1f * 255.0f),
				static_cast<sf::Uint8>(0.1f * 255.0f),
				static_cast<sf::Uint8>(0.1f * 255.0f)));

			OnRender();
			OnGUI();

			window.display();
		}
	}
// Обновление времени (Или остановка)
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
		// Считывание команды (перезапуск игры, закрытие)
		switch (e.type)
		{
		case sf::Event::Closed:
			OnWindowClose(e); // закрытие окна
		case sf::Event::KeyReleased:
			if (e.key.code == sf::Keyboard::F2)
				level.Restart(); // рестарт
			if (e.key.code == sf::Keyboard::Escape)
				running = false; // закрытие
		}

		level.OnEvent(e);
	}

	void OnGUI()
	{
		window.draw(text);

		level.OnGUI(window);
	}
	// то что закрывает окно
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

	std::string restartText = "F2 - to restart";
};
