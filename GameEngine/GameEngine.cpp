////GameEngine implementation


#include "GameEngine.h"
#include <algorithm>
#include <ostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

//********************************************************
//*************** STATE IMPLEMENTATION ***************
//********************************************************
State::State(){

    this->stateStatus="pending";
}
State::State(string state_name)
{
    this->stateStatus=state_name;
}

State::State(const State &state_cpy) :stateStatus(state_cpy.stateStatus)
{

}

string State::getStateStatus()
{
    return this->stateStatus;
}
State::~State(){

}

void State::setStateStatus(string state_name)
{
    this->stateStatus=state_name;
}
State& State::operator=(const State &state_cpy)
{
	this->stateStatus = state_cpy.stateStatus;
	return *this;
}

ostream &operator<<(ostream &out, const State &state_cpy)
{
    out << "Current State Status: " << state_cpy.stateStatus<<endl;

    return out;
}

//********************************************************
//*************** TRANSITION IMPLEMENTATION ***************
//********************************************************

Transition::Transition()
{
    this->currentState = nullptr;
    this->nextState=nullptr;
    this->userCommand="Pending";

}

Transition::Transition(State *currentState, State *nextState, const string command)
{
    this->currentState=currentState;   
    this->nextState=nextState;   
    this->userCommand=command;
}
Transition::~Transition(){

}
Transition::Transition(const Transition& transition_cpy): currentState(transition_cpy.currentState ? new State(*transition_cpy.currentState) : nullptr),nextState(transition_cpy.nextState ? new State(*transition_cpy.nextState) : nullptr),userCommand(transition_cpy.userCommand)
{}


State *Transition::getCurrentState()
{
    return currentState;
}

State *Transition::getNextState()
{
    return nextState;
}
Transition& Transition::operator=(const Transition& transition_cpy)
{
    if (this == &transition_cpy) {
        return *this; // Handle self-assignment
    }
    delete currentState;
    delete nextState;

    this->currentState = new State (*transition_cpy.currentState);
	this->nextState = new State (*transition_cpy.nextState);
	this->userCommand = transition_cpy.userCommand;

	return *this;
}
ostream &operator<<(ostream &out, const Transition &transition_cpy)
{
    out << "[State transitioning from current State: " <<transition_cpy.currentState->stateStatus<<" to next state: "<< transition_cpy.nextState->stateStatus<<"]\n";

    return out;
}

//********************************************************
//*************** GRAPH IMPLEMENTATION ***************
//********************************************************


void GameEngine::addNode(State *node) {
    nodes.push_back(node);

}
//
void GameEngine::addTransition(State *source, State *destination, const string &command) {
    transitions.emplace_back(new Transition(source,destination,command));
}

void GameEngine::printGraph() {

    for (const auto& transition : transitions) {
        cout << "Transition: State " << transition->currentState->getStateStatus()  << " to State " << transition->nextState->getStateStatus() << " (Command: " << transition->userCommand << ")" << endl;
    }
}
void GameEngine::setCurrentState(State *state){
    currentState = state;
}
State* GameEngine::getCurrenState() {
    return currentState;
}
State* GameEngine::nextState(const string &command)  {
    LogObserver *observer = new LogObserver(this);
    for (const auto& transition : transitions) {
        if (transition->currentState == currentState && transition->userCommand == command) {
            Notify(this);//NOTE: not sure if this belongs here
            delete observer;
            observer = NULL;
            return transition->nextState;
        }
    }
    return nullptr; // Invalid action or no valid transition found
}
bool GameEngine::checkCurrentState(string command) {
    for (int i = 0; i < transitions.size(); i++)
    {
        if (currentState->stateStatus == transitions[i]->currentState->stateStatus && command == transitions[i]->userCommand)
        {
            currentState = transitions[i]->nextState;
            cout << *currentState;
            return true;
        }
        else if (currentState->stateStatus == "win" && command == "end") return true;
    }
    return false;
}
GameEngine::GameEngine(const GameEngine& GameEngine_cpy) : nodes([](const vector<State*>& src) { vector<State*> dest; for(auto s : src) dest.push_back(new State(*s)); return dest; }(GameEngine_cpy.nodes)), transitions([](const vector<Transition*>& src) { vector<Transition*> dest; for(auto t : src) dest.push_back(new Transition(*t)); return dest; }(GameEngine_cpy.transitions)), currentState(new State(*GameEngine_cpy.currentState))
{

}

