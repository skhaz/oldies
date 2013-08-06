
#ifndef _GenioState_h
#define _GenioState_h

#include "State.h"
#include "GameContext.h"
#include "Animal.h"



class GenioState : public State
{
	public:
		explicit GenioState(GameContext* context);

		void ask();
		void handleAnswer();
		bool finished() const;

	private:
		GameContext* gameContext;
};

#endif


