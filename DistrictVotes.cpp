#include "DistrictVotes.h"

DistrictVotesArr::DistrictVotesArr(int size)
{
	
}

DistrictVotesArr::~DistrictVotesArr()
{
	
}

void DistrictVotesArr::addParty(Party* party_id)
{
	push_back(DistrictVotes(party_id));
}

void DistrictVotesArr::addVote(int party_id)
{
	if (party_id >= size())
		throw Not_Found("Party");
	arr[party_id].votes++;
}

void DistrictVotesArr::addRep(int party_id)
{
	if (party_id >= size())
		throw Not_Found("Party");
	arr[party_id].reps_num++;
}

void DistrictVotesArr::push_back(const DistrictVotes& value)
{
	arr.push_back(value);
}


bool DistrictVotesArr::setWinner(int winner)
{
	Winner = winner;
	return true;
}
void DistrictVotesArr::calcWinner() 
{
	int winner_votes = 0;
	int winner = 0;
	for (int i = 0; i < size(); i++)
	{
		if (winner_votes < arr[i].votes) {
			winner_votes = arr[i].votes;
			winner = i;
		}
		if (winner_votes == arr[i].votes) {
			if (arr[i].party->getId() < arr[winner].party->getId())
				winner = i;
		}

	}
	Winner = arr[winner].party->getId();
}

int DistrictVotesArr::getVotes(int party_id) const
{
	if (party_id >= size())
		throw Not_Found("Party");
	
	return arr[party_id].votes;
}

int DistrictVotesArr::getReps(int party_id) const
{
	if (party_id >= size())
		throw Not_Found("Party");
	return arr[party_id].reps_num;
}
float DistrictVotesArr::getVotedPrecent(int party_id) const
{
	return arr[party_id].votedPrecent;
}
void DistrictVotesArr::sortPartyVotes(){
	merge_sort(0,arr.size()-1);
}

void DistrictVotesArr::merge_sort(int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		merge_sort(start, mid); // merge sort the elements between [start, mid]
		merge_sort(mid + 1, end); // merge sort the elements between [mid+1, end]
		Merge(start, end);   // merge both
	}
}

// template function to merge two sorted arrays
void DistrictVotesArr::Merge(int start, int end)
{
	int z, x, y, mid;

	vector<DistrictVotes> temp(end - start + 1);
	mid = (start + end) / 2;
	z = 0;
	x = start;
	y = mid + 1;
	while (x <= mid && y <= end) {
		if (arr[x] < arr[y]) {
			temp[z] = arr[x];
			++x, ++z;
		}
		else {
			temp[z] = arr[y];
			++y, ++z;
		}
	}
	while (x <= mid) {
		temp[z] = arr[x];
		++x, ++z;
	}

	while (y <= end) {
		temp[z] = arr[y];
		++y, ++z;
	}
	for (int i = start; i <= end; ++i) {
		arr[i] = temp[i - start];
	}
}
ostream& operator<<(ostream& os, const DistrictVotesArr& distv)
{
	for (int i = 0; i < distv.size(); i++)
	{
		os << "    Party Name: " << distv[i].party->getName() << endl <<
			"    Number of Representatives: " << distv[i].reps_num << endl <<
			"    Number of Voters: " << distv[i].votes << endl <<
			"    Voted Precent: " << distv[i].votedPrecent << endl <<
			"***********************************" << endl;
	}
	return os;
}
bool DistrictVotesArr::save(ostream& out) const
{
	int lSize = size();
	out.write(rcastcc(&lSize), sizeof(lSize));
	out.write(rcastcc(&Winner), sizeof(Winner));

	for (int i = 0; i < lSize; i++)
	{
		out.write(rcastcc(&(arr[i].votes)), sizeof(int));
		out.write(rcastcc(&(arr[i].votedPrecent)), sizeof(float));
		out.write(rcastcc(&(arr[i].reps_num)), sizeof(int));
	}
	return out.good();

}

void DistrictVotesArr::load(istream& in, PartyArr& parr) {

	int lsize, win, votes, reps;
	float prec;
	in.read(rcastc(&lsize), sizeof(lsize));
	in.read(rcastc(&win), sizeof(win));
	Winner = win;
	DistrictVotes dis;
	for (int i = 0; i < lsize; i++)
	{
		if (parr[i] == nullptr)
			throw Except("Loading Error");
		dis.party = parr[i];
		in.read(rcastc(&(votes)), sizeof(votes));
		in.read(rcastc(&(prec)), sizeof(prec));
		in.read(rcastc(&(reps)), sizeof(reps));
		if (!in.good())
			throw Except("Loading Error");
		dis.votes = votes;
		dis.votedPrecent = prec;
		dis.reps_num = reps;
		push_back(dis);
	}
}