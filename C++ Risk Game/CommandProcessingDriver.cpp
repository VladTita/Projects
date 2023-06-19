#include "CommandProcessing.h"
#include <string>
#include <iostream>

void testCommandProcessor(){
    CommandProcessor *cp;
    string in;

    cout << "Please indicate your preferred method of command input (console/file): ";
    getline(cin, in);
    while (in != "console" && in != "file") {
        cout << "Invalid input method\n";
        cout << "Please indicate your preferred method of command input (console/file): ";
        getline(cin, in);
    }

    if (in == "console"){
        cout << "Initializing CommandProcessor...\n";
        cp = new CommandProcessor();
    }
    else if (in == "file") {
        cout << "Please indicate the file path: ";
        getline(cin, in);
        cout << "Initializing FileCommandProcessor...\n";
        cp = new FileCommandProcessorAdapter(in);
    }
    // 1
    Command * c = cp->getCommand();
    cp->getCommand();
    cp->getCommand();

    cout << "\nValidating initial command in state 0 (start): \n";
    cp->validate(c, 0);

    cout << "\nValidating initial command in state 2 (map validated): \n";
    cp->validate(c, 2);


    cout << "\nPrinting full commands list \n";
    cout << *cp;
}
