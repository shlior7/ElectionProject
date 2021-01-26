#pragma once
#include "Reps.h"
#include "DynamicArr.h"
class District;
class DistrictArr;
//Representative array organized by district
class RepsArr
{
public:
	/*Init*/
	RepsArr(int size=2);
	~RepsArr();

	/*Adders*/
	void addDistrict(const District* district_id);
	void addRep(const Citizen* rep, int district_id);
	void push_back(Reps* reps);
	
	/*Getters*/
	const Reps* getRepsOfDistrict(int district_num) const;
	const int size() const { return arr.size(); }
	const int capacity() const { return arr.capacity(); }
	const Citizen* getRepbyId(int repId) const;

	/*Serialization*/
	bool save(ostream& out) const;
	void load(istream& in, DistrictArr& darr);

	/*Operators*/
	Reps* operator[](int i) const { return arr[i]; }
	friend ostream& operator<<(ostream& os, const RepsArr& repsArr);
private:
	vector<Reps*> arr;

};



