#include "Player.h"

using namespace sf;

Player::Player(String f, String f_dying, String f_human, String f_sound, float X, float Y, float W, float H) {
		buffer.loadFromFile("sounds/" + f_sound);
		pop_sound.setBuffer(buffer);

		dx = 0; dy = 0; dir = -1;
		file = f;
		file_human = f_human;
		file_dying = f_dying;
		w = W; h = H;
		image.loadFromFile("images/" + f);
		image.createMaskFromColor(Color(31, 139, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		image_dying.loadFromFile("images/" + f_dying);
		image_dying.createMaskFromColor(Color(31, 139, 0));
		texture_dying.loadFromImage(image_dying);
		image_human.loadFromFile("images/" + f_human);
		image_human.createMaskFromColor(Color(31, 139, 0));
		texture_human.loadFromImage(image_human);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}

	void Player::NewGame() {
		speed = 0.15; //0.15
		score = 0;
		detonations = 0;
		lives = 3;
	}

	void Player::SetSprite(String file) {
		image.loadFromFile("images/" + file);
		image.createMaskFromColor(Color(31, 139, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

	void Player::SetDefault() {
		x = 48;
		y = 48 * 3;
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		Frame = 0;
		dying_frame = 0;
		next_bomb_timer = 0;
		exist = true;
		dying = false;
		dx = 0; dy = 0; dir = -1;
	}

	void Player::DyingAnimation(float time) {
		dying_frame += time * 0.01;
		sprite.setTexture(texture_dying);
		sprite.setTextureRect(IntRect(48 * int(dying_frame), 0, 48, 48));
		if (dying_frame > 6) {
			dying = false;
		}
	}

	void Player::Update(float time) {
		if (!exist) {
			if (dying) {
				DyingAnimation(time);
			}
			return;
		}
		Frame += 0.008 * time;
		next_bomb_timer += time;
		if (Frame > 3) Frame -= 3;

		if (dir != -1) {
			sprite.setTextureRect(IntRect(36 * int(Frame), 48 * dir, 36, 48));
		}

		switch (dir)
		{
		case -1: dx = 0; dy = 0; break;
		case 1: dx = speed; dy = 0; break;
		case 3: dx = -speed; dy = 0; break;
		case 0: dx = 0; dy = speed; break;
		case 2: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		dir = -1;

		sprite.setPosition(x, y);
		InteractionWithMap();
		MoveCorrection();
	}

	void Player::Control(const float& time, Bombs& bombs, RenderWindow& window) {
		if (!exist) {
			return;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			dir = 3;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			dir = 1;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			dir = 2;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			dir = 0;
		}

		if (!isHuman) {
			if (detonations > 0 && bombs.ExistNotExplosion()) {
				if (Keyboard::isKeyPressed(Keyboard::P) || Keyboard::isKeyPressed(Keyboard::X)) {
					bombs.Detonate();
					--detonations;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::O) || Keyboard::isKeyPressed(Keyboard::Z)) {
				if (next_bomb_timer > 500) {
					next_bomb_timer = 0;
					bombs.SetBomb(int(x + 24) / 48 * 48, int(y + 15) / 48 * 48);
				}
			}
		}
	}

	void Player::MoveCorrection() { //сглаживает повороты
		if (dx > 0) {
			if (TileMap[int(y) / 48][int(x) / 48 + 1] != ' ' && TileMap[int((y + 47) / 48)][int(x) / 48 + 1] == ' ') {
				struct Point wall_bot_left = { int(x) / 48 * 48 + 49, int(y) / 48 * 48 + 47 };
				if (wall_bot_left.x - (x + w) < 6 && wall_bot_left.y - y < 24) {
					y += 0.5;
				}
			}
			if (TileMap[int(y) / 48][int(x) / 48 + 1] == ' ' && TileMap[int((y + 47) / 48)][int(x) / 48 + 1] != ' ') {
				struct Point wall_up_left = { int(x) / 48 * 48 + 49, int(y) / 48 * 48 + 49 };
				if (wall_up_left.x - (x + w) < 6 && -wall_up_left.y + (y + h) < 24) {
					y -= 0.5;
				}
			}
		}
		if (dx < 0) {
			if (TileMap[int(y) / 48][int(x) / 48 - 1] != ' ' && TileMap[int((y + 47) / 48)][int(x) / 48 - 1] == ' ') {
				struct Point wall_bot_right = { int(x) / 48 * 48 - 2, int(y) / 48 * 48 + 47 };
				if (-wall_bot_right.x + x < 6 && wall_bot_right.y - y < 24) {
					y += 0.5;
				}
			}
			if (TileMap[int(y) / 48][int(x) / 48 - 1] == ' ' && TileMap[int((y + 47) / 48)][int(x) / 48 - 1] != ' ') {
				struct Point wall_up_right = { int(x) / 48 * 48 - 2, int(y) / 48 * 48 + 49 };
				if (-wall_up_right.x + x < 6 && -wall_up_right.y + (y + h) < 24) {
					y -= 0.5;
				}
			}
		}
		if (dy < 0) {
			if (TileMap[int(y) / 48 - 1][int(x) / 48] == ' ' && TileMap[int(y) / 48 - 1][int(x + 36) / 48] != ' ') {
				struct Point wall_left_bot = { int(x) / 48 * 48 + 49, int(y) / 48 * 48 - 2 };
				if (-wall_left_bot.y + y < 6 && -wall_left_bot.x + (x + w) < 24) {
					x -= 0.5;
				}
			}
			if (TileMap[int(y) / 48 - 1][int(x) / 48] != ' ' && TileMap[int(y) / 48 - 1][int(x + 36) / 48] == ' ') {
				struct Point wall_right_bot = { int(x) / 48 * 48 - 2, int(y) / 48 * 48 - 2 };
				if (-wall_right_bot.y + y < 6 && wall_right_bot.x - x < 24) {
					x += 0.5;
				}
			}
		}
		if (dy > 0) {
			if (TileMap[int(y) / 48 + 1][int(x) / 48] == ' ' && TileMap[int(y) / 48 + 1][int(x + 36) / 48] != ' ') {
				struct Point wall_left_up = { int(x) / 48 * 48 + 49, int(y) / 48 * 48 + 49 };
				if (wall_left_up.y - (y + h) < 6 && -wall_left_up.x + (x + w) < 24) {
					x -= 0.5;
				}
			}
			if (TileMap[int(y) / 48 + 1][int(x) / 48] != ' ' && TileMap[int(y) / 48 + 1][int(x + 36) / 48] == ' ') {
				struct Point wall_right_up = { int(x) / 48 * 48 - 2, int(y) / 48 * 48 + 49 };
				if (wall_right_up.y - (y + h) < 6 && wall_right_up.x - x < 24) {
					x += 0.5;
				}
			}
		}
	}

	void Player::InteractionWithMap()//ф-ция взаимодействия с картой
	{
		for (int i = y / 48; i < (y + 46) / 48; i++) {//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 48*48
			for (int j = x / 48; j < (x + w) / 48; j++)
			{
				if (TileMap[i][j] != ' ')//если наш квадратик не соответствует символу ' ' (проход), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)
						y = i * 48 - h;//стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем высоту спрайта персонажа.
					if (dy < 0)
						y = i * 48 + 48;
					if (dx > 0) {
						x = j * 48 - w - 1;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа						
					}
					if (dx < 0)
						x = j * 48 + 48;
				}
			}
		}
	}

	void Player::InteractionWithExplosion(const Bombs& bombs) {
		if (!exist) {
			return;
		}
		for (int i = (y + 5) / 48; i < (y + h - 5) / 48; i++) {
			for (int j = (x + 5) / 48; j < (x + w - 5) / 48; j++) {
				for (const auto& b : bombs.bombs) {
					if (b.explosion) {
						if (b.x / 48 == j && b.y / 48 == i) {
							exist = false;
							dying = true;
							pop_sound.setVolume(sound_Volume);
							pop_sound.play();
							return;
						}
						for (const auto& e : b.exp_points) {
							if (e.x / 48 == j && e.y / 48 == i) {
								exist = false;
								dying = true;
								pop_sound.setVolume(sound_Volume);
								pop_sound.play();
								return;
							}

						}
					}
				}
			}
		}
	}

	void Player::InteractionWithEnemies(const Enemies& enemies) {
		if (!exist) {
			return;
		}
		for (auto& enemy : enemies.enemies) {
			if (!enemy.exist) {
				continue;
			}
			for (int i = (y + 24) / 48; i < (y + h - 18) / 48; i++) {
				for (int j = (x + 10) / 48; j < (x + w - 10) / 48; j++) {
					if (int(enemy.x + enemy.w / 2) / 48 == j && int(enemy.y + enemy.h / 2) / 48 == i) {
						exist = false;
						dying = true;
						pop_sound.setVolume(sound_Volume);
						pop_sound.play();
						return;
					}
				}
			}
		}
	}

	void Player::InteractionWithItems(Items& items, Bombs& bombs, Enemies& enemies, bool& NextLevel) {
		if (!exist) {
			return;
		}
		for (auto& item : items.items) {
			if (!item.exist || item.dying) {
				continue;
			}
			for (int i = (y + 15) / 48; i < (y + h - 15) / 48; i++) {
				for (int j = (x + 10) / 48; j < (x + w - 10) / 48; j++) {
					if (int(item.x + item.w / 2) / 48 == j && int(item.y + item.h / 2) / 48 == i) {
						item.pick_up_sound.setVolume(sound_Volume);
						item.pick_up_sound.play();
						switch (item.code) {
						case 0: //Door
							if (enemies.IsEmpty()) {
								exist = false;
								NextLevel = true;
							}
							break;
						case 1: //BombsUp
							if (bombs.number < 6) {
								bombs.IncNumber();
							}
							item.exist = false;
							break;
						case 2: //ExplosionUp
							if (bombs.radius < 6) {
								bombs.IncRadius();
							}
							item.exist = false;
							break;
						case 3: //SpeedUp
							if (speed < 0.3) {
								speed += 0.03;
							}
							item.exist = false;
							break;
						case 4: //Chest
							score += 50;
							item.sprite.setTextureRect(IntRect(48 * item.code, 48, item.w, item.h));
							item.dying = true;
							break;
						case 5: //Detonator
							detonations += 10;
							item.exist = false;
							break;
						case 6: //Life
							lives++;
							item.exist = false;
							break;
						}

					}
				}
			}
		}
	}

	float Player::GetX() const {
		return x;
	}
	float Player::GetY() const {
		return y;
	}