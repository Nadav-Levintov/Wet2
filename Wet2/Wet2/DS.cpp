#include "DS.h"

DS::DS(int numOfFacu) :
		numOfFacultys(numOfFacu), facultys(numOfFacu) {
	if (numOfFacu < 2) {
		throw InvalidInput();
	}
	maxArray = new int[numOfFacu];
	maxIdArray = new int[numOfFacu];
	gradesHistogram = new int[101];
}

DS::~DS() {
	delete[] maxArray;
	delete[] maxIdArray;
	delete[] gradesHistogram;
}

void DS::AddStudent(int studentID, int average) {
	if (average > 100 || average < 0 || studentID < 0) {
		throw InvalidInput();
	}
	Student s(studentID, average);
	if (studentTree.find(s)) {
		throw Failure();
	}
	studentTree.insert(s);
	gradesHistogram[int(floor(average))]++;
}

void DS::AssignStudent(void * DS, int studentID, int studyGroup) {
	if (studentID < 0 || studyGroup < 0 || studyGroup >= numOfFacultys) {
		throw InvalidInput();
	}
	if (!studentTree.find(Student(studentID))) {
		throw Failure();
	}
	Student s = studentTree.find(Student(studentID))->getData();
	if (s.getGroup() != -1) {
		throw Failure();
	}
	s.setGroup(studyGroup);
	ht.insert(s);
	int faculty = facultys.Find(studyGroup);
	if (maxArray[faculty] <= s.getAvg()) {
		if (maxArray[faculty] == s.getAvg()) {
			if (maxIdArray[faculty] > s.getID()) {
				maxIdArray[faculty] = s.getID();
			}
		} else {
			maxIdArray[faculty] = s.getID();
			maxArray[faculty] = s.getAvg();
		}
	}
	studentTree.remove(s);
	studentTree.insert(s);

}

void DS::JoinFaculties(int studyGroup1, int studyGroup2) {
	if (studyGroup1 < 0 || studyGroup2 < 0 || studyGroup1 >= numOfFacultys
			|| studyGroup2 >= numOfFacultys) {
		throw InvalidInput();
	}
	int faculty1 = facultys.Find(studyGroup1);
	int faculty2 = facultys.Find(studyGroup2);
	if (faculty1 == faculty2) {
		throw Failure();
	}
	/** Updating Max */
	if (maxArray[faculty2] > maxArray[faculty1]
			|| ((maxArray[faculty2] == maxArray[faculty1])
					&& maxIdArray[faculty2] < maxIdArray[faculty1])) {
		maxArray[faculty1] = maxArray[faculty2];
		maxIdArray[faculty1] = maxIdArray[faculty2];
	}
	/** Union */
	facultys.Union(facultys.Find(studyGroup1), facultys.Find(studyGroup2));
}
