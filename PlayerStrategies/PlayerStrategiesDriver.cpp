#include "PlayerStrategies.h"
#include "../CommandProcessing/CommandProcessing.h"

#include <iostream>
#include <istream>
using namespace std;
#include <vector>
class Player;
Map* map_obj;
int main(){

    Reinforcement force;
    IssueOrder order;

    string command = "";
    Player Neutral;
    Player Cheater;
    Player Human;
    Player Agressive;
    Player Benevolent;

    Human.setId(1);
    Cheater.setId(2);
    Neutral.setId(3);
    Agressive.setId(4);
    Benevolent.setId(5);

    Player* humanptr = &Human;
    Player* neutralptr = &Neutral;
    Player* cheaterptr = &Cheater;
    Player* aggressiveptr = &Agressive;
    Player* benevolentptr = &Benevolent;

    HumanPlayerStrategy* human = new HumanPlayerStrategy(humanptr);
    NeutralPlayerStrategy *neutral = new NeutralPlayerStrategy(neutralptr);
    CheaterPlayerStrategy* cheater = new CheaterPlayerStrategy(cheaterptr);
    BenevolentPlayerStrategy* benevolent = new BenevolentPlayerStrategy(aggressiveptr);
    AggressivePlayerStrategy* aggressive = new AggressivePlayerStrategy(benevolentptr);

    Neutral.setPlayerStrategy(neutral);
    Cheater.setPlayerStrategy(cheater);
    Human.setPlayerStrategy(human);
    Agressive.setPlayerStrategy(aggressive);
    Benevolent.setPlayerStrategy(benevolent);

    MapLoader load;
    map_obj = load.instantiation("../Map/MapFiles/Europe.txt");
    auto mapPtr = load.instantiation("../Map/MapFiles/Europe.txt");
    vector<Territory*> mapTerr = mapPtr->getMapTerritories();
    
    bool gameRun = true; 
    while (gameRun) {
        
       
        std::cout << "Welcome to game loop\nEnter : print_map, assign_reinforcement, issue_order, attack, defend" << std::endl;
        string response;

        cin >> response;

        if (response == "print_map") {
            std::cout << "Printing Territories from the map :" << std::endl;
            mapPtr->printMapTerritories(); 
        }
        
        else if (response == "assign_reinforcement") {
                force.reinforcementPhase(Human);
                force.reinforcementPhase(Cheater);
                force.reinforcementPhase(Neutral);
                force.reinforcementPhase(Agressive);
                force.reinforcementPhase(Benevolent);
        }

        else if (response == "issue_order") {
                Human.toAttack();
                Human.toDefend();
                Human.issueOrders();
                order.issueOrder(Human);
                order.issueOrder(Cheater);
            
            }
        else if(response == "execute_orders"){

            }

    }
    
}

/*
 *
 *
 * if (response == "p1win") {
            vector<Territory*> empty= Human.getVecTer();
            for (Territory* terr : empty) {
            empty.pop_back();
            }
            Human.setTerritories(empty);
        }

        if (Cheater.getVecTer().size() == 0) {
            std::cout << "Player 2 won!!" << std::endl ;
            gameRun = false;
        }
        if (Cheater.getVecTer().size() == 0) {
            std::cout << "Player 1 Won!!!" << std::endl;
            gameRun = false;
        }
 */

