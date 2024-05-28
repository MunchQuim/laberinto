#pragma once
#include "Personaje.h"
#include <iostream>
class Boss : public Personaje {

public:
	Boss();
	Boss(std::string nombre, int hp, int atq, int def, int x, int y, bool isAiControlled, std::string texturaPath);
	Boss(std::string nombre, int hp, int atq, int def, bool isAiControlled);

	int ataqueEspecial(sf::RenderWindow& window);
	int ataqueFuego(sf::RenderWindow& window);
	int escogerAtaque(sf::RenderWindow& window) override;

	bool getTieneEspecial();
	bool getTieneFuego();

	void setTieneEspecial(bool cond);
	void setTieneFuego(bool cond);

private:
	bool tieneEspecial = true;
	bool tieneFuego = true;
};