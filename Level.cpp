#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include <cstdlib> //random
#include <ctime>

#include <sstream>

#include "map.h"
//#include "Player.h"
//#include "Bomb.h"
//#include "Enemy.h"
//#include "Item.h"
//#include "Menu.h"
//#include "InfoPanel.h"
#include "Level.h"

void BuildLevelMap(int level, Map& map) {
	if (level == 40) {
		TileMap = TileMapStartFinal;
	}
	else if (level % 5 == 0) {
		switch (level / 5)
		{
		case 1:
			TileMap = map.Generation(TileMapStart2, 4);
			break;
		case 2:
			TileMap = map.Generation(TileMapStart3, 4);
			break;
		case 3:
			TileMap = map.Generation(TileMapStart4, 4);
			break;
		case 4:
			TileMap = map.Generation(TileMapStart5, 4);
			break;
		case 5:
			TileMap = map.Generation(TileMapStart6, 4);
			break;
		case 6:
			TileMap = map.Generation(TileMapStart7, 3);
			break;
		case 7:
			TileMap = map.Generation(TileMapStart8, 3);
			break;
		default:
			break;
		}
	}
	else {
		if (level == 1) {
			TileMap = map.Generation(TileMapStart1, 15);
		}
		else if (level == 32) {
			TileMap = TileMapBonus;
		}
		else if (level < 15) {
			TileMap = map.Generation(TileMapStart1, 5); // обновляем карту
		}
		else if (level < 30) {
			TileMap = map.Generation(TileMapStart1, 4);
		}
		else {
			TileMap = map.Generation(TileMapStart1, 3);
		}
	}
}

void BuildLevelMusic(int level, Music& music) {
	if (level == 40) {
		music.openFromFile("music/space_fighter_loop.wav");
	}
	else {
		switch (level % 5) {
		case 0:
			music.openFromFile("music/phantom_from_space.wav");
			break;
		case 1:
			music.openFromFile("music/neo_western.wav");
			break;
		case 2:
			music.openFromFile("music/myst_on_the_moor.wav");
			break;
		case 3:
			music.openFromFile("music/half_mystery.wav");
			break;
		case 4:
			music.openFromFile("music/i_can_feel_it_coming.wav");
			break;
		default:
			music.openFromFile("music/neo_western.wav");
			break;
		}
	}
	music.setVolume(0);
	music.play();
}

