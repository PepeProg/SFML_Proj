#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "map.h"
#include "view.h"

using namespace sf;

class Object {
public:
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y, width, height, dx, dy, speed, scale;
	bool next = false;
	int score = 0;
	enum direction {
		left = 0,
		right,
		up,
		down,
		cons
	}; direction dir;

	Object(String File_Name, float x, float y, float image_x, float image_y, float width, float height, float scale) {
		this->image.loadFromFile("images/" + File_Name);
		this->texture.loadFromImage(this->image);
		this->sprite.setTexture(this->texture);
		this->x = x; this->y = y; this->width = width, this->height = height;
		this->sprite.setTextureRect(IntRect(image_x, image_y, width, height));
		this->scale = scale;
		this->sprite.setScale(this->scale, this->scale);
	}

	void update(float time) {
		switch (this->dir) {
		case left:
			this->dx = -this->speed;
			this->dy = 0;
			break;
		case right:
			this->dx = this->speed;
			this->dy = 0;
			break;
		case up:
			this->dx = 0;
			this->dy = -this->speed;
			break;
		case down:
			this->dx = 0;
			this->dy = this->speed;
			break;
		case cons:
			this->dx = 0;
			this->dy = 0;
			break;
		}
	
	
		this->x += this->dx * time;
		this->y += this->dy * time;
		
		speed = 0;

		this->sprite.setPosition(this->x, this->y);map_interaction();
	}

	void map_interaction() {
		for (int i = this->y / 32; i < (this->y + this->height * this->scale) / 32; i++) {
			for (int j = (this->x / 32); j < (this->x + this->width * this->scale) / 32; j++)
				if (TileMap[i][j] == '0' || TileMap[i][j] == 's' || TileMap[i][j] == 'f' || TileMap[i][j] == 'h') {

					if (this->dx > 0)
						this->x = j * 32 - this->width * this->scale;
					if (this->dx < 0)
						this->x = j * 32 + 32;
					if (this->dy > 0)
						this->y = i * 32 - this->height * this->scale;
					if (this->dy < 0)
						this->y = i * 32 + 32;

					if (TileMap[i][j] == 's' || TileMap[i][j] == 'f' || TileMap[i][j] == 'h') {
						TileMap[i][j] = ' ';
						this->score++;
					}
				}
					
		}
	
	}
};


int main() {

	RenderWindow window(VideoMode(1000, 800), "SFMLworks");

	Font first_font;
	first_font.loadFromFile("fonts/CyrilicOld.ttf");
	Text text("", first_font, 20);
	text.setFillColor(Color::Red);
	text.setStyle(Text::Bold | Text::Underlined);

	Object player("move.png", 180, 180, 150, 150, 206, 270, 0.3);

	Clock clock;

	float CurrentFrame = 0;
	bool is_move = false;
	float mouse_x, mouse_y;
	while (window.isOpen())

	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 100;

		Event event; 

		Vector2i MoveMouse = Mouse::getPosition(window);
		Vector2f GamePos = window.mapPixelToCoords(MoveMouse);

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					if (player.sprite.getGlobalBounds().contains(GamePos)) {

						mouse_x = GamePos.x;
						mouse_y = GamePos.y;

						is_move = true;
					}
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					is_move = false;
		}
		if (is_move) {
			player.x += GamePos.x - mouse_x;
			mouse_x = GamePos.x;
			player.y += GamePos.y - mouse_y;
			mouse_y = GamePos.y;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			CurrentFrame += 0.0008 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			player.dir = Object::left;
			player.speed = 0.05;
			player.sprite.setTextureRect(IntRect(233 * int(CurrentFrame), 566, 196, 830 - 566));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			CurrentFrame += 0.0008 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			player.dir = Object::right;
			player.speed = 0.05;
			player.sprite.setTextureRect(IntRect(233 * int(CurrentFrame), 866, 206, 830 - 566));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			CurrentFrame += 0.0008 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			player.dir = Object::down;
			player.speed = 0.05;
			player.sprite.setTextureRect(IntRect(233 * int(CurrentFrame), 0, 206, 270));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up)) {
			CurrentFrame += 0.0008 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			player.dir = Object::up;
			player.speed = 0.05;
			player.sprite.setTextureRect(IntRect(233 * int(CurrentFrame), 292, 206, 270));
		}
		else {
			player.sprite.setTextureRect(IntRect(0, 0, 206, 270));
			player.dir = Object::cons;
		}
		setView(player.x, player.y);

		Vector2i MousePos = Mouse::getPosition(window);
		

		Texture map_texture;
		map_texture.loadFromFile("images/new_map.png");
		Sprite map_sprite;
		map_sprite.setTexture(map_texture);

		if (MousePos.x < 3)
			view.move(-0.2 * time, 0);
		if (MousePos.x > window.getSize().x - 3)
			view.move(0.2 * time, 0);
		if (MousePos.y < 3)
			view.move(0, -0.2 * time);
		if (MousePos.y > window.getSize().y - 3)
			view.move(0, 0.2 * time);
		window.setView(view);
		
		window.clear();

		float y_arr[HEIGHT_MAP];
		y_arr[0] = 0;
		float x_arr[WIDTH_MAP];
		x_arr[0] = 0;
		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == '0')
					map_sprite.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 's')
					map_sprite.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == ' ')
					map_sprite.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 'f')
					map_sprite.setTextureRect(IntRect(96, 0, 32, 32));
				if (TileMap[i][j] == 'h')
					map_sprite.setTextureRect(IntRect(128, 0, 32, 32));

				float scale_y = 1, scale_x = 1;
				if (TileMap[i][j] != '0' && TileMap[i][j] != ' ') {
					scale_y = 1 - (player.y - map_sprite.getPosition().y) / 1000;
					scale_x = 1 - (player.x - map_sprite.getPosition().x) / 1000;
				}
				
				map_sprite.setScale(scale_x, scale_y);

				if (!j)
					y_arr[i] = map_sprite.getGlobalBounds().height;
				if (!i)
					x_arr[j] = map_sprite.getGlobalBounds().width;

				float map_y = 0;
				for (int a = 0; a < i; a++) 
					map_y += y_arr[a];

				float map_x = 0;
				for (int b = 0; b < j; b++)
					map_x += x_arr[b];

				map_sprite.setPosition(map_x, map_y);
				window.draw(map_sprite);
			}
		}

		player.update(time);

		move_view(time);

		std::ostringstream ScoreStr;
		ScoreStr << player.score;
		text.setString("gay" + ScoreStr.str());
		text.setPosition(view.getCenter().x, view.getCenter().y - 200);
		
		window.draw(player.sprite);  
		window.draw(text);
		window.display();   

	}

	return 0;

}