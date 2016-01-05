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

StatusType AddStudent(void * DS, int studentID, int average)
{
	if (!DS || studentID < 0 || average < 0 || average>100)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->AddStudent(studentID, average);
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

StatusType AssignStudent(void * DS, int studentID, int studyGroup)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->AssignStudent(studentID, studyGroup);
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

StatusType JoinFaculties(void * DS, int studyGroup1, int studyGroup2)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->JoinFaculties(studyGroup1, studyGroup2);
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

StatusType UnifyFacultiesByStudents(void * DS, int studentID1, int studentID2)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->UnifyFacultiesByStudents(studentID1, studentID2);
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

StatusType GetFaculty(void * DS, int studentID, int * faculty)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->GetFaculty(studentID, faculty);
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

StatusType UpgradeStudyGroup(void * DS, int studyGroup, int factor)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->UpgradeStudyGroup(studyGroup, factor);
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

StatusType GetSmartestStudent(void * DS, int facultyID, int * student)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->GetSmartestStudent(facultyID,student);
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

StatusType GetNumOfStudentsInRange(void * DS, int fromAvg, int toAvg, int * num)
{
	if (!DS)
	{
		return INVALID_INPUT;
	}
	DataStruct* data = (DataStruct*)DS;
	try {
		data->GetNumOfStudentsInRange(fromAvg,toAvg,num);
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
