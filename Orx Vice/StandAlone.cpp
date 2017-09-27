//
//  StandAlone.cpp
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 18/09/2017.
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

#include "StandAlone.h"

StandAlone* StandAlone::m_Instance = nullptr;

StandAlone* StandAlone::Instance() {
	if (m_Instance != nullptr) {
		return m_Instance;
	}
	m_Instance = new StandAlone();
	return m_Instance;
}

StandAlone::StandAlone() {}

orxSTATUS orxFASTCALL StandAlone::Init() {
	orxViewport_CreateFromConfig("Viewport");
	orxConfig_Load("StaticScene.ini");
	orxObject_CreateFromConfig("Scene");

	Player *player = new Player();

	orxCLOCK* upClock = orxClock_Create(0.02f, orxCLOCK_TYPE_USER);
	orxOBJECT* soldier = player->getEntity();
	if (soldier != orxNULL) {
		orxClock_Register(upClock, Update, soldier, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);
	}

	orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, StandAlone::EventHandler);
	orxEvent_AddHandler(orxEVENT_TYPE_INPUT, StandAlone::EventHandler);

	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL StandAlone::Run() {
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit() {
	return;
}

orxOBJECT* StandAlone::GetObjectByName(std::string objName) {
	std::string name;
	for (orxOBJECT* obj = orxOBJECT(orxStructure_GetFirst(orxSTRUCTURE_ID_OBJECT));
		 obj != orxNULL;
		 obj = orxOBJECT(orxStructure_GetNext(obj))) {
		name = orxObject_GetName(obj);
		if (name.compare(objName) == 0) {
			return obj;
		}
	}
	return orxNULL;
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* clockInfo, void* context) {
	orxOBJECT* obj = orxOBJECT(context);
	if (obj != orxNULL) {
		std::string name = orxObject_GetName(obj);
		if (name.compare("Player") == 0) {
			Player *player = (Player*)orxObject_GetUserData(obj);
			player->update(orxInput_IsActive("GoUp"),
									  orxInput_IsActive("GoDown"),
									  orxInput_IsActive("GoLeft"),
									  orxInput_IsActive("GoRight"),
									  orxInput_IsActive("Fire"),
									  GetMouseWorldPosition());
		}
	}
}

orxVECTOR orxFASTCALL StandAlone::GetMouseWorldPosition() {
	orxVECTOR worldpos = {0,0,0};
	orxVECTOR screenpos = {0,0,0};

	orxRender_GetWorldPosition(orxMouse_GetPosition(&screenpos), orxNULL, &worldpos);

	return worldpos;
}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* currentEvent) {
	switch(currentEvent->eType) {
		case orxEVENT_TYPE_INPUT:
			break;
		case orxEVENT_TYPE_PHYSICS:
			switch (currentEvent->eID) {
				case orxPHYSICS_EVENT_CONTACT_ADD:
					orxOBJECT* sender = orxOBJECT(currentEvent->hSender);
					Bullet* bullet = (Bullet*)orxObject_GetUserData(sender);
					if (bullet != orxNULL) {
						orxOBJECT* receiver = orxOBJECT(currentEvent->hRecipient);
						Entity* entity = (Entity*)orxObject_GetUserData(receiver);
						if (entity != orxNULL) {
							orxLOG("sender: %s", orxObject_GetName(sender));
							orxLOG("recipient: %s", orxObject_GetName(receiver));
						}
					}
					break;
			}
			break;
		default:
			break;
	}

	return orxSTATUS_SUCCESS;
}
