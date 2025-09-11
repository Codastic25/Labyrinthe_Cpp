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
		void possibleDeplacements();
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
void Maze::possibleDeplacements()
{
	char direction[4] = {'N', 'S', 'E', 'O'}; // mes 4 directions possibles
	random_device rd;
	uniform_int_distribution<int> distribution(0, 3); // uniforme pour avoir les memes chances de tomber sur 0 ou 1 ou 2 ou 3
	int pas = distribution(rd);

	// initialisation de chaque int random vaut une direction
	if (pas == 0)
	{
		
	}
}

int main() {
	//Création de mon objet Maze
	Maze m("source.mz");
	m.changeCharToBuildMap();// appel de fonction pour changer mes chiffres en "char"
	m.displayMap();// appel de fonction pour afficher ma map
	m.possibleDeplacements();
	return 0;
}

