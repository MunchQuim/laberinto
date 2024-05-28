#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Sala {
private:
	int x;
	int y;
	bool clear;
	int ancho; // pixeles/32
	int alto; // pixeles/32

	sf::Texture textura;
	sf::Sprite sprite;



	bool n;
	bool e;
	bool s;
	bool w;

public:
	Sala();
	Sala(int x, int y, int ancho, int alto, bool clear);
	
	void setX(int x);
	void setY(int y);
	void setClear(bool bol);
	void setAlto(int alto);
	void setAncho(int ancho);
	void setN(bool bol);
	void setE(bool bol);
	void setS(bool bol);
	void setW(bool bol);
	
	int getX();
	int getY();
	bool getClear();
	int getAlto();
	int getAncho();
	sf::Sprite getSprite();

	bool getN();
	bool getE();
	bool getS();
	bool getW();


	void drawDungeon(sf::RenderWindow& window);

};