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
			view.zoom(1.0100f); //������������, ����������
			//view.zoom(1.0006f); //���� ����� ����������� ��������������
		}

		if (Keyboard::isKeyPressed(Keyboard::R)) {
			//view.setRotation(90);//����� �� ������ ������� ������
			view.rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
		}


		if (Keyboard::isKeyPressed(Keyboard::I)) {
			view.setSize(640, 480);//������������� ������ ������ (��� ��������)
		}

		
}
