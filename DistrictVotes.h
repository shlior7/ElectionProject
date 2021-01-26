#pragma once
#include "PartyArr.h"

class Party;
class PartyArr;
//a single element is all votes related info of each party
struct DistrictVotes
{
	Party* party;
	int votes;
	float votedPrecent;
	int reps_num;

	DistrictVotes(Party* _party = nullptr) {
		party = _party;
		votes = 0;
		reps_num = 0;
		votedPrecent = 0;
	}
	DistrictVotes& operator=(const DistrictVotes& dv)
	{
		this->party = dv.party;
		this->votes = dv.votes;
		this->reps_num = dv.reps_num;
		this->votedPrecent = dv.votedPrecent;
		return *this;
	}
	~DistrictVotes(){}
	bool operator<(vector<DistrictVotes>::const_reference district_votes) const{
		return votes > district_votes.votes;
	}
};
// array of vote info by party and the winner
class DistrictVotesArr
{
public:
	/*Init*/
	DistrictVotesArr(int size = 2);
	DistrictVotesArr(istream& in, PartyArr& parr);
	~DistrictVotesArr();
	DistrictVotesArr& operator=(const DistrictVotesArr& other) = delete;
	
	/*Serialization*/
	bool save(ostream& out) const;
	void load(istream& in,PartyArr& parr);

	/*Getters: */
	int getWinner() const { return Winner; }
	int getVotes(int party_id) const;
	int getReps(int party_id) const;
	float getVotedPrecent(int party_id) const;
	void sortPartyVotes();
	void merge_sort(int start, int end);
	void Merge(int start, int end);
	const int size() const { return arr.size(); }

	/*Setters*/
	void calcWinner();
	bool setWinner(int winner);
	
	/*Adders*/
	void addParty(Party* party);
	void addVote(int party_id);
	void addRep(int party_id);
	void push_back(const DistrictVotes& value);

	/*Operators*/
	friend ostream& operator<<(ostream& os, const DistrictVotesArr& distv);
	DistrictVotes& operator[](int i) { return arr[i]; }
	const DistrictVotes& operator[](int i) const { return arr[i]; }
	const DistrictVotes& operator<(int i) const { return arr[i]; }
	//friend bool operator<(DistrictVotes const& a, DistrictVotes const& b);

private:
	vector<DistrictVotes> arr;
	int Winner;
};

