#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "Troll.h"
#include "HashTable.h"

using namespace std;

int main()
{

	HashTable<Troll, TrollComparer, TrollIDKey> ht = HashTable<Troll, TrollComparer, TrollIDKey>();
	Troll s1(1, 2);
	ht.insert(s1);
	Troll s2(2, 2);
	ht.insert(s2);
	Troll s3(3, 2);
	ht.insert(s3);

	Troll s = ht.member(3);
	try { s = ht.member(4); }
	catch (HashTable<Troll, TrollComparer, TrollIDKey>::NotFound e)
	{
		cout << "All Good" << endl;
	}
	return 0;
}