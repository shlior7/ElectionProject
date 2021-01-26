#include "Reps.h"
#include "DistrictArr.h"

Reps::Reps(int _log_size, const District* _district_num)
{
	district = _district_num;
	log_size = _log_size;
}

Reps::Reps(istream& in, District* dis, DistrictArr& darr)
{
	int id, disn;
	const Citizen* cit;
	in.read(rcastc(&log_size), sizeof(log_size));
	if (!in.good())
		throw (Except("Loading Error"));
	for (int i = 0; i < log_size; i++)
	{
		in.read(rcastc(&id), sizeof(int));
		in.read(rcastc(&disn), sizeof(int));
		if (!in.good())
			throw (Except("Loading Error"));
		cit = darr.getCitizenFrom(id, disn);
		if(cit == nullptr)
			throw (Except("Loading Error"));
		citizen_map.addCitizen(cit);
	}
	district = dis;
}
Reps::~Reps()
{
}

int Reps::size() const
{
	return log_size;
}

int Reps::getDistrictNum() const
{
	return district->getId();
}

const District* Reps::getDistrict() const
{
	return district;
}

void Reps::addCitizenToArr(const Citizen* person)
{
	citizen_map.addCitizen(person);
	log_size = citizen_map.getSize();
}

const string& Reps::getNameOfRep(int idx) const
{
	const Citizen* rep = citizen_map[idx];
	if (rep == nullptr)
		throw Not_Found("Rep");
	return rep->getName();
}


int Reps::getIDRep(int idx) const
{
	const Citizen* rep = citizen_map[idx];
	if (rep == nullptr)
		throw Not_Found("Rep");
	return rep->getID();
}
//
//Reps& Reps::operator=(const Reps& origin)
//{
//	district = origin.district;
//	log_size = origin.log_size;
//	real_size = origin.real_size;
//	for (int i = 0; i < log_size; i++)
//	{
//		citizen_arr[i] = origin.citizen_arr[i];
//	}
//	return *this;
//}

bool Reps::save(ostream& out) const
{
	int id , dis;
	out.write(rcastcc(&log_size), sizeof(log_size));
	for (auto& i : citizen_map.getMap())
	{
		id = i.first; dis = i.second->getDistrict()->getId();
		out.write(rcastcc(&id), sizeof(int));
		out.write(rcastcc(&dis), sizeof(int));
	}
	return out.good();
}

void Reps::printChosenReps(ostream& os,int reps_num) const
{
	int i = 0;
	for (auto it = citizen_map.getMap().begin();
		it != citizen_map.getMap().end()&& i< reps_num; ++it)
		os<< (i++) + 1 << ")" << it->second->getName() << "  ";
	if (!reps_num)os << "no representatives!"<<endl;
	os << endl;
}

ostream& operator<<(ostream& os, Reps& rep) {
	if(!rep.getDistrict()->getName().empty()) os << "District Number: " << rep.getDistrictNum() << endl;
	if (!rep.size())os << "No Represnetatives in district" << endl;
	else os << rep.getCitizenMap()<<endl;
	return os;
}