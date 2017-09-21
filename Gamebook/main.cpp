//Author: Ondrej Slejtr
//slejtond@fit.cvut.cz

/*! \mainpage
\section Introduction
I've created this gamebook engine as a part of BI-PA2 subject.

It's a simple engine enabling you to load custom world with their own storylines
which you can then travel through while fighting various monsters or collecting
new items to build up your strength.

\section Compilation
Compile this program using make utility: <code>make compile</code>, then run resulting binary file  <code>slejtond</code>.
*/

#include <cstdio>
#include "GameApp.h"

int main() {
	
	GameApp * MainApp = new GameApp;

	MainApp->Play();
	delete MainApp;

	std::cout << "\n\nGoodbye!\n";

}