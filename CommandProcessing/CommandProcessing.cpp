////CommandProceesing implementation
// Created by Uyi oronsaye on 2023-10-21.
//

#include "CommandProcessing.h"

Command::Command() {
    this->commandPassed="";
    this->commandEffect="";

}
Command::Command(std::string commandPassed) : commandPassed(commandPassed) {
    // Initialize other members if necessary
}

Command::Command(validCommands vCom, string concat, int maps, int players, int games, int turns)
        : commandPassed(""), commandEffect(""), toConcat(concat), commandIndex(0),
          noOfMaps(maps), noOfPlayers(players), noOfGames(games), maxTurns(turns) {
    // Handle the switch case statement as before
}
Command::Command(validCommands vCom, string concat) {
    //using switch case statement to go through validCommands, and assigning commands an index
    switch (vCom) {
        case validCommands::tournament:
            commandPassed = "tournament";
            commandIndex =0;


            break;

        case validCommands::loadmap:
            commandPassed = "loadmap"; //additional to concatenate map file name
            this->toConcat= concat;
            commandIndex =1;

            break;
        case validCommands::validatemap:
            commandPassed = "validatemap";
            commandIndex =2;

            break;
        case validCommands::addplayer:
            commandPassed = "addplayer";
            this->toConcat= concat;//additional to concatenate playerName
            commandIndex =3;

            break;
        case validCommands::gamestart:
            commandPassed = "gamestart";
            commandIndex =4;

            break;
        case validCommands::replay:
            commandPassed = "replay";
            commandIndex =5;

            break;
        case validCommands::quit:
            commandPassed = "quit";
            commandIndex =6;

            break;
        case validCommands::gameend:
            commandPassed = "gameend";
            commandIndex = 7;

            break;
    }

}

Command::Command(const Command &command_cpy) : commandPassed(command_cpy.commandPassed),commandEffect(command_cpy.commandEffect),toConcat(command_cpy.toConcat),commandIndex(command_cpy.commandIndex){ }

Command& Command::operator= (const Command& command_cpy){
    this->commandPassed=command_cpy.commandPassed;
    this->commandEffect=command_cpy.commandEffect;
    this->toConcat=command_cpy.toConcat;
    this->commandIndex=command_cpy.commandIndex;

    return *this;
}
Command::Command(string commandP, string commandE) {

    this->commandPassed=commandP;
    this->commandEffect=commandE;


}
Command::~Command(){

}
void Command::saveEffect(Command * userCommand) {
    LogObserver *observer = new LogObserver(userCommand);
    Notify(this);
    delete observer;
    observer = NULL;
//using a switch statement, to saveEffect passed by user
    switch (userCommand->commandIndex) {
        case 0:
            userCommand->commandEffect = "Tournament has commenced";//would need to add somethings else here
            break;
        case 1:
            userCommand->commandEffect=userCommand->toConcat + " Map loaded successfully";
            break;
        case 2:
            userCommand->commandEffect= "Map validated successfully";
            break;
        case 3:
            userCommand->commandEffect= userCommand->toConcat + " Player added successfully ";
            break;
        case 4:
            userCommand->commandEffect= "The Game has begun";
            break;
        case 5:
            userCommand->commandEffect= "The Game is restarting for replay";
        case 6:
            userCommand->commandEffect= "Quitting the Game";
            break;
        case 7:
            userCommand->commandEffect = "Game has ended";
            break;
    }

}

//stringToLog implementation from ILoggable
string Command::stringToLog()
{
    return "Command issued: " + getCommandPassed();
}

//Overloading the ostream output operator

ostream& operator<<(ostream &out, const Command &Command_cpy ){

    return out<< "Command: "<< Command_cpy.commandPassed << Command_cpy.toConcat << "\nCommand Effect:"<<Command_cpy.commandEffect;

}
string Command::getCommandPassed() {
    return this->commandPassed;
}
string Command::getCommandEffect() {
    return commandEffect;
}
void Command::setCommandPassed() {
    this->commandPassed = this->commandPassed +"<" + this->toConcat+">";
}


/*
 *
 * COMMAND PROCESSOR
 *
 *
 *
 */
