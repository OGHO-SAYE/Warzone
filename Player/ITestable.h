#pragma once

class ITestable {
public:
    virtual ~ITestable() {}  
    virtual void testDataMembers() = 0;
    virtual void testCopy() = 0;
    virtual void testAssignment() = 0;
    virtual void testStreamInsert() = 0;
};


