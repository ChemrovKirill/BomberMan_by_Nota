#ifndef  _DESTRUCTION_H_
#define  _DESTRUCTION_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "map.h"

using namespace sf;

class Destruction {
public:
	Image image;
	Texture texture;
	Sprite sprite;
	SoundBuffer destructionBuffer;
	Sound destruction_sound;
	int x, y;
	float frame = 0;
	bool exist = true;
	bool sound_start = true;
	Destruction(String f_image, String f_sound, int new_x, int new_y);
};

class Destructions {
public:
	std::vector<Destruction> destructions;
	void Draw(float time, RenderWindow& window);

	void Push(const Destruction& destruction);

	bool Exist(int x, int y);
};
#endif // _DESTRUCTION_H_
