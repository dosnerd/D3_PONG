/*
 * ImplemModel.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include <ImplemModel.h>

ImplemModel::ImplemModel(int data1, int data2, int data3, int data4)
	: m_data{ data1, data2, data3, data4 }
{
}

ImplemModel::~ImplemModel() {

}

const int ImplemModel::getData(unsigned int index) const {
	if (index < __MAX_ARRAY_DATA__){
		return m_data[index];
	}

	return 0;
}

void ImplemModel::setData(unsigned int index, int data){
	if (index < __MAX_ARRAY_DATA__) {
		m_data[index] = data;
		notifyObservers();
	}
}
