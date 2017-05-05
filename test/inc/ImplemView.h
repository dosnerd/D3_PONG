/*
 * ImplemView.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_IMPLEMVIEW_H_
#define TEST_INC_IMPLEMVIEW_H_

#include <MVC/View.h>

class ImplemModel;
class ImplemView: public MVC::View {
public:
								ImplemView(ImplemModel *model);
	virtual 					~ImplemView();


public:

};

#endif /* TEST_INC_IMPLEMVIEW_H_ */
