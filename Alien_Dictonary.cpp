#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to find the lexicographically smallest order of characters in an alien language.
string getAlienLanguage(vector<string> &dictionary, int k) {
    vector<char> adj[k];  // Create an array of vectors to represent the graph.

    // Convert the given dictionary into a directed graph.
    for (int i = 0; i < dictionary.size() - 1; i++) {
        string s1 = dictionary[i];
        string s2 = dictionary[i + 1];

        int minSize = min(s1.size(), s2.size());
        int j = 0;

        while (j < minSize) {
            if (s1[j] != s2[j]) {
                adj[s1[j] - 'a'].push_back(s2[j] - 'a');
                break;
            }
            j++;
        }
    }

    // Apply Kahn's algorithm to find the lexicographically smallest order.
    vector<int> indegree(k, 0);

    for (int i = 0; i < k; i++) {
        for (auto j : adj[i]) {
            indegree[j]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < k; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    string ans = "";

    while (!q.empty()) {
        int curr = q.front();
        ans += char('a' + curr);
        q.pop();

        for (auto neigh : adj[curr]) {
            indegree[neigh]--;

            if (indegree[neigh] == 0) {
                q.push(neigh);
            }
        }
    }

    // Check if the answer has all characters. If yes, it's a valid order; otherwise, no valid order found.
    if (ans.size() == k) {
        return ans;
    }
    return "";
}

int main() {
    int k;
    vector<string> dictionary;

    // Read the number of characters in the alien language.
    cout << "Enter the number of characters (k): ";
    cin >> k;

    cin.ignore(); // Clear the newline character from the input buffer.

    // Read the words in the alien language dictionary.
    cout << "Enter the words in the alien language dictionary:" << endl;
    for (int i = 0; i < k; i++) {
        string word;
        getline(cin, word);
        dictionary.push_back(word);
    }

    // Call the getAlienLanguage function to find the lexicographically smallest order.
    string alienLanguage = getAlienLanguage(dictionary, k);

    if (!alienLanguage.empty()) {
        cout << "The lexicographically smallest order of characters in the alien language is: " << alienLanguage << endl;
    } else {
        cout << "No valid order found. The input might not represent a valid alien language." << endl;
    }

    return 0;
}
