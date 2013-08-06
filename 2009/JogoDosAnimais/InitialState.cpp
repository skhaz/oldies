
#include "InitialState.h"
#include "GameContext.h"



InitialState::InitialState(GameContext* context)
: gameContext(context)
, finish(false)
{
}

void InitialState::ask()
{
	gameContext->reset();
	cout << "Pense em um animal" << endl << "use sim ou nao para responder" << endl;
}

void InitialState::handleAnswer()
{
	gameContext->setState(gameContext->getGenioState());
}

bool InitialState::finished() const
{
	return false;
}

