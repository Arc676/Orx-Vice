//
//  Weapon.cpp
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 06/11/2017.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2017 Arc676/Alessandro Vinciguerra

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

#include "Weapon.h"

Weapon::Weapon(const std::string &name, int fireRate, int dmg) : name(name), fireRate(fireRate), dmg(dmg) {}

int Weapon::getDmg() {
	return dmg;
}

std::string Weapon::getName() {
	return name;
}

int Weapon::getFireRate() {
	return fireRate;
}