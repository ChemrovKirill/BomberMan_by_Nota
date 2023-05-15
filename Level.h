#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include <cstdlib> //random
#include <ctime>

#include <sstream>

//#include "map.h"
#include "Player.h"
#include "Bomb.h"
#include "Enemy.h"
#include "Item.h"
//#include "Menu.h"
#include "InfoPanel.h"

void BuildLevelMap(int level, Map& map);

void BuildLevelMusic(int level, Music& music);

Enemies BuildLevelEnemies(int level);

Items BuildLevelItems(int level);

#endif //_LEVEL_H_