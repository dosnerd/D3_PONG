/*
 * Created by David de Prez on 2-3-2017.
 *
 * 3D pong is a game console to play the game PONG in 3D.
 *  Copyright (C) 2017  David de Prez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <MVC/Observer.h>
#include "MVC/Model.h"

MVC::Model::Model() { }

MVC::Model::~Model() { }

void MVC::Model::attach(MVC::Observer *observer) {
	observers.push_back(observer);
}

void MVC::Model::detach(MVC::Observer *observer) {
	//get list of all items that are equal to observer, than erase the items that exists in list
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void MVC::Model::notify() {
	//foreach observer, update
	for (unsigned int i = 0; i < observers.size(); ++i) {
		observers[i]->update();
	}
}
