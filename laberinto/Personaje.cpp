#include "Personaje.h"




Personaje::Personaje()
{
}

Personaje::Personaje(std::string nombre, int hp, int atq, int def, int x, int y, bool isAiControlled) {
	this->nombre = nombre;
	this->hp = hp;
	this->atq = atq;
	this->def = def;
	this->x = x;
	this->y = y;
	this->isAiControlled = isAiControlled;
};

Personaje::Personaje(std::string nombre, int hp, int atq, int def, bool isAiControlled) {
	this->nombre = nombre;
	this->hp = hp;
	this->atq = atq;
	this->def = def;
	this->isAiControlled = isAiControlled;
};

Personaje::Personaje(std::string nombre, int hp, int atq, int def, int x, int y, bool isAiControlled, std::string texturaPath)
{
	this->nombre = nombre;
	this->hp = hp;
	this->atq = atq;
	this->def = def;
	this->x = x;
	this->y = y;
	this->isAiControlled = isAiControlled;

	this->textura.loadFromFile(texturaPath);
	this->sprite.setTexture(this->textura);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 192, 192));
	this->sprite.setPosition(120, 120);
}

int Personaje::getHp()
{
	return this->hp;
}

int Personaje::getAtq()
{
	return this->atq;
}

int Personaje::getDef()
{
	return this->def;
}

float Personaje::getX()
{
	return this->x;
}

float Personaje::getY()
{
	return this->y;
}

int Personaje::getVel()
{
	return this->vel;
}



void Personaje::setHp(int hp)
{
	this->hp = hp;
}

void Personaje::setAtq(int atq)
{
	this->atq = atq;
}

void Personaje::setDef(int def)
{
	this->def = def;
}

void Personaje::setX(float x)
{
	this->x = x;
}

void Personaje::setY(float y)
{
	this->y = y;
}

void Personaje::setVel(int vel)
{
	this->vel = vel;
}



int Personaje::atacar(sf::RenderWindow& window)
{
    reloj.restart();
    std::string barra[] = { "\033[31m", "\033[33m", "\033[92m", "\033[32m", "\033[34m" };
    const std::string barra2[] = { "\033[31m", "\033[33m", "\033[92m", "\033[32m", "\033[34m" };
    int minimo = barra2[0].length();
    
    if (isAiControlled) {
        int contador = 125;
        while (true) {
            if (reloj.getElapsedTime().asMilliseconds() > 10) {
                std::cout << "\033[0m\n";
                for (std::string& elemento : barra) {
                    if (elemento.length() < minimo + 5) {
                        elemento += "|";
                        contador -= 3;
                        break;
                    }
                }

                // Mueve el cursor al inicio
                std::cout << "\033[H\033[J"; // Clear screen and move cursor to top-left
                std::cout << nombre << " te está atacando" << ", Defiendete\n";
                std::cout << barra[0] << " " << barra[1] << " " << barra[2] << " " << barra[3] << " " << barra[4] << "\n";

                reloj.restart();
            }


            // Verificar si se ha pulsado la tecla de espacio usando SFML
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    int daño = (contador * this->atq) / 100;
                    std::cout << "\033[0m\n";
                    return daño;
                }
            }
            if (barra[4].length() >= minimo + 5) {
                for (int i = 0; i < 5; ++i) {
                    barra[i] = barra2[i];
                }
                contador = 125;
            }
            Sleep(1);
        }
    }
    else {
        int contador = 0;
        while (true) {
            if (reloj.getElapsedTime().asMilliseconds() > 10) {
                std::cout << "\033[0m\n";
                for (std::string& elemento : barra) {
                    if (elemento.length() < minimo + 5) {
                        elemento += "|";
                        contador += 5;
                        break;
                    }
                }

                // Mueve el cursor al inicio
                std::cout << "\033[H\033[J"; // Clear screen and move cursor to top-left
                std::cout << nombre << " está atacando" << "\n";
                std::cout << barra[0] << " " << barra[1] << " " << barra[2] << " " << barra[3] << " " << barra[4] << "\n";

                reloj.restart();
            }


            // Verificar si se ha pulsado la tecla de espacio usando SFML
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    int daño = (contador * this->atq) / 100;
                    std::cout << "\033[0m\n";
                    return daño;
                }
            }
            if (barra[4].length() >= minimo + 5) {
                for (int i = 0; i < 5; ++i) {
                    barra[i] = barra2[i];
                }
                contador = 0;
            }
            Sleep(1);
        }
    }
 
}

int  Personaje::escogerAtaque(sf::RenderWindow& window) {
    return this->atacar(window);
}


//deprecados
void Personaje::defender()
{

}

void Personaje::move(float x, float y)
{
	this->sprite.move(x, y);
}

void Personaje::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

