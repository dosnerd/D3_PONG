/*
 * Model.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef INC_MVC_MODEL_H_
#define INC_MVC_MODEL_H_

#include <Vector.h>

namespace MVC {

class Observer;
class Model {
public:
								Model();
	virtual 					~Model();

public:
	void						notifyObservers();
	void						attach(Observer *observer);

private:
	Vector<Observer *>			m_observers;

								Model(Model &item);
								Model(Model &&item);
};

} /* namespace MVC */

#endif /* INC_MVC_MODEL_H_ */
