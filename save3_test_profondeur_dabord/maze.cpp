#include<iostream>
#include<fstream> // bibliotheque qui me permet de lire et ecrire dans un fichier
#include<cstring> // bibliotheque qui me permet de bénéficier des fonctions de manipulation de string
#include<random> // module de random
#include<cstdlib> // module pour utiliser et manip system
#include<stack> // conteneur pour utiliser la pile
#include"maze.h"

using namespace std;


// CONSTRUCTEUR avec en parametre mon nom de fichier de labyrinthe

Maze::Maze(const std::string& source){
// ici je construits un flux d'entrée f lié a mon fichier
ifstream f (source);
// dans le cas ou le fichier aurait un probleme
if (!f)
{
	std::cout << "Erreur lors de l'ouverture du fichier : " << source << std::endl;
	return;
}
// si ok, affichage :
for (int i = 0; i < 21*12 && f; i++) // on boucle et on vérifie en meme temps que le flux est toujours valide : d'ou le && f
{
	f >> _map[i]; // lecture du fichier depuis le flux
}
for (int i = 0; i < 21*12; i++)// cette boucle me sert à convertir mon tableau de int (_map) en tableau de char (_mapChar)
{
	_mapChar[i] = _map[i] + 48; // conversion de int en char par la table ASCII; une 2e map (de char issue de celle de int)
}
f.close(); // fermeture du flux
}

//booleen pour voir si a cette position il y a un obstacle dans le labyrinthe
bool Maze::obstacle(int positionSouhaitee){
	if (_map[positionSouhaitee] == 1)
		return true; // donc obstacle
	return false;
}

int Maze::getPositionEntreeLabyrinthe(){
	int i = 0;// car on démarre sur cette case
        // boucle pour toujours trouver la case de départ

        for (int k = 0; k < 21*12; k++)
        {
                if (_map[k] == 2)
                {
                        i = k;
                        break;
                }
        }
	return i;// me retourne la position de l'entrée du labyrinthe
}

int Maze::getPositionSortieLabyrinthe(){
        int i = 0;// car on démarre sur cette case
        // boucle pour toujours trouver la case de départ

        for (int k = 0; k < 21*12; k++)
        {
                if (_map[k] == 3)
                {
                        i = k;
                        break;
                }
        }
        return i;// me retourne la position de la sortie du labyrinthe
}


// ma fonction qui me permet d'afficher la map initiale
void Maze::displayMap(int positionJoueur)
{
	//system("clear");//nettoyage de la console du terminal pour chaque appel de displayMap
			//ce qui me permet de simuler un seul labyrinthe à chaque fois et pas énormément

	for (int i = 0; i < 21*12; i++)
	{
		if (i % 21 == 0)
		{
			cout << endl;
		}
		if (i == positionJoueur)
		{
			cout << "🟦";// affichage de mon personnage
		}
		else
		{
			cout << _mapChar[i];// sinon affichage du caractère à sa bonne place
		}
	}
	cout << endl;
}

// ma fonction qui me permet de modifier un chiffre par un caractere
void Maze::changeCharToBuildMap()
{
	for (int i = 0; i < 21*12; i++)
	{
		if (_map[i] == 2)
		{
			_mapChar[i] = "🟩";
		}
		if (_map[i] == 3)
		{
			_mapChar[i] = "🎯";
		}
		if (_map[i] == 1)
    		{
        		if (_map[i+1] == 1 && (i+1) % 21 != 0 && i % 21 != 0) // je regarde le suivant, egalement si je ne suis pas en fin de ligne (i+1) et si je ne suis pas en début de ligne (i)
            			_mapChar[i] = "🧱";// a l'affichage, les murs seront pareils mais initialement on différencie bien # de |
        		else
			{
            			_mapChar[i] = "🧱";
			}
    		}
		if (_map[i] == 0)
                {
                        _mapChar[i] = "⬜";
                }
	}
}
