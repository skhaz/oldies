
#include "WinnerState.h"
#include "GameContext.h"



WinnerState::WinnerState(GameContext* context)
: gameContext(context)
{
}

void WinnerState::ask()
{
}

void WinnerState::handleAnswer()
{
}

bool WinnerState::finished() const
{
	cout << "Acertei de novo!" << endl;

	return true;
}

