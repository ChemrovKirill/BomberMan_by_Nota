#ifndef _CHEAT_H_
#define _CHEAT_H_
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

class Cheat {
public:
	unsigned int level = 1;
	unsigned int bombs = 1;
	unsigned int radius = 1;
	unsigned int detonations = 0;
	unsigned int speed = 5;
	unsigned int lives = 3;

	bool exist = false;
	bool Input = false;

	Font font;
	Text text;

	Cheat();

	void IncLevel();
	void IncLives();
	void IncBombs();
	void IncRadius();
	void IncSpeed();
	void IncDetonations();

	void LevelDraw(RenderWindow& window);
	void BombsDraw(RenderWindow& window);
	void RadiusDraw(RenderWindow& window);
	void DetonationsDraw(RenderWindow& window);
	void SpeedDraw(RenderWindow& window);
	void LivesDraw(RenderWindow& window);

	void Draw(RenderWindow& window);
};

#endif //_CHEAT_H_