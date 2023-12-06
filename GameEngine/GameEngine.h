#pragma once
#include <string>
#include<iostream>
#include <vector>
#include "../LoggingObserver/LoggingObserver.h"
#include "../Player/Player.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
using namespace std;


//Forward declaration
class CommandProcessor;
// class ILoggable;
// class Subject;


//free function

//class State holds a string containing the state of the game
class State{
    //initializing all function prototypes for State class
    public:

    //string that holds the current state status
    string stateStatus;

    //default constructor
    State();
    //overloaded constructor (with Status name)
    explicit State(string state_name);
    //Copy constructor 
    State(const State& state_cpy);
    //Assignment Operators
    State& operator=(const State& state_cpy);
    //Destructor
    ~State();

    //Getters
    string getStateStatus();

    //Setters
    void setStateStatus(string state_name);
        
    //Stream insertion operator
   friend ostream& operator<<(ostream& out, const State& state_cpy);
};

//class Transition, holds a pointer that points to different states, given that the commmand is valid.
class Transition{
        //initializing all function prototypes for State class

    public:

    // current state, and next state
    State *currentState,*nextState;
    
    // required user command to initiate transition to desired state
    string userCommand;

    //default constructor
    Transition();
    //overloaded constructor (with current status, next status, and a command string)
    Transition(State* currentState,State* nextState, const string command);
    //Copy constructor 
    Transition(const Transition& transition_cpy);
    //Assignment Operators
    Transition& operator=(const Transition& transition_cpy);
    //destructor
    ~Transition();
    //Stream insertion operator
    friend ostream& operator<<(ostream& out, const Transition& transition_cpy);

    //Getters
    State* getCurrentState();
    State* getNextState();

};
class Game{

public:
    Game();
    Game(const vector<string>& maps, const vector<string>& players, int maxturns);

    void playGame();
private:
    vector<string> maps;
    vector<string> players;
    int maxTurns;
};
//Create Graph to hold nodes that represent States, and create
class GameEngine : public Subject, public ILoggable{


private:
    vector<State*> nodes;//vector nodes that holds State pointers
    vector<Transition*> transitions;//vector transitions that holds each transition added
    State* currentState;// State pointer that holds currenState in our graph.
    vector<Game> games;

public:
    GameEngine(): currentState(nullptr){}//GameEngine constructor initializing currentstate to a nullptr

    void addNode(State* node);//Function prototype for adding a node to our graph
    void addTransition(State* source,State* destination, const string& command );//Function proptotype for adding a state transition from source to destinatio.
    void setCurrentState(State* state);//Setter that sets the currentState.
    bool checkCurrentState(string);
    void tournamentExecution(const vector<string>& maps, const vector<string>& players,int numGames, int maxTurns);
    void end();
    State* getCurrenState();
    State* nextState(const string& command);
    GameEngine(const GameEngine& GameEngine_cpy);
    GameEngine& operator=(const GameEngine& GameEngine_cpy);//Assignment Operator.
    void startupPhase(CommandProcessor *cp_obj);
    //destructor
    ~GameEngine();

    void printGraph();//print GameEngine method that prints the States and possible transitions.

    string stringToLog();//overriding the pure virtual function from ILoggable


    //stream insertion operator
    friend ostream& operator<<(ostream& out, const GameEngine& GameEngine_cpy);

};



class Reinforcement{
    public:
    void reinforcementPhase(vector<Player>& playerList);
    int armyIncome(Player& player);
    void reinforcementPhase(Player& player);
};


class IssueOrder{
    public:
    void issueOrder(vector<Player>& playerList);
    void issueOrder(Player& player);
    void executeOrder(vector<Player>& playerList);
    void executeOrder(Player& player);
};


