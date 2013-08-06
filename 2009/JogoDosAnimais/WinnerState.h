
#ifndef _WinnerState_h
#define _WinnerState_h

#include "State.h"



class WinnerState : public State
{
	public:
		explicit WinnerState(GameContext* context);

		void ask();
		void handleAnswer();
		bool finished() const;

	private:
		GameContext* gameContext;
};

#endif

