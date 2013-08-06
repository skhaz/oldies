
#include "GenioState.h"



GenioState::GenioState(GameContext* context)
: gameContext(context)
{
}

void GenioState::ask()
{
}

void GenioState::handleAnswer()
{
	string input;
	if (gameContext->hasNext())
	{
		Animal* animal = gameContext->next();
		cout << "O animal que voce pensou " << animal->skill() << endl;
		cin >> input;

		if (input == string("sim"))
		{
			cout << "O animal que voce pensou e o " << animal->name() << "?" << endl;

			cin >> input;
			if (input == string("sim"))
			{
				gameContext->setState(gameContext->getWinnerState());
			}
		}

		else {
			gameContext->toggleSide();
		}
	}

	else {
		gameContext->setState(gameContext->getHaveNoIdeaState()); 
	}
}

bool GenioState::finished() const
{
	return false;
}

