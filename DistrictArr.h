#pragma once
#include "District.h"
//#include "DistrictPtr.h"
#include "DynamicArr.h"

class PartyArr;
class DistrictPtr;
class DistrictArr 
{
public:
	/*init*/
	DistrictArr(int size = 2);
	DistrictArr(const DistrictArr& origin) = delete;
	~DistrictArr();
	DistrictArr& operator=(const DistrictArr& other) = delete;
	
	/*Getters:*/
	const District* getDistrict(string& district_name) const;
	const Citizen* getCitizenFrom(int id, int district_num = -1);
	const int size() const { return arr.size(); }
	const int capacity() const { return arr.capacity(); }
	const int getTotalVotes() const { return TotalNumOfVotes; }
	
	/*Adders:*/
	District* addDistrict(string& name, int district_id, int reps,Type t);
	void addCitizen(string& name, int id, int birthyear, int district_id);
	void addParty(Party* party_num);
	void addVote(int party_num,int district_num);
	void addRep(int party_num, int id, int district_id);
	void push_back(District* value);
	
	
	/*Serialization*/
	void save(ostream& out) const;
	void load(istream& in);
	void saveVotes(ostream& out) const;
	void loadVotes(istream& in, PartyArr& parr);
	
	/*Printers*/
	void printDistricts();

	/*Operators: */
	friend ostream& operator<<(ostream& os, DistrictArr& arr);
	District* operator[](int i) { return arr[i]; }

private:
	vector<District*> arr;
	int TotalNumOfVotes;
};


