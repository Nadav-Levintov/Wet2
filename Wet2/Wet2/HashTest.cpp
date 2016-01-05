#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "Student.h"
#include "HashTable.h"

using namespace std;

int main()
{

	HashTable<Student, StudentComparer, StudentIDKey> ht = HashTable<Student, StudentComparer, StudentIDKey>();
	Student s1(1, 2);
	ht.insert(s1);
	Student s2(2, 2);
	ht.insert(s2);
	Student s3(3, 2);
	ht.insert(s3);

	Student s = ht.member(3);
	try { s = ht.member(4); }
	catch (HashTable<Student, StudentComparer, StudentIDKey>::NotFound e)
	{
		cout << "All Good" << endl;
	}
	return 0;
}