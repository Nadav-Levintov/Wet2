#ifndef STUDENT_H
#define STUDENT_H


#include <iostream>
#include <assert.h>


class Student
{
	int ID;
	double avg;

public:
	Student();
	Student(int id, double avg=0) :ID(id), avg(avg) {};
	~Student();
	int getID();
};


class StudentIDKey {
public:
	StudentIDKey() {
	}
	~StudentIDKey() {
	}
	int operator()(Student& a) {
		return a.getID();
	}
};

class StudentComparer {
public:
	StudentComparer() {
	}
	~StudentComparer() {
	}
	bool operator()(Student& a, Student& b) {
		return a.getID() > b.getID();
	}
};
#endif /*STUDENT_H*/

