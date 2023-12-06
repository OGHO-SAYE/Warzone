////PlayerStrat implementation


#include <iostream>
#include "../Orders/Orders.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "PlayerStrategies.h"
// #include <algorithm>
using namespace std;

void printTerritories(vector<Territory*> territories)
{
    for (auto t: territories) {
        cout << t->get_name() << endl;
    }
}

bool playerTerritory(Player* p, Territory* territory)
{
    vector <Territory*> territories = p->getVecTer();
    bool returnValue = false;
    for (auto t: territories) {
        if (t->get_name() == territory->get_name()) {
            returnValue = true;
        }
    }
    return returnValue;
};


PlayerStrategy::PlayerStrategy() {}
PlayerStrategy::~PlayerStrategy() {}


//----------------------------------------------------------------------------------------------
//                                  HumanPlayerStrategy
//----------------------------------------------------------------------------------------------

/*
Need to do:
- human player strategy
        - issueOrder() --> done
        - toDefend() --> done
        - toAttack() --> done
- aggressive player strategy
        - issueOrder() --> done
        - toDefend() --> done
        - toAttack() --> done
- benevolent player strategy
        - issueOrder() --> done
        - toDefend() --> done
        - toAttack() --> done
- neutral player
        - issueOrder() --> done
        - toDefend() --> done
        - toAttack() --> done
- cheater player
        - issueOrder() --> done
        - toDefend() --> done
        - toAttack() --> done
*/

HumanPlayerStrategy::~HumanPlayerStrategy() {}
void HumanPlayerStrategy::issueOrder ()
{
        string command;
        while (true)
        {
                cout << "Possible orders: deploy, advance, airlift, bomb, blockade" << endl;
                cout << "Order to execute (type exit to end order issuing): " << endl;
                cin >> command;
                
                if (command == "exit")
                {
                        break;
                }
                
                if (command ==  "deploy")
                {
                        string territoryName;
                        int numSoldiers;
                        // cout << "List of territories to deploy: " << endl;
                        // printTerritories(toDefend());
                        cout << "Enter territory to deploy:" << endl;
                        cin >> territoryName;
                        
                        cout << "Enter number of armies to deploy: " << endl;
                        cin >> numSoldiers;
                        
                        for (auto t: map_obj->getMapTerritories())
                        {
                                if (t->get_name() == territoryName)
                                {
                                        p->_orders->add(new Deploy("deploy", numSoldiers, t, p));
                                }
                        }
                }
                if (command ==  "advance")
                {
                        string territoryFrom;
                        string territoryTo;
                        int numSoldiers;
                        cout << "List of territories you can advance from: " << endl;
                        printTerritories(toDefend());
                        cout << "Enter territory to advance from:" << endl;
                        cin >> territoryFrom;
                        
                        cout << "List of territories you can advance on: " << endl;
                        printTerritories(toAttack());
                        cout << "Enter territory to advance to:" << endl;
                        cin >> territoryTo;
                        
                        cout << "Enter number of armies to advance: " << endl;
                        cin >> numSoldiers;

                        Territory* source;
                        Territory* target;

                        for (auto t: map_obj->getMapTerritories())
                        {
                                if (t->get_name() == territoryFrom)
                                {
                                        source = t;
                                }
                                if (t->get_name() == territoryTo)
                                {
                                        target = t;
                                }
                        }
                        p->_orders->add(new Advance("advance", numSoldiers, source, target, p));
                }
                
                if (command ==  "airlift")
                {
                        string territoryFrom;
                        string territoryTo;
                        int numSoldiers;
                        cout << "List of territories you can advance from: " << endl;
                        printTerritories(toDefend());
                        cout << "Enter territory to advance from:" << endl;
                        cin >> territoryFrom;
                        
                        cout << "List of territories you can advance on: " << endl;
                        printTerritories(toAttack());
                        cout << "Enter territory to advance to:" << endl;
                        cin >> territoryTo;
                        
                        cout << "Enter number of armies to airlift: " << endl;
                        cin >> numSoldiers;

                        Territory* source;
                        Territory* target;

                        for (auto t: map_obj->getMapTerritories())
                        {
                                if (t->get_name() == territoryFrom)
                                {
                                        source = t;
                                }
                                if (t->get_name() == territoryTo)
                                {
                                        target = t;
                                }
                        }
                        p->_orders->add(new Airlift("airlift", numSoldiers, source, target, p));
                }
                if (command ==  "bomb")
                {//might need to have hasCard check, so the player can only make this move if they have the card in their hand
                        string territoryName;
                        cout << "List of territories you can bomb: " << endl;
                        printTerritories(toDefend());
                        cout << "Enter territory to bomb:" << endl;
                        cin >> territoryName;

                        Territory *target;

                        for (auto t: map_obj->getMapTerritories())
                        {
                                if (t->get_name() == territoryName)
                                {
                                        target = t;
                                }
                        }
                        p->_orders->add(new Bomb("bomb", target, p));
                }
                if (command ==  "blockade")
                {//might need to have hasCard check, so the player can only make this move if they have the card in their hand
                        string territoryName;
                        int numSoldiers;

                        cout << "List of territories you can blockade: " << endl;
                        printTerritories(toDefend());
                        cout << "Enter territory to blockade:" << endl;
                        cin >> territoryName;

                        cout << "Enter number of armies to blockade: " << endl;
                        cin >> numSoldiers;

                        Territory *target;

                        for (auto t: map_obj->getMapTerritories())
                        {
                                if (t->get_name() == territoryName)
                                {
                                        target = t;
                                }
                        }
                        p->_orders->add(new Blockade("blockade", numSoldiers, target, p));
                }
                
                // if (command ==  "negotiate")
                // {//might need to have hasCard check, so the player can only make this move if they have the card in their hand
                //         int playerID;
                //         int numSoldiers;

                //         cout << "List of players you can negotiate with: " << endl;
                //         for (auto po: players_obj) 
                //         {
                //                 cout << po->getPlayerId() << endl;
                //         }
                //         cout << "Enter player ID to negotiate with:" << endl;
                //         cin >> playerID;

                //         Player *target;

                //         for (auto pl: players_obj)
                //         {
                //                 if (pl->getPlayerId() == playerID)
                //                 {
                //                         target = pl;
                //                 }
                //         }
                //         p->_orders->add(new Negotiate("negotiate", target, p));
                // }
        }
        

    cout << "Calling issue order Human strategy";
}

