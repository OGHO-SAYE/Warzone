#include "ITestable.h"
#include "Player.h"

class PlayerDriver : public ITestable {
    // ... other Player members and methods ...

public:
    // Implementing the ITestable methods
    void testDataMembers() override;
    void testCopy() override;
    void testAssignment() override;
    void testStreamInsert() override;
    
};