GameEngine& GameEngine::operator=(const GameEngine& GameEngine_cpy)
{
    this->transitions=GameEngine_cpy.transitions;
    this->currentState=GameEngine_cpy.currentState;
    this->nodes=GameEngine_cpy.nodes;


    return *this;
}

//Added A delete statement to handle transition deletion in destructor to avoid memory leaks.
GameEngine::~GameEngine() {
    // Free memory for nodes
    for (auto node : nodes) {
        delete node;
    }
    nodes.clear();

    // Free memory for transitions
    for (auto transition : transitions) {
        delete transition;
    }
    transitions.clear();
}


ostream &operator<<(ostream &out, const GameEngine &GameEngine_cpy){
    for (const auto& transition : GameEngine_cpy.transitions) {
        out << "Transition: ";
        out << "From State " << transition->currentState->getStateStatus();
        out << " to State " << transition->nextState->getStateStatus();
        out << " (Command: " << transition->userCommand << ")";
        out << "\n";
    }
    return out;
}
void GameEngine::end() {

    delete this;
    cout<<"Game has now ended, Thanks for playing! :)\n";
}

//stringToLog implementation from ILoggable
string GameEngine::stringToLog()
{
    return "GameEngine State: " + currentState->stateStatus;
}

//Assignment#2 PART2
void GameEngine::startupPhase(CommandProcessor *cp_obj) {

    Map* map_instance1;

    vector<Command *> validCommands = cp_obj->getValidcommands();
    for (const auto &command: validCommands) {
        cout << *command << "," << endl;
        string command_string = command->getCommandPassed();

        if(command_string.find("loadmap") != string::npos){
            string effect_string = command->getCommandPassed();

            std::istringstream iss(effect_string);
            std::string map_name;

            while (iss >> map_name) {
                // Check if the word ends with ".txt"
                if (map_name.size() > 4 && map_name.substr(map_name.size() - 4) == ".txt") {
                    std::cout << map_name << std::endl;
                    break;
                }
            }
            string file_path = "../Warzone/Map/MapFiles/" + map_name;
            map_instance1 = MapLoader::instantiation(file_path);
        }

        else if(command_string.find("validatemap") != string::npos){
            string effect_string = command->getCommandPassed();

            map_instance1->validate();
        }

        else if(command_string.find("addplayer") != string::npos){
            string effect_string = command->getCommandPassed();

            std::istringstream ss(effect_string);
            std::string player_name;

            //Loop through the words
            while (ss >> player_name) { //Do nothing inside the loop, let it iterate to get the last word which is the player name
            }

        }

    }




}

/*
 * **********************************************
 * **********************************************
 *ASSIGNMENT 2 IMPLEMENTATIONS, ***** PART 1*****
 * **********************************************
 * **********************************************
 */

 void Reinforcement::reinforcementPhase(vector<Player>& playerList){
        
    std::cout << "Reinforcement Phase starting" << std::endl;

     for (Player& player : playerList) {
        int amount = armyIncome(player);
        player.addArmyUnits(amount);
        std::cout << "Player " << player.getPlayerId() << " is gaining " << amount << " units" << std::endl;
        std::cout << "Player has " <<player.getArmy() << " units total \n" << std::endl;
     }   


    std::cout << "Reinforcement Phase ending" << std::endl;
}

void Reinforcement::reinforcementPhase(Player& player){


    std::cout << "Reinforcement Phase starting" << std::endl;
    int amount = armyIncome(player);
    player.addArmyUnits(amount);

    std::cout << "Player has " <<player.getArmy() << " units total \n" << std::endl;
}


int Reinforcement::armyIncome(Player& player){

    int territories = player.getVecTer().size();
    std::cout << "Player " << player.getPlayerId() << " has " << territories << " Territories" << std::endl;

    int numOfArmies = floor(territories / 3);
    if (numOfArmies < 3) {
        numOfArmies = 3;
   }
    std::cout << "Player " << player.getPlayerId() << " receives " << numOfArmies << " armies" << std::endl;

return numOfArmies;

}

