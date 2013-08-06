
#include "Animal.h"



Animal::Animal(string const& name, string const& skill)
: m_name(name)
, m_skill(skill)
{
}

Animal::~Animal()
{
	std::cout << "deletando " << name() << std::endl;
}

void Animal::setName(string const& name)
{
	m_name = name;
}

string const& Animal::name() const
{
	return m_name;
}

void Animal::setSkill(string const& skill)
{
	m_skill = skill;
}

string const& Animal::skill() const
{
	return m_skill;
}

