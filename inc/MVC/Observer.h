//
// Created by Acer on 2-3-2017.
//

#ifndef TESTING_OBSERVER_H
#define TESTING_OBSERVER_H

namespace MVC {
	class Observer {
	public:
						Observer() { };
		virtual         ~Observer() { };

	public:
		virtual void    update() = 0;
	};
}


#endif //TESTING_OBSERVER_H
