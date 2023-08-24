#include "Equipment.h"

std::string Equipment::getEquipmentName(void) const
{
	return equipmentName;
}

int Equipment::getEquipmentAddifier(void) const
{
	return equipmentAddifier;
}

Equipment::Equipment(int EquipmentType) //Armor 1 | Weapon 2
{
	std::string weaponNamesList[5] = { "\033[1;37mCommon Weapon\033[0m", "\033[1;32mUncommon Weapon\033[0m", "\033[1;36mRare Weapon\033[0m", "\033[1;35mEpic Weapon\033[0m", "\033[1;33mLegendary Weapon\033[0m" };
	std::string armorNamesList[5] = { "\033[1;37mCommon Armor\033[0m", "\033[1;32mUncommon Armor\033[0m", "\033[1;36mRare Armor\033[0m", "\033[1;35mEpic Armor\033[0m", "\033[1;33mLegendary Armor\033[0m" };

	equipmentName = "";
	equipmentAddifier = 0;

	switch (EquipmentType)
	{
	case 1:
		equipmentName = armorNamesList[Utility::randomNumber(0, 4)];
		equipmentAddifier = Utility::randomNumber(6, 10);
		
		break;
	case 2:
		equipmentName = weaponNamesList[Utility::randomNumber(0, 4)];
		equipmentAddifier = Utility::randomNumber(1, 10);
		break;
	}
}

Equipment::Equipment(int stats, int placeholder)
{
	equipmentAddifier = stats;
}


Equipment::~Equipment()
{
	std::cout << "  \033[1;36mHero\033[0m \033[1;31mdropped\033[0m: " << equipmentName << " with \033[1;31m" << equipmentAddifier << " points\033[0m!" << std::endl << std::endl;
}