
#ifndef _InitialState_h
#define _InitialState_h

#include "State.h"



class InitialState : public State
{
	public:
		explicit InitialState(GameContext* context);

		void ask();
		void handleAnswer();
		bool finished() const;

	private:
		GameContext* gameContext;
		bool finish;
};

#endif

