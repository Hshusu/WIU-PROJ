#pragma once
#include "Utility.h"

#include <iostream>
#include <string>
class Equipment
{
private:
	//Data Members
	std::string equipmentName;
	int equipmentAddifier;
	std::string weaponNamesList[5];
	std::string armorNamesList[5];
public:
	//Function Members

	//Accessors
	std::string getEquipmentName(void) const;
	int getEquipmentAddifier(void) const;

	//Functions

	//Constructors and Destructor
	Equipment(int EquipmentType);
	Equipment(int stats,int placeholder);
	~Equipment();
};