#ifndef Troll_H
#define Troll_H


#include <iostream>
#include <assert.h>


class Troll
{
	int ID;
	int strength;
	int team;

public:
	Troll();
	Troll(int id, int strength=0, int group=-1) :ID(id), strength(strength),team(group) {};
	~Troll();
	int getID();
	int getGroup();
	void setGroup(int n);
	int getStrength();
	void setStrength(int newStrength);
	void setID(int n);
};


class TrollIDKey {
public:
	TrollIDKey() {
	}
	~TrollIDKey() {
	}
	int operator()(Troll& a) {
		return a.getID();
	}
};

class TrollComparer {
public:
	TrollComparer() {
	}
	~TrollComparer() {
	}
	bool operator()(Troll& a, Troll& b) {
		return a.getID() > b.getID();
	}
};

class TrollStrengthComparer {
public:
	TrollStrengthComparer() {
	}
	~TrollStrengthComparer() {
	}
	bool operator()(Troll& a, Troll& b) {
		if(a.getStrength() == b.getStrength())
			return a.getID() > b.getID();
		else
			return a.getStrength() < b.getStrength();
	}
};

#endif /*Troll_H*/

