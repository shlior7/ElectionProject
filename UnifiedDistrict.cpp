#include "UnifiedDistrict.h"



void UnifiedDistrict::calculateReps()
{
	calculateWinner();
	for (int i = 0; i < votes_arr.size(); i++)
	{
		votes_arr[i].votedPrecent = ((float)votes_arr[i].votes / (float)numOfVotes) * 100;
		votes_arr[i].reps_num = 0;
		
	}
	votes_arr[getWinner()].reps_num = reps;
	
}
