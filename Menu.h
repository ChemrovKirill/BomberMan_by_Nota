#ifndef _MENU_H_
#define _MENU_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <sstream>

#include "map.h"
#include "Level.h"
#include "Player.h"
#include "Bomb.h"
#include "Enemy.h"
#include "Item.h"
#include "Cheat.h"

using namespace sf;

class StateImage {
public:
	Image image;
	Texture texture;
	Sprite sprite;

	StateImage(bool transparency, String file, int x, int y) {
		image.loadFromFile("images/" + file);
		if (transparency) {
			image.createMaskFromColor(Color(31, 139, 0));
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
	}
};

bool SettingsMenu(RenderWindow& window, Music& music);

bool ControlMenu(RenderWindow& window);

bool PauseMenu(bool& isPause, RenderWindow& window, Map& map, Items& items,
	Player& player, Bombs& bombs, Enemies& enemies, Music& music,
	Destructions& destructions, bool& isNextLevel, bool& MenuOpen);

bool MainMenu(RenderWindow& window, bool& MenuOpen, bool& NewGame, Music& music, Cheat& cheat);

#endif // _MENU_H_
