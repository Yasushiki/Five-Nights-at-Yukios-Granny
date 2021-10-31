#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "avo.hpp"

//　テクスチャロード
template <typename T>
bool testLoad(T& file, std::string path) {
	if(!file.loadFromFile(path)) {
		return EXIT_FAILURE;
	}
}


//　時間フォーマット
std::string getTime(int tempo) {
	
	int hora = tempo / 60;

	tempo -= 60 * hora;

	std::string horaStr = hora > 0 ? "0" + std::to_string(hora - 1) : "23";
	std::string timeStr = tempo > 9 ? std::to_string(tempo) : "0" + std::to_string(tempo);

	return horaStr + ":" + timeStr;

}


bool mudou(int valorIni, int valorAtu) {
	if(valorIni != valorAtu) {
		return true;
	} else {
		return false;
	}
}

int main() {

	sf::RenderWindow window(sf::VideoMode(1024,512), "Five nights at Yukio's granny");

	//　フォントとテキスト
	sf::Font font;
	testLoad(font, "resources/fonte/fonte3.ttf");

	sf::Text hour;
	hour.setFont(font);
	hour.setString("00:00");
	hour.setCharacterSize(75);
	hour.setFillColor(sf::Color(49, 48, 97, 255));
	hour.setPosition(373.0f, 210.0f);


	//　テクスチャとスプライト
	sf::Texture backgroundTex;
	testLoad(backgroundTex, "resources/images/background.png");
	sf::Sprite backgroundSpr(backgroundTex);

	sf::Texture celDTex;
	testLoad(celDTex, "resources/images/celularD.png");
	
	sf::Texture celLTex;
	testLoad(celLTex, "resources/images/celularL.png");

	sf::Sprite celularSpr;


	//　音
	//sf::SoundBuffer portaAvoBuffer;
	//testLoad(portaAvoBuffer, "resources/audio/porta.wav");
	//sf::Sound portaAvo; 
	//portaAvo.setBuffer(portaAvoBuffer);
	sf::Music portaAvo;
	if(!portaAvo.openFromFile("resources/audio/porta.wav")) {
		return EXIT_FAILURE;
	}


	//　ゲーム変数
	bool acordado = true;
	bool avoAcordado = false;

	int level = 5;
	int horaIni = 0;



	//　時間
	sf::Clock clock;


	//　メインループ　//
	while(window.isOpen()) {

		//　経過時間
		sf::Time tempo;
		tempo = clock.getElapsedTime();
		int hora = static_cast<int>(tempo.asSeconds() + 0.5f);

		//　時間文字列をセット
		hour.setString(getTime(hora));


		//　イベント処理
		sf::Event event;
		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//　寝る
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			acordado = false;
		} else {
			acordado = true;
		}

		//　携帯スプライト変更
		if(acordado) {
			celularSpr.setTexture(celLTex);
		} else {
			celularSpr.setTexture(celDTex);
		}


		if((mudou(horaIni, hora)) && (hora == 20)) {
			horaIni = hora;
			avoAcordado = true;
			portaAvo.play();
		}

		if(avoAcordado) {
			if(mudou(horaIni, hora)) {
				horaIni = hora;

				if(hora % 10 == 0) {
					criarAvo(level);
				}
			}
		}

		window.clear();
		window.draw(backgroundSpr);
		window.draw(celularSpr);
		window.draw(hour);
		window.display();

	}

	return 0;
}