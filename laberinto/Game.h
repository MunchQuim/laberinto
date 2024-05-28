#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Personaje.h"
#include "Sala.h"


class Game
{
private:
	//variables
	int ancho;
	int alto;

	sf::IntRect areaTile;

	float tiempoPorFrame; // 6 veces por segundo
	int selecCord[2];
	//float tiempoPorFrame;
	//ventana
	sf::RenderWindow* window;//esto es un puntero
	sf::VideoMode videoMode;
	sf::Event ev;


	sf::Texture textura;
	sf::Sprite sprite;

	sf::Clock reloj;

	//funciones
	void initVar(int pAncho, int pAlto);

	void initWin();

	Personaje* personaje; // Instancia del personaje
	Sala* sala;

public:
	//constructores
	Game(int pAncho, int pAlto);

	virtual ~Game();

	//funciones
	const bool isRunning() const;


	void update();
	void render();
	void drawDungeon();
	void pollEvent();

};