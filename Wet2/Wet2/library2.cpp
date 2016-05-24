#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#include "library2.h"
#include "DataStruct.h"

using std::exception;

void * Init(int n)
{
	if (n < 2)
	{
		return NULL;
	}
	try {
		DataStruct* ds = new DataStruct(n);
		void* ptr = (void*)ds;
		return ptr;
	}
	catch (...)
	{
		return NULL;
	}


}

StatusType AddTroll(void * DS, int TrollID, int strength)
{
	if (!DS || TrollID < 0 || strength < 0)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->AddTroll(TrollID, strength);
	}
	catch (DataStruct::Failure& f)
	{
		return FAILURE;
	}
	catch (std::bad_alloc& ba)
	{
		return ALLOCATION_ERROR;
	}


	return SUCCESS;
}

StatusType AssignTroll(void * DS, int TrollID, int team)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->AssignTroll(TrollID, team);
	}
	catch (DataStruct::Failure& f)
	{
		return FAILURE;
	}
	catch (DataStruct::InvalidInput& invalid)
	{
		return INVALID_INPUT;
	}
	catch (std::bad_alloc& ba)
	{
		return ALLOCATION_ERROR;
	}


	return SUCCESS;
}

StatusType JoinGroups(void * DS, int team1, int team2)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->JoinGroups(team1, team2);
	}
	catch (DataStruct::Failure& f)
	{
		return FAILURE;
	}
	catch (DataStruct::InvalidInput& invalid)
	{
		return INVALID_INPUT;
	}
	catch (std::bad_alloc& ba)
	{
		return ALLOCATION_ERROR;
	}


	return SUCCESS;
}
/*
StatusType UnifyFacultiesByTrolls(void * DS, int TrollID1, int TrollID2)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->UnifyFacultiesByTrolls(TrollID1, TrollID2);
	}
	catch (DataStruct::Failure& f)
	{
		return FAILURE;
	}
	catch (DataStruct::InvalidInput& invalid)
	{
		return INVALID_INPUT;
	}
	catch (std::bad_alloc& ba)
	{
		return ALLOCATION_ERROR;
	}
	

	return SUCCESS;
}
*/
StatusType GetGroup(void * DS, int TrollID, int * group)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->GetGroup(TrollID, group);
	}
	catch (DataStruct::Failure& f)
	{
		return FAILURE;
	}
	catch (DataStruct::InvalidInput& invalid)
	{
		return INVALID_INPUT;
	}
	catch (std::bad_alloc& ba)
	{
		return ALLOCATION_ERROR;
	}


	return SUCCESS;
}

StatusType TeamUpgrade(void * DS, int team, int factor)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->TeamUpgrade(team, factor);
	}
	catch (DataStruct::Failure& f)
	{
		return FAILURE;
	}
	catch (DataStruct::InvalidInput& invalid)
	{
		return INVALID_INPUT;
	}
	catch (std::bad_alloc& ba)
	{
		return ALLOCATION_ERROR;
	}


	return SUCCESS;
}

StatusType GetStrongestTroll(void * DS, int groupID, int * Troll)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->GetStrongestTroll(groupID,Troll);
	}
	catch (DataStruct::Failure& f)
	{
		return FAILURE;
	}
	catch (DataStruct::InvalidInput& invalid)
	{
		return INVALID_INPUT;
	}
	catch (std::bad_alloc& ba)
	{
		return ALLOCATION_ERROR;
	}


	return SUCCESS;
}

StatusType GetNumOfTrollsInRange(void * DS, int min, int max, int * num)
{
	if (!DS || !num)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->GetNumOfTrollsInRange(min,max,num);
	}
	catch (DataStruct::Failure& f)
	{
		return FAILURE;
	}
	catch (DataStruct::InvalidInput& invalid)
	{
		return INVALID_INPUT;
	}
	catch (std::bad_alloc& ba)
	{
		return ALLOCATION_ERROR;
	}


	return SUCCESS;
}

void Quit(void ** DS)
{
	if (!DS)
	{
		return;
	}
	DataStruct* data = (DataStruct*)*DS;
	delete data;
	*DS = NULL;

}
