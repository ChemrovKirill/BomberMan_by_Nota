#ifndef _INFOPANEL_H_
#define _INFOPANEL_H_
#include <SFML/Graphics.hpp>
#include <iomanip>

#include <sstream>

#include "Player.h"
#include "Bomb.h"

using namespace sf;

class Info {
public:
	Font font;//רנטפע 
	Text text;

	Info(String file_font, int size);

	void ScoreDraw(Player& player, RenderWindow& window);

	void BombsDraw(Bombs& bombs, RenderWindow& window);

	void TimeDraw(int time, RenderWindow& window);

	void LevelDraw(int level, RenderWindow& window);

	void DetonationsDraw(const int& detonations, RenderWindow& window);

	void LivesDraw(Player& player, RenderWindow& window);

	void RadiusDraw(Bombs& bombs, RenderWindow& window);

	void MusicDraw(int time, int level, RenderWindow& window);

	void Draw(int time, Player& player, Bombs& bombs, RenderWindow& window, const int& detonations, const int& level);
};

#endif //_INFOPANEL_H_