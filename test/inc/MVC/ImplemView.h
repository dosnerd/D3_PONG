/*
 * ImplemView.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_MVC_IMPLEMVIEW_H_
#define TEST_INC_MVC_IMPLEMVIEW_H_

#include <MVC/View.h>
#include <MVC/ImplemModel.h>

class ImplemView: public MVC::View {
public:
								ImplemView(ImplemModel *model);
	virtual 					~ImplemView();


public:
	virtual void				onNotify();
	virtual const int			getValidData(unsigned int index) const;

private:
	int							m_data[__MAX_ARRAY_DATA__];
};

#endif /* TEST_INC_MVC_IMPLEMVIEW_H_ */
