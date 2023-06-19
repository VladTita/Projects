#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Map.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

//Command Class =================================================
Command::Command(string c, string e){
    subject->Attach(this);
    if(!validCommand(c)){
        if (cmdDisplay)
            cout << "Invalid command: " << c << endl;
        c = "INVALID";
    }
    this->command = c;
    saveEffect(e);
}

void Command::Update(){
    myfile << "COMMAND: " << this->getComm() << "\n";
}

Command::Command(){
    subject->Attach(this);
}

Command::~Command(){
    subject->Detach(this);
}

string Command::getComm(){
    return this->command;
}
string Command::getEff(){
    return this->effect;
}

void Command::saveEffect(string e){
    if( e == "err"){
        effect = "ERROR";
        return;
    }
    switch (commandIndex(command)){
        case 0:
            effect = e;
            break;
        case 1:
            effect = "Validate map";
            break;
        case 2:
            effect = e;
            break;
        case 3:
            effect = "Start game";
            break;
        case 4:
            effect = "Replay game";
            break;
        case 5:
            effect = "Quit game";
        case 6:
            effect = e;
    }
    subject->Notify();
}

bool Command::validCommand(string c){
    if(commandIndex(c) >= 0) {return true;}
    return false;
}

int Command::commandIndex(string c){
    int end = sizeof(Commands)/sizeof(Commands[0]);
    int i = 0;
    while(i < end){
        if(Commands[i] == c)
            return i;
        i++;
    }
    return -1;
}

ostream & operator << (ostream &out, const Command &c){
    out << "\tCommand: " << c.command << "\n\tEffect: " << c.effect;
    return out << endl;
}

//CommandProcessor Class =======================================

CommandProcessor::CommandProcessor(){
    subject->Attach(this);
}

void CommandProcessor::Update(){
    myfile << "COMMAND PROCESSOR:\n";
    for (Command* command : this->commandList)
    {
        myfile << "\t" << command->getComm() << "\n";
    }
    myfile << "\n";
}

Command* CommandProcessor::readCommand(){
    cout << "Please input command:\n";
    string input, commandInput, effectInput;
    string delim = " ";

    getline(cin, input);

    commandInput = input.substr(0, input.find(delim));
    effectInput = input.substr(input.find(delim)+1);

    Command * c = new Command(commandInput, effectInput);
    if (cmdDisplay)
        cout << "Read command\n";
    return c;
}

Command* CommandProcessor::getCommand(){
    Command * c = readCommand();
    saveCommand(c);
    if (cmdDisplay)
        cout << "Got command:\n" << *c << "\n";
    return c;
}

void CommandProcessor::saveCommand(Command *c){
    commandList.push_back(c);
    if (cmdDisplay)
        cout << "Saved command\n";
    subject->Notify();
}

bool CommandProcessor::validate(Command *c, int state){
    string err = "err";
    bool valid = false;

    int newState = -1;
    int comm = c->commandIndex(c->getComm());
    switch(comm){
        case 0:
            if (state <= 1) {valid = true;}
            else{ c->saveEffect(err); }
            break;

        case 1:
            if (state == 1) {valid = true;}
            else{ c->saveEffect(err); }
            break;

        case 2:
            if (state == 2 || state == 3) {valid = true;}
            else{ c->saveEffect(err); }
            break;

        case 3:
            if (state == 3) {valid = true;}
            else{ c->saveEffect(err); }
            break;

        case 4:
            if (state == 7) {valid = true;}
            else{ c->saveEffect(err); }
            break;

        case 5:
            if (state == 7) {valid = true;}
            else{ c->saveEffect(err); }
            break;

        case 6:
            if (state == 0) {valid = true;}
            else{ c->saveEffect(err); }
            break;

        default:
            c->saveEffect(err);
            break;
    }

    if (cmdDisplay)
        cout << *c;
    return valid;
}

ostream & operator << (ostream &out, const CommandProcessor &c){
    out << "Commands List:\n";
    for (Command* command : c.commandList) {
        out << *command << "\n";
    }
    return out << endl;
}


CommandProcessor::~CommandProcessor(){
    subject->Detach(this);
    for(Command *c: commandList){
        delete(c);
        c = NULL;
    }
}

//FileLineReader Class ==============================================

FileLineReader::FileLineReader(string f){
    fName = f;
    file = ifstream (fName);
}
string FileLineReader::readLineFromFile(){
    string in;
    getline(file, in);
    return in;
}

//FileCommandProcessor Class ==============================================
FileCommandProcessor::FileCommandProcessor(string f){
    this->flr = new FileLineReader(f);
}

FileCommandProcessor::~FileCommandProcessor(){
    delete flr;
    flr = NULL;
}

Command* FileCommandProcessor::readCommandFromFile(){
    string commandInput, effectInput;
    string line = flr->readLineFromFile();
    string delim = " ";

    commandInput = line.substr(0, line.find(delim));
    effectInput = line.substr(line.find(delim)+1);

    Command * c = new Command(commandInput, effectInput);
    if (cmdDisplay)
        cout << "Read from file\n";
    return c;
}

//FileCommandProcessorAdapter Class =======================================
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string f){
    this->fcp = new FileCommandProcessor(f);
}

Command* FileCommandProcessorAdapter::readCommand(){
    if (cmdDisplay)
        cout << "Adapting CommandProcessor to FileCommandProcessor...\n";
    fcp->readCommandFromFile();
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    delete fcp;
    fcp = NULL;
}