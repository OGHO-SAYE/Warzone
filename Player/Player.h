#pragma once
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../PlayerStrategies/PlayerStrategies.h"


#include <ostream>
#include <vector>

class OrdersList;
class Orders;
class Territory;
class Card;
class PlayerStrategy;

class Player{

private:

vector<Territory*> _territories;
int _playerId;
Hand * _hand;
int _army;



public:
        //Default constructor
        Player();
        //Parameterized constructor
        Player(vector<Territory*>& territories,OrdersList& orders, int playerID, Hand& hand, PlayerStrategy& strategy);
        //copy constructor
        Player(const Player& PlayerCopy);
        //destructor
        ~Player();

        //Assignment operator overload
        Player& operator =(const Player& obj);

        //Output stream operator overload
        friend std::ostream& operator<<(std::ostream& os, const Player& player);

        PlayerStrategy* ps;//making this public bc it's not that serious; can change to private + add getters and setters if you want
        
        //Getters
        const int getPlayerId() const;
        const std::string getTerritories() const;
        OrdersList* getOrders();//removed const so add would work
        const Hand* getHand() const;
        const int getArmy() const;
        const PlayerStrategy getPlayerStrategy();

        const vector<Territory*> getVecTer()const;

        OrdersList* _orders ;//making this public so we don't have to deal with accessibility.

        //Setters
        void setId(int id);
        void setTerritories(vector<Territory*>& territories);
        void setOrders(OrdersList& orders);
        void setHand(Hand& hand);
        void addArmyUnits(int unit);
        void setPlayerStrategy(PlayerStrategy* p);

        //methods
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        void issueOrders();

        const string printOrder() const;
        vector<Territory*> getNeighbourTerr(Player& player);

        void addArmytoTerritory(int amount, int terrNum);
        void setArmySize(int size);

};
