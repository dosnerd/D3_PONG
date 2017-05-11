/*
 * ImplemView.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include "../inc/MVC/ImplemView.h"

ImplemView::ImplemView(ImplemModel *model)
		: MVC::View(model)
		, m_data { 	model->getData(0), model->getData(1),
					model->getData(2), model->getData(3) } {

}

ImplemView::~ImplemView() {

}

void ImplemView::onNotify(){
	int i;
	for (i = 0; i < __MAX_ARRAY_DATA__; ++i) {
		m_data[i] = ((ImplemModel *)getModel())->getData(i);
	}
}

const int ImplemView::getValidData(unsigned int index) const{
	if (index < __MAX_ARRAY_DATA__){
		return m_data[index];
	}

	return -1;
}
