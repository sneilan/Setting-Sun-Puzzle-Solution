#include "includes.h"
#include "Test.h"
#include <fstream>
#include <stdio.h>
#include <string>


using namespace std;


int main() {
    if (!test()) {
        cout << "NOOOOOOO!\n";
        exit(0);
    } else {
        cout << "testing completed.\n";
    }

    State * initialState = createInitialState();
    StateMiner stateMiner;

    ofstream output;
    output.open("output.txt");

    // retrieve initial list of states
    vector<State *> stateList = stateMiner.getNewStates(initialState); // stateList contains a list of the current states we haven't checked yet

    // do a depth first search to find the solution
    while (solutionNotFound(stateList)) {
        int count = 0;
        count = stateList.size();
        cout << "State list is now of size " << count << endl;
        cout << "State miner is now at " << stateMiner.numStates() << " states\n";
        for (int i = 0; i < count; i++) {
            // for every state, get a list of new states from the state miner
            vector<State *> newStates = stateMiner.getNewStates(stateList[i]);
            //cout << "State miner returned " << newStates.size() << " states\n";
            if (newStates.size() > 6) {
                cout << "returned more than 6 states\n";
                exit(1);
            }

            // add all the new states to the end of the vector
            for (int j = 0; j < newStates.size(); j++) {
                stateList.push_back(newStates[j]);
		char buffer [50];
		sprintf(buffer, "%lu ->  %lu;\n", stateList[i]->getHash(), newStates[j]->getHash());
		output << buffer;
		output.flush();
            }
        }
        // pop off old states from the list
        stateList.erase(stateList.begin(), stateList.begin()+count);
    }

    output.close();

    cout << "meow\n";

    return 0;
}

