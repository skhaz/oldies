
#include "GameContext.h"



GameContext::GameContext()
{
	animalTree = new AnimalTree();

	winnerState = new WinnerState(this);
	genioState = new GenioState(this);
	haveNoIdeaState = new HaveNoIdeaState(this);
	initialState = new InitialState(this);

	AnimalTree* tree = animalTree->addRight(new Animal("Tubarao", "vive na agua"));
	tree->addLeft(new Animal("Macaco", "vive na arvore"));

	treeRoot = animalTree;
}

GameContext::~GameContext()
{
	delete initialState;
	delete haveNoIdeaState;
	delete genioState;
	delete winnerState;

	delete animalTree;
}

int GameContext::play()
{
	for (;;)
	{
		currentState = initialState;

		do
		{
			currentState->ask();
			currentState->handleAnswer();
		} while (!currentState->finished());
	}

	return 0;
}

void GameContext::setState(State* state)
{
	currentState = state;
}

State* GameContext::getWinnerState() const
{
	return winnerState;
} 

State* GameContext::getGenioState() const
{
	return genioState;
}

State* GameContext::getHaveNoIdeaState() const
{
	return haveNoIdeaState;
}

State* GameContext::getInitialState() const
{
	return initialState;
}

void GameContext::reset()
{
	currentSide = RIGHT;
	animalTree = treeRoot;
}

void GameContext::add(Animal* animal)
{
	if (currentSide == RIGHT)
	{
		animalTree->addRight(animal);
	}

	else {
		animalTree->addLeft(animal);
	}
}

bool GameContext::hasNext() const
{
	AnimalTree* tree;

	if (currentSide == RIGHT)
	{
		tree = animalTree->right();
	}

	else {
		tree = animalTree->left();
	}

	// check if the binary tree is valid and have any data
	return tree ? tree->data() != 0 : false;
}

Animal* GameContext::next()
{
	if (currentSide == RIGHT)
	{
		animalTree = animalTree->right();
	}

	else {
		animalTree = animalTree->left();
	}

	return animalTree->data();
}

void GameContext::toggleSide()
{
	currentSide = currentSide == RIGHT ? LEFT : RIGHT;
}

