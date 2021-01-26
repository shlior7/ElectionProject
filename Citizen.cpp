#include "Citizen.h"
#include "District.h"

Citizen::Citizen()
{
	id = 0;
	name = "";
	yearOfBirth = 0;
	votedfor = -1;
	district = nullptr;
}

Citizen::Citizen(istream& in, District* dis)
{
	getline(in, name, '\0');
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&yearOfBirth), sizeof(yearOfBirth));
	in.read(rcastc(&votedfor), sizeof(votedfor));
	if (!in.good())
		throw Except("Loading Error");
	district = dis;
}

Citizen::Citizen(string& _name, int _id, int _yearOfBirth, District* _district) :id(_id),
yearOfBirth(_yearOfBirth) {
	name = _name;
	district = _district;
	votedfor = -1;
}

Citizen::~Citizen() {}

Citizen::Citizen(const Citizen& citizen) {
	SetName(citizen.getName());
	SetId(citizen.getID());
	SetYearOfBirth(citizen.getYearOfBirth());
}

bool Citizen::SetName(string name) {
	this->name = name;
	return true;
}

bool Citizen::SetId(int id) {
	this->id = id;
	return true;
}

bool Citizen::SetYearOfBirth(int yearOfBirth) {
	this->yearOfBirth = yearOfBirth;
	return true;
}

bool Citizen::SetDistrictNumber(int districtNumber) {
	return true;
}

bool Citizen::SetVotedFor(int votedfor) {
	this->votedfor = votedfor;
	return true;
}

bool Citizen::save(ostream& out) const
{
	out.write(name.c_str(), name.size());
	out.write("\0", sizeof(char));
	out.write(rcastcc(&id), sizeof(id));
	out.write(rcastcc(&yearOfBirth), sizeof(yearOfBirth));
	out.write(rcastcc(&votedfor), sizeof(votedfor));
	return out.good();
}
ostream& operator<<(ostream& os, const Citizen& citizen)
{
	os << "********************" << std::endl <<
		"Name: " << citizen.name << std::endl <<
		"Id:" << citizen.id << std::endl <<
		"Birth Year: " << citizen.yearOfBirth << std::endl;
	if (citizen.votedfor != -1) os << "voted for: " << citizen.votedfor << std::endl;
	if (!citizen.district->getName().empty())os<<"District: " << citizen.district->getName() << std::endl
		<< "********************" << std::endl;;
	return os;
}

ostream& operator<<(ostream& os, Citizen& citizen)
{
	os << "********************" << std::endl <<
		"Name: " << citizen.name << std::endl <<
		"Id:" << citizen.id << std::endl <<
		"Birth Year: " << citizen.yearOfBirth << std::endl;
		if (citizen.votedfor != -1) os << "voted for: " << citizen.votedfor << std::endl;
		if (!citizen.district->getName().empty())os <<"District: " << citizen.district->getName() << std::endl
		<< "********************" << std::endl;;
	return os;
}