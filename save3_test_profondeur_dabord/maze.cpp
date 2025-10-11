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

// ma fonction de déplacements possibles en fonction de ma situation
void Maze::deplacementsToResolve()
{
	//0 = N; 1 = S; 2 = E; 3 = O
	//tant qu'on a pas atteint la sortie alors on boucle sur un nouveau random de déplacement
	
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

	while (_map[i] != 3)
	{
		random_device rd;
		uniform_int_distribution<int> distribution(0, 3); // uniforme pour avoir les memes chances de tomber sur 0 ou 1 ou 2 ou 3
		int pas = distribution(rd);

		// initialisation de chaque int random vaut une direction
		switch(pas)
		{
			case 0:
				//déplacement vers 1 case nord
				//condition + borne nord car l'entrée du source.mz est en haut
        			if (_map[i-21] != 1 && i-21 >= 0)
        			{
                			i = i-21;
					cpt++;
        			}
        			else
        			{
                			cout << "Not possible to go up.";
        			}
				//displayMap(i);
				cout << " i : " << i << endl;
				break;
			case 1:
				//déplacement vers 1 case sud
				//condition
        			if (_map[i+21] != 1)
        			{
                			i = i+21;
					cpt++;
        			}
        			else
        			{
                			cout << "Not possible to go down.";
        			}
				//displayMap(i);
				cout << " i : " << i << endl;
				break;
			case 2:
				//déplacement vers 1 case est
				//condition
        			if (_map[i+1] != 1)
        			{
                			i = i+1;
					cpt++;
        			}
        			else
        			{
                			cout << "Not possible to go right.";
        			}
				//displayMap(i);
				cout << " i : " << i << endl;
				break;
			case 3:
				//déplacement vers 1 case ouest
				//condition
        			if (_map[i-1] != 1)
        			{
                			i = i-1;
					cpt++;
        			}
        			else
        			{
                			cout << "Not possible to go left.";
        			}
				//displayMap(i);
				cout << " i : " << i << endl;
				break;
			default:
				break;
		}
		displayMap(i); // affichage unique de la map car elle se met à jour ensuite dans display
		cout << "compteur de pas : " << cpt << endl;
	}
	cout << " i-position : " << i << endl;
	cout << "Sortie trouvée par le numéro : " << _map[i] << endl;
	cout << "Déplacements effectués pour arriver à la sortie : " << cpt << endl;
}

bool Maze::caseDejaVue(int position)
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

void Maze::deplacementsProfondeurDabord()
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
