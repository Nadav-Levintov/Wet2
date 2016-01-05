#include "Student.h"



Student::Student()
{
	ID = 0;
	avg = 0;
	studyGroup = -1;
}


Student::~Student()
{
}


int Student::getID()
{
	return ID;
}

int Student::getGroup()
{
	return studyGroup;
}

void Student::setGroup(int n)
{
	studyGroup = n;
}

int Student::getAvg()
{
	return avg;
}

void Student::setAvg(int newAvg) {
	avg = newAvg;
}
