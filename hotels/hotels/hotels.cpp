// hotels.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std; 

int main()
{

    vector<vector<int>> hotels;

    vector<int> a = {1, 2};
    vector<int> b = {1};
    vector<int> c = {1};
    vector<int> d = {2};
    vector<int> e = {3};
    vector<int> f = {1, 2};
    vector<int> g = {1};
    vector<int> h = {1};
    vector<int> k = {4};
    vector<int> l = {3};

    hotels.push_back(a);
    hotels.push_back(b);
    hotels.push_back(c);
    hotels.push_back(d);
    hotels.push_back(e);
    hotels.push_back(f);
    hotels.push_back(g);
    hotels.push_back(h);
    hotels.push_back(k);
    hotels.push_back(l);

    int start = 0, end = 0; 
    int goal = 100;
    int stay = 0; 

    while (start < hotels.size()) {
        unordered_set<int> set;
        for (int i = start; i < hotels.size(); i++) {
            for (int j = 0; j < hotels[i].size(); j++) {
                set.insert(hotels[i][j]);
                cout << "curr: " << i << "-" << j << endl;
            }
            if (set.size() == 4) {
                end = i;
                cout << "end: " << end << "start: " << start << endl;
                cout << "old: " << goal << "new: " << (end - (start + end) / 2) << endl;
                if ((end - (start + end) / 2) < goal) {
                    goal = (end - (start + end) / 2);
                    stay = ((start + end) / 2); 
                }
                cout << "stay: " << stay << endl;
            }
        }

        start++;

    }

    cout << stay << endl;  
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"
