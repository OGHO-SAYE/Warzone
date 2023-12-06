#include "CommandProcessing.h"
#include <iostream>
#include <istream>

using namespace std;

void testCommandProcessor() {

    //create an instance of the commandProcessor, so we can proccess and prompt user based on their commands.
    CommandProcessor *cprocessor = new CommandProcessor();

    //Create an instance of the GameEngine.
    GameEngine *game = new GameEngine();

    //create instances of the States valid in our game phases
    State *start = new State("start");
    State *map_loaded = new State("map_loaded");
    State *map_validated = new State("map_validated");
    State *players_added = new State("players_added");
    State *assign_reinforcement = new State("assign_reinforcement");
    State *win = new State("win");
    State *end_game = new State("end_game");
    State *tournament = new State("tournament_started");

    //create the nodes needed for the Gamestates
    game->addNode(start);
    game->addNode(map_loaded);
    game->addNode(map_validated);
    game->addNode(players_added);
    game->addNode(assign_reinforcement);
    game->addNode(win);
    game->addNode(end_game);
    game->addNode(tournament);


    //Add valid Transitions to our existing gameEngine.
    game->addTransition(start, tournament,"tournament");
    game->addTransition(tournament,end_game,"quit");
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

//While loop to ensure that the user enters the correct input
    while (true) {
        cout<< "which method would you like to accept commands from, via the console or via reading from a file? please type \"console\" or \"file\"\n";
        cin >> userResponse;


        if (userResponse == "console") {
            cout << "***Now accepting command from console***" << endl;

            while (!(cprocessor->getExitProgramstatus())) {
                cprocessor->getCommand(game, cprocessor);
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
            delete cprocessor;
            break;
        } else if (userResponse == "file") {
            cout << "***Now accepting command from file***\n Please enter the file name you wish to open\n";

            cin >> fileName;
            cout << endl;

            FileLineReader *fileReader = new FileLineReader();
            fileReader->readFromFile(fileName);

            FileCommandProcessorAdapter *commandFile = new FileCommandProcessorAdapter(fileReader);

            while (!(cprocessor->getExitProgramstatus())) {
                cprocessor->getCommand(game, commandFile);
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

            break;
        }
        else{
            cout << "Invalid input. Please enter either \"console\" or \"file\".\n";
        }
    }

    game->end();
}

int main(){

    testCommandProcessor();

    return 0;
}




