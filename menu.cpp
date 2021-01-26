#define _CRTDBG_MAP_ALLOC
#include"Menu.h"

void Menu::ElectionMenu() {
	int choice = 0;
	while (true)
	{
		try {
			system("cls");
			printPreMenu();
			choice = getInt(1, 3, "\b");
			preNavigator(choice);
			if (choice == 3) return;
			break;
		}
		catch(exception& ex){//while the loading or creating is not ok 
			cout << ex.what() << endl;
			system("pause");
		}
	}
	do {
		system("cls");
		printMenu();
		choice = getInt(1, 12, "\b");
		try {
			navigator(choice);
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
			system("pause");
		}
	} while (choice != 10);
}

void Menu::preNavigator(int choice) {
	switch (choice)
	{
	case PreMenu::NewElec://1
		newElection();
		system("pause");
		break;
	case PreMenu::LoadElec1://2
		loadElection();
		cout << "Loaded" << endl;
		system("pause");
		break;
	case PreMenu::Exit1://3
		cout << "Thank you, goodbye" << endl;
		system("pause");
		break;
	default:
		cout << "Invalid input" << endl;
		break;
	}
}
void Menu::navigator(int choice) {
	switch (choice)
	{
	case MainMenu::newDis://1
		addDistrict();
		system("pause");
		break;
	case MainMenu::newCit://2
		addCitizen();
		system("pause");
		break;
	case MainMenu::newPar://3
		addParty();
		system("pause");
		break;
	case MainMenu::newRep://4
		addRep();
		system("pause");
		break;
	case MainMenu::printDis://5
		showAllDistricts();
		system("pause");
		break;
	case MainMenu::printCit://6
		showAllCitizens();
		system("pause");
		break;
	case MainMenu::printPar://7
		showAllParties();
		system("pause");
		break;
	case MainMenu::Vote://8
		vote();
		system("pause");
		break;
	case MainMenu::ShowVotes://9
		showElectionResults();
		system("pause");
		break;
	case MainMenu::Exit2://10
		cout << "Thank you, goodbye" << endl;
		break;
	case MainMenu::SaveElec://11
		saveElection();
		cout << "Saved" << endl;
		system("pause");
		break;
	case MainMenu::LoadElec2://12
		loadElection();
		cout << "Loaded" << endl;
		system("pause");
		break;
	default:
		cout << "Invalid input" << endl;
		break;
	}
}
void Menu::printPreMenu() {

	cout << "* * * * * * * * * * * * * * * * * *" << endl;
	cout << "* Please choose action:           *" << endl;
	cout << "* 1.Create a new Election         *" << endl;
	cout << "* 2.Load an old Election          *" << endl;
	cout << "* 3.exit                          *" << endl;
	cout << "* * * * * * * * * * * * * * * * * *" << endl;
}

void Menu::printMenu() {

	cout << "* * * * * * * * * * * * * * *" << endl;
	cout << "* Please choose action:     *" << endl;
	cout << "* 1.Add New District        *" << endl;
	cout << "* 2.Add new Citizen         *" << endl;
	cout << "* 3.Add new Party           *" << endl;
	cout << "* 4.Add new Representative  *" << endl;
	cout << "* 5.Show all Districts      *" << endl;
	cout << "* 6.Show all Citizens       *" << endl;
	cout << "* 7.Show all Parties        *" << endl;
	cout << "* 8.Vote                    *" << endl;
	cout << "* 9.Election Results        *" << endl;
	cout << "* 10.Exit                   *" << endl;
	cout << "* 11.Save                   *" << endl;
	cout << "* 12.Load                   *" << endl;
	cout << "* * * * * * * * * * * * * * *" << endl;
}
void Menu::newElection()
{
	system("cls");
	string t;
	int day, month, year, election_type;
	cout << "Please enter election date:" << endl;
	day = getInt(1, 31, "Day Month Year");
	month = getInt(1, 12, "");
	year = getInt(1, INT_MAX, "");
	
	system("cls");
	if (elections != nullptr)
		delete elections;
	Date date(day, month, year);
	SimpleElection* elec = new SimpleElection(date);
	election_type = getInt(1, 2, "Please enter the type of election (1-Simple/2-Regular):");
	if (--election_type) { elections = new Election(date); delete elec; }
	else       elections = elec;
}


void Menu::addDistrict() {
	try {
		if (elections->getType())
			throw Except("Cant add districts in a simple elections");
		string name;
		int type = getInt(1, 2, "Please enter the district's type:(1-Unified/2-Divided) ");
		const Type t = (--type ? Type::divided : Type::unified);
	
		cout << "Please enter district's name: " << endl;
		cin >> name;

		const auto reps = getInt(1,INT_MAX, "Please enter number of representatives: ");
		elections->addDistrict(name, reps, t);
		throw Added("District");
	}
	catch (const exception& s){
		cout << s.what() <<endl;
	}
}

