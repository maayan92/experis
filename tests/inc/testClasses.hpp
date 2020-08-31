#ifndef TEST_CLASSES_HPP
#define TEST_CLASSES_HPP

#include <cmath>

class Number {
public:
    Number(int a_value = 0) : m_value(a_value) { ++count; }
    virtual ~Number() { --count; }
    virtual int GetValue() const { return m_value; }

private:
    static int count;
    int m_value;
};

int Number::count = 0;

class Pow : public Number {
public:
    Pow(int a_value) : Number(a_value), m_value(pow(a_value, 2)) {}
    //virtual ~Pow() = default;

    virtual int GetValue() const { return m_value; }

private:
    int m_value;
};

class Double : public Number {
public:
    Double(int a_value) : Number(a_value), m_value(a_value * 2) {}
    //virtual ~Double() = default;

    virtual int GetValue() const { return m_value; }

private:
    int m_value;
};

#endif