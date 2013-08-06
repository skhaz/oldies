
#ifndef _State_h
#define _State_h

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;

class GameContext;



class State
{
	public:
		virtual void ask() = 0;

		virtual void handleAnswer() = 0;

		virtual bool finished() const = 0;

		virtual ~State() {}
};

#endif

