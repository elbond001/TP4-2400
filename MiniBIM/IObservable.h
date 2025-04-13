#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <string>

class User; // forward declaration

class IObservable {
public:
    virtual ~IObservable() {}
    virtual void attach(User* observer) = 0;
    virtual void detach(User* observer) = 0;
    virtual void notifyAll(const std::string& message) = 0;
};

#endif
