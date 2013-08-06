
#ifndef _GameContext_h
#define _GameContext_h

#include "BinaryTree.h"
#include "Animal.h"

#include "State.h"
#include "GenioState.h"
#include "WinnerState.h"
#include "HaveNoIdeaState.h"
#include "InitialState.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

typedef BinaryTree<Animal *> AnimalTree;



class GameContext
{
	public:
		GameContext();
		virtual ~GameContext();
		int play();

		void setState(State* state);
		State* getWinnerState() const;
		State* getGenioState() const;
		State* getHaveNoIdeaState() const;
		State* getInitialState() const;

		void reset();
		void add(Animal* animal);
		bool hasNext() const;
		Animal* next();
		void toggleSide();

	private:
		enum Side
		{
			RIGHT,
			LEFT
		};

		Side currentSide;
		AnimalTree* animalTree;
		AnimalTree* treeRoot;

		State* currentState;
		State* winnerState;
		State* genioState;
		State* haveNoIdeaState;
		State* initialState;
};

#endif

