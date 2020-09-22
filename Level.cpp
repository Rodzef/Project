#include <poorpch.h>
#include "Level.h"

#include "Base.h"

#include "Random.h"

void Level::Load(const sf::Texture& texture, const sf::Font& font, const LevelParams& params)
{
	timeTxt.setFont(font);
	timeTxt.setFillColor(sf::Color::White);
	timeTxt.setCharacterSize(20);
	timeTxt.setPosition(800.0f - 250.0f, 130.0f);

	sprite.setTexture(texture);
	sprite.setScale(params.Scale);
	sprite.setOrigin(0.5f, 0.5f);

	for (unsigned int i = 0; i < 16; i++)
	{
		if (i < 15)
		{
			entities[i].Slot = i;
			entities[i].Num = i + 1;
			entities[i].TexRect = sf::IntRect((i + 1) * params.TexSize.x, 0,
				params.TexSize.x, params.TexSize.y);
		}

		positions[i].x = i % 4 * (params.TexSize.x * params.Scale.x + params.Offset.x) + 100;
		positions[i].y = i / 4 * (params.TexSize.x * params.Scale.x + params.Offset.y) + 100;
	}

	Restart();
}

void Level::Restart()
{
	timer.restart();
	elapsed = 0.0f;

	// TODO: GET RID OF THAT OVERHEAD

	auto findEntity = [this](unsigned int slot) {
		for (auto& entity : entities)
			if (entity.Slot == slot)
				return &entity;
	};

	for (unsigned int i = 0; i < 200; i++)
	{
		int dir = Random::NextInt(0, 4);
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

void Level::Render(sf::RenderWindow& window)
{
	for (auto& entity : entities)
	{
		sprite.setTextureRect(entity.TexRect);
		sprite.setPosition(positions[entity.Slot]);
		window.draw(sprite);
	}
}

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

void Level::OnGUI(sf::RenderWindow& window)
{
	std::stringstream ss;
	ss << "Elapsed: " << static_cast<int>(elapsed) << "s";
	timeTxt.setString(ss.str());
	window.draw(timeTxt);
}

void Level::Move(const sf::Vector2f& mouse)
{
	for (unsigned int i = 0; i < 15; i++)
	{
		sprite.setTextureRect(entities[i].TexRect);
		sprite.setPosition(positions[entities[i].Slot]);
		if (sprite.getGlobalBounds().contains(mouse))
		{
			if (CanIMove(entities[i].Slot))
			{
				unsigned int tempSlot = freeSlot;
				freeSlot = entities[i].Slot;
				entities[i].Slot = tempSlot;
			}
		}
	}
}

bool Level::IsGameOver()
{
	for (unsigned int i = 0; i < 15; i++)
	{
		if (entities[i].Num != (entities[i].Slot + 1))
			return false;
	}
	return true;
}

bool Level::CanIMove(unsigned int slot)
{
	if (slot == freeSlot - 1 ||
		slot == freeSlot + 1 ||
		slot == freeSlot - 4 ||
		slot == freeSlot + 4)
		return true;
	return false;
}
