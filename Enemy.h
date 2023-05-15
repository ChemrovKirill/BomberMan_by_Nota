#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdlib>
#include <ctime>

//#include "map.h"
#include "Bomb.h"



using namespace sf;

class Enemy {
public:
	String name;
	float x, y, w, h, dx, dy;
	float Frame = 0, dying_frame = 0, timer = 0;
	float  speed = 0.1;
	int dir = 0, life = 1, progeny = 0;
	bool exist = true;
	bool dying = false;
	bool appearing = true;
	String file_dying, file;
	Image image, image_dying;
	Texture texture, texture_dying;
	Sprite sprite;
	SoundBuffer buffer;
	Sound pop_sound;

	Enemy(String f, String f_dying, String f_sound, float X, float Y, float W, float H, float s, String n);

	void Update(float time, Destructions& destructions);

	void DyingAnimation(float time);

	void Draw(RenderWindow& window);

	void InteractionWithExplosion(const Bombs& bombs, int& score);

	void InteractionWithMap(Destructions& ds);

	void InteractionWithMapBalloom();

	void InteractionWithMapOneal();

	void InteractionWithMapMinvo(Destructions& ds);

	void InteractionWithMapKondoria();

	void InteractionWithMapOvapi();
};

class Enemies {
public:
	std::vector<Enemy> enemies;

	void RandSpawn(int number, Enemy& enemy);

	void Push(Enemy& enemy);

	bool IsEmpty();

	void Update(float time, Destructions& destructions);

	void InteractionWithExplosion(const Bombs& bombs, int& score);

	void InteractionWithMap(Destructions& destructions);

	void Draw(RenderWindow& window);

};
#endif // _ENEMY_H_
