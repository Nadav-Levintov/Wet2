#ifndef STUDENT_H
#define STUDENT_H


#include <iostream>
#include <assert.h>


class Student
{
	int ID;
	double avg;
	int studyGroup;

public:
	Student();
	Student(int id, int avg=0, int group=-1) :ID(id), avg(avg),studyGroup(group) {};
	~Student();
	int getID();
	int getGroup();
	void setGroup(int n);
	double getAvg();
	void setAvg(int newAvg);
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

