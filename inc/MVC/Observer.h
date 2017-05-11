/*
 * Observer.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef INC_MVC_OBSERVER_H_
#define INC_MVC_OBSERVER_H_

namespace MVC {

class Model;
class Observer {
public:
								Observer(Model *model);
	virtual 					~Observer();

public:
	void						notify();
	virtual void				onNotify() = 0;
	const bool					isNotified() const;
	const void					resetNotifyFlag();

protected:
	const Model					*getModel() const;

private:
	Model						*m_model;
	bool						m_notifyFlag;
};

} /* namespace MVC */

#endif /* INC_MVC_OBSERVER_H_ */
