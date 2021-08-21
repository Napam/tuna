#include <iostream>
// #include <fstream>
// #include <nlohmann/json.hpp>

// using json = nlohmann::json;


class Parent
{
public:
    void hi();
    virtual ~Parent() {};
};

void Parent::hi()
{
    std::cout << "Hi from parent\n";
}


class ChildA: public Parent
{
public:
    void hi();
    ChildA();
    virtual ~ChildA();
};

void ChildA::hi()
{
    std::cout << "Hi from child A\n";
}

ChildA::ChildA()
{

}

ChildA::~ChildA()
{
    std::cout << "Killing Child A\n";
}

class ChildB: public Parent
{
public:
    void hi();
    ChildB();
    virtual ~ChildB();
};

void ChildB::hi()
{
    std::cout << "Hi from child B\n";
}

ChildB::ChildB()
{

}

ChildB::~ChildB()
{
    std::cout << "Killing Child B\n";
}


int main(int argc, char **argv)
{
    ChildA *childA = new ChildA();
    ChildB *childB = new ChildB();
    Parent *parent = childA;

    (*childA).hi();
    (*childB).hi();
    (*parent).hi();

    delete parent;
    parent = childB;
    delete parent;

    return 0;
}