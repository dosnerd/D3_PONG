//
// Created by Acer on 2-3-2017.
//

#ifndef TESTING_MODEL_H
#define TESTING_MODEL_H

#include <vector>

namespace MVC {
	class Observer;

	class Model {
	public:
									Model();
		virtual                     ~Model();

	public:
		virtual void                attach(Observer *observer);
		virtual void                detach(Observer *observer);
		virtual void                notify();

	private:
		std::vector<Observer *>     observers;
	};
}


#endif //TESTING_MODEL_H