Enemies BuildLevelEnemies(int level) {
	Enemies enemies;

	Enemy Balloom("Balloom.png", "Balloom_dying.png", "pop.wav", 0, 0, 48.0, 48.0, 0.06, "Balloom");
	Enemy Oneal("Oneal.png", "Oneal_dying.png", "pop.wav", 0, 0, 48.0, 48.0, 0.1, "Oneal");
	Enemy Doll("Doll.png", "Doll_dying.png", "pop.wav", 0, 0, 48.0, 48.0, 0.12, "Doll");
	Enemy Minvo("Minvo.png", "Minvo_dying.png", "pop.wav", 0, 0, 48, 48, 0.15, "Minvo");
	Enemy Kondoria("Kondoria.png", "Kondoria_dying.png", "pop.wav", 0, 0, 48, 48, 0.1, "Kondoria");
	Enemy Ovapi("Ovapi.png", "Ovapi_dying.png", "pop.wav", 0, 0, 48, 48, 0.08, "Ovapi");
	Enemy Pass("Pass.png", "Pass_dying.png", "pop.wav", 0, 0, 48, 48, 0.08, "Pass");

	switch (level) {
	case 1:
		enemies.RandSpawn(1, Balloom);
		break;
	case 2:
		enemies.RandSpawn(3, Balloom);
		break;
	case 3:
		enemies.RandSpawn(6, Balloom);
		break;
	case 4:
		enemies.RandSpawn(3, Oneal);
		break;
	case 5:
		enemies.RandSpawn(3, Balloom);
		enemies.RandSpawn(3, Oneal);
		break;
	case 6:
		enemies.RandSpawn(2, Balloom);
		enemies.RandSpawn(4, Oneal);
		break;
	case 7:
		enemies.RandSpawn(6, Oneal);
		break;
	case 8:
		enemies.RandSpawn(4, Balloom);
		enemies.RandSpawn(4, Oneal);
		break;
	case 9:
		enemies.RandSpawn(3, Doll);
		break;
	case 10:
		enemies.RandSpawn(2, Doll);
		enemies.RandSpawn(2, Balloom);
		enemies.RandSpawn(2, Oneal);
		break;
	case 11:
		enemies.RandSpawn(3, Doll);
		enemies.RandSpawn(3, Oneal);
		break;
	case 12:
		enemies.RandSpawn(1, Doll);
		enemies.RandSpawn(2, Balloom);
		enemies.RandSpawn(4, Oneal);
		break;
	case 13:
		enemies.RandSpawn(5, Doll);
		break;
	case 14:
		enemies.RandSpawn(3, Minvo);
		break;
	case 15:
		enemies.RandSpawn(3, Minvo);
		enemies.RandSpawn(1, Oneal);
		enemies.RandSpawn(2, Doll);
		break;
	case 16:
		enemies.RandSpawn(3, Minvo);
		enemies.RandSpawn(3, Doll);
		break;
	case 17:
		enemies.RandSpawn(3, Minvo);
		enemies.RandSpawn(3, Oneal);
		break;
	case 18:
		enemies.RandSpawn(2, Minvo);
		enemies.RandSpawn(4, Balloom);
		break;
	case 19:
		enemies.RandSpawn(4, Kondoria);
		break;
	case 20:
		enemies.RandSpawn(3, Minvo);
		enemies.RandSpawn(3, Kondoria);
		break;
	case 21:
		enemies.RandSpawn(1, Kondoria);
		enemies.RandSpawn(1, Minvo);
		enemies.RandSpawn(1, Oneal);
		enemies.RandSpawn(1, Doll);
		enemies.RandSpawn(1, Balloom);
		break;
	case 22:
		enemies.RandSpawn(2, Kondoria);
		enemies.RandSpawn(3, Minvo);
		enemies.RandSpawn(3, Doll);
		break;
	case 23:
		enemies.RandSpawn(2, Kondoria);
		enemies.RandSpawn(2, Oneal);
		enemies.RandSpawn(6, Balloom);
		break;
	case 24:
		enemies.RandSpawn(4, Ovapi);
		break;
	case 25:
		enemies.RandSpawn(3, Ovapi);
		enemies.RandSpawn(3, Kondoria);
		break;
	case 26:
		enemies.RandSpawn(3, Kondoria);
		enemies.RandSpawn(3, Ovapi);
		enemies.RandSpawn(3, Oneal);
		break;
	case 27:
		enemies.RandSpawn(3, Ovapi);
		enemies.RandSpawn(3, Doll);
		enemies.RandSpawn(3, Minvo);
		break;
	case 28:
		enemies.RandSpawn(2, Ovapi);
		enemies.RandSpawn(2, Kondoria);
		enemies.RandSpawn(4, Oneal);
		break;
	case 29:
		enemies.RandSpawn(4, Pass);
		break;
	case 30:
		enemies.RandSpawn(4, Pass);
		enemies.RandSpawn(4, Doll);
		break;
	case 31:
		enemies.RandSpawn(1, Pass);
		enemies.RandSpawn(2, Ovapi);
		enemies.RandSpawn(2, Kondoria);
		enemies.RandSpawn(2, Minvo);
		enemies.RandSpawn(2, Oneal);
		enemies.RandSpawn(2, Doll);
		enemies.RandSpawn(2, Balloom);
		break;
	case 32:
		//bonus with chests
		break;
	case 33:
		enemies.RandSpawn(20, Balloom);
		break;
	case 34:
		enemies.RandSpawn(15, Oneal);
		break;
	case 35:
		enemies.RandSpawn(10, Doll);
		break;
	case 36:
		enemies.RandSpawn(10, Minvo);
		break;
	case 37:
		enemies.RandSpawn(10, Kondoria);
		break;
	case 38:
		enemies.RandSpawn(10, Ovapi);
		break;
	case 39:
		enemies.RandSpawn(15, Pass);
		break;
	case 40:
		//
		break;
	}
	return enemies;
}

