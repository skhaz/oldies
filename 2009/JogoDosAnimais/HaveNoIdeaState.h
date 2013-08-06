
#ifndef _HaveNoIdeaState_h
#define _HaveNoIdeaState_h

#include "State.h"



class HaveNoIdeaState : public State
{
	public:
		explicit HaveNoIdeaState(GameContext* context);

		void ask();
		void handleAnswer();
		bool finished() const;

	private:
		GameContext* gameContext;
};

#endif

