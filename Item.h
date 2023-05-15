#ifndef _ITEM_H_
#define _ITEM_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include <cstdlib> //random
#include <ctime>

#include "Bomb.h"
#include "Enemy.h"

using namespace sf;

class Item {
public:
	int w = 48, h = 48;
	int x = 0, y = 0;
	bool exist = false;
	bool dying = false;
	float dying_time;
	int code;
	String file_image;
	Image image;
	Texture texture;
	Sprite sprite;
	SoundBuffer buffer;
	Sound pick_up_sound;

	Item(String f_image, String name, String file_sound);

	void Update(Bombs& bombs, Enemies& enemies, Destructions& destructions, 
				int level, int& score, const float& time);

	void RandSpawn();

	void RandSpawnWallEmpty();

	void Spawn(int new_x, int new_y);

	void InteractionWithExplosion(Bombs& bombs, Enemies& enemies,
								  Destructions& destructions, int& score, int level);

	void Draw(RenderWindow& window);
};

class Items {
public:
	std::vector<Item> items;

	void Push(Item item);

	void RandSpawn();

	void Update(Bombs& bombs, Enemies& enemies, Destructions& destructions, 
				int level, int& score, float time);

	void Draw(RenderWindow& window);

};

#endif // _ITEM_H_