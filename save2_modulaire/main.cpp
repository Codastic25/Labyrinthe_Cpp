#include"maze.h"

using namespace std;

int main() {
	//Création de mon objet Maze
	Maze m("source.mz");
	m.changeCharToBuildMap();// appel de fonction pour changer mes chiffres en "char"
	m.deplacementsToResolve();
	return 0;
}
