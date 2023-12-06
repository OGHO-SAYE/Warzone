#pragma once
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include "../Map/Map.h"
#include "../Player/Player.h"

using namespace std;

class Player;
class Map;

extern Map* map_obj;
extern vector <Player*> players_obj;

void printTerritories(vector<Territory*>);

class PlayerStrategy
{
    public:
        Player *p;

        // Default constructor
        PlayerStrategy(Player* player = nullptr) : p(player) {}
        //Default constructor
        virtual ~PlayerStrategy();
        //Parameterized constructor
        PlayerStrategy();

        //Copy constructor
        PlayerStrategy(const PlayerStrategy *p);

        virtual void issueOrder() = 0;
        virtual vector <Territory*> toAttack() = 0; 
        virtual vector <Territory*> toDefend() = 0; 

};


class HumanPlayerStrategy : public PlayerStrategy
{
    private:

    public:
        //Default constructor
        HumanPlayerStrategy();

        HumanPlayerStrategy(Player* player) : PlayerStrategy(player) {}


        //Destructor
        ~HumanPlayerStrategy();

        void issueOrder() override;
        vector <Territory*> toDefend() override;
        vector <Territory*> toAttack() override;

};

class AggressivePlayerStrategy : public PlayerStrategy
{
    public:
        //Default constructor
        AggressivePlayerStrategy();

        AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) {}


    //Destructor
        ~AggressivePlayerStrategy();

        void issueOrder()override;
        vector <Territory*> toDefend()override;
        vector <Territory*> toAttack() override;

};

class BenevolentPlayerStrategy : public PlayerStrategy
{
    public:
        //Default constructor
        BenevolentPlayerStrategy();
        BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {}

        //Destructor
        ~BenevolentPlayerStrategy();

        void issueOrder()override;
        vector <Territory*> toDefend() override;
        vector <Territory*> toAttack()override;

};

class NeutralPlayerStrategy : public PlayerStrategy
{
    private:

    public:
        //Default constructor
        NeutralPlayerStrategy();
        NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) {}

        //Destructor
        ~NeutralPlayerStrategy();
        
        void issueOrder()override;
        vector <Territory*> toDefend()override;
        vector <Territory*> toAttack()override;

};

class CheaterPlayerStrategy : public PlayerStrategy
{
    private:

    public:
        //Default constructor
        CheaterPlayerStrategy();
        CheaterPlayerStrategy(Player* player) : PlayerStrategy(player) {}

    //Destructor
        ~CheaterPlayerStrategy();
        
        void issueOrder()override;
        vector <Territory*> toDefend()override;
        vector <Territory*> toAttack()override;

};
