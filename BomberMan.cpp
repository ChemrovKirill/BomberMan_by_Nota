
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include <cstdlib> //random
#include <ctime>

#include <sstream>

#include <windows.h>

#include "map.h"
//#include "Player.h"
//#include "Bomb.h"
//#include "Enemy.h"
//#include "Item.h"
//#include "Menu.h"
//#include "InfoPanel.h"
#include "GameRunning.h"

using namespace sf;

int main()
{
	Music music;
	music.setLoop(true);
	music.setVolume(0);
	RenderWindow window(sf::VideoMode(1488, 816), "BomberMan_by_Nota");

	if (x_screen - 50 < 1488 && x_screen * 816 / 1488 < y_screen - 50) {
		window.setSize(sf::Vector2u((x_screen - 100), (x_screen - 100) * 816 / 1488));
		window.setPosition(sf::Vector2i(50, 50));
	}
	else if ((x_screen - 50 < 1488 || y_screen - 50 < 816)) {
		window.setSize(sf::Vector2u((y_screen - 100) * 1488 / 816, y_screen - 100));
		window.setPosition(sf::Vector2i(50, 50));
	}

	int level = 1;
	bool MenuOpen = true;
	bool NewGame = true;
	Player player("hero.png", "hero_dying.png", "hero_human.png", "pop_2.wav", 48, 48 * 3, 36.0, 48.0);

	Bomb bomb("explosion.wav", "Bomb.png", 48, 48); //создаем объект bomb класса Bomb размера 48*48
	Bombs bombs(bomb, 1, 1); // создаем объект bombs класса Bombs с радиусом поражения 1, количеством бомб 1

	GameRunning(window, player, bombs, level, MenuOpen, NewGame, music);

	return 0;
}