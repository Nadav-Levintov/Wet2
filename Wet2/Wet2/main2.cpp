/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2016                                          */
/*                                                                         */
/* Homework : Wet 2                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main2.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "library2.h"
#include <cstring>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
	NONE_CMD = -2,
	COMMENT_CMD = -1,
	INIT_CMD = 0,
	ADDTROLL_CMD = 1,
	ASSIGNTROLL_CMD = 2,
	JOINGROUPS_CMD = 3,
	GETGROUP_CMD = 4,
	TEAMUPGRADE_CMD = 5,
	GETSTRONGEST_CMD = 6,
	GETINRANGE_CMD = 7,
	QUIT_CMD = 8
} commandType;

static const int numActions = 9;
static const char *commandStr[] = { "Init", "AddTroll", "AssignTroll",
		"JoinGroups", "GetGroup", "TeamUpgrade",
		"GetStrongestTroll", "GetNumOfTrollsInRange", "Quit" };

static const char* ReturnValToStr(int val) {
	switch (val) {
	case (SUCCESS):
		return "Success";
	case (FAILURE):
		return "Failure";
	case (ALLOCATION_ERROR):
		return "Allocation_error";
	case (INVALID_INPUT):
		return "Invalid_input";
	default:
		return "";
	}
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
	error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
	char buffer[MAX_STRING_INPUT_SIZE];
	// Reading commands
	while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
		fflush(stdout);
		if (parser(buffer) == error)
			break;
	};
	return 0;
}
;

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
		const char** const command_arg) {
	if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
		return (NONE_CMD);
	if (StrCmp("#", command)) {
		if (strlen(command) > 1)
			printf("%s", command);
		return (COMMENT_CMD);
	};
	for (int index = 0; index < numActions; index++) {
		if (StrCmp(commandStr[index], command)) {
			*command_arg = command + strlen(commandStr[index]) + 1;
			return ((commandType) index);
		};
	};
	return (NONE_CMD);
}
;

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddTroll(void* DS, const char* const command);
static errorType OnAssignTroll(void* DS, const char* const command);
static errorType OnJoinGroups(void* DS, const char* const command);
static errorType OnGetGroup(void* DS, const char* const command);
static errorType OnTeamUpgrade(void* DS, const char* const command);
static errorType OnGetStrongestTroll(void* DS, const char* const command);
static errorType OnGetNumOfTrollsInRange(void* DS,
		const char* const command);
static errorType OnQuit(void** DS, const char* const command);


/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
	static void *DS = NULL; /* The general data structure */
	const char* command_args = NULL;
	errorType rtn_val = error;

	commandType command_val = CheckCommand(command, &command_args);

	switch (command_val) {

	case (INIT_CMD):
		rtn_val = OnInit(&DS, command_args);
		break;
	case (ADDTROLL_CMD):
		rtn_val = OnAddTroll(DS, command_args);
		break;
	case (ASSIGNTROLL_CMD):
		rtn_val = OnAssignTroll(DS, command_args);
		break;
	case (JOINGROUPS_CMD):
		rtn_val = OnJoinGroups(DS, command_args);
		break;
	case (GETGROUP_CMD):
		rtn_val = OnGetGroup(DS, command_args);
		break;
	case (TEAMUPGRADE_CMD):
		rtn_val = OnTeamUpgrade(DS, command_args);
		break;
	case (GETSTRONGEST_CMD):
		rtn_val = OnGetStrongestTroll(DS, command_args);
		break;
	case (GETINRANGE_CMD):
		rtn_val = OnGetNumOfTrollsInRange(DS, command_args);
		break;
	case (QUIT_CMD):
		rtn_val = OnQuit(&DS, command_args);
		break;

	case (COMMENT_CMD):
		rtn_val = error_free;
		break;
	case (NONE_CMD):
		rtn_val = error;
		break;
	default:
		assert(false);
	};
	return (rtn_val);
}
;

int INIT_n;

/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if (isInit) {
		printf("Init was already called.\n");
		return (error_free);
	};
	isInit = true;

	ValidateRead( sscanf(command, "%d",&INIT_n), 1, "Init failed.\n");

	*DS = Init(INIT_n);
	if (*DS == NULL) {
		printf("Init failed.\n");
		return (error);
	};
	printf("Init done.\n");

	return error_free;
}

