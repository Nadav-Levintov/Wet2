#include "DS.h"

void DS::AddStudent(int studentID, int average)
{
	if (average > 100 || average < 0 || studentID < 0)
	{
		throw InvalidInput();
	}
	Student s(studentID, average);
	if (studentTree.find(s))
	{
		throw Failure();
	}
	studentTree.insert(s);
	gradesHistogram[int(floor(average))]++;
	}

void DS::AssignStudent(void * DS, int studentID, int studyGroup)
{
	if (studentID < 0 || studyGroup < 0 || studyGroup >= numOfFacultys)
	{
		throw InvalidInput();
	}
	if (!studentTree.find(Student(studentID)))
	{
		throw Failure();
	}
	Student s = studentTree.find(Student(studentID))->getData();
	if (s.getGroup() != -1)
	{
		throw Failure();
	}
	s.setGroup(studyGroup);
	ht.insert(s);
	int faculty = facultys.Find(studyGroup);
	if (maxArray[faculty] <= s.getAvg())
	{
		if (maxArray[faculty] == s.getAvg())
		{
			if (maxIdArray[faculty] > s.getID())
			{
				maxIdArray[faculty] = s.getID();
			}
		}
		else
		{
			maxIdArray[faculty] = s.getID();
			maxArray[faculty] = s.getAvg();
		}
	}
	studentTree.remove(s);
	studentTree.insert(s);

}
