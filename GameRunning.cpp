
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include <cstdlib> //random
#include <ctime>

#include <sstream>

//#include "map.h"
//#include "Player.h"
//#include "Bomb.h"
//#include "Enemy.h"
//#include "Item.h"
//#include "Menu.h"
//#include "InfoPanel.h"
//#include "Level.h"
#include "GameRunning.h"


using namespace sf;

void MusicFading(Music& music) {
	if (music.getVolume() > 0.2) {
		music.setVolume(music.getVolume() - 0.2);
	}
	else {
		music.setVolume(0);
		//music.stop();
	}
}

void NewGameMode(int& level, Player& player, Bombs& bombs, bool& NewGame, Cheat& cheat) {
	if (NewGame) {
		level = 1;
		player.NewGame();
		player.isHuman = false;
		bombs.NewGame();
		if (cheat.exist) {
			level = cheat.level;
			for (int i = 1; i < cheat.bombs; ++i) {
				bombs.IncNumber();
			}
			for (int i = 1; i < cheat.radius; ++i) {
				bombs.IncRadius();
			}
			player.speed = 0.03 * cheat.speed;
			player.detonations = cheat.detonations;
			player.lives = cheat.lives;
		}
		NewGame = false;
	}
}

bool StartGame(RenderWindow& window, Player& player, Bombs& bombs, int& level, bool& MenuOpen, bool& NewGame, Music& music) {
	Cheat cheat;
	if (!MainMenu(window, MenuOpen, NewGame, music, cheat)) {//открывает меню и завершает программу, если был выход из меню
		return false;
	}

	NewGameMode(level, player, bombs, NewGame, cheat);

	BuildLevelMusic(level, music);

	player.SetDefault();
	bombs.SetDefault();

	bool isPause = false;
	bool isNextLevel = false;


	Map map("map.png", "map_head.png");

	BuildLevelMap(level, map);

	Info info("AllStarResort.ttf", 50);

	StateImage GameOverState(true, "GameOver.png", 0, 0);
	StateImage NextLevelState(true, "NextLevel.png", 0, 0);
	StateImage LivesmmState(true, "Livesmm.png", 0, 0);
	StateImage EndGameState(false, "EndGame.png", 0, 0);

	Destructions destructions;

	srand(time(0));

	Enemies enemies = BuildLevelEnemies(level);

	Items items = BuildLevelItems(level);

	Clock clock;
	Clock level_clock;
	int level_time = 0;

	while (window.isOpen()) {
		if (player.exist && !isNextLevel) {
			level_time = level_clock.getElapsedTime().asSeconds();
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;

		if (level == 40) {
			if (player.GetY() > 448) {
				player.isHuman = true;
				player.sprite.setTexture(player.texture_human);
			}
			else {
				player.isHuman = false;
				player.sprite.setTexture(player.texture);
			}
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return false;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (isPause) {
						isPause = false;
					}
					else {
						isPause = true;
					}
				}
				/*if (event.key.code == sf::Keyboard::F)
				{			
					window.setSize(sf::Vector2u(x_screen, y_screen));
				}*/
			}

		}

		if (isPause) {
			if (PauseMenu(isPause, window, map, items, player, bombs, enemies, music, destructions, isNextLevel, MenuOpen)) {
				clock.restart();
				if (MenuOpen) {
					return true;
				}
			}
			else
				return false;
		}

		bombs.Update(time);
		bombs.DestructionTracking(destructions);

		player.Control(time, bombs, window);
		player.InteractionWithExplosion(bombs);
		player.InteractionWithEnemies(enemies);
		player.InteractionWithItems(items, bombs, enemies, isNextLevel);
		player.Update(time);

		items.Update(bombs, enemies, destructions, level, player.score, time);

		enemies.InteractionWithExplosion(bombs, player.score);
		enemies.Update(time, destructions);

		std::vector<Point> objects_points;
		objects_points.push_back({ int(player.GetX()), int(player.GetY()) });
		for (auto& enemy : enemies.enemies) {
			objects_points.push_back({ int(enemy.x), int(enemy.y) });
		}

		bombs.InterectionWithObjects(objects_points);

		window.clear();

		map.Draw(window);
		items.Draw(window);
		window.draw(player.sprite);


		bombs.Draw(window); //вклюает ExploseDraw
		enemies.Draw(window);
		destructions.Draw(time, window);

		if (music.getVolume() < music_Volume) {
			music.setVolume(music.getVolume() + 0.1);
		}

		if (!player.exist && !player.dying && !isNextLevel) {
			if (player.lives < 1) {
				window.draw(GameOverState.sprite);
				MusicFading(music);
				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					MenuOpen = true;
					return true;
				}
			}
			else {
				window.draw(LivesmmState.sprite);
				MusicFading(music);
				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					--player.lives;
					if (bombs.number > bombs.radius) {
						bombs.DecNumber();
					}
					else {
						bombs.DecRadius();
					}
					return true;
				}
			}
		}
		else if (isNextLevel) {
			if (level < 40) {
				window.draw(NextLevelState.sprite);
				MusicFading(music);
				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					level++;
					return true;
				}
			}
		}

		info.Draw(level_time, player, bombs, window, player.detonations, level);

		if (isNextLevel && level == 40) {
			window.draw(EndGameState.sprite);
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				MenuOpen = true;
				return true;
			}
		}
		window.display();

		//if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//если эскейп, то выходим из игры
	}
}

void GameRunning(RenderWindow& window, Player& player, Bombs& bombs, int& level, bool& MenuOpen, bool& NewGame, Music& music) {
	if (StartGame(window, player, bombs, level, MenuOpen, NewGame, music)) {
		GameRunning(window, player, bombs, level, MenuOpen, NewGame, music);
	}
}