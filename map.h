#ifndef _MAP_H_
#define _MAP_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> //random
#include <ctime>
#define HEIGHT_MAP 17
#define WIDTH_MAP 31

using namespace  sf;

extern int x_screen;
extern int y_screen;

extern int music_Volume;
extern int sound_Volume;

struct Point {
	int x;
	int y;
};

extern std::vector<String> TileMap;

extern std::vector<String> TileMap1;

extern std::vector<String> TileMapStart1;

extern std::vector<String> TileMapStart2;

extern std::vector<String> TileMapStart3;

extern std::vector<String> TileMapStart4;

extern std::vector<String> TileMapStart5;

extern std::vector<String> TileMapStart6;

extern std::vector<String> TileMapStart7;

extern std::vector<String> TileMapStart8;

extern std::vector<String> TileMapBonus;

extern std::vector<String> TileMapStartFinal;

class Map {
public:
	Image image;
	Texture texture;
	Sprite sprite;
	String File;
	Image head_image;
	Texture head_texture;
	Sprite head_sprite;

	Map(String F, String f_head) {
		File = F;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		head_image.loadFromFile("images/" + f_head);
		head_texture.loadFromImage(head_image);
		head_sprite.setTexture(head_texture);
	}

	std::vector<String> Generation(std::vector<String> TileMapStart, int filling_rarity) {
		for (int i = 3; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (i > 4 || j > 2) {
					if (TileMapStart[i][j] == ' ') {
						if (rand() % filling_rarity == 0) {
							TileMapStart[i][j] = 'o';
						}
					}
				}
			}
		return TileMapStart;
	}

	void Draw(RenderWindow& window) {
		window.draw(head_sprite);
		for (int i = 2; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ' || TileMap[i][j] == 'b') sprite.setTextureRect(IntRect(48*3, 0, 48, 48)); //если встретили символ пробел, то рисуем 1й квадратик
				else if (TileMap[i][j] == '0') sprite.setTextureRect(IntRect(48*0, 0, 48, 48));//если встретили символ 0, то рисуем 3й квадратик
				else if (TileMap[i][j] == 'o') sprite.setTextureRect(IntRect(48*2, 0, 48, 48));

				sprite.setPosition(j * 48, i * 48);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате

				window.draw(sprite);//рисуем квадратики на экран
			}
	}
};

#endif // MAP_H_
