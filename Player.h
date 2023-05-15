#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "Item.h"
#include "Bomb.h"

using namespace sf;

class Player {
private: float x, y;
public:
	float w, h, dx, dy;
	int score = 0;
	int detonations = 0;
	int lives = 3;
	float Frame = 0, dying_frame = 0;
	float next_bomb_timer = 0;
	float  speed = 0.15;
	int dir;
	bool exist = true;
	bool dying = false;
	bool isHuman = false;
	String file_dying, file, file_human;
	Image image, image_dying, image_human;
	Texture texture, texture_dying, texture_human;
	Sprite sprite;
	SoundBuffer buffer;
	Sound pop_sound;

	Player(String f, String f_dying, String f_human, String f_sound, float X, float Y, float W, float H);

	void NewGame();

	void SetSprite(String file);

	void SetDefault();

	void DyingAnimation(float time);

	void Update(float time);

	void Control(const float& time, Bombs& bombs, RenderWindow& window);

	void MoveCorrection();

	void InteractionWithMap();

	void InteractionWithExplosion(const Bombs& bombs);

	void InteractionWithEnemies(const Enemies& enemies);

	void InteractionWithItems(Items& items, Bombs& bombs, Enemies& enemies, bool& NextLevel);

	float GetX() const;
	float GetY() const;

};

#endif // _PLAYER_H_