vector <Territory*> HumanPlayerStrategy::toAttack(){
        std::cout << "Calling Human player Strategy to attack" << std::endl;
        // return p->getNeighbourTerr(*p);
        vector <Territory*> territories = p->getVecTer();
        vector <Territory*> attack_territories = p->getVecTer();

        if(territories.size() != 0)
        {
                vector <Territory*> enemy_territories = map_obj->getMapTerritories(); //get enemy territories
                
                for(int i = 0; i<enemy_territories.size(); i++)
                {
                        if(!playerTerritory(p, enemy_territories[i]))
                        {
                                attack_territories.push_back(enemy_territories[i]);
                        }
                }
        }      
        return attack_territories;
}

vector <Territory*> HumanPlayerStrategy::toDefend(){
    std::cout << "Calling Human player Strategy to Defend" << std::endl;
    return p->getVecTer();
}

//----------------------------------------------------------------------------------------------
//                                  AggressivePlayerStrategy
//----------------------------------------------------------------------------------------------

AggressivePlayerStrategy::~AggressivePlayerStrategy()  {}

void AggressivePlayerStrategy::issueOrder(){
        std::cout << "Calling Aggressive player Strategy to issue Order" << std::endl;
        vector<Territory*> defend_territories = toDefend();
        vector<Territory*> attack_territories = toAttack();
        
        if(defend_territories.size()!=0)
        {
                p->getOrders()->add(new Deploy("deploy", p->getArmy(), defend_territories[0], p));
        }
        
        if (attack_territories.size() != 0) {
                
                for (int i=0; i<attack_territories.size(); i++)
                {
                        p->getOrders()->add(new Advance("advance", p->getArmy(), defend_territories[0], attack_territories[i], p));
                }
        }
}

vector <Territory*> AggressivePlayerStrategy::toAttack(){
        std::cout << "Calling Aggressive player Strategy to Attack" <<std::endl;

        vector <Territory*> territories = p->getVecTer();
        vector <Territory*> attack_territories = p->getVecTer();

        if(territories.size() != 0)
        {
                vector <Territory*> enemy_territories = map_obj->getMapTerritories(); //get enemy territories
                
                for(int i = 0; i<enemy_territories.size(); i++)
                {
                        if(!playerTerritory(p, enemy_territories[i]))
                        {
                                attack_territories.push_back(enemy_territories[i]);
                        }
                }
        }      
        return attack_territories;
}

