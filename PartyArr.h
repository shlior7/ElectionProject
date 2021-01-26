#pragma once
#include "PartyPtr.h"
#include "DynamicArr.h"
class District;
class PartyArr
{ 
public:
	/*Init*/
	PartyArr(int _size = 0);
	PartyArr(istream& in, DistrictArr& darr);
	PartyArr(const PartyArr& origin) = delete;
	~PartyArr();

	/*Getters*/
	const Party* getParty(string& name) const;
	const int size() const { return arr.size(); }
	const int capacity() const { return arr.capacity(); }

	/*Serialization*/
	void save(ostream& out) const;
	void load(istream& in, DistrictArr& darr);

	/*Adders*/
	Party* addParty(string& name, int _partyNum, const Citizen* leader);
	void addDistrict(District* district_id);
	void addRep(int party_num, int district_num, const Citizen* newrep);
	void push_back(Party* value);

	/*Sort*/
	void party_sort();
	void merge_sort(int start, int end);

	void Merge(int start, int end);
	/*Checks if RepId is a representative*/
	void CheckIfRep(int repId) const;

	/*Operators*/
	friend ostream& operator<<(ostream& os, PartyArr& arr);
	friend ostream& operator<<(ostream& os, const PartyArr& arr);
	Party* operator[](int i) { return arr[i]; }
	const Party* operator[](int i) const{ return arr[i]; }
	
private:
	vector<Party*> arr;
};
