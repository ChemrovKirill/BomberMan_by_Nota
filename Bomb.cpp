#include "Bomb.h"

Bomb::Bomb(String f_sound, String f_image, float W, float H) {
	file_image = f_image;
	file_sound = f_sound;
	w = W; h = H;
	image.loadFromFile("images/" + file_image);
	image.createMaskFromColor(Color(31, 139, 0));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));

	explosionBuffer.loadFromFile("sounds/" + file_sound);
	explosion_sound.setBuffer(explosionBuffer);
}
void Bomb::Clear() {
	explosion = false;
	exist = false;
	x = 0;
	y = 0;
	explosion_frame = 0;
	current_frame = 0;
	time_left = BOMB_TIMER;
}

Bombs::Bombs(Bomb b, int r, int n) {
	radius = r;
	number = n;
	for (int i = 0; i < number; ++i) {
		bombs.push_back(b);
	}
}

bool Bombs::BombIsHere(int x, int y) {
	for (auto& b : bombs) {
		if (b.x == x && b.y == y) {
			return true;
		}
	}
	return false;
}

void Bombs::SetBomb(int new_x, int new_y) {
	for (auto& b : bombs) {
		if (b.exist && b.x == new_x && b.y == new_y) {
			return;
		}
	}
	for (auto& b : bombs) {
		if (!b.exist) {
			b.time_left = BOMB_TIMER;
			b.x = new_x;
			b.y = new_y;
			b.sprite.setPosition(b.x, b.y);
			b.exist = true;
			break;
		}
	}
}

void Bombs::Update(float time) {
	for (auto& b : bombs) {
		if (b.exist && !b.explosion) {
			b.sprite.setPosition(b.x, b.y);
			b.time_left -= time;
			b.current_frame += 0.007 * time;
			if (b.current_frame > 4) {
				b.current_frame -= 4;
			}
			b.sprite.setTextureRect(IntRect(48 * int(b.current_frame), 0, 48, 48));
			if (b.time_left < 0) {
				b.time_left = BOMB_TIMER;
				b.explosion = true;
				b.explosion_sound.setVolume(sound_Volume);
				b.explosion_sound.play();
			}
		}
		if (b.explosion) {
			b.sprite.setPosition(b.x, b.y);
			if (b.explosion_frame > 4) {
				b.go_back = true;
			}
			if (b.go_back) {
				b.explosion_frame -= 0.03 * time;
			}
			else {
				b.explosion_frame += 0.02 * time;
			}
			if (b.explosion_frame < 0) {
				b.go_back = false;
				TileMap[b.y / 48][b.x / 48] = ' ';
				b.Clear();
			}
			b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48, 48, 48));
		}
	}
}

bool Bombs::ExistNotExplosion() {
	for (const auto& b : bombs) {
		if (b.exist && !b.explosion) {
			return true;
		}
	}
	return false;
}

void Bombs::SetDefault() {
	for (auto& b : bombs) {
		b.Clear();
	}
}

void Bombs::NewGame() {
	radius = 1;
	number = 1;
	Bomb bomb = bombs[0];
	bombs.clear();
	bombs.push_back(bomb);
}

void Bombs::InterectionWithObjects(std::vector<Point> objs) {
	for (auto& b : bombs) {
		if (b.exist) {
			bool lets_set_b = true;
			for (auto& o : objs) {
				if (b.x / 48 == o.x / 48 || b.x / 48 == (o.x + 47) / 48) {
					if (b.y / 48 == o.y / 48 || b.y / 48 == (o.y + 47) / 48) {
						lets_set_b = false;
						break;
					}
				}
			}
			if (lets_set_b) {
				TileMap[b.y / 48][b.x / 48] = 'b';
			}
		}
	}
}

