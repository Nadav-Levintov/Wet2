#include "DataStruct.h"

DataStruct::DataStruct(int numOfFacu) :
		numOfGroups(numOfFacu), groups(numOfFacu) {
	if (numOfFacu < 2) {
		throw InvalidInput();
	}
	maxArray = new int[numOfFacu];
	maxIdArray = new int[numOfFacu];
	strengthHistogram = new int[101];
	for (int i = 0; i < numOfFacu; i++) {
		maxArray[i] = EMPTY;
		maxIdArray[i] = EMPTY;
	}
	for (int i = 0; i <= 100; i++) {
		strengthHistogram[i] = 0;
	}
}

DataStruct::~DataStruct() {
	delete[] maxArray;
	delete[] maxIdArray;
	delete[] strengthHistogram;
}

void DataStruct::AddTroll(int TrollID, int strength) {
	if (strength < 0 || TrollID < 0) {
		throw InvalidInput();
	}
	Troll s(TrollID, strength);
	if (TrollTree.find(s)) {
		throw Failure();
	}
	TrollTree.insert(s);
	strengthHistogram[strength]++;
}

void DataStruct::AssignTroll(int TrollID, int team) {
	if (TrollID < 0 || team < 0 || team >= numOfGroups) {
		throw InvalidInput();
	}
	Troll tmp(TrollID);
	if (!TrollTree.find(tmp)) {
		throw Failure();
	}
	Troll s = TrollTree.find(tmp)->getData();
	if (s.getGroup() == team) {
		return;
	}
	if (s.getGroup() != -1) {
		throw Failure();
	}
	s.setGroup(team);
	ht.insert(s);
	int group = groups.Find(team);
	if (maxArray[group] <= s.getStrength()) {
		if (maxArray[group] == s.getStrength()) {
			if (maxIdArray[group] > s.getID()) {
				maxIdArray[group] = s.getID();
			}
		} else {
			maxIdArray[group] = s.getID();
			maxArray[group] = s.getStrength();
		}
	}
	TrollTree.remove(s);
	TrollTree.insert(s);

}

void DataStruct::JoinGroups(int team1, int team2) {
	if (team1 < 0 || team2 < 0 || team1 >= numOfGroups
			|| team2 >= numOfGroups) {
		throw InvalidInput();
	}
	int group1 = groups.Find(team1);
	int group2 = groups.Find(team2);
	if (group1 == group2) {
		throw Failure();
	}
	/** Updating Max */
	if (maxArray[group2] > maxArray[group1]
			|| ((maxArray[group2] == maxArray[group1])
					&& maxIdArray[group2] < maxIdArray[group1])) {
		maxArray[group1] = maxArray[group2];
		maxIdArray[group1] = maxIdArray[group2];
	}
	maxArray[group2] = EMPTY;
	maxIdArray[group2] = EMPTY;
	/** Union */
	groups.Union(group1, group2);
}

void DataStruct::GetGroup(int TrollID, int* group) {
	if (TrollID < 0 || !group) {
		throw InvalidInput();
	}
	Troll s;
	try {
		s = ht.member(TrollID);
	} catch (HashTable<Troll, TrollComparer, TrollIDKey>::NotFound& e) {
		throw Failure();
	}
	*group = groups.Find(ht.member(TrollID).getGroup());
}
/*
void DataStruct::UnifyFacultiesByTrolls(int TrollID1, int TrollID2) {
	if (TrollID1 < 0 || TrollID2 < 0) {
		throw InvalidInput();
	}
	try {
		if (groups.Find(ht.member(TrollID1).getGroup())
				== groups.Find(ht.member(TrollID2).getGroup())) {
			throw Failure();
		}
	} catch (HashTable<Troll, TrollComparer, TrollIDKey>::NotFound& e) {
		throw Failure();
	}
	JoinFaculties(groups.Find(ht.member(TrollID1).getGroup()),
			groups.Find(ht.member(TrollID2).getGroup()));
}
*/
void DataStruct::TeamUpgrade(int team, int factor) {
	if (factor < 1 || team < 0 || team >= numOfGroups) {
		throw InvalidInput();
	}
	int group = groups.Find(team);
	Troll* Trolls = TrollTree.inOrder();
	int numOfTrolls = TrollTree.getSize();
	for (int i = 0; i < numOfTrolls; i++) {
		if (Trolls[i].getGroup() == team) {
			int oldStrength = Trolls[i].getStrength();
			int newStrength = (100 < oldStrength * factor) ? 100 : oldStrength * factor;
			Trolls[i].setStrength(newStrength);
			strengthHistogram[oldStrength]--;
			strengthHistogram[newStrength]++;
			if (newStrength > maxArray[group]
					|| ((newStrength == maxArray[group])
							&& Trolls[i].getID() < maxIdArray[group])) {
				maxArray[group] = newStrength;
				maxIdArray[group] = Trolls[i].getID();
			}
		}
	}
	TrollTree.clear();
	TrollTree.buildEmpty(numOfTrolls);
	int index = 0;
	TrollTree.inOrderInsert(Trolls, &index);
	delete[] Trolls;
}

void DataStruct::GetStrongestTroll(int groupID, int* Troll) {
	if (!Troll || groupID < 0 || groupID >= numOfGroups) {
		throw InvalidInput();
	}
	if (maxIdArray[groupID] == EMPTY) {
		throw Failure();
	}
	*Troll = maxIdArray[groupID];
}

void DataStruct::GetNumOfTrollsInRange(int fromStrength, int toStrength, int* num) {
	if (fromStrength >= toStrength || fromStrength < 0 || toStrength > 100) {
		throw InvalidInput();
	}
	int counter = 0;
	for (int i = fromStrength + 1; i <= toStrength; i++) {
		counter += strengthHistogram[i];
	}
	*num = counter;
}
