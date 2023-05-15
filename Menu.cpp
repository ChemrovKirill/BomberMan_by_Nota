#include "Menu.h"

bool SettingsMenu(RenderWindow& window, Music& music) {
	bool SettingsOpen = true;
	int selected_button = 1;
	int num_buttons = 2;

	StateImage SettingsState(false, "SettingsMenu.png", 0, 0); //no transparency

	SoundBuffer explosionBuffer;
	Sound explosion_sound;
	explosionBuffer.loadFromFile("sounds/explosion.wav");
	explosion_sound.setBuffer(explosionBuffer);

	Image Triangle_image;
	Texture Triangle_texture;
	Sprite sound_tr_sprite, music_tr_sprite;
	Triangle_image.loadFromFile("images/SettingsTriangle.png");
	Triangle_texture.loadFromImage(Triangle_image);
	sound_tr_sprite.setTexture(Triangle_texture);
	music_tr_sprite.setTexture(Triangle_texture);
	sound_tr_sprite.setPosition(496 + int(sound_Volume * 6.9), 348);
	music_tr_sprite.setPosition(496 + int(music_Volume * 6.9), 494);

	while (SettingsOpen) {

		window.clear();
		sound_tr_sprite.setPosition(496 + int(sound_Volume * 6.9), 348);
		sound_tr_sprite.setTextureRect(IntRect(0, 0, 53, 53));
		music_tr_sprite.setPosition(496 + int(music_Volume * 6.9), 494);
		music_tr_sprite.setTextureRect(IntRect(0, 0, 53, 53));

		switch (selected_button)
		{
		case 1:
			sound_tr_sprite.setTextureRect(IntRect(53, 0, 53, 53));
			break;
		case 2:
			music_tr_sprite.setTextureRect(IntRect(53, 0, 53, 53));
			break;
		}

		window.draw(SettingsState.sprite);
		window.draw(sound_tr_sprite);
		window.draw(music_tr_sprite);
		window.display();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return false;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					return true;
				}

				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
				{
					selected_button--;
					if (selected_button < 1) {
						selected_button = num_buttons;
					}
				}
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					selected_button++;
					if (selected_button > num_buttons) {
						selected_button = 1;
					}
				}
				if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
					switch (selected_button)
					{
					case 1:
						if (sound_Volume >= 100) {
							sound_Volume = 100;
						}
						else {
							sound_Volume += 5;
						}
						explosion_sound.setVolume(sound_Volume);
						explosion_sound.play();
						break;
					case 2:
						if (music_Volume >= 100) {
							music_Volume = 100;
						}
						else {
							music_Volume += 5;
						}
						music.setVolume(music_Volume);
						break;
					}
				}
				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
					switch (selected_button)
					{
					case 1:
						if (sound_Volume <= 0) {
							sound_Volume = 0;
						}
						else {
							sound_Volume -= 5;
						}
						explosion_sound.setVolume(sound_Volume);
						explosion_sound.play();
						break;
					case 2:
						if (music_Volume <= 0) {
							music_Volume = 0;
						}
						else {
							music_Volume -= 5;
						}
						music.setVolume(music_Volume);
						break;
					}
				}
			}
		}
	}
}

bool ControlMenu(RenderWindow& window) {
	StateImage ControlState(false, "Control.png", 0, 0);
	window.clear();
	window.draw(ControlState.sprite);
	window.display();
	while (1) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return false;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					return true;
				}
			}
		}
	}
}

