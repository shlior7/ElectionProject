#pragma once
#include "SimpleElection.h"
#include<windows.h>


enum PreMenu {
	NewElec = 1, LoadElec1 = 2,Exit1 = 3
};
enum MainMenu {
	newDis = 1, newCit = 2, newPar = 3, newRep = 4,
	printDis = 5, printCit = 6, printPar = 7, Vote = 8, ShowVotes = 9, Exit2 = 10,
	SaveElec = 11, LoadElec2 = 12};

class Menu {
private:
	Election* elections;


public:
	/*Init*/
	Menu() { elections = nullptr; }
	~Menu() { delete elections; }
	
	/*Setters*/
	bool SetDate(int day, int month, int year);
	
	/*Menu*/
	void ElectionMenu();//actual loop of menu
	void preNavigator(int choice);//navigator for the pre menu
	void navigator(int choice);//navigator for the main menu
	
	/*Prints*/
	void printMenu();//main Menu
	void printPreMenu();//Pre Menu

	/*Menu Options*/
	void newElection();
	void loadElection();
	void saveElection();
	void addDistrict();
	void addParty();
	void addCitizen();
	void addRep();
	void vote();

	/*Show all*/
	void showAllDistricts()const;
	void showAllCitizens()const;
	void showAllParties()const;
	void showElectionResults() const;
};

