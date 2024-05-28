#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <conio.h> // Para kbhit() y getch() en Windows
#include "windows.h"

class Personaje {
protected:
	std::string nombre;
	int hp;
	int atq;
	int def;
	int x;
	int y;
	bool isAiControlled;

	sf::Clock reloj;

	//deprecados
	int vel;
	sf::Texture textura;
	sf::Sprite sprite;
public:
	Personaje();

	Personaje(std::string nombre, int hp, int atq, int def, int x, int y, bool isAiControlled);

	Personaje(std::string nombre, int hp, int atq, int def, bool isAiControlled);

	Personaje(std::string nombre, int hp, int atq, int def,int x, int y, bool isAiControlled, std::string texturaPath);

	int getHp();
	int getAtq();
	int getDef();
	float getX();
	float getY();

	void setHp(int hp);
	void setAtq(int atq);
	void setDef(int def);
	void setX(float x);
	void setY(float y);

	virtual int escogerAtaque(sf::RenderWindow& window);
	int atacar(sf::RenderWindow& window);

	//deprecados
	int getVel();
	void defender();
	void setVel(int vel);
	void move(float x, float y);
	void draw(sf::RenderWindow& window);
};