bool PauseMenu(bool& isPause, RenderWindow& window, Map& map, Items& items,
	Player& player, Bombs& bombs, Enemies& enemies, Music& music,
	Destructions& destructions, bool& isNextLevel, bool& MenuOpen)
{

	StateImage PauseState(true, "Pause.png", 0, 0);
	Image ButtonsImage;
	Texture ButtonsTexture;
	Sprite ContinueSprite, SettingsSprite, ControlSprite, MenuSprite;

	ButtonsImage.loadFromFile("images/PauseButtons.png");
	ButtonsImage.createMaskFromColor(Color(31, 139, 0));
	ButtonsTexture.loadFromImage(ButtonsImage);
	ContinueSprite.setTexture(ButtonsTexture);
	ContinueSprite.setTextureRect(IntRect(0, 0, 397, 81));
	ContinueSprite.setPosition(543, 327);
	SettingsSprite.setTexture(ButtonsTexture);
	SettingsSprite.setTextureRect(IntRect(0, 81, 397, 81));
	SettingsSprite.setPosition(543, 427);
	ControlSprite.setTexture(ButtonsTexture);
	ControlSprite.setTextureRect(IntRect(0, 162, 397, 81));
	ControlSprite.setPosition(543, 527);
	MenuSprite.setTexture(ButtonsTexture);
	MenuSprite.setTextureRect(IntRect(0, 243, 397, 81));
	MenuSprite.setPosition(543, 627);

	int selected_button = 0;
	int num_buttons = 4;
	int menuNum = 0;

	while (isPause) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return false;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					isPause = false;
					return true;

				}

				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
				{
					selected_button--;
					if (selected_button < 1) {
						selected_button = num_buttons;
					}
				}
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					selected_button++;
					if (selected_button > num_buttons) {
						selected_button = 1;
					}
				}
				if (event.key.code == sf::Keyboard::Enter) {
					menuNum = selected_button;
					switch (menuNum)
					{
					case 1: //continue
						isPause = false;
						return true;
						break;
					case 2: //settings
						if (!SettingsMenu(window, music)) {
							return false;
						}
						break;
					case 3: //control
						if (!ControlMenu(window)) {
							return false;
						}
						break;
					case 4: //menu
						MenuOpen = true;
						isPause = false;
						return true;
						break;
					default:
						break;
					}
				}
			}
		}

		window.clear();
		map.Draw(window);
		items.Draw(window);
		window.draw(player.sprite);


		bombs.Draw(window); //вклюает ExploseDraw
		enemies.Draw(window);
		destructions.Draw(0, window);

		window.draw(PauseState.sprite);
		ContinueSprite.setTextureRect(IntRect(0, 0, 397, 81));
		SettingsSprite.setTextureRect(IntRect(0, 81, 397, 81));
		ControlSprite.setTextureRect(IntRect(0, 162, 397, 81));
		MenuSprite.setTextureRect(IntRect(0, 243, 397, 81));
		switch (selected_button)
		{
		case 1:
			ContinueSprite.setTextureRect(IntRect(397, 0, 397, 81));
			break;
		case 2:
			SettingsSprite.setTextureRect(IntRect(397, 81, 397, 81));
			break;
		case 3:
			ControlSprite.setTextureRect(IntRect(397, 162, 397, 81));
			break;
		case 4:
			MenuSprite.setTextureRect(IntRect(397, 243, 397, 81));
		default:
			break;
		}
		window.draw(ContinueSprite);
		window.draw(SettingsSprite);
		window.draw(ControlSprite);
		window.draw(MenuSprite);
		window.display();

		if (Keyboard::isKeyPressed(Keyboard::N)) {
			isPause = false;
			isNextLevel = true;
			return true;
		}
	}
}

