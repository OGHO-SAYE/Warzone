#include "GameEngine.h"

#include "../CommandProcessing/CommandProcessing.h"
#include <iostream>
#include <istream>
#include "../GameEngine/GameEngine.h"

using namespace std;
#include <vector>

/**
 * @brief This function would take an input from the user, then it will continue taking inputs till player ends game. 
 * 
 * @return ** void does not return anything
 */
void testStartupPhase(){
    CommandProcessor *cprocessor = new CommandProcessor();

    GameEngine *game = new GameEngine();

    State *start = new State("start");
    State *map_loaded = new State("map_loaded");
    State *map_validated = new State("map_validated");
    State *players_added = new State("players_added");
    State *assign_reinforcement = new State("assign_reinforcement");
    State *win = new State("win");
    State *end_game = new State("end_game");


    game->addNode(start);
    game->addNode(map_loaded);
    game->addNode(map_validated);
    game->addNode(players_added);
    game->addNode(assign_reinforcement);
    game->addNode(win);
    game->addNode(end_game);

    //Add valid Transitions to our existing gameEngine.
    game->addTransition(start, map_loaded, "loadmap");
    game->addTransition(map_loaded, map_loaded, "loadmap");
    game->addTransition(map_loaded, map_validated, "validatemap");
    game->addTransition(map_validated, players_added, "addplayer");
    game->addTransition(players_added, players_added, "addplayer");
    game->addTransition(players_added, assign_reinforcement, "gamestart");
    game->addTransition(assign_reinforcement, win, "gameend");

    game->addTransition(win, start, "replay");
    game->addTransition(win, end_game, "quit");

    game->setCurrentState(start);

    string userResponse;
    string followUpResponse;
    string fileName;

    cout << "which method would you like to accept commands from, via the console or via reading from a file? please type \"console\" or \"file\"\n";
    cin >> userResponse;


    if (userResponse == "console") {
        cout<<"***Now accepting command from console***" << endl;

        while (!(cprocessor->getExitProgramstatus())) {
            cprocessor->getCommand(game, cprocessor);
        }

        game->startupPhase(cprocessor);

        cout << "\n All commands:";
        vector<Command *> commands = cprocessor->getCommandsList();
        for (const auto &command: commands) {
            cout << *command << "," << endl;
        }
        cout << "\n All valid commands:";
        vector<Command *> validCommands = cprocessor->getValidcommands();
        for (const auto &command: validCommands) {
            cout << *command << "," << endl;
        }
        delete cprocessor;
    }

    else if(userResponse== "file"){
        cout<<"***Now accepting command from file***\n Please enter the file name you wish to open\n";

        cin>>fileName;
        cout<<endl;

        FileLineReader* fileReader = new FileLineReader();
        fileReader->readFromFile(fileName);

        FileCommandProcessorAdapter* commandFile = new FileCommandProcessorAdapter(fileReader);

        while (!(cprocessor->getExitProgramstatus())){
            cprocessor->getCommand(game,commandFile);
        }

        cout << "\n All commands:";
        vector<Command *> commands = cprocessor->getCommandsList();
        for (const auto &command: commands) {
            cout << *command << "," << endl;
        }
        cout << "\n All valid commands:";
        vector<Command *> validCommands = cprocessor->getValidcommands();
        for (const auto &command: validCommands) {
            cout << *command << "," << endl;
        }

        delete commandFile;
        delete fileReader;
        delete cprocessor;
    }

    game->end();
    game=NULL;
}