void Menu::addCitizen() {
	string name;
	int id, yearOfBirth, disNumber = 0;
	try {
		if(!elections->getDistrictList().size())
			throw Except("No Districts yet");
	

		cout << "Please enter the name: ";
		cin >> name;

		id = getInt(1, 999999999, "Please enter ID (9 digits MAX): ");
		yearOfBirth = getInt(1, 2021, "Please enter Year of Birth: ");
		if (!elections->getType())
		{
			for (int i = 0; i < elections->getDistrictList().size(); i++)
				cout << elections->getDistrictList()[i]->getName() << ": (" << elections->getDistrictList()[i]->getId() << ")  ";
			disNumber = getInt(0, elections->getDistrictList().size()-1, "\nPlease enter citizen district number from the List: ");
		}
		elections->addCitizen(name, id, yearOfBirth, disNumber);
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}

void Menu::addParty() {
	string name;
	int presidentId;
	cout << "Please Enter the Party Name:"<<endl <<flush;
	cin >> name;
	presidentId = getInt(1, 999999999, "Please Enter the President Candidate ID:");
	try {
		elections->addParty(name, presidentId);
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}

void Menu::addRep() {
	int id, partyNumber, disNumber = 0;
	try {
		id = getInt(1, 999999999, "Please enter Representative ID: ");
		for (int i = 0; i < elections->getPartyList().size(); i++)
			cout << elections->getPartyList()[i]->getName() << ": (" << elections->getPartyList()[i]->getId() << ")  ";
		partyNumber = getInt(0, elections->getPartyList().size(), "\nPlease enter Representative party number from the List: ");

		if (!elections->getType())
		{
			for (int i = 0; i < elections->getDistrictList().size(); i++)
				cout << elections->getDistrictList()[i]->getName() << ": (" << elections->getDistrictList()[i]->getId() << ")  ";
			disNumber = getInt(0, elections->getDistrictList().size() - 1, "\nPlease enter Representative district number from the List: ");
		}
		elections->addRep(partyNumber, id, disNumber);
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}


void Menu::showAllDistricts() const {
	try {
		elections->getDistrictList().printDistricts();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

}

void Menu::showAllCitizens() const {
	try {
		cout << elections->getDistrictList();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}

void Menu::showAllParties() const {
	try {
		cout << elections->getPartyList();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}

void Menu::vote() {
	int id, partyNumber,districtNumber = 0;
	try {
	id = getInt(1, 999999999, "Please Enter your ID number:");
	for (int i = 0; i < elections->getPartyList().size(); i++)
		cout << " (" << i << " - " << elections->getPartyList()[i]->getName() << ") ";
	partyNumber = getInt(0, elections->getPartyList().size(),"\nPlease Enter Party number you vote for from the list : " );
	if (!elections->getType())
	{
		for (int i = 0; i < elections->getDistrictList().size(); i++)
			cout << elections->getDistrictList()[i]->getName() << ": (" << elections->getDistrictList()[i]->getId() << ")  ";
		districtNumber = getInt(0, elections->getDistrictList().size() - 1, "\nPlease Enter District number you vote for from the list :: ");
	}
		elections->addVote(id, districtNumber,partyNumber);
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}

void Menu::loadElection()
{
	int election_type;
	string ElectionName;
	cout << "Please enter election file name(Don't need \".bin\"):" << flush;
	cin >> ElectionName;
	ElectionName = ElectionName + ".bin";
	ifstream in(ElectionName, ios::binary);
	in.read(rcastc(&election_type), sizeof(election_type));
	if (!in.good())
		throw Except("Loading Error");
	if (elections != nullptr)
		delete elections;
	if (!election_type)
		elections = new Election(in);
	else
		elections = new SimpleElection(in);
	in.close();
}
void Menu::saveElection()
{
	int type;
	string fileName;
	try {
		cout << "Enter File Name to be saved in(Don't need \".bin\"): " << endl;
		cin >> fileName;
		fileName = fileName + ".bin";

		ofstream out(fileName, ios::binary);
		out.seekp(0, ios::beg);
		type = elections->getType();//1 -simple :: 0 - regular
		out.write(rcastcc(&type), sizeof(type));
		elections->save(out);
		out.close();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}

void Menu::showElectionResults() const{
	try {
		elections->sumResults();
		cout << *elections;
	}
	catch (const exception& ex)
	{
		cout << ex.what();
	}
}
