#include "Game.h"
#include <iostream>

void Game::initVar(int pAncho, int pAlto)
{
	this->ancho = pAncho;
	this->alto = pAlto;

	this->window = nullptr;

	this->tiempoPorFrame = 1.0f / 60.0f;

	
	this->sala = new Sala(0, 0, pAncho, pAlto, false);

	this->reloj.restart();
}

void Game::initWin()
{
	this->videoMode.height = (this->alto) * 32;
	this->videoMode.width = (this->ancho) * 32;
	this->window = new sf::RenderWindow(this->videoMode, "Gatuga Dungeons", sf::Style::Titlebar | sf::Style::Close /*se ve un titulo y un pulsador para cerrar*/); //window del juego pasara a tener ¡estas especificaciones
}

Game::Game(int pAncho, int pAlto)
{
	this->initVar(pAncho, pAlto);
	this->initWin();
}

Game::~Game()
{
	delete this->window;
	delete this->personaje;
	delete this->sala;
}



void Game::render()
{
	
	
	//renderizar
	this->window->display(); 
}

void Game::drawDungeon()
{
}

/*

void Game::drawDungeon()
{


	//limpiar
	this->window->clear();
	this->textura.loadFromFile("../recursos/Sprites/14-TileSets/Terrain (32x32).png");
	//dibujar
	for (int fila = 0; fila < this->alto; fila++)
	{
		for (int columna = 0; columna < this->ancho; columna++)
		{
			if (fila == 0 && columna ==0) {
				this->areaTile = sf::IntRect(32, 224, 32, 32);
			}
			else if (fila == 0 && columna == ancho-1) {
				this->areaTile = sf::IntRect(96, 224, 32, 32);
			}
			else if (fila == alto-1 && columna == ancho - 1) {
				this->areaTile = sf::IntRect(96, 288, 32, 32);
			}
			else if (fila == alto - 1 && columna == 0) {
				this->areaTile = sf::IntRect(32, 288, 32, 32);
			}
			else {
				if (fila == 0) {
					this->areaTile = sf::IntRect(64, 224, 32, 32);
				}
				else if (fila == alto-1) {
					this->areaTile = sf::IntRect(64, 288, 32, 32);
				}
				else if (columna == 0) {
					this->areaTile = sf::IntRect(32, 256, 32, 32);
				}
				else if (columna == ancho-1) {
					this->areaTile = sf::IntRect(96, 256, 32, 32);
				}
				else {
					this->areaTile = sf::IntRect(64, 256, 32, 32);
				}
			}
			this->sprite.setTextureRect(areaTile);
			// Establecer la posición del sprite en la cuadrícula
			this->sprite.setPosition(columna * 32, fila * 32);

			// Dibujar el sprite en la ventana
			this->window->draw(this->sprite);
		}
	}

}

*/

void Game::update()
{
	this->window->clear();
	//this->sala->drawDungeon(*this->window);
	//mover las funciones de personajes y personajes a sala
	this->personaje->draw(*this->window);
	this->pollEvent();
	if (this->reloj.getElapsedTime().asSeconds() >= this->tiempoPorFrame) {
		render();
		this->reloj.restart();
	}
	

}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}
void Game::pollEvent()
{
	while (this->window->pollEvent(this->ev)) {/*todos los eventos que ocurran se van guardando en ev, este bucle funciona mientras ev tenga eventos*/
		switch (this->ev.type) 
		{
		case sf::Event::Closed:

			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;	
		} 
		float deltaTime = reloj.restart().asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			std::cout<<deltaTime<<"\n";
			this->personaje->move(0.0f, -1 * deltaTime*1000);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->personaje->move(0.0f, 1 * deltaTime * 1000);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->personaje->move(-1 * deltaTime * 1000, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->personaje->move(1 * deltaTime * 1000, 0.0f);
		}
		


	}
}