void IssueOrder::issueOrder(vector<Player>& playerList){

    std::cout << "Order Issue phase starting" << std::endl;

    for(Player& player :playerList){
        string decision;
        std::cout << "Player: " << player.getPlayerId()<< "\n"<< "choose Attack or Defend"  << std::endl;
        std::cin >> decision;

        if (decision == "attack") {
            std::cout << "Which territories do you want to attack?" << std::endl;
            auto terrtoAttack = player.getNeighbourTerr(player);
             
            for (Territory* terr : terrtoAttack) {
            std::cout << terr->get_name() << std::endl;
            }
        }

        else if (decision == "defend") {
            std::cout << "Which territories do you want to defend?" << std::endl;
        
        }
    }


    std::cout << "Order issue phase ending" << std::endl;

}

void IssueOrder::issueOrder(Player& player){
    
    std::cout << "Order Issue phase starting" << std::endl;
    std::cout << "Player " << player.getPlayerId() << " is starting his phase" << std::endl;
    std::cout << "Attack or defend?" << std::endl;
    string decision;
    cin >> decision;

        if (decision == "attack") {
            std::cout << "Which territories do you want to attack?" << std::endl;
            auto terrtoAttack = player.getNeighbourTerr(player);
            
            int count = 0;
            int count2 = 0;
            int destination; 
            int units;
            int source;

            for (Territory* terr : terrtoAttack) {
            std::cout << count  << " " << terr->get_name() << std::endl;
            count ++;
            }

            cin >> destination;
        
            std::cout << "From which territory? " << std::endl;
            auto terrOwnedByplayer = player.getVecTer();
            for (Territory* ter : terrOwnedByplayer) {
                std::cout << count2 << " "<<ter->get_name() << " army size :" << ter->get_army_size() << std::endl;
                count2 ++;
            
            }
            cin >> source;

            std::cout << "How many units to attack with ?" << std::endl;
            cin >> units;

            if (units > terrOwnedByplayer[destination]->get_army_size()) {
                std::cout << "You have gained the territory!" << std::endl;
            }

            

        }

        else if (decision == "defend") {
            int answer;
            int amount;
            std::cout << "Which territories do you want to defend?" << std::endl;
            auto terrtoDefend = player.getVecTer();

            int count = 0;
             
            for (Territory* terr : terrtoDefend) {
            std::cout << count<<" " << terr->get_name() << std::endl;
            count ++;
            }
            
            cin >> answer;
            

            std::cout << "How many armies to defend?" << std::endl;
            cin >> amount;
            
            player.addArmytoTerritory(amount,answer);
            std::cout << "Territory "<< terrtoDefend[answer]->get_name() << " has " <<  player.getVecTer()[answer]->get_army_size() << " army" << std::endl;
            int newArmySize = player.getArmy() - amount;
            player.setArmySize(newArmySize);
            cout << "Player " << player.getPlayerId() << " has " << player.getArmy() << " unit left "<< endl;



        }

}

void IssueOrder::executeOrder(vector<Player>& playerList){
        
    std::cout << "Executing orders..." << std::endl;

std::cout << "Executing orders finished" << std::endl;

}
//GAME
Game::Game() {
    // Initialize default values or leave vectors empty if needed
    maxTurns = 0;  // You might want to set a meaningful default value
}

// Parameterized constructor
Game::Game(const vector<string>& maps, const vector<string>& players, int maxturns) {
    this->maps = maps;
    this->players = players;
    this->maxTurns = maxturns;
}
void Game::playGame() {

     cout<< "Game is commencing using these maps:";
     for(const auto& map : maps){
         cout<< map<< " ";
     }

     cout<< ", PLayers:";
    for (const auto& player : players) {
        cout << player << " ";
    }

    cout<<", having max turns of"<< maxTurns<<endl;

 }
void GameEngine::tournamentExecution(const vector<string>& maps, const vector<string>& players, int numGames, int maxTurns) {
     for(int gameidx = 1; gameidx<= numGames; ++gameidx){
         Game game(maps, players, maxTurns);
         game.playGame();
         games.push_back(game);
     }

     //log results of game....
 }


