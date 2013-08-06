
#ifndef _Animal_h
#define _Animal_h

#include <iostream>
#include <string>
using std::string;



class Animal
{
	public:
		explicit Animal(string const& name, string const& skill = string());

		virtual ~Animal();

		void setName(string const& name);

		string const& name() const;

		void setSkill(string const& skill);

		string const& skill() const;

	private:
		string m_name;
		string m_skill;
};

#endif

