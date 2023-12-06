#include <iostream>
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;

void addEdge(vector<vector<int>>& adj, int follower, int followed) {
    adj[follower].push_back(followed);
}

void addEdgeForSearch(vector<vector<int>>& adj, int follower, int followed) { // creates an adjecency list the other way easier to search backward looking at followers of a given account
    adj[followed].push_back(follower);
}

vector<int> findRoot(vector<vector<int>> adj, vector<pair <int, string>> acctPair) {
    vector <int> countFollowers(acctPair.size());
    int currAccountNum;
    int highestAcctFollow = 0; // highest in degree centrality
    int currRootNode = 0;
    vector <int> returnVals(2);

    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj.at(i).size(); j++) {
            currAccountNum = adj.at(i).at(j);
            countFollowers.at(currAccountNum) += 1;
        }
    }

    for (int i = 0; i < countFollowers.size(); i++) {

        if (countFollowers.at(i) >= highestAcctFollow) {

            if (countFollowers.at(i) == highestAcctFollow) {
                if (acctPair.at(i).second < acctPair.at(currRootNode).second) {
                    highestAcctFollow = countFollowers.at(i);
                    currRootNode = i;
                }
            }

            else {
                highestAcctFollow = countFollowers.at(i);
                currRootNode = i;
            }
        }
    }

    returnVals.at(0) = currRootNode;
    returnVals.at(1) = highestAcctFollow;

    return returnVals;
}


void PrintFollowers(int root, vector<vector<int>> adj, vector<pair<int, string>> acctPair) {
    vector <string> depth1Accounts, depth2Accounts;
    int depth1Int;

    cout << acctPair.at(root).second << " (0)" << endl;

    for (int i = 0; i < adj.at(root).size(); i++) { // add all depth 1 nodes from the root
        depth1Accounts.push_back(acctPair[adj.at(root).at(i)].second);
        transform(depth1Accounts.at(i).begin(), depth1Accounts.at(i).end(), depth1Accounts.at(i).begin(), ::tolower);
    }

    sort(depth1Accounts.begin(), depth1Accounts.end()); // sort alphabetically

    for (int i = 0; i < depth1Accounts.size(); i++) { // prints out all depth 1 and 2 data in alphabetical order
        cout << depth1Accounts.at(i) << " (1)" << endl; // prints the first alphabetical depth 1 account

        for (int j = 0; j < acctPair.size(); j++) { // gets the corresponding int of the depth 1 node for the following for loop
            if (depth1Accounts.at(i) == acctPair.at(j).second) {
                depth1Int = acctPair.at(j).first;
            }
        }

        depth2Accounts.clear();

        for (int j = 0; j < adj.at(depth1Int).size(); j++) { // fills the depth2Accounts with the accounts that follow depth1
            depth2Accounts.push_back(acctPair[adj.at(depth1Int).at(j)].second);
            transform(depth2Accounts.at(j).begin(), depth2Accounts.at(j).end(), depth2Accounts.at(j).begin(), ::tolower);
        }


        sort(depth2Accounts.begin(), depth2Accounts.end()); // alphabetical order

        for (int j = 0; j < depth2Accounts.size(); j++) { // prints the depth 2 accounts of depth 1 in order
            cout << depth2Accounts.at(j) << " (2)" << endl;
        }
    }

}
