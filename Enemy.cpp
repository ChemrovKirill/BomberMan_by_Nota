#include "Enemy.h"

using namespace sf;

Enemy::Enemy(String f, String f_dying, String f_sound, float X, float Y, float W, float H, float s, String n) {
		buffer.loadFromFile("sounds/" + f_sound);
		pop_sound.setBuffer(buffer);

		dx = 0; dy = 0; dir = 0;
		speed = s;
		file_dying = f_dying;
		file = f;
		w = W; h = H;
		name = n;
		image.loadFromFile("images/" + file);
		image.createMaskFromColor(Color(31, 139, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		image_dying.loadFromFile("images/" + f_dying);
		image_dying.createMaskFromColor(Color(31, 139, 0));
		texture_dying.loadFromImage(image_dying);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setPosition(x, y);
	}

void Enemy::Update(float time, Destructions& destructions) {

	timer += time * 0.001;

	if (appearing) {
		exist = true;
		dying = false;
		if (timer > 1) {
			appearing = false;
		}
	}
	if (!exist) {
		if (dying) {
			DyingAnimation(time);
		}
		return;
	}

	Frame += 0.008 * time;
	if (Frame > 3) {
		Frame -= 3;
	}

	switch (dir)
	{
	case 1: dx = speed; dy = 0;
		sprite.setTextureRect(IntRect(48 * int(Frame), 48, w, h));
		break;
	case 3: dx = -speed; dy = 0;
		sprite.setTextureRect(IntRect(48 * int(Frame), 0, w, h));
		break;
	case 0: dx = 0; dy = speed;
		sprite.setTextureRect(IntRect(48 * int(Frame), 0, w, h));
		break;
	case 2: dx = 0; dy = -speed;
		sprite.setTextureRect(IntRect(48 * int(Frame), 48, w, h));
		break;
	}

	x += dx * time;
	y += dy * time;

	sprite.setPosition(x, y);
	InteractionWithMap(destructions);
}

void Enemy::DyingAnimation(float time) {
	if (dying_frame > 4.9) {
		if (name == "Doll" && life == 1) {
			life--;
			image.loadFromFile("images/2" + file);
			image.createMaskFromColor(Color(31, 139, 0));
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			exist = true;
			dying = false;
			dying_frame = 0;
			return;
		}
	}
	if (dying_frame > 5) {
		dying_frame += time * 0.001;
	}
	else {
		dying_frame += time * 0.01;
	}
	sprite.setTexture(texture_dying);
	sprite.setTextureRect(IntRect(48 * int(dying_frame), 0, 48, 48));
	if (dying_frame > 6) {
		dying = false;
	}
}

void Enemy::Draw(RenderWindow& window) {
	if (exist || dying) {
		window.draw(sprite);
	}
}

void Enemy::InteractionWithExplosion(const Bombs& bombs, int& score) {
	for (int i = (y + 5) / 48; i < (y + h - 5) / 48; i++) {
		for (int j = (x + 5) / 48; j < (x + w - 5) / 48; j++)
		{
			for (const auto& b : bombs.bombs) {
				if (b.explosion) {
					for (const auto& e : b.exp_points) {
						if (e.x / 48 == j && e.y / 48 == i) {
							exist = false;
							dying = true;
							pop_sound.setVolume(sound_Volume);
							pop_sound.play();
							if (name == "Balloom") {
								score += 10;
							}
							else if (name == "Oneal") {
								score += 20;
							}
							else if (name == "Doll") {
								if (life == 0) {
									score += 30;
								}
							}
							else if (name == "Minvo") {
								score += 40;
							}
							else if (name == "Kondoria") {
								score += 50;
							}
							else if (name == "Ovapi") {
								score += 100;
							}
							else if (name == "Pontan" && !appearing) {
								score += 100;
							}
							else if (name == "Pass") {
								score += 15;
							}
							return;
						}

					}
				}
			}
		}
	}
}

void Enemy::InteractionWithMap(Destructions& ds) {
	if (name == "Balloom") {
		InteractionWithMapBalloom();
	}
	else if (name == "Oneal") {
		InteractionWithMapOneal();
	}
	else if (name == "Doll") {
		InteractionWithMapBalloom();
	}
	else if (name == "Minvo") {
		InteractionWithMapMinvo(ds);
	}
	else if (name == "Kondoria") {
		InteractionWithMapKondoria();
	}
	else if (name == "Ovapi") {
		InteractionWithMapOvapi();
	}
	else if (name == "Pontan") {
		InteractionWithMapOvapi();
	}
	else if (name == "Pass") {
		InteractionWithMapOneal();
	}
}

void Enemy::InteractionWithMapBalloom() {
	for (int i = y / 48; i < (y + h - 1) / 48; i++) {
		for (int j = x / 48; j < (x + w - 1) / 48; j++)
		{
			if (TileMap[i][j] != ' ')
			{
				dir = rand() % 4;
				if (dy > 0)
					y = i * 48 - h;
				if (dy < 0)
					y = i * 48 + 48;
				if (dx > 0)
					x = j * 48 - w;
				if (dx < 0)
					x = j * 48 + 48;
			}
		}
	}
}

void Enemy::InteractionWithMapOneal()
{
	for (int i = y / 48; i < (y + h - 1) / 48; i++) {
		for (int j = x / 48; j < (x + w - 1) / 48; j++)
		{
			if (TileMap[i][j] != ' ')
			{
				dir = rand() % 4;
				if (dy > 0)
					y = i * 48 - h;
				if (dy < 0)
					y = i * 48 + 48;
				if (dx > 0)
					x = j * 48 - w;
				if (dx < 0)
					x = j * 48 + 48;
			}
			if (dx == 0) {
				if (rand() % 3 == 1);
				else if ((TileMap[y / 48][x / 48 - 1] == ' ' && TileMap[(y + 47) / 48][x / 48 - 1] == ' ') ||
					(TileMap[y / 48][x / 48 + 1] == ' ' && TileMap[(y + 47) / 48][x / 48 + 1] == ' ')) {
					if (int(y / 48) == int((y + 47) / 48)) {
						int new_dir = rand() % 4;
						if (new_dir != (dir + 2) % 4) {
							dir = new_dir;
						}
					}
				}
			}
			if (dy == 0) {
				if (rand() % 3 == 1);
				else if ((TileMap[y / 48 - 1][x / 48] == ' ' && TileMap[y / 48 - 1][(x + 47) / 48] == ' ') ||
					(TileMap[y / 48 + 1][x / 48] == ' ' && TileMap[y / 48 + 1][(x + 47) / 48] == ' ')) {
					if (int(x / 48) == int((x + 47) / 48)) {
						int new_dir = rand() % 4;
						if (new_dir != (dir + 2) % 4) {
							dir = new_dir;
						}
					}
				}
			}
		}
	}
}

void Enemy::InteractionWithMapMinvo(Destructions& ds)
{
	for (int i = y / 48; i < (y + h - 1) / 48; i++) {
		for (int j = x / 48; j < (x + w - 1) / 48; j++)
		{
			if (TileMap[i][j] != ' ')
			{
				if (TileMap[i][j] == 'o') {
					if (rand() % 5 == 1) {
						TileMap[i][j] = ' ';
						ds.Push({ "wall_destruction.png", "wall_destruction.wav",  j * 48, i * 48 });
					}
				}
				dir = rand() % 4;
				if (dy > 0)
					y = i * 48 - h;
				if (dy < 0)
					y = i * 48 + 48;
				if (dx > 0)
					x = j * 48 - w;
				if (dx < 0)
					x = j * 48 + 48;
			}
		}
	}
}

void Enemy::InteractionWithMapKondoria() {
	for (int i = y / 48; i < (y + h - 1) / 48; i++) {
		for (int j = x / 48; j < (x + w - 1) / 48; j++)
		{
			if (TileMap[i][j] != ' ' && TileMap[i][j] != 'o')
			{
				dir = (dir + 2) % 4;
				if (TileMap[i][j] == 'b') {
					dir = rand() % 4;
				}
				if (rand() % 5 == 1) {
					dir = rand() % 4;
				}
				if (dy > 0)
					y = i * 48 - h;
				if (dy < 0)
					y = i * 48 + 48;
				if (dx > 0)
					x = j * 48 - w;
				if (dx < 0)
					x = j * 48 + 48;
			}
		}
	}
}

void Enemy::InteractionWithMapOvapi() {
	for (int i = y / 48; i < (y + h - 1) / 48; i++) {
		for (int j = x / 48; j < (x + w - 1) / 48; j++)
		{
			if (TileMap[i][j] == '0')
			{
				dir = rand() % 4;
				if (dy > 0)
					y = i * 48 - h;
				if (dy < 0)
					y = i * 48 + 48;
				if (dx > 0)
					x = j * 48 - w;
				if (dx < 0)
					x = j * 48 + 48;
			}
			else if (dx == 0) {
				if (rand() % 3 == 1);
				else if ((TileMap[y / 48][x / 48 - 1] != '0' && TileMap[(y + 47) / 48][x / 48 - 1] != '0') ||
					(TileMap[y / 48][x / 48 + 1] != '0' && TileMap[(y + 47) / 48][x / 48 + 1] != '0')) {
					if (int(y / 48) == int((y + 47) / 48)) {
						int new_dir = rand() % 4;
						if (new_dir != (dir + 2) % 4) {
							dir = new_dir;
						}
					}
				}
			}
			if (dy == 0) {
				if (rand() % 3 == 1);
				else if ((TileMap[y / 48 - 1][x / 48] != '0' && TileMap[y / 48 - 1][(x + 47) / 48] != '0') ||
					(TileMap[y / 48 + 1][x / 48] != '0' && TileMap[y / 48 + 1][(x + 47) / 48] != '0')) {
					if (int(x / 48) == int((x + 47) / 48)) {
						int new_dir = rand() % 4;
						if (new_dir != (dir + 2) % 4) {
							dir = new_dir;
						}
					}
				}
			}
		}
	}
}

void Enemies::RandSpawn(int number, Enemy& enemy) {
	for (int k = 0; k < number; ++k) {
		bool searching = true;
		while (searching) {
			int i = rand() % HEIGHT_MAP;
			int j = rand() % WIDTH_MAP;
			if (i > 5 || j > 4) {
				if (TileMap[i][j] == ' ') {
					enemy.x = j * 48;
					enemy.y = i * 48;
					Push(enemy);
					searching = false;
				}
			}
		}
	}
}

void Enemies::Push(Enemy& enemy) {
	enemies.push_back(enemy);
}

bool Enemies::IsEmpty() {
	for (auto& e : enemies) {
		if (e.exist) {
			return false;
		}
	}
	return true;
}

void Enemies::Update(float time, Destructions& destructions) {
	for (auto& e : enemies) {
		if (e.exist || e.dying) {
			if (e.exist) {
				if (e.name == "Pass") {
					if (e.progeny < 2) {
						if (e.timer > 15) {
							e.timer = 0;
							e.progeny++;
							enemies.push_back(e);
							e.dir = (e.dir + 2) % 4;
						}
					}
				}
			}
			e.sprite.setTexture(e.texture); //important for Pontan
			e.Update(time, destructions);
		}
	}
}

void Enemies::InteractionWithExplosion(const Bombs& bombs, int& score) {
	for (auto& e : enemies) {
		if (e.exist) {
			e.InteractionWithExplosion(bombs, score);
		}
	}
}

void Enemies::InteractionWithMap(Destructions& destructions) {
	for (auto& e : enemies) {
		if (e.exist) {
			e.InteractionWithMap(destructions);
		}
	}
}

void Enemies::Draw(RenderWindow& window) {
	for (auto& e : enemies) {
		e.Draw(window);
	}
}