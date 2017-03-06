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

#ifndef TESTING_CONTROLLER_H
#define TESTING_CONTROLLER_H


#include <MVC/Observer.h>

namespace MVC {
	class Model;
	class View;

	class Controller: public Observer {

	//constructors
	public:
						Controller(Model *model);
		virtual         ~Controller();

	//overrides
	public:
		void            update();

	//getters
	public:
		virtual View    *getView();
		virtual Model   *getModel();

	public:
		void            setView(View *view);

	//member variables
	private:
		View            *view;
		Model           *model;
	};
}


#endif //TESTING_CONTROLLER_H
