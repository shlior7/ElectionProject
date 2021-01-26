#include "CitizenMap.h"

class District;

CitizenMap::~CitizenMap() {
	for(auto a:citizen_map)
	{
		delete a.second;
	}
	citizen_map.clear();
}

Citizen* CitizenMap::getCitizenByID(const int id) const
{
	
	if (citizen_map.find(id) == citizen_map.end())
		return nullptr;
	return citizen_map.at(id);
}

void CitizenMap::addCitizen(string& _name, int _id, int _birth_year, District* district)
{
	citizen_map[_id] = (new Citizen(_name, _id, _birth_year, district));
}


bool CitizenMap::save(ostream& out) const
{
	int size = getSize();
	out.write(rcastcc(&size), sizeof(size));
	for (auto& pair : citizen_map) {
		int id = pair.first;
		Citizen* Cit = pair.second;
		out.write(rcastcc(&(id)), sizeof(id));
		Cit->save(out);
	}
	return out.good();
}

void CitizenMap::load(istream& in, District* dis)
{
	Citizen* newCit;
	int size;
	in.read(rcastc(&size), sizeof(size));
	if (!in.good())
		throw Except("Loading Error");
	for (int i = 0; i < size; i++)
	{
		int id;
		in.read(rcastc(&id), sizeof(id));
		if (!in.good())
			throw Except("Loading Error");
		newCit = new Citizen(in,dis);
		citizen_map[id] = newCit;
	}
}

ostream& operator<<(ostream& os, const CitizenMap& map)
{
	for (auto& c: map.citizen_map)
	{
		os << *(c.second);
	}
	return os;
}

ConstCitizenMap::~ConstCitizenMap() {
	citizen_map.clear();
}

const Citizen* ConstCitizenMap::getCitizenByID(const int id) const
{

	if (citizen_map.find(id) == citizen_map.end())
		return nullptr;
	return citizen_map.at(id);
}

void ConstCitizenMap::addCitizen(const Citizen* cit)
{
	citizen_map[cit->getID()] = cit;
}

bool ConstCitizenMap::save(ostream& out) const
{
	int size = getSize();
	out.write(rcastcc(&size), sizeof(size));
	for (auto& pair : citizen_map) {
		out.write(rcastcc(&(pair.first)), sizeof(int));
		pair.second->save(out);
	}
	return out.good();
}

ostream& operator<<(ostream& os, const ConstCitizenMap& map)
{
	int i = 0;
	for (auto& c : map.citizen_map){
		os << (i++) + 1 << ")" << c.second->getName() << "  ";
	}
	return os;
}

