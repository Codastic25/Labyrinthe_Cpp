#include<iostream>
#include<fstream> // bibliotheque qui me permet de lire et ecrire dans un fichier
#include<cstring> // bibliotheque qui me permet de bénéficier des fonctions de manipulation de string
#include<random> // module de random

using namespace std;

class Maze
{
	//mes variables private
	private:
		int _map[21*12]; // ma map en 1 dimension plutot que 2, ma map source A NE PAS MODIFIER, qui va me servir de comparaison dans mes fonctions
		string _mapChar[21*12];// ma map en map de char

	public:
    		// CONSTRUCTEUR avec en parametre mon nom de fichier de labyrinthe
    		Maze(const string& source){
			// ici je construits un flux d'entrée f lié a mon fichier
			ifstream f (source);
			// dans le cas ou le fichier aurait un probleme
			if (!f)
			{
				cout << "Erreur lors de l'ouverture du fichier : " << source << endl;
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


		// ICI MES PROTOTYPES
    		// Setters

    		// Getters

    		// Méthodes utilitaires
		void changeCharToBuildMap();
		void displayMap();
		void deplacementsToResolve();
};

// mes fonctions, méthodes ci-dessous
//Comme ca je partitionne bien et le jour ou je dois mettre les methodes dans un .h, ce sera possible

// ma fonction qui me permet d'afficher la map initiale
void Maze::displayMap()
{
	for (int i = 0; i < 21*12; i++)
	{
		if (i % 21 == 0)
		{
			cout << endl;
		}
		cout << _mapChar[i];
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
	
	int i = 1;// car on démarre sur cette case
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
				//condition
        			if (_map[i-21] != 1 && i-21 >= 0)
        			{
                			i = i-21;
        			}
        			else
        			{
                			cout << "Not possible to go up.";
        			}
				displayMap();
				cout << " i : " << i << endl;
				break;
			case 1:
				//déplacement vers 1 case sud
				//condition
        			if (_map[i+21] != 1)
        			{
                			i = i+21;
        			}
        			else
        			{
                			cout << "Not possible to go down.";
        			}
				displayMap();
				cout << " i : " << i << endl;
				break;
			case 2:
				//déplacement vers 1 case est
				//condition
        			if (_map[i+1] != 1)
        			{
                			i = i+1;
        			}
        			else
        			{
                			cout << "Not possible to go right.";
        			}
				displayMap();
				cout << " i : " << i << endl;
				break;
			case 3:
				//déplacement vers 1 case ouest
				//condition
        			if (_map[i-1] != 1)
        			{
                			i = i-1;
        			}
        			else
        			{
                			cout << "Not possible to go left.";
        			}
				displayMap();
				cout << " i : " << i << endl;
				break;
			default:
				break;
		}
		cpt++;//+1 au compteur de déplacements
	}
	cout << " i-position : " << i << endl;
	cout << "Sortie trouvée par le numéro : " << _map[i] << endl;
	cout << "Déplacements effectués pour arriver à la sortie : " << cpt << endl;
}


int main() {
	//Création de mon objet Maze
	Maze m("source.mz");
	m.changeCharToBuildMap();// appel de fonction pour changer mes chiffres en "char"
	//m.displayMap();// appel de fonction pour afficher ma map
	m.deplacementsToResolve();
	return 0;
}

