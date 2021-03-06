//
//  Weapon.h
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 06/11/2017.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2017-8 Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3)

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README and LICENSE for more details

#ifndef Weapon_h
#define Weapon_h

#include "../Items/Item.h"

#define WEAPONCOUNT 3
enum WeaponType {
	HANDGUN = 0,
	FASTGUN = 1,
	SHOTGUN = 2,
	GATLING = 3
};

class Weapon : public Item {
	static Weapon* handgun;
	static Weapon* fastGun;
	static Weapon* shotgun;
	static Weapon* gatling;
	
	Weapon* copy();
protected:
	double firingDelay;
	int dmg;
	double bulletSpeed;
public:
	Weapon(orxSTRING, double, int, double);
	double getFiringDelay();
	int getDmg();
	double getBulletSpeed();

	static Weapon* copyOf(WeaponType);
};

#endif
