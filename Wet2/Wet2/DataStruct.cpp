#include "DataStruct.h"

DataStruct::DataStruct(int numOfTeams) :
	numOfGroups(numOfTeams), groups(numOfTeams) {
	if (numOfTeams < 2) {
		throw InvalidInput();
	}
	maxArray = new int[numOfTeams];
	maxIdArray = new int[numOfTeams];
	for (int i = 0; i < numOfTeams; i++) {
		maxArray[i] = EMPTY;
		maxIdArray[i] = EMPTY;
	}
}

DataStruct::~DataStruct() {
	delete[] maxArray;
	delete[] maxIdArray;
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
	TrollStrengthTree.insert(s);
	rankNode<int, intComparer>* strengthNode = strengthTree.find(strength);
	if (!strengthNode)
	{
			strengthTree.insert(strength);
	}
	else
	{
		strengthNode->setCurrentData(strengthNode->getCurrentData() + 1);
		strengthTree.updateRankDataOnPath(strength);
	}
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
		}
		else {
			maxIdArray[group] = s.getID();
			maxArray[group] = s.getStrength();
		}
	}
	TrollTree.remove(s);
	TrollTree.insert(s);
	TrollStrengthTree.remove(s);
	TrollStrengthTree.insert(s);

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
	}
	catch (HashTable<Troll, TrollComparer, TrollIDKey>::NotFound& e) {
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
	/*
	int* rankDataArray= new int[strengthTree.getSize()];
	int* strengthArray = strengthTree.inOrder(rankDataArray);
	int* strengthIndexArray = new int[strengthArray[strengthTree.getSize() - 1] * factor];
	for (int i = 0; i < strengthTree.getSize(); i++)
	{
		strengthIndexArray[strengthArray[i]] = i;
	}
	*/


	Troll* Trolls = TrollTree.inOrder();
	Troll* TrollsByStrength = TrollStrengthTree.inOrder();
	int numOfTrolls = TrollTree.getSize();
	for (int i = 0; i < numOfTrolls; i++) {
		if (Trolls[i].getGroup() == group) {
			int oldStrength = Trolls[i].getStrength();
			int newStrength = oldStrength * factor;
			Trolls[i].setStrength(newStrength);
			/*
			Need to create a new Trolls array, which will hold all the trolls that have been updated
			sorted by strength.
			also, remove these trolls from the TrollsByStrength array.
			then do a merge of the 2 arrays to 1 sorted array and push it back into the TrollsStrenthTree
			(just like to the trolls tree few lines down)

			then, in some way( need to think excaly how) update the rankTree data accordingly.
			shouldn't be too hard because we have a sorted array of all strengths, just need to 
			convert it to histogram and "push" it to the rank tree with inOrderInsert.
			
			*/



			if (newStrength > maxArray[group]
				|| ((newStrength == maxArray[group])
					&& Trolls[i].getID() < maxIdArray[group])) {
				maxArray[group] = newStrength;
				maxIdArray[group] = Trolls[i].getID();
			}
		}
	}

	/*push updated Troll Array to TrollTree*/
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
	if (fromStrength >= toStrength || fromStrength < 0) {
		throw InvalidInput();
	}

	rankNode<int, intComparer>* fromNode = strengthTree.find(fromStrength);
	rankNode<int, intComparer>* toNode = strengthTree.find(toStrength);
	bool addedFrom = false, addedTo = false;
	if (!fromNode)
	{
		addedFrom = true;
		strengthTree.insert(fromStrength);
		fromNode = strengthTree.find(fromStrength);
	}
	if (!toNode)
	{
		addedTo = true;
		strengthTree.insert(toStrength);
		toNode = strengthTree.find(toStrength);
	}
	int fromRank = strengthTree.rank(fromStrength);
	int toRank = strengthTree.rank(toStrength);
	int counter = 0;
	counter = toRank - fromRank;
	if (addedTo)
	{
		counter--;
		strengthTree.remove(toStrength);
	}
	if (addedFrom)
	{
		strengthTree.remove(fromStrength);
	}
	*num = counter;
}


