#include "Main_character.h"

Main_character::Main_character(float character_Modifiers[6], std::string Name, int Weak, int Res)
{
	Weakness = Weak;
	Resistance = Res;
	this->Name = Name;
	for (int i = 0; i < 6; i++) {
		this->character_Modifiers[i] = character_Modifiers[i];
	}
	CalculateStats();
	HP = MaxHp;
	Mana = MaxMana;
	Skills.push_back({ "\033[1;33mShield bash\033[0m","A well rounded maneuver that blocks and deals damage.", 5, 4, false, false, true, None, 0 });
	Skills.push_back({ "\033[1;32mMeditate\033[0m","Heals hp and blocks. Also advances turn by 50%", 50, 15, true, true, false, Healing, -50 });
	Skills.push_back({ "\033[1;31mBerzerk blade\033[0m","High damage and high cost slash.", 10, 15, false, false, false, Fire, 0 });

};

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
	if (Skills[Choice].Healing == true)
	{
		AttackGame attackgame;
		float finalHeal = HP + (Skills[Choice].Base * DMGModifier) * attackgame.GetdmgModifier();
		HP = finalHeal;
		//for checking if hp is over maximum
		if (HP > MaxHp) 
		{
			HP = MaxHp;
		}
		std::cout << Name << " used " << Skills[Choice].Name << " on itself" << std::endl;

		std::cout << Name << " healed for "	<< "\033[32m\033[1m" << finalHeal << "\033[0m";
	}
	else
	{
		if (Skills[Choice].Element == Enemy->getWeakness()) 
		{
			AttackGame attackgame;
			dmg = Skills[Choice].Base * DMGModifier * 1.5 * (Enemy->getBlocking() ? 0.5f : 1) - Enemy->getArmorVal() + getWeaponVal();
			float finalDmg = dmg * attackgame.GetdmgModifier();
			Enemy->UpdateCR(50);
			Enemy->TakeDMG(finalDmg);
			std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs(finalDmg) << std::endl;
			std::cout << "it did critical damage!!   Pushing the enemies turn back" << std::endl;

		}
		else if ((Skills[Choice].Element == Enemy->getResistance())) 
		{
			AttackGame attackgame;
			dmg = Skills[Choice].Base * DMGModifier * 0.5 * (Enemy->getBlocking() ? 0.5f : 1) - Enemy->getArmorVal() + getWeaponVal();
			float finalDmg = dmg * attackgame.GetdmgModifier();
			Enemy->TakeDMG(finalDmg);
			std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs(finalDmg) << std::endl;
			std::cout << "it did low damage......" << std::endl;
		}
		else
		{
			AttackGame attackgame;
			dmg = Skills[Choice].Base * DMGModifier * (Enemy->getBlocking() ? 0.5f : 1) - Enemy->getArmorVal() + getWeaponVal();
			float finalDmg = dmg * attackgame.GetdmgModifier();
			Enemy->TakeDMG(finalDmg);
			std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs(finalDmg) << std::endl;
		}
	}
}

void Main_character::inv(int x, int y, std::string name, int ID) {
	int current = NULL;
	while (1) {
		if(current == NULL) {
			for (int i = 0; i < 20; i++) {
				if (Itemptr[i] == nullptr) {
					Itemptr[i] = new Item(x, y, name, ID);
						current = i;
						break;
				}

			}
	}
		player_inv.RenderInventory(*Itemptr[current]);
		for (int i = 0; i < 20; i++) {
			if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {
				player_inv.setscroll(min(player_inv.getscroll(), i));
				player_inv.setmaxscroll(max(player_inv.getmaxscroll(), i));
				SetConsoleTextAttribute(outputHandle, Itemptr[i]->getID() + 1);
				std::cout << std::endl << Itemptr[i]->getName() << std::endl;
			}

		}
		if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D') || GetAsyncKeyState('K') || GetAsyncKeyState('L')
			|| GetAsyncKeyState('O') || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)) {
			system("cls");
			player_inv.RenderInventory(*Itemptr[current]);
			for (int i = 0; i < 20; i++) {

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
			if (GetAsyncKeyState('K')) {
				Itemptr[current]->rotate();
			}
			if (GetAsyncKeyState('O')) {
				int x = player_inv.discard(Itemptr[-player_inv.getscroll()]->getID());
				if ((x != -999) && (Itemptr[x] != nullptr)) {
					delete Itemptr[x];
					Itemptr[x] = nullptr;
					player_inv.setscroll(-999);
					player_inv.setmaxscroll(0);
					for (int i = 0; i < 20; i++) {
						if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {
							player_inv.setscroll(max(player_inv.getscroll(), -i));
							player_inv.setmaxscroll(min(player_inv.getmaxscroll(), -i));
						}

					}
				}
			}
			if (GetAsyncKeyState(VK_UP)) {
				player_inv.movescroll(-1);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				player_inv.movescroll(1);
				Sleep(100);
			}
			if (GetAsyncKeyState('L')) {
				if (player_inv.placeitem(*Itemptr[current]) == true) {
					Itemptr[current]->place();
					player_inv.RenderInventory(*Itemptr[current]);
					Sleep(100);
					return ;
				}
			}
		}

	}

}

int Main_character::inv()
{
	while (1) {
		player_inv.RenderInventory();
		for (int i = 0; i < 20; i++) {
			if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {
				player_inv.setscroll(min(player_inv.getscroll(), i));
				player_inv.setmaxscroll(max(player_inv.getmaxscroll(), i));
				SetConsoleTextAttribute(outputHandle, Itemptr[i]->getID() + 1);
				std::cout << std::endl << Itemptr[i]->getName() << std::endl;
			}

		}
		if (GetAsyncKeyState('X') || GetAsyncKeyState('O') || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)) {
			system("cls");
			player_inv.RenderInventory();
			for (int i = 0; i < 20; i++) {

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
			if (GetAsyncKeyState('O')) {
				int x = player_inv.discard(Itemptr[-player_inv.getscroll()]->getID());
				if ((x != -999) && (Itemptr[x] != nullptr)) {
					delete Itemptr[x];
					Itemptr[x] = nullptr;
					player_inv.setscroll(-999);
					player_inv.setmaxscroll(0);
					for (int i = 0; i < 20; i++) {
						if ((Itemptr[i] != nullptr) && (Itemptr[i]->getplaced() == true)) {
							player_inv.setscroll(max(player_inv.getscroll(), -i));
							player_inv.setmaxscroll(min(player_inv.getmaxscroll(), -i));
						}

					}
				}
				return -player_inv.getscroll();
			}
			if (GetAsyncKeyState('X')) {
				return -1;
			}
			if (GetAsyncKeyState(VK_UP)) {
				player_inv.movescroll(-1);
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				player_inv.movescroll(1);
				Sleep(100);
			}

		}

	}

}
