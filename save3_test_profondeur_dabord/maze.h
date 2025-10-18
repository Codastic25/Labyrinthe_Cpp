#include<iostream>
#include<fstream> // bibliotheque qui me permet de lire et ecrire dans un fichier
#include<string> // bibliotheque qui me permet de bénéficier des fonctions de manipulation de string

#ifndef _MAZE_H
#define _MAZE_H


class Maze
{
        //mes variables private
        private:
                int _map[21*12]; // ma map en 1 dimension plutot que 2, ma map source A NE PAS MODIFIER, qui va me servir de comparaison dans mes fonctions
		std::string _mapChar[21*12];// ma map en map de char
		int _map_cases_parcourues[21*12];// ma map des cases parcourues
		int taille_parcourue = 0; // initialisation de la taille de mon tableau de cases parcourues

        public:
                // CONSTRUCTEUR avec en parametre mon nom de fichier de labyrinthe
                Maze(const std::string& source);


                // ICI MES PROTOTYPES
                // Setters

                // Getters
		int getPositionEntreeLabyrinthe();
		int getPositionSortieLabyrinthe();

                // Méthodes utilitaires
                void changeCharToBuildMap();
                void displayMap(int positionActuelle);
		bool obstacle(int positionSouhaitee);
};

#endif
