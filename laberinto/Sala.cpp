#include "Sala.h"

Sala::Sala()
{
}

Sala::Sala(int x, int y, int ancho, int alto, bool clear)
{
	this->x = x;
	this->y = y;

	this->ancho = ancho;
	this->alto = alto;
	this->clear = clear;

	this->textura.loadFromFile("../recursos/Sprites/14-TileSets/Terrain (32x32).png");
	this->sprite.setTexture(textura);
	this->sprite.setTextureRect(sf::IntRect(64, 256, 32, 32));

}

void Sala::setX(int x)
{
	this->x = x;
}

void Sala::setY(int y)
{
	this->y = y;
}

void Sala::setClear(bool bol)
{
	this->clear = bol;
}

void Sala::setAlto(int alto)
{
	this->alto = alto;
}

void Sala::setAncho(int ancho)
{
	this->ancho = ancho;
}

void Sala::setN(bool bol)
{
	this->n = bol;
}

void Sala::setE(bool bol)
{
	this->e = bol;
}

void Sala::setS(bool bol)
{
	this->s = bol;
}

void Sala::setW(bool bol)
{
	w = bol;

}

int Sala::getX()
{
	return x;
}

int Sala::getY()
{
	return y;
}

bool Sala::getClear()
{
	return clear;
}

int Sala::getAlto()
{
	return alto;
}

int Sala::getAncho()
{
	return ancho;
}

sf::Sprite Sala::getSprite()
{
	return sprite;
}

bool Sala::getN()
{
	return n;
}

bool Sala::getE()
{
	return e;
}

bool Sala::getS()
{
	return s;
}

bool Sala::getW()
{
	return w;
}

void Sala::drawDungeon(sf::RenderWindow& window)
{

	this->textura.loadFromFile("../recursos/Sprites/14-TileSets/Terrain (32x32).png");
	//dibujar
	for (int fila = 0; fila < this->alto; fila++)
	{
		for (int columna = 0; columna < this->ancho; columna++)
		{
			if (fila == 0 && columna == 0) {
				this->sprite.setTextureRect(sf::IntRect(32, 224, 32, 32));
			}
			else if (fila == 0 && columna == ancho - 1) {
				this->sprite.setTextureRect(sf::IntRect(96, 224, 32, 32));
			}
			else if (fila == alto - 1 && columna == ancho - 1) {
				this->sprite.setTextureRect(sf::IntRect(96, 288, 32, 32));
			}
			else if (fila == alto - 1 && columna == 0) {
				this->sprite.setTextureRect(sf::IntRect(32, 288, 32, 32));
			}
			else {
				if (fila == 0) {
					this->sprite.setTextureRect(sf::IntRect(64, 224, 32, 32));
				}
				else if (fila == alto - 1) {
					this->sprite.setTextureRect(sf::IntRect(64, 288, 32, 32));
				}
				else if (columna == 0) {
					this->sprite.setTextureRect(sf::IntRect(32, 256, 32, 32));
				}
				else if (columna == ancho - 1) {
					this->sprite.setTextureRect(sf::IntRect(96, 256, 32, 32));
				}
				else {
					this->sprite.setTextureRect(sf::IntRect(64, 256, 32, 32));
				}
			}
			// Establecer la posición del sprite en la cuadrícula
			this->sprite.setPosition(columna * 32, fila * 32);

			// Dibujar el sprite en la ventana
			window.draw(this->sprite);
		}
	}

}
