#include "Destruction.h"

using namespace sf;


Destruction::Destruction(String f_image, String f_sound, int new_x, int new_y) {
	image.loadFromFile("images/" + f_image);
	image.createMaskFromColor(Color(31, 139, 0));
	texture.loadFromImage(image);
	//sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 48, 48));
	x = new_x;
	y = new_y;
	sprite.setPosition(x, y);

	destructionBuffer.loadFromFile("sounds/" + f_sound);
	//destruction_sound.setBuffer(destructionBuffer);
}

void Destructions::Draw(float time, RenderWindow& window) {
	bool lets_clear = true;
	for (auto& d : destructions) {
		if (d.frame > 5) {
			d.exist = false;
			d.frame = 0;
		}
		if (d.sound_start) {
			d.sound_start = false;

			//d.destruction_sound.setBuffer(d.destructionBuffer); //?????????
			d.destruction_sound.setVolume(sound_Volume);
			d.destruction_sound.play();

			//d.sprite.setTexture(d.texture); //????????
		}
		if (d.exist) {
			lets_clear = false;
			d.frame += time * 0.008;

			d.sprite.setTextureRect(IntRect(48 * int(d.frame), 0, 48, 48));

			window.draw(d.sprite);
		}
	}
	if (lets_clear) {
		destructions.clear();
	}
}

void Destructions::Push(const Destruction& destruction) {
	destructions.push_back(destruction);
	for (auto& d : destructions) {
		d.sprite.setTexture(d.texture);
		d.destruction_sound.setBuffer(d.destructionBuffer);
	}
	/*int i = destructions.size() - 1;
	destructions[i].sprite.setTexture(destructions[i].texture);
	destructions[i].destruction_sound.setBuffer(destructions[i].destructionBuffer);*/
}

bool Destructions::Exist(int x, int y) {
	x *= 48; y *= 48;
	for (auto& d : destructions) {
		if (d.x == x && d.y == y) {
			return true;
		}
	}
	return false;
}