Items BuildLevelItems(int level) {
	Items items;

	Item Door("items.png", "Door", "pick_up.wav");
	Item Chest("items.png", "Chest", "pick_up.wav");
	Item SpeedUp("items.png", "SpeedUp", "pick_up.wav");
	Item BombsUp("items.png", "BombsUp", "pick_up.wav");
	Item ExplosionUp("items.png", "ExplosionUp", "pick_up.wav");
	Item Detonator("items.png", "Detonator", "pick_up.wav");
	Item Life("items.png", "Life", "pick_up.wav");

	if (level == 40) {
		items.Push(Door);
		items.Push(Door);
		items.items[0].Spawn(29 * 48, 5 * 48);
		items.items[1].Spawn(29 * 48, 13 * 48);
		return items;
	}
	items.Push(Door);
	if (level != 1) {
		items.Push(Chest);
		if (rand() % 3 == 1) {
			items.Push(Chest);
		}
		if (rand() % 5 == 1) {
			items.Push(BombsUp);
		}
		if (rand() % 5 == 1) {
			items.Push(ExplosionUp);
		}
		if (rand() % 5 == 1) {
			items.Push(Life);
		}
	}
	switch (level) {
	case 1:

		break;
	case 2:
		items.Push(BombsUp);
		break;
	case 3:
		items.Push(SpeedUp);
		break;
	case 4:
		items.Push(ExplosionUp);
		break;
	case 5:
		items.Push(Chest);
		items.Push(Life);
		break;
	case 6:
		items.Push(BombsUp);
		break;
	case 7:
		items.Push(SpeedUp);
		break;
	case 8:
		items.Push(ExplosionUp);
		break;
	case 9:
		items.Push(SpeedUp);
		break;
	case 10:
		items.Push(Life);
		items.Push(Chest);
		items.Push(Detonator);
		break;
	case 11:
		items.Push(BombsUp);
		break;
	case 12:
		items.Push(Detonator);
		break;
	case 13:
		items.Push(ExplosionUp);
		break;
	case 14:
		items.Push(Detonator);
		break;
	case 15:
		items.Push(Life);
		items.Push(BombsUp);
		break;
	case 16:
		items.Push(Detonator);
		break;
	case 17:
		items.Push(ExplosionUp);
		break;
	case 18:
		items.Push(Detonator);
		break;
	case 19:
		items.Push(SpeedUp);
		break;
	case 20:
		items.Push(Life);
		items.Push(Detonator);
		break;
	case 21:
		items.Push(BombsUp);
		break;
	case 22:
		items.Push(SpeedUp);
		break;
	case 23:
		items.Push(ExplosionUp);
		break;
	case 24:
		items.Push(Detonator);
		items.Push(Chest);
		break;
	case 25:
		items.Push(Life);
		items.Push(Detonator);
		break;
	case 26:
		items.Push(SpeedUp);
		items.Push(Chest);
		break;
	case 27:
		items.Push(BombsUp);
		break;
	case 28:
		items.Push(ExplosionUp);
		break;
	case 29:
		items.Push(Detonator);
		items.Push(Chest);
		break;
	case 30:
		items.Push(Life);
		items.Push(BombsUp);
		break;
	case 31:
		items.Push(SpeedUp);
		items.Push(BombsUp);
		items.Push(ExplosionUp);
		items.Push(Detonator);
		break;
	case 32:
		for (int i = 0; i < 19; i++)
			items.Push(Chest);
		break;
	case 33:
		items.Push(Chest);
		items.Push(Chest);
		items.Push(Chest);
		break;
	case 34:
		items.Push(SpeedUp);
		items.Push(BombsUp);
		items.Push(ExplosionUp);
		items.Push(Detonator);
		break;
	case 35:
		items.Push(Chest);
		items.Push(Chest);
		items.Push(Chest);
		break;
	case 36:
		items.Push(SpeedUp);
		items.Push(BombsUp);
		items.Push(ExplosionUp);
		items.Push(Detonator);
	case 37:
		items.Push(Chest);
		items.Push(Chest);
		items.Push(Chest);
		break;
	case 38:
		items.Push(Detonator);
		items.Push(Detonator);
		items.Push(Detonator);
		break;
	case 39:
		items.Push(Detonator);
		items.Push(Detonator);
		items.Push(Chest);
		items.Push(Chest);
		items.Push(Chest);
		break;
	case 40:
		//
		break;
	}

	items.RandSpawn();
	return items;
}