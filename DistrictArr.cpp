#include "DistrictArr.h"
#include "DividedDistrict.h"
#include "UnifiedDistrict.h"
class Citizen;
DistrictArr::DistrictArr(int size) {
	TotalNumOfVotes = 0;
}

DistrictArr::~DistrictArr()
{
	for (int i = 0; i < size(); i++)
		delete arr[i];
}


const District* DistrictArr::getDistrict(string& district_name) const
{
	for (int i = 0; i < size(); i++)
	{
		if (arr[i]->getName() == district_name) {
			return arr[i];
		}
	}
	return nullptr;
}

District* DistrictArr::addDistrict(string& name, int district_id, int reps,Type t)
{
	District* new_district = NULL;
	switch (t) {
	case Type::unified:
		new_district = new UnifiedDistrict(name, district_id, reps);
		break;
	case Type::divided:
		new_district = new DividedDistrict(name, district_id, reps);
		break;
	}
	arr.push_back(new_district);
	return new_district;
}



void DistrictArr::addCitizen(string& name, int id, int birth_year, int district_id)
{

	if (size() <= district_id)
		throw Not_Found("District");
	for (int j = 0; j < size(); j++)
	{
		if (arr[j]->getCitizen(id) != nullptr)
			throw Already_Exists("Citizen");
	}
	arr[district_id]->addCitizen(name, id, birth_year);
}

void DistrictArr::addParty(Party* party_num)
{
	for (int i = 0; i < size(); i++) {
		arr[i]->addParty(party_num);
	}
}

void DistrictArr::addVote(int party_num, int district_num)
{
	if (district_num >= size())
		throw Not_Found("District");

	arr[district_num]->addVote(party_num);
	TotalNumOfVotes++;
}

void DistrictArr::addRep(int party_num, int id, int district_id)
{
	arr[district_id]->addRep(party_num);
}

const Citizen* DistrictArr::getCitizenFrom(int id, int district_num) 
{
	
	if (district_num != -1) {
		return arr[district_num]->getCitizen(id);
	}
	const Citizen* get = nullptr;
	for (int i = 0; i < size(); i++) {
		get = arr[i]->getCitizen(id);
		if (get != nullptr)
			return get;
	}
	return nullptr;
}
ostream& operator<<(ostream& os, DistrictArr& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if(!arr[0]->getName().empty()) os << *(arr[i]) << endl;
		os << arr[i]->getCitizenMap();
	}
	return os;
}

void DistrictArr::printDistricts()
{
	for (int i = 0; i < size(); i++)
	{
		cout << *arr[i] << endl;
	}
}
void DistrictArr::push_back(District* value) {
	
	arr.push_back(value);
}
void DistrictArr::save(ostream& out) const
{
	int t;
	int lSize = size();
	out.write(rcastcc(&lSize), sizeof(lSize));
	out.write(rcastcc(&TotalNumOfVotes), sizeof(TotalNumOfVotes));
	for (int i = 0; i < lSize; i++)
	{
		t = (int)(arr[i]->getType());
		out.write(rcastcc(&t), sizeof(t));
		arr[i]->save(out);
	}
	if (!out.good())
		throw Except("Saving Error");
}
void DistrictArr::load(istream& in)
{
	District* d = NULL;
	int type;
	int logsize;
	in.read(rcastc(&logsize), sizeof(logsize));
	in.read(rcastc(&TotalNumOfVotes), sizeof(TotalNumOfVotes));
	if (!in.good())
		throw Except("Loading Error");
	for (int i = 0; i < logsize; i++)
	{
		in.read(rcastc(&type), sizeof(type));
		switch (type) {
		case (int)Type::divided:
			d = new DividedDistrict(in);
			break;
		case (int)Type::unified:
			d = new UnifiedDistrict(in);
			break;
		}
		push_back(d);
	}
}
void DistrictArr::saveVotes(ostream& out) const
{
	int lSize = size();
	//out.write(rcastcc(&lSize), sizeof(lSize));
	for (int i = 0; i < size(); i++)
		arr[i]->getVotesArr().save(out);
	
	if (!out.good())
		throw Except("Saving Error");
}
void DistrictArr::loadVotes(istream& in, PartyArr& parr)
{
	int lSize;
	//in.read(rcastc(&lSize), sizeof(lSize));
	for (int i = 0; i < size(); i++)
		arr[i]->loadVotes(in, parr);
	if (!in.good())
		throw Except("Loading Error");
}