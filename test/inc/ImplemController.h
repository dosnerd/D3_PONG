/*
 * ImplemController.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_IMPLEMCONTROLLER_H_
#define TEST_INC_IMPLEMCONTROLLER_H_

#include <MVC/Controller.h>

class ImplemModel;
class ImplemController: public MVC::Controller {
public:
								ImplemController(ImplemModel *model);
	virtual 					~ImplemController();

public:
	virtual void				setData(int data);
	virtual void				process();

private:
	unsigned int				m_iData;
};

#endif /* TEST_INC_IMPLEMCONTROLLER_H_ */
