#ifndef TEST_CONTAINER_HPP
#define TEST_CONTAINER_HPP

#include <gui_generated/containers/Test_containerBase.hpp>

class Test_container : public Test_containerBase
{
public:
    Test_container();
    virtual ~Test_container() {}

    virtual void initialize();
protected:
};

#endif // TEST_CONTAINER_HPP