CommandProcessor::CommandProcessor() {

}
//copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor& CommandProcessor_cpy) {
    for (const auto& cmd : CommandProcessor_cpy.commands) {
        commands.push_back(cmd);
    }

    for (const auto& validCmd : CommandProcessor_cpy.validCommands) {
        validCommands.push_back(validCmd);
    }
}
//Deep Assignment Operator
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& CommandProcessor_cpy) {
    if (this == &CommandProcessor_cpy) {
        return *this; // Return *this to handle self-assignment
    }

    // Clear the existing commands and validCommands
    for (Command* cmd : commands) {
        delete cmd;
    }
    for (Command* cmd : validCommands) {
        delete cmd;
    }
    commands.clear();
    validCommands.clear();

    // Deep copy the commands and validCommands from 'CommandProcessor_cpy'
    for (Command* cmd : CommandProcessor_cpy.commands) {
        commands.push_back(new Command(*cmd));
    }
    for (Command* cmd : CommandProcessor_cpy.validCommands) {
        validCommands.push_back(new Command(*cmd));
    }

    exitProgram = CommandProcessor_cpy.exitProgram;
    validCommVec = CommandProcessor_cpy.validCommVec;

    return *this; // Return *this for chaining assignments
}

CommandProcessor::~CommandProcessor() {
    // Delete dynamically allocated Command objects in the 'commands' vector to prevent memory leak
    for (Command* cmd : commands) {
        delete cmd;
    }

    // Delete dynamically allocated Command objects in the 'validCommands' vector to prevent memory leak
    for (Command* cmd : validCommands) {
        delete cmd;
    }
}

int CommandProcessor::commandStrTocommandIndex(string commandStr) {
    int index{};
    for(int i=0; i< validCommVec.size();i++){
        if (validCommVec[i]== commandStr){
            index=i;
            return index;
        }
    }
    return -1;
}

