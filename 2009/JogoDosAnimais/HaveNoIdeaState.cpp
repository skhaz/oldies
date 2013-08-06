
#include "HaveNoIdeaState.h"
#include "GameContext.h"
#include "Animal.h"



HaveNoIdeaState::HaveNoIdeaState(GameContext* context)
: gameContext(context)
{
}

void HaveNoIdeaState::ask()
{
}

void HaveNoIdeaState::handleAnswer()
{
}

bool HaveNoIdeaState::finished() const
{
	string current(""), name, skill;

	cout << "desisto" << endl;
	cout << "qual animal voce pensou?" << endl;
	cin >> name;

	cout << "complete" << endl;
	cout << "um(a) " << name << " _______ mas um(a) " << current << " nao." << endl;
	cin >> skill;

	gameContext->add(new Animal(name, skill));

	return true;
}

