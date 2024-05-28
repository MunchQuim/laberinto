#include "Boss.h"

Boss::Boss(std::string nombre, int hp, int atq, int def, int x, int y, bool isAiControlled, std::string texturaPath) : Personaje (nombre, hp, atq, def,x,y, isAiControlled,texturaPath)
{

}
Boss::Boss(std::string nombre, int hp, int atq, int def, bool isAiControlled) : Personaje(nombre, hp, atq, def, isAiControlled) {

}
bool Boss::getTieneEspecial() {
    return tieneEspecial;
}
bool Boss::getTieneFuego()
{
    return tieneFuego;
}
void Boss::setTieneEspecial(bool cond) {
    tieneEspecial = cond;
}

void Boss::setTieneFuego(bool cond)
{
    tieneFuego = cond;
}

int Boss::ataqueEspecial(sf::RenderWindow& window)
{
    reloj.restart();
    std::string barra[] = { "\033[31m", "\033[33m", "\033[92m", "\033[32m", "\033[34m" };
    const std::string barra2[] = { "\033[31m", "\033[33m", "\033[92m", "\033[32m", "\033[34m" };
    int minimo = barra2[0].length();

    int contador = 250;
    while (true) {
        if (reloj.getElapsedTime().asMilliseconds() > 10) {
            std::cout << "\033[0m\n";
            for (std::string& elemento : barra) {
                if (elemento.length() < minimo + 5) {
                    elemento += "|";
                    contador -= 6;
                    break;
                }
            }

            // Mueve el cursor al inicio
            std::cout << "\033[H\033[J"; // Clear screen and move cursor to top-left
            std::cout << nombre << " te está atacando con un ataque MUY especial y UNICO, Defiendete\n";
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
                setTieneEspecial(false);
                return daño;
            }
        }
        if (barra[4].length() >= minimo + 5) {
            for (int i = 0; i < 5; ++i) {
                barra[i] = barra2[i];
            }
            contador = 250;
        }
        Sleep(1);
    }
}

int Boss::ataqueFuego(sf::RenderWindow& window)
{
    reloj.restart();
    std::string barra[] = { "\033[31m", "\033[33m", "\033[92m", "\033[32m", "\033[34m" };
    const std::string barra2[] = { "\033[31m", "\033[33m", "\033[92m", "\033[32m", "\033[34m" };
    int minimo = barra2[0].length();

    int contador = 250;
    while (true) {
        if (reloj.getElapsedTime().asMilliseconds() > 10) {
            std::cout << "\033[0m\n";
            for (std::string& elemento : barra) {
                if (elemento.length() < minimo + 5) {
                    elemento += "|";
                    contador -= 6;
                    break;
                }
            }

            // Mueve el cursor al inicio
            std::cout << "\033[H\033[J"; // Clear screen and move cursor to top-left
            std::cout << nombre << " te está atacando con un ataque MUY FOGOSO y UNICO, Defiendete\n";
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
                int daño = (contador * this->atq*2) / 100;
                std::cout << "\033[0m\n";
                setTieneFuego(false);
                return daño;
            }
        }
        if (barra[4].length() >= minimo + 5) {
            for (int i = 0; i < 5; ++i) {
                barra[i] = barra2[i];
            }
            contador = 250;
        }
        Sleep(1);
    }
}

int Boss::escogerAtaque(sf::RenderWindow& window)
{
    int num = trunc(rand() % 6); //3 ataques
    if (num == 5 && tieneEspecial) {
        return this->ataqueEspecial(window);
    }
    else if (num == 4 && tieneFuego) {
        return this->ataqueFuego(window);
    }
    else {
        return this->atacar(window);
    }
}

