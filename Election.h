#pragma once

/****
 *We have Array of District with each district having
 *an array of DistrictVotes Orginized by party
 *and a citizen map of all citizen in the district
 *
 *Also an Array of Parties with each party having
 *an array of reps orginized by district
 *and with a const citizen map pointers to the reps
 * 
 */



enum election_type { regular_election = 0,simple_election = 1 };
#include "Date.h"
#include "PartyArr.h"
#include "DistrictArr.h"
	class Election
	{
	protected:
		election_type type;
		Date date_Of_Election;
		DistrictArr districtList;
		PartyArr partyList;
		int new_party_id;
		int new_district_id;

	public:
		/*Init*/
		Election();
		Election(Date& date);
		Election(istream& in);
		~Election() { }
		
		/*Getters*/
		Date& getDateOfElection() { return date_Of_Election; }
		PartyArr& getPartyList() { return partyList; }
		DistrictArr& getDistrictList() { return districtList; }
		const election_type& getType() const{ return type; }
		
		/*Setters*/
		bool SetDate(int day, int month, int year);
		bool setType(election_type& t) { type = t; }
		
		/*Adders*/
		void addDistrict(string& name,const int reps,Type type);
		void addParty(string& name, int candidate_id);
		virtual void addCitizen(string& name, int id, int birth_year, int district_num);
		virtual void addRep(int party_num, int id, int district_num);
		virtual void addVote(int id, int district_num,int party_num);
		
		/*Calculation*/
		void sumResults();
		void checkReps();
		
		/*Serialization*/
		void save(ostream& out) const;
		
		/*Operators*/
		friend ostream& operator<<(ostream& os, Election& election);
	};