#ifndef _BOMB_H_
#define _BOMB_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Destruction.h"

#define BOMB_TIMER 3000;

using namespace sf;

class Bomb {
private:
public:
	float current_frame = 0, explosion_frame = 0;
	float w, h;
	int x, y;
	float time_left = BOMB_TIMER;
	bool exist = false;
	bool explosion = false;
	bool go_back = false;
	std::vector<Point> exp_points;
	String file_sound, file_image;
	Image image;
	Texture texture;
	Sprite sprite;
	SoundBuffer explosionBuffer;
	Sound explosion_sound;

	Bomb(String f_sound, String f_image, float W, float H);

	void Clear();
};

class Bombs {
public: 
	int radius, number;
	std::vector<Bomb> bombs;
	Bombs(Bomb b, int r, int n);

	bool BombIsHere(int x, int y);

	void SetBomb(int new_x, int new_y);

	void Update(float time);

	bool ExistNotExplosion();

	void SetDefault();

	void NewGame();

	void InterectionWithObjects(std::vector<Point> objs);

	void DestructionTracking(Destructions& ds);

	void ExplosionDraw(RenderWindow& window);

	void Draw(RenderWindow& window);

	void Detonate();

	void IncRadius();
	void DecRadius();
	void IncNumber();
	void DecNumber();
};

#endif _BOMB_H_