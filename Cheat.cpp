#include "Cheat.h"

Cheat::Cheat() {
		font.loadFromFile("AllStarResort.ttf"); //"AllStarResort.ttf"
		text = Text("", font, 30);
	}

void Cheat::IncLevel() {
	if (level < 40) {
		++level;
	}
	else {
		level = 1;
	}
}
void Cheat::IncLives() {
	if (lives < 100) {
		++lives;
	}
	else {
		lives = 0;
	}
}
void Cheat::IncBombs() {
	if (bombs < 7) {
		++bombs;
	}
	else {
		bombs = 1;
	}
}
void Cheat::IncRadius() {
	if (radius < 30) {
		++radius;
	}
	else {
		radius = 1;
	}
}
void Cheat::IncSpeed() {
	if (speed < 15) {
		++speed;
	}
	else {
		speed = 0;
	}
}
void Cheat::IncDetonations() {
	if (detonations < 1000) {
		detonations += 10;
	}
	else {
		detonations = 0;
	}
}
void Cheat::LevelDraw(RenderWindow& window) {
	std::ostringstream stream;
	stream << level;
	text.setString("(L) level: " + stream.str());
	text.setPosition(40, 40);
	window.draw(text);
}
void Cheat::BombsDraw(RenderWindow& window) {
	std::ostringstream stream;
	stream << bombs;
	text.setString("(B) Bombs: " + stream.str());
	text.setPosition(40, 70);
	window.draw(text);
}
void Cheat::RadiusDraw(RenderWindow& window) {
	std::ostringstream stream;
	stream << radius;
	text.setString("(R) Expl.Radius: " + stream.str());
	text.setPosition(40, 100);
	window.draw(text);
}
void Cheat::DetonationsDraw(RenderWindow& window) {
	std::ostringstream stream;
	stream << detonations;
	text.setString("(D) Detonations: " + stream.str());
	text.setPosition(40, 130);
	window.draw(text);
}
void Cheat::SpeedDraw(RenderWindow& window) {
	std::ostringstream stream;
	stream << speed;
	text.setString("(V) Speed: " + stream.str());
	text.setPosition(40, 160);
	window.draw(text);
}
void Cheat::LivesDraw(RenderWindow& window) {
	std::ostringstream stream;
	stream << lives;
	text.setString("(H) Lives: " + stream.str());
	text.setPosition(40, 190);
	window.draw(text);
}
void Cheat::Draw(RenderWindow& window) {
	text.setString("CHEAT MOD");
	text.setPosition(40, 10);
	window.draw(text);
	LevelDraw(window);
	BombsDraw(window);
	RadiusDraw(window);
	DetonationsDraw(window);
	SpeedDraw(window);
	LivesDraw(window);
}