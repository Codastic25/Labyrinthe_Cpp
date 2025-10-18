#include "maze.h"
#include "agent.h"

using namespace std;

int main() {
	//Création de mon objet Maze et de mon Agent
	Maze m("source.mz");
	Agent a(m);
	m.changeCharToBuildMap();// appel de fonction pour changer mes chiffres en "char"
	a.deplacementsRandom(m);
	return 0;
}
