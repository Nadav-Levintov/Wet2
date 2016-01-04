#include "Student.h"



Student::Student()
{
	ID = 0;
	avg = 0.0;
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

double Student::getAvg()
{
	return avg;
}
