#include <iostream>
#include "Mutex.h"

class Singleton {
public:
	static Singleton* getInstance() {
		if (this->instance == NULL) {
			MutexLockGurad mlg(&mutex);

			if (this->instance == NULL)
				this->instance = new Singleton();
		}

		return this->instance;
	}

private:
	Singleton();
	~Singleton();

	static MutexLock mutex;
	static Singleton *instance;
};