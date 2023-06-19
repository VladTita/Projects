#pragma once
#include "GameEngine.h"
#include "Map.h"
#include "Global.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Command : Observer
{
    public:
        Command(); //Constructor
        ~Command();
        Command(string, string);
        string getComm();
        string getEff();
        void saveEffect(string); //Save effect of a command
        int commandIndex(string);
        friend ostream & operator << (ostream&, const Command&);
        void Update();

    private:
        string effect; //Effect
        string command; //Command
        bool validCommand(string);
        const string Commands[7] = {"loadmap", "validatemap", "addplayer", "gamestart", "replay", "end", "tournament"};
};

class CommandProcessor : Observer
{
    public:
        CommandProcessor(); //Constructor
        Command* getCommand(); //Returns command
        bool validate(Command*, int); //Validate a command in the current game state (int)
        ~CommandProcessor(); //Destructor
        friend ostream & operator << (ostream&, const CommandProcessor&);
        void Update();
    private:
        virtual Command* readCommand(); //Read a command from console input
        void saveCommand(Command*); //Save command to commandList
    protected:
        vector<Command*> commandList; //vector of commandList

};

class FileLineReader
{
    public:
        FileLineReader(string);
        string readLineFromFile();
    private:
        ifstream file;
        string fName;

};

class FileCommandProcessor
{
    public:
        FileCommandProcessor(string);
        ~FileCommandProcessor();
        Command* readCommandFromFile();
    private:
        FileLineReader* flr;
};

class FileCommandProcessorAdapter: virtual public CommandProcessor
{
    public:
        FileCommandProcessorAdapter(string);
        ~FileCommandProcessorAdapter();
    private:
        virtual Command* readCommand();
        FileCommandProcessor* fcp;
};

