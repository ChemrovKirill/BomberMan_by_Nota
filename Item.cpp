#include "Item.h"

using namespace sf;

/*ITEM*/
Item::Item(String f_image, String name, String file_sound) {
		buffer.loadFromFile("sounds/" + file_sound);
		pick_up_sound.setBuffer(buffer);
		dying_time = 0;
		file_image = f_image;
		if (name == "Door") {
			code = 0;
		}
		else if (name == "BombsUp") {
			code = 1;
		}
		else if (name == "ExplosionUp") {
			code = 2;
		}
		else if (name == "SpeedUp") {
			code = 3;
		}
		else if (name == "Chest") {
			code = 4;
		}
		else if (name == "Detonator") {
			code = 5;
		}
		else if (name == "Life") {
			code = 6;
		}
		image.loadFromFile("images/" + file_image);
		image.createMaskFromColor(Color(31, 139, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(48 * code, 0, w, h));
	}

	void Item::Update(Bombs& bombs, Enemies& enemies, Destructions& destructions, int level, int& score, const float& time) {
		if (dying) {
			dying_time += (time * 0.001);
			if (dying_time > 1) {
				exist = false;
				dying = false;
			}
		}
		if (code == 0) {
			if (enemies.IsEmpty()) {
				sprite.setTextureRect(IntRect(0, 48, w, h));
			}
			else {
				sprite.setTextureRect(IntRect(0, 0, w, h));
			}
		}
		InteractionWithExplosion(bombs, enemies, destructions, score, level);
	}

	void Item::RandSpawn() {
		bool searching = true;
		while (searching) {
			int i = rand() % HEIGHT_MAP;
			int j = rand() % WIDTH_MAP;
			if (i > 4 || j > 2) {
				if (TileMap[i][j] == 'o') {
					x = j * 48;
					y = i * 48;
					sprite.setPosition(x, y);
					exist = true;
					searching = false;
				}
			}
		}
	}
	void Item::RandSpawnWallEmpty() {
		bool searching = true;
		while (searching) {
			int i = rand() % HEIGHT_MAP;
			int j = rand() % WIDTH_MAP;
			if (i > 4 || j > 2) {
				if (TileMap[i][j] == 'o' || TileMap[i][j] == ' ') {
					x = j * 48;
					y = i * 48;
					sprite.setPosition(x, y);
					exist = true;
					searching = false;
				}
			}
		}
	}

	void Item::Spawn(int new_x, int new_y) {
		x = new_x;
		y = new_y;
		sprite.setPosition(x, y);
		exist = true;
	}

	void Item::InteractionWithExplosion(Bombs& bombs, Enemies& enemies, Destructions& destructions, int& score, int level) {
		if (!exist) {
			return;
		}
		if (destructions.Exist(x / 48, y / 48)) {
			return;
		}
		if (TileMap[y / 48][x / 48] == 'o') {
			return;
		}
		for (int i = y / 48; i < (y + h) / 48; i++) {
			for (int j = (x) / 48; j < (x + w) / 48; j++) {
				for (const auto& b : bombs.bombs) {
					if (b.explosion) {
						for (const auto& e : b.exp_points) {
							if (e.x / 48 == j && e.y / 48 == i) {
								if (code == 4) {
									exist = false;
									Enemy Pontan("Pontan.png", "Pontan_dying.png", "pop.wav", x, y, 48.0, 48.0, 0.15, "Pontan");
									for (int i = 0; i < level / 5; ++i) {
										enemies.Push(Pontan);
									}
								}
								else if (code == 0) {
									if (level != 40) {
										Enemy Pontan("Pontan.png", "Pontan_dying.png", "pop.wav", x, y, 48.0, 48.0, 0.2, "Pontan");
										RandSpawnWallEmpty();
										for (int i = 0; i < level / 4; ++i) {
											enemies.Push(Pontan);
										}
									}
								}
								else {
									score += 20;
									sprite.setTextureRect(IntRect(48 * code, 48, w, h));
									dying = true;
									exist = false;
								}
								return;
							}

						}
					}
				}
			}
		}
	}

	void Item::Draw(RenderWindow& window) {
		if ((dying || exist) && TileMap[y / 48][x / 48] != 'o') {
			window.draw(sprite);
		}
	}

/*ITEMS*/
	void Items::Push(Item item) {
		item.exist = true;
		items.push_back(item);
	}

	void Items::RandSpawn() {
		for (int i = 0; i < items.size(); ++i) {
			bool searching = true;
			while (searching) {
				items[i].RandSpawn();
				searching = false;
				for (int j = 0; j < items.size(); ++j) {
					if (i != j && items[i].x == items[j].x && items[i].y == items[j].y) {
						searching = true;
						break;
					}
				}
			}
		}
	}

	void Items::Update(Bombs& bombs, Enemies& enemies, Destructions& destructions, int level, int& score, float time) {
		for (auto& i : items) {
			i.Update(bombs, enemies, destructions, level, score, time);
		}
	}

	void Items::Draw(RenderWindow& window) {
		for (auto& i : items) {
			i.sprite.setTexture(i.texture);
			i.Draw(window);
		}
	}