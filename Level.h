#pragma once

#include <SFML/Graphics.hpp>
//структкра параметров
struct LevelParams
{
	// Объекты отвечающие за смещение,маштабирование и размещение
	sf::Vector2i TexSize;
	sf::Vector2f Scale;
	sf::Vector2f Offset;
};
//структура плашек 
struct Entity
{
	sf::IntRect TexRect; //размер прямоугольника плашки и положение 
	unsigned int Num;// номеры плашки
	unsigned int Slot;// где она находится
};

class Level
{
public:

	void Load(const sf::Texture& texture, const sf::Font& font, const LevelParams& params); //метод в котором храниться размер, расположение шрифта, цвет, спрайты плашек, их размещение
	void Restart(); // метод перезагружаюющий игру

	void Update(float deltaTime); //метод обновляющий время
	void Render(sf::RenderWindow& window); //Метод рисующий спрайты
	void OnEvent(sf::Event& e);//// метод получающий е, если  это кооринаты левой клавиши мыши, то идем в move
	void OnGUI(sf::RenderWindow& window);// метод рисующий время

private:
	bool IsGameOver();// метод проверяющий закончилась ли игра
	void Move(const sf::Vector2f& pos);// метод меняющий плашку н которую наали и пустуюю
	bool CanIMove(unsigned int slot);// метод проверяющий могу ли я двигать плашку

private:
	sf::Text timeTxt; // объект который отвечает за прошедшее время с начала игры
	float elapsed = 0; // переменная прошедшего времени
	sf::Clock timer; // объект таймер
	sf::Sprite sprite; //объект отвечающий за спрайты
	Entity entities[15]; //массив с информацией про плашки
	sf::Vector2f positions[16];// массив в котором показано на каком месте стоит плашка
	unsigned int freeSlot = 15; //объект отвечающий за пустую плашку 
};