/***************************************************************************/
/* OnAddTroll                                                          */
/***************************************************************************/
static errorType OnAddTroll(void* DS, const char* const command) {
	int trollID;
	int strength;
	ValidateRead( sscanf(command, "%d %d",&trollID,&strength), 2,
			"AddTroll failed.\n");
	StatusType res = AddTroll(DS, trollID, strength);

	printf("AddTroll: %s\n", ReturnValToStr(res));

	return error_free;
}

/***************************************************************************/
/* OnAssignTroll                                                       */
/***************************************************************************/
static errorType OnAssignTroll(void* DS, const char* const command) {
	int trollID;
	int team;
	ValidateRead( sscanf(command, "%d %d",&trollID,&team), 2,
			"AssignTroll failed.\n");
	StatusType res = AssignTroll(DS, trollID, team);

	printf("AssignTroll: %s\n", ReturnValToStr(res));

	return error_free;
}

/***************************************************************************/
/* OnJoinGroups                                                       */
/***************************************************************************/
static errorType OnJoinGroups(void* DS, const char* const command) {
	int team1;
	int team2;
	ValidateRead( sscanf(command, "%d %d",&team1,&team2), 2,
			"JoinGroups failed.\n");
	StatusType res = JoinGroups(DS, team1, team2);

	printf("JoinGroups: %s\n", ReturnValToStr(res));

	return error_free;
}

/***************************************************************************/
/* OnGetGroup                                                         */
/***************************************************************************/
static errorType OnGetGroup(void* DS, const char* const command) {
	int trollID;
	ValidateRead( sscanf(command, "%d",&trollID), 1,
			"GetGroup failed.\n");
	int dep;
	StatusType res = GetGroup(DS, trollID, &dep);

	if (res != SUCCESS) {
		printf("GetGroup: %s\n", ReturnValToStr(res));
	} else {
		printf("GetGroup: %s %d\n", ReturnValToStr(res), dep);
	}

	return error_free;
}

/***************************************************************************/
/* OnTeamUpgrade                                                           */
/***************************************************************************/
static errorType OnTeamUpgrade(void* DS, const char* const command) {
	int teamID;
	int factor;
	ValidateRead( sscanf(command, "%d %d",&teamID,&factor), 2,
			"TeamUpgrade failed.\n");
	StatusType res = TeamUpgrade(DS, teamID, factor);

	printf("TeamUpgrade: %s\n", ReturnValToStr(res));

	return error_free;
}

/***************************************************************************/
/* OnGetStrongestTroll                                                 */
/***************************************************************************/
static errorType OnGetStrongestTroll(void* DS, const char* const command) {
	int groupID;
	ValidateRead( sscanf(command, "%d",&groupID), 1,
			"GetStrongestTroll failed.\n");
	int troll;
	StatusType res = GetStrongestTroll(DS, groupID, &troll);

	if (res != SUCCESS) {
		printf("GetStrongestTroll: %s\n", ReturnValToStr(res));
	} else {
		printf("GetStrongestTroll: %s %d\n", ReturnValToStr(res),
				troll);
	}

	return error_free;
}

/***************************************************************************/
/* OnGetNumOfTrollsInRange                                             */
/***************************************************************************/
static errorType OnGetNumOfTrollsInRange(void* DS,
		const char* const command) {
	int min;
	int max;
	ValidateRead( sscanf(command, "%d %d",&min,&max), 2,
			"GetNumOfTrollsInRange failed.\n");
	int troll;
	StatusType res = GetNumOfTrollsInRange(DS, min, max, &troll);

	if (res != SUCCESS) {
		printf("GetNumOfTrollsInRange: %s\n", ReturnValToStr(res));
	} else {
		printf("GetNumOfTrollsInRange: %s %d\n", ReturnValToStr(res),
				troll);
	}

	return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	Quit(DS);
	if (*DS != NULL) {
		printf("Quit failed.\n");
		return (error);
	};
	isInit = false;
	printf("Quit done.\n");

	return error_free;
}

#ifdef __cplusplus
}
#endif
