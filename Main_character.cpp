#include "Main_character.h"
#include "Utility.h"

int Main_character::playerCoins = 10;
int Main_character::playerLevel = 1;
int Main_character::playerExp = 0;

Main_character::Main_character(float character_Modifiers[6], std::string Name, int Weak, int Res)
{
	Weakness = Weak;
	Resistance = Res;
	this->Name = Name;
	for (int i = 0; i < 6; i++) {
		this->character_Modifiers[i] = character_Modifiers[i];
	}
	CalculateStats();
	Armor = new Equipment(1);
	Weapon = new Equipment(1);
	HP = MaxHp;
	Mana = MaxMana;
	Skills.push_back({ "\033[1;33mShield bash\033[0m","A well rounded maneuver that blocks and deals damage.", 5, 4, false, false, true, false, None, 0 });
	Skills.push_back({ "\033[1;32mMeditate\033[0m","Heals hp and blocks. Also advances turn by 50%", 50, 15, true, true, false, false, Healing, -50 });
	Skills.push_back({ "\033[1;31mBerzerk blade\033[0m","High damage and high cost slash.", 10, 15, false, false, false, false, Fire, 0 });
	Skills.push_back({ "\033[36m\033[1mInventory", "Open Inventory.", NULL, NULL, true, false, false, true, None, 0 });
};
void Main_character::statpotion()
{
	// | 0 is STR | 1 is DEX | 2 is INT | 3 is VIT | 4 is LUK | 5 is WIS | 

	int x = Utility::randomNumber(0, 5);
	character_Level[x]++;
	for (int i = 0; i < 6; i++)
	{
		character_Base_Stats[i] = (10 + character_Level[i]) * character_Modifiers[i];
	}
	//HP Calculations
	MaxHp = (character_Base_Stats[3] * 0.8f) + (character_Base_Stats[4] * 0.6f) + (character_Base_Stats[5] * 0.4f);
	//Mana Calculations
	MaxMana = (character_Base_Stats[2] * 5) + (character_Base_Stats[5] * 10);
	//Damage Caluclations
	DMGModifier = log10(character_Base_Stats[0] + (character_Base_Stats[1] * 0.5f));
	//Speed Calculations
	speed = log10((character_Base_Stats[1] * 1.5f) + (character_Base_Stats[0] * 0.8f) + 5);//log is used inorder to prevent modifiers from becoming too high
	//Magic Modifier
	MagicModifier = log10(character_Base_Stats[2] + (character_Base_Stats[5] * 0.5f));

	switch (x)
	{
	case 0:
		std::cout << "\033[0m" << "You feel your \033[33m\033[1mStrength\033[0m increase" << std::endl;
		break;
	case 1:
		std::cout << "\033[0m" << "You feel your \033[36m\033[1mDexterity\033[0m increase" << std::endl;
		break;
	case 2:
		std::cout << "\033[0m" << "You feel your \033[35m\033[1mIntelligence\033[0m increase" << std::endl;
		break;
	case 3:
		std::cout << "\033[0m" << "You feel your \033[31m\033[1mVitality\033[0mincrease" << std::endl;
		break;
	case 4:
		std::cout << "\033[0m" << "You feel your \033[33m\033Luck\033[0mincrease" << std::endl;
		break;
	case 5:
		std::cout << "\033[0m" << "You feel your \033[95m\033Wisdom\033[0mincrease" << std::endl;
		break;
	}
}
void Main_character::CalculateStats()
{
	// | 0 is STR | 1 is DEX | 2 is INT | 3 is VIT | 4 is LUK | 5 is WIS | 
	for (int i = 0; i < 6; i++) {
		character_Base_Stats[i] = (10 + character_Level[i]) * character_Modifiers[i];
	}
	//HP Calculations
	MaxHp = (character_Base_Stats[3] * 0.8f) + (character_Base_Stats[4] * 0.6f) + (character_Base_Stats[5] * 0.4f);
	//Mana Calculations
	MaxMana = (character_Base_Stats[2] * 5) + (character_Base_Stats[5] * 10);
	//Damage Caluclations
	DMGModifier = log10(character_Base_Stats[0] + (character_Base_Stats[1] * 0.5f));
	//Speed Calculations
	speed = log10((character_Base_Stats[1] * 1.5f) + (character_Base_Stats[0] * 0.8f) + 5);//log is used inorder to prevent modifiers from becoming too high
	//Magic Modifier
	MagicModifier = log10(character_Base_Stats[2] + (character_Base_Stats[5] * 0.5f));
}
void Main_character::ExecuteSkill(Entity* Enemy, int Choice)
{
	if (Skills[Choice].Blocking) {
		Blocking = true;
	}
	if (((Skills[Choice].Healing == true) || (Skills[Choice].ManaCost == true)) && (Mana > (Skills[Choice].Cost))) {
		Mana = Mana - Skills[Choice].Cost;
	}
	else {
		HP = HP - Skills[Choice].Cost;
	}
	if (Skills[Choice].Inventory == true)
	{
		system("cls");
		this->inv();
		this->UpdateCR(-99);
	}
	if (Skills[Choice].Healing == true)
	{
		HP = HP + (Skills[Choice].Base * DMGModifier);
		//for checking if hp is over maximum
		if (HP > MaxHp) {
			HP = MaxHp;
		}
		Utility::PositionText(0, 30);
		std::cout << Name << " used " << Skills[Choice].Name << " on itself" << std::endl;
	}
	else
	{
		if (Skills[Choice].Element == Enemy->getWeakness()) {
			Enemy->UpdateCR(50);
			Enemy->TakeDMG(((Skills[Choice].Base * DMGModifier * 1.5 * (Enemy->getBlocking() ? 0.5f : 1))) - Enemy->getArmorVal() + getWeaponVal());
			std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs((Skills[Choice].Base * DMGModifier * 1.5 * (Enemy->getBlocking() ? 0.5f : 1)) - Enemy->getArmorVal() + getWeaponVal()) << std::endl;
			Utility::PositionText(0, 30);
			std::cout << "it did critical damage!!   Pushing the enemies turn back" << std::endl;

		}
		 if ((Skills[Choice].Element == Enemy->getResistance())) {
			Enemy->TakeDMG(((Skills[Choice].Base * DMGModifier * 0.5 * (Enemy->getBlocking() ? 0.5f : 1))) - Enemy->getArmorVal() + getWeaponVal());
			std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs((Skills[Choice].Base * DMGModifier * 1.5 * (Enemy->getBlocking() ? 0.5f : 1)) - Enemy->getArmorVal() + getWeaponVal()) << std::endl;
			Utility::PositionText(0, 30);
			std::cout << "it did low damage......" << std::endl;
		}
		if (Skills[Choice].Inventory == false)
			{
				AttackGame attackgame;
				dmg = Skills[Choice].Base * DMGModifier * (Enemy->getBlocking() ? 0.5f : 1) - Enemy->getArmorVal() + getWeaponVal();
				float finalDmg = dmg * attackgame.GetdmgModifier();
				Enemy->TakeDMG(finalDmg);
				Utility::PositionText(0, 30);
				std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs(finalDmg) << std::endl;
		}
	}

}
void Main_character::inv(int x, int y, std::string name, int ID) {
	int current = NULL;
	while (1) {
		if (current == NULL) {
			for (int i = 0; i < maxitm; i++) {
				if (Itemptr[i] == nullptr) {
					Itemptr[i] = new Item(x, y, name, ID);
					current = i;
					break;
				}

			}
		}
		player_inv.RenderInventory(*Itemptr[current]);
		for (int i = 0; i < maxitm; i++) {
			if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {
				player_inv.setscroll(min(player_inv.getscroll(), i));
				player_inv.setmaxscroll(max(player_inv.getmaxscroll(), i));
				SetConsoleTextAttribute(outputHandle, Itemptr[i]->getID() + 1);
				Utility::PositionText(50, 17 + i);
				std::cout  << Itemptr[i]->getName() << std::endl;
			}

		}
		if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D') || GetAsyncKeyState('R') || GetAsyncKeyState('E')
			|| GetAsyncKeyState('O') || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)) {
			system("cls");
			player_inv.RenderInventory(*Itemptr[current]);
			for (int i = 0; i < maxitm; i++) {

				if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {

					player_inv.setmaxscroll(max(player_inv.getmaxscroll(), i));
					SetConsoleTextAttribute(outputHandle, Itemptr[i]->getID() + 1);
					Utility::PositionText(50, 17 + i);
					if (player_inv.getscroll() == -i) {
						
						std::cout	<< Itemptr[i]->getName() << " <-" << std::endl;
					}
					else {
						std::cout << std::endl << Itemptr[i]->getName() << std::endl;
					}
				}

			}
			std::cout << player_inv.getmaxscroll() << player_inv.getscroll();

			if (GetAsyncKeyState('S')) {
				player_inv.Move(0, 1, *Itemptr[current]);
			}
			if (GetAsyncKeyState('W')) {
				player_inv.Move(0, -1, *Itemptr[current]);
			}
			if (GetAsyncKeyState('A')) {
				player_inv.Move(-1, 0, *Itemptr[current]);
			}
			if (GetAsyncKeyState('D')) {
				player_inv.Move(1, 0, *Itemptr[current]);
			}
			if (GetAsyncKeyState('R')) {
				Itemptr[current]->rotate();
			}
			if ((GetAsyncKeyState('O')) && (Itemptr[-player_inv.getscroll()] != nullptr) && ((-player_inv.getscroll()) != maxitm) && (-player_inv.getscroll()!=999)) {
				int x = player_inv.discard(Itemptr[-player_inv.getscroll()]->getID());
				if ((x != -999) && (Itemptr[x] != nullptr)) {
					delete Itemptr[x];
					Itemptr[x] = nullptr;
					player_inv.setscroll(-999);
					player_inv.setmaxscroll(0);
					for (int i = 0; i < maxitm; i++) {
						if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {
							player_inv.setscroll(max(player_inv.getscroll(), -i));
							player_inv.setmaxscroll(min(player_inv.getmaxscroll(), -i));
						}

					}
				}
			}
			if (GetAsyncKeyState(VK_UP)) {
				for (int i = maxitm; i > 0; i--) {
					if ((Itemptr[i] != nullptr) && (i < -player_inv.getscroll()) && (Itemptr[i]->getplaced() == true)) {
						player_inv.setscroll(-i);
						break;
					}

				}
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				for (int i = 0; i < maxitm; i++) {
					if ((Itemptr[i] != nullptr) && (i > -player_inv.getscroll()) && (Itemptr[i]->getplaced() == true)) {
						player_inv.setscroll(-i);
						break;
					}

				}
				Sleep(100);
			}
			if (GetAsyncKeyState('E')) {
				if (player_inv.placeitem(*Itemptr[current]) == true) {
					Itemptr[current]->place();
					player_inv.RenderInventory(*Itemptr[current]);
					Sleep(100);
					return;
				}
			}
		}

	}

}
int Main_character::inv()
{
	while (1) {
		player_inv.RenderInventory();
		for (int i = 0; i < maxitm; i++) {
			if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {
				player_inv.setscroll(min(player_inv.getscroll(), i));
				player_inv.setmaxscroll(max(player_inv.getmaxscroll(), i));
				SetConsoleTextAttribute(outputHandle, Itemptr[i]->getID() + 1);
				std::cout << std::endl << Itemptr[i]->getName() << std::endl;
			}

		}
		if (GetAsyncKeyState('I') || GetAsyncKeyState('O') || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)) {
			system("cls");
			player_inv.RenderInventory();
			for (int i = 0; i < maxitm; i++) {

				if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {

					player_inv.setmaxscroll(max(player_inv.getmaxscroll(), i));
					SetConsoleTextAttribute(outputHandle, Itemptr[i]->getID() + 1);
					if (player_inv.getscroll() == -i) {
						std::cout << std::endl << Itemptr[i]->getName() << " <-" << std::endl;
					}
					else {
						std::cout << std::endl << Itemptr[i]->getName() << std::endl;
					}
				}

			}
			std::cout << player_inv.getmaxscroll() << player_inv.getscroll();
			if (GetAsyncKeyState('O') && (Itemptr[-player_inv.getscroll()] != nullptr) && ((-player_inv.getscroll()) != maxitm) && (-player_inv.getscroll() != 999)) {
				int y = Itemptr[-player_inv.getscroll()]->getID();
				int x = player_inv.discard(Itemptr[-player_inv.getscroll()]->getID());
				if ((x != -999) && (Itemptr[x] != nullptr)) {
					delete Itemptr[x];
					Itemptr[x] = nullptr;
					player_inv.setscroll(-999);
					player_inv.setmaxscroll(0);
					for (int i = 0; i < maxitm; i++) {
						if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {
							player_inv.setscroll(max(player_inv.getscroll(), -i));
							player_inv.setmaxscroll(min(player_inv.getmaxscroll(), -i));
						}

					}
				}
				Consumable(y); // For Integration

				return y;
			}
			if (GetAsyncKeyState('I')) {
				return -1;
			}
			if (GetAsyncKeyState(VK_UP)) {
				for (int i = maxitm; i > 0; i--) {
					if ((Itemptr[i] != nullptr) && (i < -player_inv.getscroll()) && (Itemptr[i]->getplaced() == true)) {
						player_inv.setscroll(-i);
						break;
					}

				}
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				for (int i = 0; i < maxitm; i++) {
					if ((Itemptr[i] != nullptr) && (i > -player_inv.getscroll()) && (Itemptr[i]->getplaced() == true)) {
						player_inv.setscroll(-i);
						break;
					}

				}
				Sleep(100);
			}

		}

	}

}
void Main_character::Consumable(int itemid)
{
	if (itemid == 1 || itemid == 2 || itemid == 3 || itemid == 4 || itemid == 5)
	{
		HP += 20;

		if (HP > MaxHp)
		{
			HP = MaxHp;
		}

		//Testing purposes
		/*std::cout << std::endl << itemid << std::endl;*/

		std::cout << "\033[0m" << Name << " used Healing Potion on itself" << std::endl;

		std::cout << Name << " healed for " << "\033[32m\033[1m" << "20 HP" << "\033[0m" << std::endl;

		std::cout << "\033[0m" << "Current HP: " << "\033[32m\033[1m" << HP << "\033[0m" << std::endl;

		Sleep(3000);
	}

	if (itemid == 6 || itemid == 7 || itemid == 8 || itemid == 9 || itemid == 10)
	{
		Mana += 50;

		if (Mana > MaxMana)
		{
			Mana = MaxMana;
		}

		std::cout << "\033[0m" << Name << " used Mana Potion on itself" << std::endl;

		std::cout << Name << " usage for " << "\033[32m\033[1m" << "50 Mana" << "\033[0m" << std::endl;

		std::cout << "\033[0m" << "Current Mana: " << "\033[32m\033[1m" << Mana << "\033[0m" << std::endl;

		Sleep(3000);
	}

	if (itemid == 11 || itemid == 12 || itemid == 13 || itemid == 14 || itemid == 15)
	{
		statpotion();

		Sleep(3000);
	}

}