Command* CommandProcessor::readCommand() {
    string commandP{}; //Command passed
    string toConcat{}; //Command Effect
    int noOfMaps,noOfGames,noOfPlayers,maxTurns;


    cout << "Please Enter a command\n";
    cin >> commandP;

    if(commandP=="tournament"){
        //Add more things here
        cout<<"How many maps do you wish to load? please choose between 1-5 ";
        cin>> noOfMaps;

        cout<<"How many Players would you wish to add? Please choose between 2-4 ";
        cin>>noOfPlayers;

        cout<<"How many Games do you want to be simulated? Please choose between 1-5 ";
        cin>>noOfGames;

        cout<<"What is the maximum number of turns allowed? Please choose between 10-50 ";
        cin>>maxTurns;


        //potentially use the existing commands to run game, and change states internally.

        return new Command(Command::validCommands::tournament, toConcat, noOfMaps, noOfPlayers, noOfGames, maxTurns);
    } else if (commandP == "loadmap") {
        cout << "Which Map do you want to load?";
        cin >> toConcat;
        cout << endl;
    } else if (commandP == "addplayer") {
        cout << "Which player do you want to add to the game?";
        cin >> toConcat;
        cout << endl;
    }
    else if (commandP == "loadmap") {
        cout << "Which Map do you want to load?";
        cin >> toConcat;
        cout << endl;

    } else if (commandP == "addplayer") {
        cout << "Which player do you want to add to the game?";
        cin>>toConcat;
        cout<<endl;

    }
    //Switch case statement for other commands 
    switch (commandStrTocommandIndex(commandP)) {
        case 0:
            return  new Command(Command::validCommands::tournament,toConcat);
        case 1:
            return new Command(Command::validCommands::loadmap,toConcat);
        case 2:
            return new Command(Command::validCommands::validatemap,toConcat);
        case 3:
            return new Command(Command::validCommands::addplayer,toConcat);
        case 4:
            return new Command(Command::validCommands::gamestart,toConcat);
        case 5:
            return new Command(Command::validCommands::replay,toConcat);
        case 6:
            return new Command(Command::validCommands::quit,toConcat);
        case 7:
            return new Command(Command::validCommands::gameend,toConcat);
        default:
            return new Command(commandP);

    }

}
void CommandProcessor::startTournament(Command * command, GameEngine* tournamentGame) {
    //get user inputs for tournament mode.
    int noOfMaps = command->getNoOfMaps();
    int noOfPlayers = command->getNoOfPlayers();
    int noOfGames = command->getNoOfGames();
    int maxTurns = command->getMaxTurns();

    string mapName="";
    string playerName="";

    // Output tournament information to log
    cout << "Tournament mode: M: " << noOfMaps << " maps, P: " << noOfPlayers << " players, G: " << noOfGames << " games, D: " << maxTurns << endl;
    cout<<"what maps do you wish to play on?:\n";

    for(int i=1; i<=noOfMaps;i++){

        cout<<"map "<< i<<endl;
        cin>> mapName;

        maps.push_back(mapName);

    }
    cout<<"what players do you want to add?:\n";
    for(int i=1; i<=noOfPlayers;i++){

        cout<<"Player "<< i<<endl;
        cin>> playerName;

        players.push_back(playerName);

    }

    tournamentGame->tournamentExecution(maps,players,noOfGames,maxTurns);
    // TODO: Implement the tournament logic here, play G games on each of the M different maps between the chosen computer player strategies.



    // Output tournament results to log

}
bool CommandProcessor::validate(Command* command, GameEngine* gameloop) {


    // Checks if the command can be called in the current state
    if (gameloop->checkCurrentState(command->getCommandPassed())) {

        // If the commands are the following then we add the toAdd string to get an output such as loadmap <map name>
        if (command->getCommandPassed() == "tournament") {
            // Start the tournament
            startTournament(command,gameloop);
            return true;
        }
        else if (command->getCommandPassed() == "loadmap") {
            command->setCommandPassed();
        }
        else if (command->getCommandPassed() == "addplayer") {
            command->setCommandPassed();
        }
        else if (command->getCommandPassed() == "quit") {
            cout << "Quitting the game.";

            exitProgram = true;
        }
        // Save the effect if the commands are valid
        command->saveEffect(command);
        return true;
    }

    cout << "Invalid command.\n";

    return false;
}
void CommandProcessor::saveCommand( Command* command) {
    commands.push_back(command);
}
void CommandProcessor::saveValidCommands(Command* command) {
    LogObserver *observer = new LogObserver(this);
    Notify(this);
    delete observer;
    observer = NULL;
    validCommands.push_back(command);
}
vector<Command*> CommandProcessor::getCommandsList() {
    return this->commands;
}

// Gets the vector of the valid command list
vector<Command*> CommandProcessor::getValidcommands()  {
    return this->validCommands;
}

void CommandProcessor::getCommand(GameEngine* gameState, CommandProcessor* command) {
    Command *userCommand = command->readCommand();
    
    if(validate(userCommand,gameState)){
        saveValidCommands(userCommand);
    }
    saveCommand(userCommand);
    cout << "Command has been saved\n";
}

//Overloading the ostream output operator
ostream& operator<< (ostream& out, const vector<Command*>& command_cpy) {

    for(const auto& command : command_cpy){
        out<< *command<<endl;
    }

    return out;
}

bool CommandProcessor::getExitProgramstatus() {
    return exitProgram;
}
void CommandProcessor::setcmdPause(bool isPaused) {
    cmdProPause = isPaused;
}

// Gets the bool cmdProPause
bool CommandProcessor::getcmdPausestatus() {
    return cmdProPause;
}

//stringToLog implementation from ILoggable
string CommandProcessor::stringToLog()
{
    cout<<"\n\n\nCPROCESSOR STRINGTOLOG!!!\n\n\n"<<endl;
    return "Inserted previous command into the list.";
}

/*
 *
 * FILELINEREADER IMPLEMENTATION
 *
 *
 */
