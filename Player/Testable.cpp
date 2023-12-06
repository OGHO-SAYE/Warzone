#include <iostream>
#include <vector>
#include "Player.h"
#include "Testable.h"
#include <type_traits>


using std::vector;
void testDataMembers(Player obj);

////////////////////////////////
//=============================
//      General Requirements
//=============================
//
//1. All data members of user-defined class type must be of pointer type.


//2. All file names and the content of the files must be according to what is given in the description below.
//3. All different parts must be implemented in their own separate .cpp/.h file duo. All functions’ implementation
//must be provided in the .cpp file (i.e. no inline functions are allowed).

//4. All classes must implement a correct copy constructor, assignment operator, and stream insertion operator.
void testCopy(Player obj);
void testAssignment(Player obj);
void testStreamInsert(Player obj);

//5. Memory leaks must be avoided.
//6. Code must be documented using comments (user-defined classes, methods, free functions, operators).
//7. If you use third-party libraries that are not available in the labs and require setup/installation, you may not
//assume to have help using them and you are entirely responsible for their proper installation for grading
//purposes. 

/////////////////////
//===================
//  Player Section
//  ================
/////////////////////

std::string countries[] = {
        "Afghanistan", "Albania", "Algeria", "Andorra", "Angola",
        "Antigua and Barbuda", "Argentina", "Armenia", "Australia", "Austria"
     
    };

int armySize[]={

    0,1,2,3,4,5,6,7,8,9,10
};

int coordinates[]={
    0, 111, 222, 333, 444, 555, 666, 777, 888, 999

};

std::string continent[] = {
        "North America","Europe"
     
    };

 vector<Territory*> createTerritoriesWithContinents(){
    Continent* cont1 = new Continent(continent[0], 5, {});
    Continent* cont2 = new Continent(continent[1], 5, {});
    auto ter1 = new Territory(countries[1], armySize[0], coordinates[0], coordinates[1] ,{}, cont1);
    auto ter2 = new Territory(countries[0] , armySize[3], coordinates[3], coordinates[4],{} , cont2);
    auto ter4 = new Territory(countries[4] , armySize[2], coordinates[7], coordinates[6],{} , cont2);
    auto ter3 = new Territory(countries[5] , armySize[5], coordinates[5], coordinates[5],{} , cont2);

    // creating some arbitrary vector of territory objects
    vector<Territory*> terrList;

    terrList.push_back(ter1);
    terrList.push_back(ter2);
    terrList.push_back(ter3);
    terrList.push_back(ter4);
    cout << "Territories created\n";
    return terrList;

 }

 Hand* createNewHand(){

    // creating some arbitrary hand of cards
    auto *deck = new Deck();
    deck->addCardTypeToDeck(CardType::REINFORCEMENT);
    deck->addCardTypeToDeck(CardType::BLOCKADE);
    deck->addCardTypeToDeck(CardType::AIRLIFT);
    deck->addCardTypeToDeck(CardType::DIPLOMACY);

    auto *hand1 = new Hand();
    
    deck->draw(hand1);
    deck->draw(hand1);
    deck->draw(hand1);
    deck->draw(hand1);
    deck->draw(hand1);

    return hand1;
 }

 OrdersList* createOrders(vector<Territory*> terrList){
    // creating some arbitrary vector of orders
    int numSoldiers = 1;
    OrdersList* orders = new OrdersList();
    Deploy* deploy = new Deploy("deploy", numSoldiers, terrList[2]);
    Advance* advance = new Advance("advance", numSoldiers, terrList[3], terrList[4]);
    Bomb* bomb = new Bomb("bomb", terrList[1]);
    Blockade* blockade = new Blockade("blockade", numSoldiers, terrList[2]);
    Airlift* airlift = new Airlift("airlift", numSoldiers, terrList[0], terrList[1]);
    orders->add(deploy);
    orders->add(advance);
    orders->add(bomb);
    cout << "Orders created \n";
    cout <<"\n";
    return orders;

 }

 int main (int argc, char *argv[]) {
   
   auto territories = createTerritoriesWithContinents();
   auto hand = createNewHand();
   auto orders = createOrders(territories);
   Player one(territories,*orders,1,*hand);

   
   testDataMembers(one);
   testCopy(one); 
   testAssignment(one);

}

void testDataMembers(Player obj){

   cout << "Player Attributes Will return true if all are ptrs \n";
   cout << "Hand? " << boolalpha << std::is_pointer<decltype(obj.getHand())>::value << "\n";
   cout << "Orders? " << std::boolalpha << std::is_pointer<decltype(obj.getOrders())>::value << "\n";
   cout << "Territories? " << std::boolalpha << std::is_pointer<decltype(obj.getVecTer())::value_type>::value << "\n\n";
   
}

void testCopy(Player obj){
   cout << "Testing Copy constructor \n";
   Player copy(obj);
   cout << copy;

}

void testAssignment(Player obj){
   cout << "\nTesting Assignment operator \n";
   Player copy = obj;
   cout <<obj;
}