void testGameStates() {

    //Instantiate pointer Objects from Class State, and assign various States which represent State Nodes
    State *start = new State("start");
    State *map_loaded = new State("map_loaded");
    State *map_validated = new State("map_validated");
    State *players_added = new State("players_added");
    State *assign_reinforcement = new State("assign_reinforcement");
    State *issue_orders = new State("issue_orders");
    State *execute_orders = new State("execute_orders");
    State *win = new State("win");

    //Instantiate one pointer of GameEngine object that we would use to hold our States, and Valid Transitions.
    GameEngine *Play = new GameEngine;

    //Populate the Graphs with Nodes that represent the States of our Game.
    Play->addNode(start);
    Play->addNode(map_loaded);
    Play->addNode(map_validated);
    Play->addNode(players_added);
    Play->addNode(assign_reinforcement);
    Play->addNode(issue_orders);
    Play->addNode(execute_orders);
    Play->addNode(win);

    //Add valid Transitions to our existing Play GameEngine.
    Play->addTransition(start, map_loaded, "loadmap");
    Play->addTransition(map_loaded, map_loaded, "loadmap");
    Play->addTransition(map_loaded, map_validated, "validatemap");
    Play->addTransition(map_validated, players_added, "addplayer");
    Play->addTransition(players_added, players_added, "addplayer");
    Play->addTransition(players_added, assign_reinforcement, "assigncountries");
    Play->addTransition(assign_reinforcement, issue_orders, "assign_reinforcement");
    Play->addTransition(issue_orders, issue_orders, "issueorder");
    Play->addTransition(issue_orders, execute_orders, "endissueorders");
    Play->addTransition(execute_orders, execute_orders, "execorder");
    Play->addTransition(execute_orders, assign_reinforcement, "endexecorders");
    Play->addTransition(execute_orders, win, "win");
    Play->addTransition(win, start, "play");
    Play->addTransition(win, nullptr, "end");

//    //Print out to the console, the valid transitions that represent our graph.
//    cout<<"\t\t*******************************"<<endl<<"\t\t****VALID GRAPH TRANSITIONS****"<<endl<<"\t\t*******************************"<<endl;
//    Play->printGraph();

    //When Code runs the game automatically starts, and our initial state would always be 'START'
    Play->setCurrentState(players_added);

    Reinforcement force;
    IssueOrder order;

    //Initialize and define an empty command string that takes input from the user
    string command = "";
    Player one;
    Player two;
    one.setId(1);
    two.setId(2);
   // vector<Player> playerList;
    MapLoader load;
    auto mapPtr = load.instantiation("../Map/MapFiles/Africa.txt");

    std::cout << "Printing Territories from the map :" << std::endl;
    mapPtr->printMapTerritories(); 
    std::cout << "===================================" << std::endl;
    std::cout << "Printing Continents from the map" << std::endl;

    mapPtr->printMapContinents();
    vector<Territory*> mapTerr = mapPtr->getMapTerritories();
    
    vector<Territory*> oneTerr;
    oneTerr.push_back(mapTerr[0]);
    oneTerr.push_back(mapTerr[1]);
    oneTerr.push_back(mapTerr[2]);
    oneTerr.push_back(mapTerr[3]);
    oneTerr.push_back(mapTerr[4]);

    vector<Territory*> twoTerr;
    twoTerr.push_back(mapTerr[5]);
    twoTerr.push_back(mapTerr[6]);
    twoTerr.push_back(mapTerr[7]);
    twoTerr.push_back(mapTerr[8]);
    twoTerr.push_back(mapTerr[9]);
    twoTerr.push_back(mapTerr[10]);
    twoTerr.push_back(mapTerr[11]);
    twoTerr.push_back(mapTerr[12]);
    twoTerr.push_back(mapTerr[13]);
    twoTerr.push_back(mapTerr[14]);
    twoTerr.push_back(mapTerr[15]);
    twoTerr.push_back(mapTerr[16]);
    one.setTerritories(oneTerr);
    two.setTerritories(twoTerr);
        //Infinte loop that breaks either when a transition is wrong, or a command is invalid, or The user decides to end game.
        while (true) {
            //prompt user for command
            cout << "Please enter command: ";
            cin >> command;

            //Keep Track of our next State, so we can inform the user. whilst he makes his transitions.
            State *nextState = Play->nextState(command);

            //While there exists a nextState, keep prompting user for an input.
            if (nextState) {

                //Print out CurrentState, NextState.
                cout << *Play->getCurrenState();
                cout << "Next State: " << nextState->stateStatus << "\n\n";
                //Set the nextState to be the currenState in order to update the graph, as the user Traverses the GameEngine.
            if (command == "assign_reinforcement") {
               force.reinforcementPhase(one);
               force.reinforcementPhase(two);
            }

            if (command == "issueorder") {
                order.issueOrder(one);
                order.issueOrder(two);
            
            }
            if(command == "execute_orders"){

            }
                Play->setCurrentState(nextState);
            } else {
                if (command == "end" && Play->getCurrenState()== win ) {
                    //Concluding Message once the user attempts to finish the game after winning.
                    cout << "Thanks for participating" << endl;
                    break;
                }
                //Throw Error once we receive an invalid action, and an invalid transaction.
                cerr<<"Invalid action or no valid transition.\nPlease enter Valid transition.\n";
            }
        }


    //Deallocate all pointers, and free up all used memory to ensure no memory leak occurs.

    delete Play;

}

