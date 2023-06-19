#pragma once
#include "LoggingObserver.h"
#include <list>

using namespace std;

class Observer {
    public:
        ~Observer();
        virtual void Update() = 0;
    protected:
        Observer();
};


class Subject {
    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
        Subject();
        ~Subject();
    private:
        list<Observer*> *_observers;
};
