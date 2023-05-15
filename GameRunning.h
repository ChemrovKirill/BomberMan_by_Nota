#pragma once

#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include <cstdlib> //random
#include <ctime>

#include <sstream>

#include "map.h"
#include "Level.h"
#include "Player.h"
#include "Bomb.h"
#include "Enemy.h"
#include "Item.h"
#include "Menu.h"
#include "InfoPanel.h"


using namespace sf;

void MusicFading(Music&);

void NewGameMode(int& level, Player& player, Bombs& bombs, bool& NewGame, Cheat& cheat);

bool StartGame(RenderWindow& window, Player& player, Bombs& bombs, int& level, bool& MenuOpen, bool& NewGame, Music& music);

void GameRunning(RenderWindow& window, Player& player, Bombs& bombs, int& level, bool& MenuOpen, bool& NewGame, Music& music);