//default
FileLineReader::FileLineReader() {}
//copy
FileLineReader::FileLineReader(const FileLineReader& fileReader_cpy) {
    this->contentOfFile = fileReader_cpy.contentOfFile;
}
//assignment
FileLineReader& FileLineReader::operator=(const FileLineReader& fileReader_cpy) {
    this->contentOfFile = fileReader_cpy.contentOfFile;

    return *this;
}
//Function for reading from a file
void FileLineReader::readFromFile(string fileName) {
    //create a vector that holds the lines of the text file
    vector<string> lineContent;
    fileName = fileName + ".txt";//concatenate the filename with the .txt text file extension.

    cout<<fileName<<endl;

    ifstream commandfile(fileName); //open commandFile, and pass the filename in the ifstream operator to enable reading from file.

    if(commandfile.is_open()){
        string line;

        //while the file is open, and a line exist keep looping, and store the content of the file in our vector template
        while(getline(commandfile, line)){
            lineContent.push_back(line);
        }

        //close file
        commandfile.close();

        //copy the content of the file into our contentoffile attribute.
        for (int i = 0; i < lineContent.size(); i++) {
            contentOfFile.push_back(lineContent[i]);
        }

    }else{
        //error handling, incase the file could not be read.
        cerr<<"File does not exist in current directory, please check for spelling error."<<endl;
    }


}
vector<string> FileLineReader::getContentOfFile(){
    return contentOfFile;

}
/*
 *
 * FILECOMMANDPROCESSORADAPTER IMPLEMENTATION
 *
 *
 */
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader*  fileReader):fileReader(fileReader) {
    const auto& content = fileReader->getContentOfFile();
    for (const auto& command : content) {
        commands.push_back(command);
    }

}
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& FileCommandProcessorAdapter_cpy): CommandProcessor(FileCommandProcessorAdapter_cpy), fileReader(new FileLineReader(*(FileCommandProcessorAdapter_cpy.fileReader))), indexCurrentLine(FileCommandProcessorAdapter_cpy.indexCurrentLine), commands(FileCommandProcessorAdapter_cpy.commands) {
}
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator= (const FileCommandProcessorAdapter& FileCommandProcessorAdapter_cpy) {
    if (this == &FileCommandProcessorAdapter_cpy) {
        return *this; //Return *this Handle self-assignment
    }

    // Call base class assignment operator
    CommandProcessor::operator=(FileCommandProcessorAdapter_cpy);

    // Delete the current fileReader and create a new one to prevent unused attribute
    delete fileReader;
    //crete new fileReader.
    fileReader = new FileLineReader(*(FileCommandProcessorAdapter_cpy.fileReader));

    // Copy FileCommandProcessorAdapter_cpy members
    indexCurrentLine = FileCommandProcessorAdapter_cpy.indexCurrentLine;
    commands = FileCommandProcessorAdapter_cpy.commands;

    return *this;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete fileReader; // Clean up the dynamically allocated fileReader
}

FileLineReader* FileCommandProcessorAdapter::getFileLineReader() {
    return fileReader;
}
Command* FileCommandProcessorAdapter::readCommand() {
    string toConcat,firstWord,secondWord ="";
    string delimiter =" ";

    indexCurrentLine++;


    size_t posdel{};

    size_t delimiterPosition = commands[indexCurrentLine].find(delimiter);

    if (delimiterPosition != string::npos) {
        // Separate every line at the delimiter " " into two words
        string firstWord = commands[indexCurrentLine].substr(0, delimiterPosition);
        string secondWord = commands[indexCurrentLine].substr(delimiterPosition + 1);

        if (firstWord == "loadmap") {
            return new Command(Command::validCommands::loadmap, secondWord);
        }
        else if (firstWord == "addplayer") {
            return new Command(Command::validCommands::addplayer, secondWord);
        }
    }
    //if we don't encounter a delimiter "white space" we read line normally
    else if(commands[indexCurrentLine]== "validatemap"){
        return new Command(Command::validCommands::validatemap, toConcat);
    }
    else if(commands[indexCurrentLine]== "gamestart"){
        return new Command(Command::validCommands::gamestart, toConcat);
    }
    else if(commands[indexCurrentLine]== "replay"){
        return new Command(Command::validCommands::replay, toConcat);
    }
    else if(commands[indexCurrentLine]== "quit"){
        return new Command(Command::validCommands::quit, toConcat);
    }
    else if(commands[indexCurrentLine]=="gameend"){
        return new Command(Command::validCommands::gameend,toConcat);
    }
    else{
        return  new Command(commands[indexCurrentLine]);
    }

}


