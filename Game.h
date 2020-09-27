#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

int main(int argc, char* argv[]);
// Cоздаем класс игры
class Game
{
public:
	Game()
	{
		//Открываем окошко игры, подргужаем файл с числами, шрифт, цвет выбираем шрифта и размер
		window.create(sf::VideoMode(500, 500), "15 Puzzle");
		window.setVerticalSyncEnabled(true); // Обновляем картинку с частотой обновления экрана 

		texture.loadFromFile("numbers.png"); // подключаем файл с числами
		font.loadFromFile("Montserrat-Regular.otf"); //подключаем шрифт
		text.setFont(font); // используем наш шрифт для текста 
		text.setFillColor(sf::Color::Green); // цвет шрифта текста делаю зеленным
		text.setCharacterSize(20); // Размер шрифта текста
		text.setString("F2 - to restart"); // текс который помещаю в text
		text.setPosition({ static_cast<float>(100), 30.0f }); // { static_cast<float>(100) можно просто 100.0f написать... Место в ручную подирал где текст будет

		level.Load(texture, font, { { 32, 32 }, {2.0f, 2.0f }, { 10.0f, 10.0f } }); // это размер, увеличение и расстояние между плашками
	}
	// Деструктор
	~Game()
	{
		window.close(); // закрываю окно
	}


private:
	friend int ::main(int argc, char* argv[]);

	void Run() // метод run
	{
		// Обработка времени
		sf::Time pastTime; // создаю переменную класса time, для оторажения прошедшего времени
		sf::Time deltaTime; // переменная для отображения разницы времени
		sf::Clock clock; // Время от начала игры
		sf::Event e; // храню событие (тык клавиши или мышки)

		while (running)
		{
			sf::Time time = clock.getElapsedTime(); //прошедшее время с начала игры
			deltaTime = time - pastTime;
			pastTime = time;

			while (window.pollEvent(e)) // выполняем метод OnEvent пока не обратаем все события(команды)
			{
				OnEvent(e);
			}

			OnUpdate(deltaTime.asSeconds()); // если игра закончится, то выдаст время за сколько собрали, иначе просто обновляет время 
			

			window.clear(); // очищает экран

			OnRender(); // отрисовываем спрайты плашек заного
			OnGUI();

			window.display(); // оторажаем фрейм на экране
		}
	}
// метод следящий за временем, если игра кончилась то перестает обновлять время
	void OnUpdate(float deltaTime)
	{
		level.Update(deltaTime);
	}

	void OnRender() // метод отрисовывающий плашки
	{
		level.Render(window);
	}

	void OnEvent(sf::Event& e) // Метод который получает событие от пользователя и что-то(закрывает окно, перезапускает игру, двигает плашки) делает 
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

		level.OnEvent(e); //Там много что происходит, но основная суть если может, то меняет плашки местами
	}

	void OnGUI() // отображение на экране буковок и чисел 
	{
		window.draw(text); // рисуем наш text (f2 заного)

		level.OnGUI(window); // рисуем наше время
	}
	// то что закрывает окно
	void OnWindowClose(sf::Event& e)
	{
		running = false; 
	}

private:
	sf::RenderWindow window;
	bool running = true;
	sf::Texture texture; // создание переменной, где буду хранить текстуры 
	sf::Font font; // создание переменной, где буду хранить  шрифт
	sf::Text text; // создание переменной, где буду хранить текст
	Level level; //  создание объекта класса level (выше по сути не переменные,а тоже объекты, но классов sfml библиотек)

};