vector <Territory*> AggressivePlayerStrategy::toDefend(){
        // std::cout << "Calling AggressivePlayerStrategy to Defend" << std::endl;
        // return p->getVecTer(); // Return an empty vector
        vector <Territory*> territories = p->getVecTer();
        //sort the player's territories in descending order
        sort( territories.begin( ), territories.end( ), [ ]( const auto& lhs, const auto& rhs )
        {
                return lhs->get_army_size() > rhs->get_army_size();
        });
        return territories;
}

//----------------------------------------------------------------------------------------------
//                                  BenevolentPlayerStrategy
//----------------------------------------------------------------------------------------------
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

void BenevolentPlayerStrategy::issueOrder(){
        std::cout << "Calling Benevolent player Strategy to issue order" << std::endl;
        vector <Territory*> weakestTerritories = toDefend();

        if(weakestTerritories.size() != 0) // needs to be changed so that it doesn't just do all territories
        {
                for(int i=0; i<weakestTerritories.size(); i++)
                {
                        p->getOrders()->add(new Deploy("deploy", p->getArmy(), weakestTerritories[i], p));
                }
        }
}

vector <Territory*> BenevolentPlayerStrategy::toAttack(){
        std::cout << "Calling benevolent player strategy to attack" << std::endl;
        return p->getNeighbourTerr(*p); // Return an empty vector since benevolvent players don't attack

}

vector <Territory*> BenevolentPlayerStrategy::toDefend(){
        vector <Territory*> territories = p->getVecTer();

        sort( territories.begin( ), territories.end( ), [ ]( const auto& lhs, const auto& rhs )
         {
             return lhs->get_army_size() < rhs->get_army_size();
         });

        vector <Territory*> defend_territories;
        //push into vector the weakest countries
        for(int i = 0; i<territories.size(); i++)
        {
                if(territories[i]->get_army_size()==territories[0]->get_army_size())
                {
                        defend_territories.push_back(territories[i]);
                }
                }
        return defend_territories;
        std::cout << "Calling Benevolent player Strategy to defend" << std::endl;
        // return p->getVecTer(); // Return an empty vector for now
}

//----------------------------------------------------------------------------------------------
//                                  NeutralPlayerStrategy
//----------------------------------------------------------------------------------------------
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}
void NeutralPlayerStrategy::issueOrder(){
        //do nothing
        std::cout << "Calling Neutral player Strategy to issue order\n nothing happens" << std::endl;
}

vector <Territory*> NeutralPlayerStrategy::toAttack(){
        std::cout << "Calling Neutral player Strategy to attack\ndoes not attack" << std::endl;
        vector <Territory*> attack;
        return attack;
}

vector <Territory*> NeutralPlayerStrategy::toDefend(){
        std::cout << "Calling Neutral player Strategy to Defend" << std::endl;
        return p->getVecTer();
}

//----------------------------------------------------------------------------------------------
//                                  CheaterPlayerStrategy
//----------------------------------------------------------------------------------------------
CheaterPlayerStrategy::~CheaterPlayerStrategy() {}

void CheaterPlayerStrategy::issueOrder(){
        std::cout << "Calling Cheater player Strategy to issue order" << std::endl;
        
        // vector<Territory*> defend_territories = toDefend();
        vector<Territory*> attack_territories = toAttack();
                
        for (int i=0; i<attack_territories.size(); i++)
        {
                attack_territories[i]->set_player_id(this->p->getPlayerId());//i don't know if this works
        }
}

vector <Territory*> CheaterPlayerStrategy::toAttack(){
    std::cout << "Calling Cheater player Strategy to attack" << std::endl;
//     return p->getNeighbourTerr(*p);

        vector <Territory*> territories = p->getVecTer();
        vector <Territory*> attack_territories = p->getVecTer();

        if(territories.size() != 0)
        {
                vector <Territory*> enemy_territories = map_obj->getMapTerritories(); //get enemy territories
                
                for(int i = 0; i<enemy_territories.size(); i++)
                {
                        if(!playerTerritory(p, enemy_territories[i]))
                        {
                                attack_territories.push_back(enemy_territories[i]);
                        }
                }
        }      
        return attack_territories;

}

vector <Territory*> CheaterPlayerStrategy::toDefend()
{
    std::cout << "Calling Cheater player Strategy to defend" << std::endl;
    return vector<Territory*>(); // Return an empty vector for now

}
