#ifndef __UNCOPYABLE_H__
#define __UNCOPYABLE_H__

namespace experis {

class Uncopyable { // TODO: move this to uncopyable.h
public:
    Uncopyable() {}
    //~Uncopyable() = default;

private:
    Uncopyable(const Uncopyable &);
    Uncopyable &operator=(const Uncopyable &);
};

class Unassignable { // move this to uncopyable.h
public:
    //Unassignable() = default;
    //Unassignable(const Unassignable &a_other) = default;
    //~Unassignable() = default;

private:
    Unassignable &operator=(const Unassignable &);
};

} // experis

#endif