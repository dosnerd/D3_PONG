/*
 * ImplemModel.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_MVC_IMPLEMMODEL_H_
#define TEST_INC_MVC_IMPLEMMODEL_H_

#include <MVC/Model.h>

#define __MAX_ARRAY_DATA__ 4

class ImplemModel: public MVC::Model {
public:
								ImplemModel(int data1, int data2, int data3, int data4);
	virtual 					~ImplemModel();


public:
	virtual const int			getData(unsigned int index) const;
	void 						setData(unsigned int index, int data);
private:
	int							m_data[__MAX_ARRAY_DATA__];
};

#endif /* TEST_INC_MVC_IMPLEMMODEL_H_ */
