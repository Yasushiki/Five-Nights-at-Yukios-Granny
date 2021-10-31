#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

//�@�e�N�X�`�����[�h
template <typename T>
bool testLoad(T& file, std::string path) {
	if(!file.loadFromFile(path)) {
		return EXIT_FAILURE;
	}
}


//�@���ԃt�H�[�}�b�g
std::string getTime(int time) {
	
	int hora = time / 60;

	time -= 60 * hora;

	std::string horaStr = hora > 0 ? "0" + std::to_string(hora - 1) : "23";
	std::string timeStr = time > 9 ? std::to_string(time) : "0" + std::to_string(time);

	return horaStr + ":" + timeStr;

}


int main() {

	sf::RenderWindow window(sf::VideoMode(1024,512), "Five nights at Yukio's granny");

	//�@�t�H���g�ƃe�L�X�g
	sf::Font font;
	testLoad(font, "resources/fonte/fonte3.ttf");

	sf::Text hour;
	hour.setFont(font);
	hour.setString("00:00");
	hour.setCharacterSize(75);
	hour.setFillColor(sf::Color(49, 48, 97, 255));
	hour.setPosition(373.0f, 210.0f);


	//�@�e�N�X�`���ƃX�v���C�g
	sf::Texture backgroundTex;
	testLoad(backgroundTex, "resources/images/background.png");
	sf::Sprite backgroundSpr(backgroundTex);

	sf::Texture celDTex;
	testLoad(celDTex, "resources/images/celularD.png");
	
	sf::Texture celLTex;
	testLoad(celLTex, "resources/images/celularL.png");

	sf::Sprite celularSpr;


	//�@�Q�[���ϐ�
	bool acordado = true;
	bool avoAcordado = false;

	int level = 1;




	//�@����
	sf::Clock clock;


	//�@���C�����[�v�@//
	while(window.isOpen()) {

		//�@�o�ߎ���
		sf::Time time;
		time = clock.getElapsedTime();

		//�@���ԕ�������Z�b�g
		hour.setString(getTime(static_cast<int>(time.asSeconds() + 0.5f)));


		//�@�C�x���g����
		sf::Event event;
		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//�@�Q��
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			acordado = false;
		} else {
			acordado = true;
		}

		//�@�g�уX�v���C�g�ύX
		if(acordado) {
			celularSpr.setTexture(celLTex);
		} else {
			celularSpr.setTexture(celDTex);
		}


		window.clear();
		window.draw(backgroundSpr);
		window.draw(celularSpr);
		window.draw(hour);
		window.display();

	}

	return 0;
}