/*
 * ImplemController.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include "../inc/MVC/ImplemController.h"

#include <iostream>
#include "../inc/MVC/ImplemModel.h"

ImplemController::ImplemController(ImplemModel *model)
	: MVC::Controller(model)
	, m_iData(0)
{

}

ImplemController::~ImplemController() {

}

void ImplemController::setData(int data) {
	((ImplemModel *)getModel())->setData(m_iData, data);

	if (++m_iData >= __MAX_ARRAY_DATA__){
		m_iData = 0;
	}
}

void ImplemController::onNotify()
{
	unsigned int i;
	ImplemModel *model = (ImplemModel *)getModel();

	for (i = 0; i < __MAX_ARRAY_DATA__; ++i) {
		if (model->getData(i) > 10){
			model->setData(i, 10);
		} else if (model->getData(i) < 0){
			model->setData(i, 0);
		}
	}
}