void Main_character::setPlayerExp(int pE, int& States)
{
	playerExp += pE;
	if (playerExp >= 100)
	{
		playerExp = 0;
		playerLevel++;
		playerCoins += 5;
		States = LEVELUP;
	}
	else
	{
		States = EXPLORATION;
	}
}

//ItemID for HealthPots 1 - 10
void Main_character::HealthPotCounter()
{
	HealthPotCount++;

	if (HealthPotCount > MaxHealthPot)
	{
		HealthPotCount = NULL;
	}
}

int Main_character::GetHealthPotCount(void)
{
	return HealthPotCount;
}

void Main_character::setPlayerLevel(int pL)
{
	playerLevel += pL;
}

void Main_character::ManaPotCounter()
{
	ManaPotCount++;

	if (ManaPotCount > MaxManaPotCount)
	{
		ManaPotCount = NULL;
	}
}

void Main_character::setPlayerCoins(int pC)
{
	playerCoins += pC;
}

int Main_character::GetManaPotCount(void)
{
	return ManaPotCount;
}

void Main_character::StatPotCounter()
{
	StatPotCount++;

	if (StatPotCount > MaxStatPotCount)
	{
		StatPotCount = NULL;
	}
}

int Main_character::GetStatPotCount(void)
{
	return StatPotCount;
}

int Main_character::getPlayerLevel(void)
{
	return playerLevel;
}

int Main_character::getPlayerExp(void)
{
	return playerExp;
}

int Main_character::getPlayerCoins(void)
{
	return playerCoins;
}
