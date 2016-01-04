#include "DS.h"

DS::DS(int numOfFacu) :
		numOfFacultys(numOfFacu), facultys(numOfFacu) {
	if (numOfFacu < 2) {
		throw InvalidInput();
	}
	maxArray = new int[numOfFacu];
	maxIdArray = new int[numOfFacu];
	gradesHistogram = new int[101];
	for (int i = 0; i < numOfFacu; i++) {
		maxArray[i] = EMPTY;
		maxIdArray[i] = EMPTY;
	}
	for (int i = 0; i <= 100; i++) {
		gradesHistogram[i] = 0;
	}
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
	gradesHistogram[average]++;
}

void DS::AssignStudent(void * DS, int studentID, int studyGroup) {
	if (studentID < 0 || studyGroup < 0 || studyGroup >= numOfFacultys) {
		throw InvalidInput();
	}
	Student tmp(studentID);
	if (!studentTree.find(tmp)) {
		throw Failure();
	}
	Student s = studentTree.find(tmp)->getData();
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

void DS::GetFaculty(int studentID, int* faculty) {
	if (studentID < 0 || !faculty) {
		throw InvalidInput();
	}
	Student s;
	try {
		s = ht.member(studentID);
	} catch (HashTable<Student, StudentComparer, StudentIDKey>::NotFound& e) {
		throw Failure();
	}
	*faculty = facultys.Find(ht.member(studentID).getGroup());
}

void DS::UnifyFacultiesByStudents(void* DS, int studentID1, int studentID2) {
	if (studentID1 < 0 || studentID2 < 0) {
		throw InvalidInput();
	}
	try {
		if (facultys.Find(ht.member(studentID1).getGroup())
				== facultys.Find(ht.member(studentID2).getGroup())) {
			throw Failure();
		}
	} catch (HashTable<Student, StudentComparer, StudentIDKey>::NotFound& e) {
		throw Failure();
	}
	JoinFaculties(facultys.Find(ht.member(studentID1).getGroup()),
			facultys.Find(ht.member(studentID2).getGroup()));
}

void DS::UpgradeStudyGroup(void* DS, int studyGroup, int factor) {
	if (factor < 1 || studyGroup < 0 || studyGroup >= numOfFacultys) {
		throw InvalidInput();
	}
	int faculty = facultys.Find(studyGroup);
	Student* students = studentTree.inOrder();
	int numOfStudents = studentTree.getSize();
	for (int i = 0; i < numOfStudents; i++) {
		if (students[i].getGroup() == studyGroup) {
			int oldAvg = students[i].getAvg();
			int newAvg = (100 < oldAvg * factor) ? 100 : oldAvg * factor;
			students[i].setAvg(newAvg);
			gradesHistogram[oldAvg]--;
			gradesHistogram[newAvg]++;
			if (newAvg > maxArray[faculty]
					|| ((newAvg == maxArray[faculty])
							&& students[i].getID() < maxIdArray[faculty])) {
				maxArray[faculty] = newAvg;
				maxIdArray[faculty] = students[i].getID();
			}
		}
	}
	studentTree.clear();
	studentTree.buildEmpty(numOfStudents);
	int index = 0;
	studentTree.inOrderInsert(students, &index);
}

void DS::GetSmartestStudent(void* DS, int facultyID, int* student) {
	if (!student || facultyID < 0 || facultyID >= numOfFacultys) {
		throw InvalidInput();
	}
	if (maxIdArray[facultyID] == EMPTY) {
		throw Failure();
	}
	*student = maxIdArray[facultyID];
}

void DS::GetNumOfStudentsInRange(void* DS, int fromAvg, int toAvg, int* num) {
	if (fromAvg >= toAvg || fromAvg < 0 || toAvg > 100) {
		throw InvalidInput();
	}
	int counter = 0;
	for (int i = fromAvg + 1; i <= toAvg; i++) {
		counter += gradesHistogram[i];
	}
	*num = counter;
}
