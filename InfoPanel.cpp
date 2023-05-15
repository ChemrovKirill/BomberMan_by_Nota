#include "InfoPanel.h"

using namespace sf;

Info::Info(String file_font, int size) {
		font.loadFromFile(file_font); //"AllStarResort.ttf"
		text = Text("", font, size);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		//text.setFillColor(Color::White);
		//text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	}
	void Info::ScoreDraw(Player& player, RenderWindow& window) {
		std::ostringstream stream;
		stream << player.score;
		text.setCharacterSize(35);
		text.setString("Score:");
		text.setPosition(50, 10);
		window.draw(text);
		if (player.score > 9999999) {
			text.setCharacterSize(30);
			text.setPosition(45, 45);
		}
		else {
			text.setCharacterSize(45);
			text.setPosition(50, 40);
		}
		text.setString(stream.str());
		window.draw(text);
	}
	void Info::BombsDraw(Bombs& bombs, RenderWindow& window) {
		std::ostringstream stream;
		stream << bombs.number;
		text.setCharacterSize(35);
		text.setString("Bombs: ");
		text.setPosition(590, 10);
		window.draw(text);
		text.setCharacterSize(45);
		text.setString(stream.str());
		text.setPosition(630, 40);
		window.draw(text);
	}
	void Info::TimeDraw(int time, RenderWindow& window) {
		std::ostringstream stream;
		stream << time;
		text.setCharacterSize(35);
		text.setString("Time: ");
		text.setPosition(0, 10);
		window.draw(text);
		text.setCharacterSize(45);
		text.setString(stream.str());
		text.setPosition(0, 40);
		window.draw(text);
	}

	void Info::LevelDraw(int level, RenderWindow& window) {
		std::ostringstream stream;
		stream << std::setw(2) << std::setfill('0') << level;
		text.setCharacterSize(35);
		text.setString("Level: ");
		text.setPosition(1335, 10);
		window.draw(text);
		text.setCharacterSize(45);
		text.setString(stream.str());
		text.setPosition(1365, 40);
		window.draw(text);
	}

	void Info::DetonationsDraw(const int& detonations, RenderWindow& window) {
		std::ostringstream stream;
		stream << detonations;
		text.setCharacterSize(35);
		text.setString("Detonators: ");
		text.setPosition(830, 10);
		window.draw(text);
		text.setCharacterSize(45);
		text.setString(stream.str());
		text.setPosition(830, 40);
		window.draw(text);
	}

	void Info::LivesDraw(Player& player, RenderWindow& window) {
		std::ostringstream stream;
		stream << player.lives;		//занесли в нее число очков, то есть формируем строку
		text.setCharacterSize(35);
		text.setString("Lives: ");
		text.setPosition(1145, 10);
		window.draw(text);
		text.setCharacterSize(45);
		text.setString(stream.str());
		text.setPosition(1180, 40);
		window.draw(text);
	}

	void Info::RadiusDraw(Bombs& bombs, RenderWindow& window) {
		std::ostringstream stream;
		stream << bombs.radius;		//занесли в нее число очков, то есть формируем строку
		text.setCharacterSize(35);
		text.setString("Radius: ");
		text.setPosition(343, 10);
		window.draw(text);
		text.setCharacterSize(45);
		text.setString(stream.str());
		text.setPosition(393, 40);
		window.draw(text);
	}

	void Info::MusicDraw(int time, int level, RenderWindow& window) {
		if (time < 1 || time > 15) {
			return;
		}
		if (level == 40) {
			text.setString("Kevin MacLeod - Space Fighter Loop");
		}
		else {
			switch (level % 5) {
			case 0:
				text.setString("Kevin MacLeod - Phantom From Space");
				break;
			case 1:
				text.setString("Kevin MacLeod - Neo Western");
				break;
			case 2:
				text.setString("Kevin MacLeod - Myst On The Moor");
				break;
			case 3:
				text.setString("Kevin MacLeod - Mystery");
				break;
			case 4:
				text.setString("Kevin MacLeod - I Can Feel It Coming");
				break;
			default:
				text.setString("Kevin MacLeod - Neo Western.wav");
				break;
			}
		}
		text.setFillColor(Color::Black);
		text.setStyle(sf::Text::Bold);
		text.setCharacterSize(35);
		text.setPosition(760, 765);
		window.draw(text);
		text.setFillColor(Color::White);
		text.setStyle(sf::Text::Regular);
	}

	void Info::Draw(int time, Player& player, Bombs& bombs, RenderWindow& window, const int& detonations, const int& level) {
		ScoreDraw(player, window);
		BombsDraw(bombs, window);
		LivesDraw(player, window);
		RadiusDraw(bombs, window);
		//TimeDraw(time, window);
		DetonationsDraw(detonations, window);
		LevelDraw(level, window);
		MusicDraw(time, level, window);
	}