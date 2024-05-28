// laberinto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <random>
#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>

using namespace ::std;

const int anchoMap = 5;
const int altoMap = 10;

void imprimeMapaDebug(int pArray[anchoMap][altoMap]) {
	//system("cls");
	for (int i = 0; i < altoMap; i++) {
		for (int j = 0; j < anchoMap; j++) {
			cout << "[" << pArray[j][i] << "]";
		}
		cout << '\n';
	}

}

void obtenerMapa(int(&pArray)[anchoMap][altoMap]) {
	// mapa 8 inicio, 9 guarida, 1 mazmorra principal, 2 mazmorra secundaria, 3 botin.


	int aPj[2] = { trunc(rand() % (anchoMap)),0 };//0-ancho
	int aGuarida[2] = { trunc(rand() % (anchoMap)), altoMap-1 };
	
	//posiciono la guarida y el jugador en el mapa
	for (int i = 0; i < altoMap; i++) {

		for (int j = 0; j < anchoMap; j++) {
			if (aPj[0] == j && i == 0) {
				pArray[j][i] = 8;
			}
			else if (aGuarida[0] == j && i == (altoMap - 1)) {
				pArray[j][i] = 9;
			}
			else {
				pArray[j][i] = 0;
			}
		}
	}

	//creo una ruta entre la guarida y el jugador
	struct {
		int contador = 0;
		int dir = 0;//0-1-2-3 up-right-down-left
		vector<vector<vector<int>>> histPos;//{[[x,y],[0,1,2,3],...],....} [x,y][escogidos][posibles]
		
		int x = 0; //x,y 
		int y = 0;
		void escDir() {
			int size = this->histPos.back()[2].size();
			if (size > 0) {
				this-> dir = histPos.back()[2][trunc(rand() % size)];

				this->histPos.back()[1].push_back(this->dir);
			}
			else {
				this->dir = 4;
			}

		};

		void quitarPosible(int pNum) {
			this->histPos.back()[2].erase(remove(this->histPos.back()[2].begin(), this->histPos.back()[2].end(), pNum), this->histPos.back()[2].end());
		};

		void imprHist() {
			cout << "\n";
			for (int i = 0; i < this->histPos.size(); i++) {
				cout << "x:" << this->histPos[i][0][0] << "y:" << this->histPos[i][0][1] << "\n";
			}
		};

	} tile; 

	tile.x = aPj[0];
	tile.y = aPj[1];

	//vector<vector<int>> 

	int contaCasillas = 0;
	int maxRecorrido = altoMap+anchoMap;
	cout << "\n--------\n";
	imprimeMapaDebug(pArray);
	// crear mapa básico // 8-1-1-1-1-9
	while (!(tile.x == aGuarida[0] && tile.y == aGuarida[1])) {

		if (!(tile.histPos.size() > 0)) {
			tile.histPos.push_back({ {tile.x,tile.y},{},{0,1,2,3} }); //guardo su primera posicion 
		}
		else if (!(tile.histPos.back()[0][0] == tile.x && tile.histPos.back()[0][1] == tile.y)) {
			tile.histPos.push_back({ {tile.x,tile.y},{},{0,1,2,3} });//si la ultima no es igual a su posicion añadela
		}

		
		//retirar lugares imposibles
		
		if ((tile.y == 0 || (pArray[tile.x][tile.y-1] > 0 && pArray[tile.x][tile.y - 1] != 9)) || (find(tile.histPos.back()[1].begin(), tile.histPos.back()[1].end(), 0) != tile.histPos.back()[1].end()) ) {// si es y = 0 O hay un valor que no sea 9, o ya ha sido escogido se prohibe
			tile.quitarPosible(0);
			//cout << "imposible ir arriba\n";
		}
		if ((tile.x == anchoMap-1 || (pArray[tile.x + 1][tile.y] > 0 && pArray[tile.x+1][tile.y] != 9)) || (find(tile.histPos.back()[1].begin(), tile.histPos.back()[1].end(), 1) != tile.histPos.back()[1].end())) { //si estoy en el borde derecho O hay una valor que no sea... prohibido
			tile.quitarPosible(1);
			//cout << "imposible ir derecha\n";
		}
		if ((tile.y == altoMap-1 || (pArray[tile.x][tile.y + 1] > 0 && pArray[tile.x][tile.y + 1] != 9)) || (find(tile.histPos.back()[1].begin(), tile.histPos.back()[1].end(), 2) != tile.histPos.back()[1].end())) {
			tile.quitarPosible(2);
			//cout << "imposible ir abajo\n";
		}
		if ((tile.x == 0 || (pArray[tile.x - 1][tile.y] > 0 && pArray[tile.x - 1][tile.y] != 9)) || (find(tile.histPos.back()[1].begin(), tile.histPos.back()[1].end(), 3) != tile.histPos.back()[1].end()) ) {
			tile.quitarPosible(3);
			//cout << "imposible ir izquierda\n";
		}

		tile.escDir();// escoge una direccion entre las posibles y la añade a la lista de direcciones escogidas


		
		if (tile.dir == 4 || contaCasillas >= maxRecorrido) {
			// no hay direcciones disponibles
			//el regresa a la casilla anterior y le prohibo que pueda ir alli
			//cout << "retrocediendo\n";
			pArray[tile.x][tile.y] = 0;
			tile.x = tile.histPos[tile.histPos.size() - 2][0][0];
			tile.y = tile.histPos[tile.histPos.size() - 2][0][1];
			contaCasillas--;
			tile.histPos.pop_back();
		}
		else {
			contaCasillas++;
			switch (tile.dir)
			{
			case 0:
				tile.y--;
				//cout << "moviendo arriba\n";
				break;
			case 1:
				tile.x++; 
				//cout << "moviendo derecha\n";
				break;
			case 2:
				tile.y++;
				//cout << "moviendo abajo\n";
				break;
			case 3:
				tile.x--;
				//cout << "moviendo izquierda\n";
				break;
			default:
				break;
			}
			//cout << "moviendo a x:" << tile.x << " y:" << tile.y << "\n";

			if (!(tile.x == aGuarida[0] && tile.y == aGuarida[1])) {

				pArray[tile.x][tile.y] = 1;

			}
			else {
				tile.histPos.push_back({ {tile.x,tile.y},{},{0,1,2,3} });
				//system("cls");
				cout << "llegado a guarida\n";
				
			}
		}
		//imprimeMapaDebug(pArray);
		//Sleep(100);
		//cout << "\n----------------------------------\n";
		
		
	}
	cout << "\n--------\n";
	imprimeMapaDebug(pArray);
	// añadir pasillos pequeños // 1-2-3
	int maxMazmorras = 3;
	int mazmorras = 0;
	while (mazmorras <maxMazmorras) {
		//escoge una posicion posible en todo el recorrido
		int index = trunc(rand() % (tile.histPos.size() - 2)) + 1;  //deberia recoger un indice entre el 1 y el penultimo
		//por cada dirección
		int x = tile.histPos[index][0][0]; 
		int y = tile.histPos[index][0][1];
		bool pendiente = true;
		int numRan = trunc(rand() % 4)+1;
		int numRan2 = trunc(rand() % 3);
		/*
		switch (numRan2)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				default:
					break;
				}
		*/
		switch (numRan)
		{

		case 1:
			if (y > 0 && pendiente) {//arriba
				/*
				if (pArray[x][y - 1] == 0 && pArray[x][y - 2] == 0) {
					pArray[x][y - 1] = 2;
					pArray[x][y - 2] = 3;
					pendiente = !pendiente;
				}
				*/

				if (pArray[x][y - 1] == 0) {

					switch (numRan2)
					{
					case 0:
						if (pArray[x][y - 2] == 0 && y > 1) {
							pArray[x][y - 1] = 2;
							pArray[x][y - 2] = 3;
							pendiente = !pendiente;
						}
						break;
					case 1:
						if (pArray[x - 1][y - 1] == 0 && x > 0) {
							pArray[x][y - 1] = 2;
							pArray[x - 1][y - 1] = 3;
							pendiente = !pendiente;
						}
						break;
					case 2:
						if (pArray[x + 1][y - 1] == 0 && x < anchoMap) {
							pArray[x][y - 1] = 2;
							pArray[x + 1][y - 1] = 3;
							pendiente = !pendiente;
						}
						break;
					default:
						break;
					}
				}
			}
			break;
		case 2:
			if (x < anchoMap - 1 && pendiente) {//derecha
				/*
				if (pArray[x+1][y] == 0 && pArray[x+2][y] == 0) {
					pArray[x+1][y] = 2;
					pArray[x+2][y] = 3;
					pendiente = !pendiente;
				}
				*/

				if (pArray[x + 1][y] == 0) {
					switch (numRan2)
					{
					case 0:
						if (pArray[x + 1][y - 1] == 0 && y > 0) {//arriba
							pArray[x + 1][y] = 2;
							pArray[x + 1][y - 1] = 3;
							pendiente = !pendiente;
						}
						break;
					case 1:
						if (pArray[x + 2][y] == 0 && x < anchoMap - 1) {//derecha
							pArray[x + 1][y] = 2;
							pArray[x + 2][y] = 3;
							pendiente = !pendiente;
						}
						break;
					case 2:
						if (pArray[x + 1][y + 1] == 0 && y < altoMap - 1) {//abajo
							pArray[x + 1][y] = 2;
							pArray[x + 1][y + 1] = 3;
							pendiente = !pendiente;
						}
						break;
					default:
						break;
					}
				}
			}
			break;
		case 3:
			if (y < altoMap - 1 && pendiente) {//abajo

				/*
				if (pArray[x][y + 1] == 0 && pArray[x][y + 2] == 0) {
					pArray[x][y + 1] = 2;
					pArray[x][y + 2] = 3;
					pendiente = !pendiente;
				}
				*/
				if (pArray[x][y + 1] == 0) {
					switch (numRan2)
					{
					case 0:
						if (pArray[x][y + 2] == 0 && y < altoMap - 2) {
							pArray[x][y + 1] = 2;
							pArray[x][y + 2] = 3;
							pendiente = !pendiente;
						}
						break;
					case 1:
						if (pArray[x - 1][y + 1] == 0 && x > 0) {
							pArray[x][y + 1] = 2;
							pArray[x - 1][y + 1] = 3;
							pendiente = !pendiente;
						}
						break;
					case 2:
						if (pArray[x + 1][y + 1] == 0 && x < anchoMap - 1) {
							pArray[x][y + 1] = 2;
							pArray[x + 1][y + 1] = 3;
							pendiente = !pendiente;
						}
						break;
					default:
						break;
					}
				}

			}
			break;
		case 4:
			if (x > 1 && pendiente) {//izquierda
				/*
				if (pArray[x - 1][y] == 0 && pArray[x - 2][y] == 0) {
					pArray[x - 1][y] = 2;
					pArray[x - 2][y] = 3;
					pendiente = !pendiente;
				}
				*/

				if (pArray[x - 1][y] == 0) {
					switch (numRan2)
					{
					case 0:
						if (pArray[x - 1][y - 1] == 0 && y > 0) {//arriba
							pArray[x - 1][y] = 2;
							pArray[x - 1][y - 1] = 3;
							pendiente = !pendiente;
						}
						break;
					case 1:
						if (pArray[x - 2][y] == 0 && x > 1) {//izquierda
							pArray[x - 1][y] = 2;
							pArray[x - 2][y] = 3;
							pendiente = !pendiente;
						}
						break;
					case 2:
						if (pArray[x - 1][y + 1] == 0 && y < altoMap - 1) {//abajo
							pArray[x - 1][y] = 2;
							pArray[x - 1][y + 1] = 3;
							pendiente = !pendiente;
						}
						break;
					default:
						break;
					}
				}
			}
			break;
		default:
			break;

		}
		if (!pendiente) {
			cout << "\n--------\n";
			imprimeMapaDebug(pArray);
			mazmorras++;
		}
	}
	cout << "\n--------\n";
	imprimeMapaDebug(pArray); 
	//tile.imprHist(); 
	cout << "\n"; 
	



}

int main()
{
	srand(time(NULL));
	int mapArray[anchoMap][altoMap];//mapa
	obtenerMapa(mapArray);


}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