void Bombs::DestructionTracking(Destructions& ds) {
	for (auto& b : bombs) {
		if (b.explosion) {
			for (int i = 1; i <= radius; ++i) {
				if (TileMap[b.y / 48 - i][b.x / 48] == '0') {	//up
					break;
				}
				if (TileMap[b.y / 48 - i][b.x / 48] == 'o') {
					TileMap[b.y / 48 - i][b.x / 48] = ' ';
					ds.Push({ "wall_destruction.png", "wall_destruction.wav", b.x, b.y - 48 * i });
				}
			}

			for (int i = 1; i <= radius; ++i) {
				if (TileMap[b.y / 48 + i][b.x / 48] == '0') {	//down
					break;
				}
				if (TileMap[b.y / 48 + i][b.x / 48] == 'o') {
					TileMap[b.y / 48 + i][b.x / 48] = ' ';
					ds.Push({ "wall_destruction.png", "wall_destruction.wav", b.x, b.y + 48 * i });
					break;
				}
			}

			for (int i = 1; i <= radius; ++i) {
				if (TileMap[b.y / 48][b.x / 48 + i] == '0') {	//right
					break;
				}
				if (TileMap[b.y / 48][b.x / 48 + i] == 'o') {
					TileMap[b.y / 48][b.x / 48 + i] = ' ';
					ds.Push(Destruction("wall_destruction.png", "wall_destruction.wav", b.x + i * 48, b.y));
					break;
				}
			}

			for (int i = 1; i <= radius; ++i) {
				if (TileMap[b.y / 48][b.x / 48 - i] == '0') {	//left
					break;
				}
				if (TileMap[b.y / 48][b.x / 48 - i] == 'o') {
					TileMap[b.y / 48][b.x / 48 - i] = ' ';
					ds.Push({ "wall_destruction.png", "wall_destruction.wav", b.x - i * 48, b.y });
					break;
				}
			}
		}
	}
}

void Bombs::ExplosionDraw(RenderWindow& window) {
	for (auto& b : bombs) {
		if (b.explosion) {
			for (int i = 1; i <= radius; ++i) {
				if (TileMap[b.y / 48 - i][b.x / 48] == ' ' || TileMap[b.y / 48 - i][b.x / 48] == 'b') {  //up
					if (i == radius) {
						b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48 * 2, 48, 48));
					}
					else {
						b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48 * 3, 48, 48));
					}
					b.sprite.setPosition(b.x, b.y - i * 48);
					b.exp_points.push_back({ b.x, b.y - i * 48 });
					window.draw(b.sprite);
				}
				else {
					break;
				}
			}

			for (int i = 1; i <= radius; ++i) {
				if (TileMap[b.y / 48 + i][b.x / 48] == ' ' || TileMap[b.y / 48 + i][b.x / 48] == 'b') {  //down
					if (i == radius) {
						b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48 * 4, 48, 48));
					}
					else {
						b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48 * 3, 48, 48));
					}
					b.sprite.setPosition(b.x, b.y + i * 48);
					b.exp_points.push_back({ b.x, b.y + i * 48 });
					window.draw(b.sprite);
				}
				else {
					break;
				}
			}

			for (int i = 1; i <= radius; ++i) {
				if (TileMap[b.y / 48][b.x / 48 - i] == ' ' || TileMap[b.y / 48][b.x / 48 - i] == 'b') {  //right
					if (i == radius) {
						b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48 * 5, 48, 48));
					}
					else {
						b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48 * 6, 48, 48));
					}
					b.sprite.setPosition(b.x - i * 48, b.y);
					b.exp_points.push_back({ b.x - i * 48, b.y });
					window.draw(b.sprite);
				}
				else {
					break;
				}
			}

			for (int i = 1; i <= radius; ++i) {
				if (TileMap[b.y / 48][b.x / 48 + i] == ' ' || TileMap[b.y / 48][b.x / 48 + i] == 'b') {  //left
					if (i == radius) {
						b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48 * 7, 48, 48));
					}
					else {
						b.sprite.setTextureRect(IntRect(48 * int(b.explosion_frame), 48 * 6, 48, 48));
					}
					b.sprite.setPosition(b.x + i * 48, b.y);
					b.exp_points.push_back({ b.x + i * 48, b.y });
					window.draw(b.sprite);
				}
				else {
					break;
				}
			}
		}
		else {
			b.exp_points.clear();
		}
	}

}

void Bombs::Draw(RenderWindow& window) {
	for (auto& b : bombs) {
		if (b.exist || b.explosion) {
			window.draw(b.sprite);
		}
	}
	ExplosionDraw(window);
}

void Bombs::Detonate() {
	for (auto& b : bombs) {
		if (b.exist && !b.explosion) {
			b.time_left = 0;
		}
	}
}

void Bombs::IncRadius() {
	radius++;
}
void Bombs::DecRadius() {
	if (radius > 2) {
		radius--;
	}
}
void Bombs::IncNumber() {
	number++;
	bombs.push_back(bombs[0]);
}
void Bombs::DecNumber() {
	if (number > 2) {
		number--;
		bombs.pop_back();
	}
}