//int main(){
////free function.
////testGameStates();
//testStartupPhase();
//}
////    //call free function.
////    testGameStates();
////}
int main(){
    //free function.
    //testStartupPhase();
    //call free function.
    //
    //
    //

    Reinforcement force;
    IssueOrder order;

    //Initialize and define an empty command string that takes input from the user
    string command = "";
    Player one;
    Player two;
    one.setId(1);
    two.setId(2);
   // vector<Player> playerList;
     MapLoader load;
        auto mapPtr = load.instantiation("../Map/MapFiles/Europe.txt");
    vector<Territory*> mapTerr = mapPtr->getMapTerritories();
    
    vector<Territory*> oneTerr;
    oneTerr.push_back(mapTerr[0]);
    oneTerr.push_back(mapTerr[1]);
    oneTerr.push_back(mapTerr[2]);
    oneTerr.push_back(mapTerr[3]);
    oneTerr.push_back(mapTerr[4]);

    vector<Territory*> twoTerr;
    twoTerr.push_back(mapTerr[5]);
    twoTerr.push_back(mapTerr[6]);
    twoTerr.push_back(mapTerr[7]);
    twoTerr.push_back(mapTerr[8]);
    twoTerr.push_back(mapTerr[9]);
    twoTerr.push_back(mapTerr[10]);
    twoTerr.push_back(mapTerr[11]);
    twoTerr.push_back(mapTerr[12]);
    twoTerr.push_back(mapTerr[13]);
    twoTerr.push_back(mapTerr[14]);
    twoTerr.push_back(mapTerr[15]);
    twoTerr.push_back(mapTerr[16]);
    one.setTerritories(oneTerr);
    two.setTerritories(twoTerr);
   
    bool gameRun = true; 
    while (gameRun) {
        
       
        std::cout << "Welcome to game loop\nEnter : print_map, assign_reinforcement, issue_order, p1win, p2win" << std::endl;
        string response;

        cin >> response;

        if (response == "print_map") {
            std::cout << "Printing Territories from the map :" << std::endl;
            mapPtr->printMapTerritories(); 
            std::cout << "===================================" << std::endl;
            std::cout << "Printing Continents from the map" << std::endl;
        }
        
        else if (response == "assign_reinforcement") {
               force.reinforcementPhase(one);
               force.reinforcementPhase(two);
        }

        else if (response == "issue_order") {
                order.issueOrder(one);
                order.issueOrder(two);
            
            }
        else if(response == "execute_orders"){

            }
        if (response == "p1win") {
            vector<Territory*> empty= two.getVecTer();
            for (Territory* terr : empty) {
            empty.pop_back();
            }
            two.setTerritories(empty);
        }
        
        if (one.getVecTer().size() == 0) {
            std::cout << "Player 2 won!!" << std::endl ; 
            gameRun = false;
        }
        if (two.getVecTer().size() == 0) {
            std::cout << "Player 1 Won!!!" << std::endl;
            gameRun = false;
        }   
    }
    //testGameStates();
}