bool MainMenu(RenderWindow& window, bool& MenuOpen, bool& NewGame, Music& music, Cheat& cheat) {
	if (!MenuOpen) {
		return true;
	}
	music.openFromFile("music/gearhead.wav");
	music.setVolume(music_Volume);
	music.play();
	Font font;
	Text text;
	font.loadFromFile("AllStarResort.ttf");
	text = Text("Kevin MacLeod - Gearhead", font, 35);
	text.setFillColor(Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(960, 765);

	Texture BomberMan;
	BomberMan.loadFromFile("images/Menu_BomberMan.png");

	Sprite BomberMan_sprite(BomberMan);
	BomberMan_sprite.setPosition(517, 30);

	Image ButtonsImage;
	Texture ButtonsTexture;
	Sprite StartSprite, SettingsSprite, ControlSprite, ExitSprite;

	ButtonsImage.loadFromFile("images/MenuButtons.png");
	ButtonsImage.createMaskFromColor(Color(31, 139, 0));
	ButtonsTexture.loadFromImage(ButtonsImage);
	StartSprite.setTexture(ButtonsTexture);
	StartSprite.setPosition(543, 327);
	SettingsSprite.setTexture(ButtonsTexture);
	SettingsSprite.setPosition(543, 427);
	ControlSprite.setTexture(ButtonsTexture);
	ControlSprite.setPosition(543, 527);
	ExitSprite.setTexture(ButtonsTexture);
	ExitSprite.setPosition(543, 627);

	int menuNum = 0;
	int selected_button = 0;
	int num_buttons = 4;

	while (MenuOpen)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return false;
			}


			if (event.type == sf::Event::KeyPressed)
			{

				if (event.key.code == sf::Keyboard::C) {
					if (cheat.Input) {
						cheat.Input = false;
					}
					else {
						cheat.Input = true;
						cheat.exist = true;
					}
				}
				if (cheat.Input) {
					if (event.key.code == sf::Keyboard::L) {
						cheat.IncLevel();
					}
					if (event.key.code == sf::Keyboard::B) {
						cheat.IncBombs();
					}
					if (event.key.code == sf::Keyboard::R) {
						cheat.IncRadius();
					}
					if (event.key.code == sf::Keyboard::V) {
						cheat.IncSpeed();
					}
					if (event.key.code == sf::Keyboard::D) {
						cheat.IncDetonations();
					}
					if (event.key.code == sf::Keyboard::H) {
						cheat.IncLives();
					}
				}


				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
				{
					selected_button--;
					if (selected_button < 1) {
						selected_button = num_buttons;
					}
				}
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					selected_button++;
					if (selected_button > num_buttons) {
						selected_button = 1;
					}
				}
				if (event.key.code == sf::Keyboard::Enter) {
					menuNum = selected_button;
					switch (menuNum) {
					case 1: //start
						NewGame = true;
						MenuOpen = false;
						return true;
						break;
					case 2: //settings
						if (!SettingsMenu(window, music)) {
							return false;
						}
						break;
					case 3: //control
						if (!ControlMenu(window)) {
							return false;
						}
						break;
					case 4: //exit
						window.close();
						MenuOpen = false;
						return false;
					}
				}
			}
		}

		menuNum = 0;
		window.clear(Color(31, 139, 0));

		StartSprite.setTextureRect(IntRect(397, 0, 397, 81));
		SettingsSprite.setTextureRect(IntRect(397, 81, 397, 81));
		ControlSprite.setTextureRect(IntRect(397, 162, 397, 81));
		ExitSprite.setTextureRect(IntRect(397, 243, 397, 81));
		switch (selected_button)
		{
		case 1:
			StartSprite.setTextureRect(IntRect(0, 0, 397, 81));
			break;
		case 2:
			SettingsSprite.setTextureRect(IntRect(0, 81, 397, 81));
			break;
		case 3:
			ControlSprite.setTextureRect(IntRect(0, 162, 397, 81));
			break;
		case 4:
			ExitSprite.setTextureRect(IntRect(0, 243, 397, 81));
		default:
			break;
		}
		window.draw(BomberMan_sprite);
		window.draw(StartSprite);
		window.draw(SettingsSprite);
		window.draw(ControlSprite);
		window.draw(ExitSprite);

		window.draw(text);

		if (cheat.Input) {
			cheat.Draw(window);
		}

		//if (IntRect(672, 500, 144, 48).contains(Mouse::getPosition(window))) { Start_sprite.setColor(Color::Blue); menuNum = 1; }
		//if (IntRect(672, 600, 144, 48).contains(Mouse::getPosition(window))) { Exit_sprite.setColor(Color::Blue); menuNum = 2; }

		//if (Mouse::isButtonPressed(Mouse::Left))
		//{
		//	if (menuNum == 1) {
		//		MenuOpen = false;//если нажали первую кнопку, то выходим из меню 
		//	}
		//	if (menuNum == 2) { 
		//		window.close(); 
		//		MenuOpen = false; 
		//		return false;
		//	}
		//	/*if (menuNum == 2) { 
		//		window.display(); 
		//		while (!Keyboard::isKeyPressed(Keyboard::Escape));
		//	}*/
		//}

		window.display();
	}
	return true;
}