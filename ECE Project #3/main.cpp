#include <iostream>
#include <list>
#include <vector>
#include "Project3a.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;


int main(void) {
    string inputFileName = "input3.txt";    
    ifstream inFS;
    string currAccount, followed, follower;
    vector <string> accountList;
    bool inList;
    int rootInt, rootDegreeCent;
    vector <int> returnRootVals(2);


    inFS.open(inputFileName);

    if (!inFS.is_open()) {
        cout << "could not open input file" << endl;
    }

    // This section finds all unique accounts and adds them to a vector, the size is the num users in the social network
    while (!inFS.eof() && inFS.good()) {
        inFS >> currAccount;
        transform(currAccount.begin(), currAccount.end(), currAccount.begin(), ::tolower);
        inList = false;

        for (int i = 0; i < accountList.size(); i++) {
            if (currAccount == accountList.at(i)) {
                inList = true;
            }
        }

        if (inList == false) {
            accountList.push_back(currAccount);
        }
    }
    //

    // This makes a pair to match the vertex int with the unique account name for the graph
    vector<pair <int, string>> intAccountPair;
    pair <int, string> currPair;
    for (int i = 0; i < accountList.size(); i++) {
        currPair = make_pair(i, accountList.at(i));
        intAccountPair.push_back(currPair);
    }
    //

    int graphSize = intAccountPair.size();
    vector<vector<int>> adj(graphSize);
    vector<vector<int>> adjSearch(graphSize);

    inFS.clear(); // returns inFS to the top of the file
    inFS.seekg(0);

    // This section creates the edges and followings of the accounts using the ints from the accountpairs
    while (inFS >> followed >> follower) {

        transform(followed.begin(), followed.end(), followed.begin(), ::tolower);
        transform(follower.begin(), follower.end(), follower.begin(), ::tolower);

        for (int i = 0; i < intAccountPair.size(); i++) {
            if (follower == intAccountPair.at(i).second) {
                for (int j = 0; j < intAccountPair.size(); j++) {
                    if (followed == intAccountPair.at(j).second) {
                        addEdge(adj, i, j);
                        addEdgeForSearch(adjSearch, i, j);
                        break;
                    }
                }
            }
        }
    }


    returnRootVals = findRoot(adj, intAccountPair);
    rootInt = returnRootVals.at(0);
    rootDegreeCent = returnRootVals.at(1);

    cout << "The root user is " << intAccountPair.at(rootInt).second << ", with in-degree centrality of " << rootDegreeCent << "." << endl;
    cout << "There are " << intAccountPair.size() << " users in the social network." << endl;

    PrintFollowers(rootInt, adjSearch, intAccountPair);

    return 0;
}