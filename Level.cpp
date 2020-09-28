#include "X.h"
#include "Level.h"

#include "Random.h"

void Level::Load(const sf::Texture& texture, const sf::Font& font, const LevelParams& params)
{   
	/* То что отображает текст времени (цвет, размер, параметры)
	*/

	timeTxt.setFont(font); // берем шрифт тот,что раньше подключили
	timeTxt.setFillColor(sf::Color::Green); // делаем зеленный свет шрифта ля timeTxt
	timeTxt.setCharacterSize(20); // Размер текста
	timeTxt.setPosition(100.0f, 60.0f); // Место нахождения текста

	sprite.setTexture(texture); // Создаем спрайт
	sprite.setScale(params.Scale); // Маштабирую 
	sprite.setOrigin(0.5f, 0.5f); // Выбираю опорную точку для размещения плашек
	// Заполняем наш массив по порядку (так же ставим в соответсвие с рисунка числа)
	for (unsigned int i = 0; i < 16; i++)
	{
		if (i < 15)
		{
			entities[i].Slot = i;
			entities[i].Num = i + 1; // число которое храниться в данной ячейке массива  
			entities[i].TexRect = sf::IntRect((i + 1) * params.TexSize.x, 0,
				params.TexSize.x, params.TexSize.y); // подгружаю то что будет храниться в плашках
		}

		positions[i].x = i % 4 * (params.TexSize.x * params.Scale.x + params.Offset.x) + 100; // где мои плашки буду расположены (первое х координата, вторая y)
		positions[i].y = i / 4 * (params.TexSize.x * params.Scale.x + params.Offset.y) + 100;
	}

}
//метод отвечающий за перезапуск игры
void Level::Restart()
{
	timer.restart(); // время обнуляется
	elapsed = 0.0f;


	//ссылается на то место где стоит плашка
	auto findEntity = [this](unsigned int slot) {
		for (auto& entity : entities)
			if (entity.Slot == slot)
				return &entity;
	};
	// Перемешивание (т.к изначаль создаем правильную, и ее мешаем, то она всегда решабельна)
	for (unsigned int i = 0; i < 123; i++)
	{
		// В какую сторону двигаем пустую (ну или точнее на место пустой)
		int dir = rand() % 4; // рандомлюю, а дальше в соответствии с тем что выпало двигаю плашки, если возможно
		switch (dir)
		{
		case 0:
		{
			int slot = static_cast<int>(freeSlot) - 1;
			if (slot > -1 && slot < 16)
			{
				Entity* entity = findEntity(slot);
				unsigned int tempSlot = freeSlot;
				freeSlot = entity->Slot;
				entity->Slot = tempSlot;
				break;
			}
		}
		case 1:
		{
			int slot = static_cast<int>(freeSlot) + 1;
			if (slot > -1 && slot < 16)
			{
				Entity* entity = findEntity(slot);
				unsigned int tempSlot = freeSlot;
				freeSlot = entity->Slot;
				entity->Slot = tempSlot;
				break;
			}
		}
		case 2:
		{
			int slot = static_cast<int>(freeSlot) - 4;
			if (slot > -1 && slot < 16)
			{
				Entity* entity = findEntity(slot);
				unsigned int tempSlot = freeSlot;
				freeSlot = entity->Slot;
				entity->Slot = tempSlot;
				break;
			}
		}
		case 3:
		{
			int slot = static_cast<int>(freeSlot) +4;
			if (slot > -1 && slot < 16)
			{
				Entity* entity = findEntity(slot);
				unsigned int tempSlot = freeSlot;
				freeSlot = entity->Slot;
				entity->Slot = tempSlot;
				break;
			}
		}
		}
	}
}
//метод обновляющий время, как конец перестает обновлять время
void Level::Update(float deltaTime)
{
	if (IsGameOver())
	{
		
	}
	else
	{
		elapsed = timer.getElapsedTime().asSeconds();
	}
}
// Отрисовка спрайтов плашек
void Level::Render(sf::RenderWindow& window)
{
	for (auto& entity : entities)
	{
		sprite.setTextureRect(entity.TexRect);
		sprite.setPosition(positions[entity.Slot]);
		window.draw(sprite);
	}
}


// метод получающий е, если  это кооринаты левой клавиши мыши, то идем в move
void Level::OnEvent(sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::MouseButtonReleased:
		if (e.mouseButton.button == sf::Mouse::Button::Left)
		{
			Move({ (float)e.mouseButton.x, (float)e.mouseButton.y });
		}
	}
}
// метод рисующий в окошке сколько времени прошло
void Level::OnGUI(sf::RenderWindow& window)
{
	std::stringstream ss;
	ss << "Time: " << static_cast<int>(elapsed) << "s";// строка прошедшего времени 
	timeTxt.setString(ss.str());
	window.draw(timeTxt);//рисуем ее на экране
}
// перемещение если оно возможно
void Level::Move(const sf::Vector2f& mouse)
{
	for (unsigned int i = 0; i < 15; i++)
	{
		sprite.setPosition(positions[entities[i].Slot]);
		if (sprite.getGlobalBounds().contains(mouse))//если попадаем по спрайту плашек и можем двигать, то меняем пустую плашку и на которую тыкнули
		{
			if (CanIMove(entities[i].Slot))
			{
				// сам процесс обмена (позиции)
				unsigned int tempSlot = freeSlot;
				freeSlot = entities[i].Slot;
				entities[i].Slot = tempSlot;
			}
		}
	}
}
// Проверяет собрана или нет головоломка
bool Level::IsGameOver()
{
	for (unsigned int i = 0; i < 15; i++)
	{
		if (entities[i].Num != (entities[i].Slot + 1))
			return false;
	}
	return true;
}
// Проверка могу ли я передвинуть ту плашку на которую нажал (теперь точно не двигает лишние)
bool Level::CanIMove(unsigned int slot)
{
	if ((slot == 3 && freeSlot == 4) || (slot == 4 && freeSlot == 3)) return false;
	if ((slot == 7 && freeSlot == 8) || (slot == 8 && freeSlot == 7)) return false;
	if ((slot == 11 && freeSlot == 12) || (slot == 12 && freeSlot == 11)) return false;
	if (slot == freeSlot - 1 ||
		slot == freeSlot + 1 ||
		slot == freeSlot - 4 ||
		slot == freeSlot + 4)
		return true;
	return false;
}
