#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <cstdlib>
#include <stack>

#include "maze.h"
#include "agent.h"

using namespace std;

//mon constructeur Agent
Agent::Agent(Maze& maze)
{
	position = maze.getPositionEntreeLabyrinthe();// j'initialise la position (dans le constructeur) la où il y a l'entrée peu importe le type de labyrinthe
}

//peut servir si mon maze a besoin de récupérer la position de l'agent
int Agent::getPosition(){
	return position;
}

void Agent::setPosition(int newPosition){
	position = newPosition;
}

// ma fonction de déplacements possibles en fonction de ma situation
void Agent::deplacementsRandom(Maze& maze)
{
	//0 = N; 1 = S; 2 = E; 3 = O
	//tant qu'on a pas atteint la sortie alors on boucle sur un nouveau random de déplacement

	int cpt = 0;// mon compteur de déplacements, me sert à évaluer les ressources dépensées pour sortir

	int positionFin = maze.getPositionSortieLabyrinthe();

	//maze.obstacle --> fonction bool obstacle pour indiquer si sur la position précisée il y a un obstacle ou non; true = obstacle, false = pas obstacle

	while (position != positionFin)// tant que position actuelle différente de la position de fin (_map[i] = 3)
	{
		random_device rd;
		uniform_int_distribution<int> distribution(0, 3); // uniforme pour avoir les memes chances de tomber sur 0 ou 1 ou 2 ou 3
		int pas = distribution(rd);

		// initialisation de chaque int random vaut une direction
		switch(pas)
		{
			case 0:
				//déplacement vers 1 case nord
				//condition pas d'obstacles en haut + borne nord car l'entrée du source.mz est en haut
        			if (maze.obstacle(position - 21) == false && position-21 >= 0)
        			{
                			position = position-21;
					cpt++;
        			}
				break;
			case 1:
				//déplacement vers 1 case sud
				//condition
        			if (maze.obstacle(position+21) == false && position < (21 * (12-1)))
        			{
                			position = position+21;
					cpt++;
        			}
				break;
			case 2:
				//déplacement vers 1 case est
				//condition
        			if (maze.obstacle(position+1) == false && (position % 21) != 20)
        			{
                			position = position+1;
					cpt++;
        			}
				break;
			case 3:
				//déplacement vers 1 case ouest
				//condition
        			if (maze.obstacle(position-1) == false && (position % 21) != 0)
        			{
                			position = position-1;
					cpt++;
        			}
				break;
			default:
				break;
		}

		maze.displayMap(position); // affichage unique de la map car elle se met à jour ensuite dans display
		cout << "compteur de pas : " << cpt << endl;
		cout << "Position actuelle : " << position << endl;
	}
	//cout << " i-position : " << i << endl;
	//cout << "Sortie trouvée par le numéro : " << _map[i] << endl;
	//cout << "Déplacements effectués pour arriver à la sortie : " << cpt << endl;
}

/*
bool Agent::caseDejaVue(int position)
{
         // boucle qui parcours mon tableau cases_parcourues et qui verifie si mon element est dans mon tableau
         for (int j = 0; j < taille_parcourue; j++)
         {
                if (_map_cases_parcourues[j] == position)
                {
                        return true;
                }
        }
         return false;
}

void Agent::deplacementsProfondeur(Maze& maze)
{

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

        int cpt = 0;// mon compteur de déplacements, me sert à évaluer les ressources dépensées pour sortir

	// on applique la méthode de parcours profondeur d'abord
	// on utilise une PILE soit modele LIFO (last in first out)
	// LA PILE CONTIENT LES ENDROITS A VISITER
	// DEPILER UNE CASE = EXPLPORER LA CASE ET LA METTRE DANS UNE LISTE pour les cases déja parcourues

	// déclaration d'une pile pour les cases à visiter
	stack<int> endroits_a_visiter;

	endroits_a_visiter.push(i); // ajout de la position de départ dans la pile

	// je définis un ORDRE DE DIRECTIONS -> disons que je décide de tout le temps aller à droite -> haut -> gauche -> bas
	while (!endroits_a_visiter.empty() && _map[i] != 3) // tant que pas de sortie et que pile pas vide
	{
		i = endroits_a_visiter.top(); // la nouvelle position est au sommet de la pile
		if (i+1 >= 0 && i+1 < 21*12 && _map[i+1] != 1 && !caseDejaVue(i+1))// droite possible et pas parcourue
		{
			_map_cases_parcourues[taille_parcourue++] = i+1; // ajout de cette case dans le tableau des cases parcourues
			endroits_a_visiter.push(i+1);
			i = i+1;
			cpt++;
		}
		else if (i-21 >= 0 && i-21 < 21*12 && _map[i-21] != 1 && !caseDejaVue(i-21)) // haut possible et pas parcourue
		{
			_map_cases_parcourues[taille_parcourue++] = i-21; // ajout de cette case dans le tableau des cases parcourues
			endroits_a_visiter.push(i-21);
			i = i-21;
			cpt++;
		}
		else if (i-1 >= 0 && i-1 < 21*12 && _map[i-1] != 1 && !caseDejaVue(i-1)) // gauche possible et pas parcourue
		{
			_map_cases_parcourues[taille_parcourue++] = i-1; // ajout de cette case dans le tableau des cases parcourues
			endroits_a_visiter.push(i-1);
			i = i-1;
			cpt++;
		}
		else if (i+21 >= 0 && i+21 < 21*12 && _map[i+21] != 1 && !caseDejaVue(i+21)) // bas possible et pas parcourue
		{
			_map_cases_parcourues[taille_parcourue++] = i+21; // ajout de cette case dans le tableau des cases parcourues
			endroits_a_visiter.push(i+21);
			i = i+21;
			cpt++;
		}
		else // cas d'impasse
		{
			endroits_a_visiter.pop(); // donc je reviens en arriere si impasse
		}
		displayMap(i);
		cout << "compteur de pas : " << cpt << endl;
	}
}
*/

//void Agent::deplacementsLargeur(Maze& maze){
//}

//void Agent::deplacementsAEtoile(Maze& maze){
//}
