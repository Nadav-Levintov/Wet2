#include "DataStruct.h"

Troll * DataStruct::mergeTrollsArray(Troll * array1, Troll * array2, int num)
{
	Troll* merged = new Troll[num];
	int a = 0, b = 0, i = 0;
	while ((a < num) && (b < num) && (i < num))
	{
		if ((array1[a].getID() != 0) && (array2[b].getID() != 0))
		{
			if (array1[a].getStrength() < array2[b].getStrength())
			{
				merged[i] = array1[a];
				i++;
				a++;
			}
			else
			{
				merged[i] = array2[b];
				i++;
				b++;
			}
		}
		else {
			if (array1[a].getID() == 0)
				a++;
			if (array2[b].getID() == 0)
				b++;
		}
	}
	while ((a < num) && (i < num))
	{
		if (array1[a].getID() != 0)
		{
			merged[i] = array1[a];
			i++;
		}
		a++;

	}
	while ((b < num) && (i < num))
	{
		if (array2[b].getID() != 0)
		{
			merged[i] = array2[b];
			i++;
		}
		b++;

	}


	delete[] array1;
	delete[] array2;

	return merged;
}

void DataStruct::buildStrengthHistogram(Troll * strengthArray, int ** histogramData, int ** histogramBase, int numOfTrolls, int* numOfStrengths)
{
	int numOfStrength = 1;
	for (int i = 0; i < numOfTrolls - 1; i++)
	{
		if (strengthArray[i].getStrength() != strengthArray[i + 1].getStrength())
		{
			numOfStrength++;
		}
	}
	int* base = new int[numOfStrength];
	int* data = new int[numOfStrength];
	for (int i = 0; i < numOfStrength; i++)
	{
		data[i] = 1;
	}
	int histoCounter = 1, histoIndex = 0;
	base[0] = strengthArray[0].getStrength();
	for (int i = 1; i < numOfTrolls; i++)
	{
		if (strengthArray[i].getStrength() == strengthArray[i - 1].getStrength())
		{
			histoCounter++;
		}
		else
		{
			data[histoIndex] = histoCounter;
			histoIndex++;
			histoCounter = 1;
			base[histoIndex] = strengthArray[i].getStrength();
		}

	}

	data[histoIndex] = histoCounter;

	*numOfStrengths = numOfStrength;
	*histogramBase = base;
	*histogramData = data;
}

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
	/*ID tree update*/
	int group = groups.Find(team), tempMax = maxArray[group], tempMaxID = maxIdArray[group];
	Troll* Trolls = TrollTree.inOrder();
	int numOfTrolls = TrollTree.getSize();
	for (int i = 0; i < numOfTrolls; i++) {
		if (Trolls[i].getGroup() == team) {
			int oldStrength = Trolls[i].getStrength();
			int newStrength = oldStrength * factor;
			Trolls[i].setStrength(newStrength);


			if (newStrength > tempMax
				|| ((newStrength == tempMax)
					&& Trolls[i].getID() < tempMaxID)) {
				tempMax = newStrength;
				tempMaxID = Trolls[i].getID();
			}
		}
	}

	/*push updated Troll Array to TrollTree*/
	TrollTree.clear();
	TrollTree.buildEmpty(numOfTrolls);
	int index = 0;
	TrollTree.inOrderInsert(Trolls, &index);
	delete[] Trolls;
	/*update max*/
	maxArray[group] = tempMax;
	maxIdArray[group] = tempMaxID;
	/*strength Tree update*/

	Troll* TrollsByStrength = TrollStrengthTree.inOrder();
	Troll* newStrengthArray = new Troll[numOfTrolls];
	numOfTrolls = TrollTree.getSize();
	int x = 0;
	for (int i = 0; i < numOfTrolls; i++) {
		if (TrollsByStrength[i].getGroup() == team) {
			int oldStrength = TrollsByStrength[i].getStrength();
			int newStrength = oldStrength * factor;
			newStrengthArray[x] = TrollsByStrength[i];
			newStrengthArray[x].setStrength(newStrength);
			Trolls[i] = Troll();
			x++;
		}
	}
	Troll* mergedArray = mergeTrollsArray(TrollsByStrength, newStrengthArray, numOfTrolls);
	/*push updated Troll Array to TrollTree*/
	TrollStrengthTree.clear();
	TrollStrengthTree.buildEmpty(numOfTrolls);
	index = 0;
	TrollStrengthTree.inOrderInsert(mergedArray, &index);
	/*build histogram for strengthTree and update the tree*/
	int numOfStrength = 0;
	int* histogramData = NULL, *histogramBase = NULL;
	buildStrengthHistogram(mergedArray, &histogramData, &histogramBase, numOfTrolls, &numOfStrength);
	strengthTree.clear();
	strengthTree.buildEmpty(numOfStrength);
	index = 0;
	strengthTree.inOrderInsert(histogramBase, histogramData, &index);


	delete[] histogramBase;
	delete[] histogramData;
	delete[] mergedArray;
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


