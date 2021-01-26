#include "DividedDistrict.h"


void DividedDistrict::calculateReps()
{
	calculateWinner();
	for (auto i = 0; i < votes_arr.size(); i++)
	{
		votes_arr[i].votedPrecent = ((float)votes_arr[i].votes / (float)numOfVotes) * 100;
		if (i < votes_arr.size() - 1)votes_arr[i].reps_num = round((float)((float)reps * (float)votes_arr[i].votedPrecent) / 100.f);
		else votes_arr[i].reps_num = floor((float)((float)reps * (float)votes_arr[i].votedPrecent) / 100.f);//round down the last party for so the sum of all of (reps_num) will be (reps)
		cout<<round((float)((float)reps * (float)votes_arr[i].votedPrecent) / 100.f);
		cout << "votes_arr[i].votedPrecent" << votes_arr[i].votedPrecent << endl;
		cout << "votes_arr[i].votes" << votes_arr[i].votes << endl;
		cout << "numOfVotes" << numOfVotes << endl;
		cout << "reps" << reps << endl;
		cout << "votes_arr[i].reps_num " << votes_arr[i].reps_num << endl;
	}
	
}

