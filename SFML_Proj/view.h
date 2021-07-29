#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View setView(float x, float y) {
	/*if (x < 400) x = 400;
	if (y < 450) y = 450;
	if (x > 800) x = 800;
	if (y > 500) y = 500;
	*/
	view.setCenter(x + 50, y);
	return view;
}

void move_view(float time) {
	time /= 1.5;
	if (Keyboard::isKeyPressed(Keyboard::A))
		view.move(-0.1 * time, 0);
	if (Keyboard::isKeyPressed(Keyboard::D))
		view.move(0.1 * time, 0);
	if (Keyboard::isKeyPressed(Keyboard::S))
		view.move(0, 0.1 * time);
	if (Keyboard::isKeyPressed(Keyboard::W))
		view.move(0, -0.1 * time);



		if (Keyboard::isKeyPressed(Keyboard::U)) {
			view.zoom(1.0100f); //масштабируем, уменьшение
			//view.zoom(1.0006f); //тоже самое помедленнее соответственно
		}

		if (Keyboard::isKeyPressed(Keyboard::R)) {
			//view.setRotation(90);//сразу же задает поворот камере
			view.rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
		}


		if (Keyboard::isKeyPressed(Keyboard::I)) {
			view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
		}

		
}
