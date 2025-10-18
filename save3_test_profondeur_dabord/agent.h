#include "maze.h"

#ifndef AGENT_H
#define AGENT_H

class Agent {
	private:
		int position; // position actuelle de mon agent sur mon maze 1D
	public:
		Agent(Maze& maze);

		// mes fonctions de résolution
		void deplacementsRandom(Maze& maze);// reference vers notre Maze
		//void deplacementsProfondeur(Maze& maze);
		//bool caseDejaVue (int position);
		//void deplacementsLargeur(Maze& maze);
		//void deplacementsAEtoile(Maze& maze);
		
		// mes getters et setters
		int getPosition();
		void setPosition(int newPosition);
};

#endif
