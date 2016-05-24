/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet  2                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library2.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET2_
#define _234218_WET2_


#ifdef __cplusplus
extern "C" {
#endif




/* Return Values
 * ----------------------------------- */
typedef enum {
	SUCCESS = 0,
	FAILURE = -1,
	ALLOCATION_ERROR = -2,
	INVALID_INPUT = -3

} StatusType;



/* Required Interface for the Data Structure
 * -----------------------------------------*/



/* Description:   Initializes the system with n teams.
 * Input:         n - Number of teams.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void*       Init(int n);


/* Description:   A troll was added to the system.
 * Input:         DS - A pointer to the data structure.
 *                trollID - The ID of the troll.
 *                strength - initial strength value of the troll.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or trollID<0 or strength<0.
 *                FAILURE - If a troll with trollID already in the system, or in the case of any other problem.
 *                SUCCESS - Otherwise.
 */
StatusType   AddTroll(void* DS, int trollID, int strength);


/* Description:   The troll with ID trollID decides to join a team.
 * Input:         DS - A pointer to the data structure.
 *                trollID - The ID of the troll.
 *                team - The ID of the team he joins.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, trollID<0 or team is not an illegal team number.
 *                FAILURE - If a troll with same ID already assigned to another team, there is no troll in the system with this ID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   AssignTroll(void* DS, int trollID, int team);


/* Description:   Joins the two groups of team1 and team2 together, the name of the joined group is the name of team1 group.
 * Input:         DS - A pointer to the data structure.
 *                team1 - The identifier of the 1st team.
 *                team2 - The identifier of the 2nd team.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or either team1 or team2 are illegal team numbers.
 *                FAILURE - If both teams belong to the same groups, or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   JoinGroups(void* DS, int team1, int team2);


/* Description:   Returns the group to which trollID belongs.
 * Input:         DS - A pointer to the data structure.
 *                trollID - The identifier of the troll.
 * Output:        group - The identifier of the group.
 * Return Values: INVALID_INPUT - If DS==NULL, trollID<0 or group==NULL.
 *                FAILURE - If there is no troll in the system with this ID, or trollID doesn't belong to any team or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   GetGroup(void* DS, int trollID, int* group);


/* Description:   Multiplies the strength of every troll in teamID by factor.
 * Input:         DS - A pointer to the data structure.
 *                teamID - The team which is upgraded.
 *                factor - the factor in which to multiply the strength of the trolls.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 * 				  INVALID_INPUT - If DS==NULL, factor<1 or teamID is an illegal team number.
 *                SUCCESS - Otherwise.
 */
StatusType   TeamUpgrade(void* DS, int teamID, int factor);

/* Description:   Returns the ID of the strongest troll in group groupID.
 * 				  If two or more trolls have the same strength, the troll with minimal ID is returned.
 * Input:         DS - A pointer to the data structure.
 *                groupID - The identifier of the group.
 * Output:        troll - The identifier of the troll.
 * Return Values: INVALID_INPUT - If DS==NULL, groupID isn't in range 0,.., n-1 or troll==NULL.
 *                FAILURE - If there is no trolls in groupID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   GetStrongestTroll(void* DS, int groupID, int* troll);

/* Description:   Returns the number of trolls in system with strength in range (min, max].
 * Input:         DS - A pointer to the data structure.
 *                min - The strength minimal value.
 *                max - The strength maximal value.
 * Output:        num - The number of trolls.
 * Return Values: INVALID_INPUT - If DS==NULL, num==NULL, min>=max or min<0.
 *                FAILURE - In case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   GetNumOfTrollsInRange(void* DS, int min, int max, int* num);

/* Description:   Quits and deletes the database.
 *                The variable pointed by DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS);





#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET2_ */
