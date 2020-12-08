#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>
#include <queue>
#include <math.h.>
#include <algorithm>
#include "Game.h"
using namespace std;


//comment out algorithm 2 for compileable code




//algorithm 1
vector<Game> alg1(unordered_map<string, Game*> games, Param &toggles) {

    priority_queue<Game, vector<Game>> filtered;
    set<string> inFilter;
    for (auto const& cycle : games) {
        if (toggles.tags.size() == 0) {
            filtered.push(games[cycle.first]);
            inFilter.insert(games[cycle.first]->name);

        }
        else {
            int determin = 0;
            for (auto const& looper : toggles.tags) {

                if (games[cycle.first]->tags.find(looper) != games[cycle.first]->tags.end() && games[cycle.first]->price <= toggles.price.second && games[cycle.first]->price >= toggles.price.first
                    && games[cycle.first]->dateNum < toggles.date.second && games[cycle.first]->dateNum > toggles.date.first) {
                    determin++;
                }
                if (determin == (int(toggles.tags.size()) / 2) + 1) {
                    filtered.push(games[cycle.first]);
                    inFilter.insert(games[cycle.first]->name);
                    break;
                }
            }
        }


    }
    if (filtered.size() == 0) {
        Game na = new Game("No Games Match", " ", "N/A", 0.0, 0.0, {}, {}, 0, 0.0);
        filtered.push(na);
    }
    vector<Game> recommendations;

    while (recommendations.size() < 5 && filtered.size() > 0) {

        recommendations.push_back(filtered.top());
        filtered.pop();
    }
    return recommendations;
}








//algorithm 2

vector<Game> alg2(unordered_map<string, Game*> games, vector<Game> given, bool flag) {
    priority_queue<Game, vector<Game>, simI> mHeap;
    map<double, vector<Game>> avlTree;
    set<string> five;
    Game* averg = new Game();
    for (int i = 0; i < given.size(); i++) {
        for (auto const& looper : given.at(i).genres) {
            averg->genres.insert(looper);
        }
        for (auto const& looper : given.at(i).tags) {
            averg->tags.insert(looper);
        }
        five.insert(given.at(i).name);
        averg->price += given.at(i).price;
        averg->dateNum += given.at(i).dateNum;
    }
    averg->price = averg->price / given.size();
    averg->dateNum = averg->dateNum / given.size();

    int score = 0;
    int total = averg->tags.size() + averg->genres.size() + 4;

    for (auto const& cycle : games) {

        for (auto const& looper : averg->genres) {
            if (games[cycle.first]->genres.find(looper) != games[cycle.first]->genres.end()) {
                score++;
            }
        }
        for (auto const& looper : averg->tags) {
            if (games[cycle.first]->tags.find(looper) != games[cycle.first]->tags.end()) {
                score++;
            }
        }
        if (games[cycle.first]->price < averg->price + 5 && games[cycle.first]->price > averg->price - 5) {
            score += 2;
        }
        if (games[cycle.first]->dateNum < averg->dateNum + 3 && games[cycle.first]->dateNum > averg->dateNum - 3) {
            score += 2;
        }
        games[cycle.first]->simIndex = float(score) / total;

        if (flag) {
            mHeap.push(cycle.second);
        }
        else {
            avlTree[cycle.second->simIndex].push_back( cycle.second);
        }
        score = 0;
    }
    vector<Game> results;


    if (flag) {
        while (results.size() < 5) {
            if (five.find(mHeap.top().name) == five.end()) {
                results.push_back(mHeap.top());
                mHeap.pop();
            }
            else {
                mHeap.pop();
            }
        }
    }
    else {
        cout << "here" << endl;
        map<double, vector<Game>>::iterator looper = --avlTree.end();

        while (results.size() < 5) {
            for (int i = 0; i < looper->second.size(); i++) {
                if (five.count(looper->second.at(i).name) == 0) {
                    results.push_back(avlTree[looper->first].at(i));
                }
                if (results.size() == 5) {
                    break;
                }
            }
            --looper;
        }
    }
    return results;
}








string nameF(string Name) {
    if (Name.length() == 0)
        return "";
    string newN = "";
    for (int i = 0; i < Name.length(); i++) {
        newN += tolower(int(Name.at(i)));
    }
    return newN;
}

double reviewF(string reviewP) {
    if (reviewP == "NA" || isdigit(reviewP.at(1)))
        return 0.0;
    int found = reviewP.find(')') - reviewP.find('(');
    string percentage = reviewP.substr(reviewP.find('-') + 2, 2);
    string total = reviewP.substr(reviewP.find('(')+1, found - 1);

    if (total.find(',') != string::npos) {
        total.erase(total.find(','), 1);
    }
    if (total.find(',') != string::npos) {
        total.erase(total.find(','), 1);
    }

    double percent = stoi(percentage) / 100.0;
    double result = percent * sqrt(stoi(total));
    return result;
}

double priceF(string price) {
    if (price.find('$') == string::npos) {
        return 0.0;
    }
    string dollar, cent;
    dollar = price.substr(1, price.find('.'));
    cent = price.substr(price.find('.') + 1);
    double result = stoi(dollar) + stoi(cent) / 100.0;
    return result;
}

set<string> tagF(string tags) {
    string tag1;
    set<string> taggy;
    if (tags.find(',') == string::npos) {
        string newT = "";
        for (int i = 0; i < tags.length(); i++) {
            newT += tolower(int(tags.at(i)));
        }
        taggy.insert(newT);

        return taggy;
    }
    else {
        int counted = count(tags.begin(), tags.end(), ',');
        for (int i = 0; i < counted; i++) {
            tag1 = tags.substr(0, tags.find(','));

            tags = tags.substr(tags.find(',') + 1);
            string newN = "";
            for (int i = 0; i < tag1.length(); i++) {
                newN += tolower(int(tag1.at(i)));
            }

            taggy.insert(newN);
        }
        string newT = "";
        for (int i = 0; i < tags.length(); i++) {
            newT += tolower(int(tags.at(i)));
        }
        taggy.insert(newT);
        return taggy;
    }
}

set<string> genreF(string genres) {
    string genre1;
    set<string> genreSet;
    if (genres.find(',') == string::npos) {

        string newT = "";
        for (int i = 0; i < genres.length(); i++) {
            newT += tolower(int(genres.at(i)));
        }
        genreSet.insert(newT);

        return genreSet;
    }
    else {
        int counted = count(genres.begin(), genres.end(), ',');
        for (int i = 0; i < counted; i++) {
            genre1 = genres.substr(0, genres.find(','));

            genres = genres.substr(genres.find(',') + 1);
            string newN = "";
            for (int i = 0; i < genre1.length(); i++) {
                newN += tolower(int(genre1.at(i)));
            }

            genreSet.insert(newN);
        }
        string newT = "";
        for (int i = 0; i < genres.length(); i++) {
            newT += tolower(int(genres.at(i)));
        }
        genreSet.insert(newT);
        return genreSet;
    }
}

int dateF(string date) {
    string d = "20";

    date = date.substr(date.find_last_of('-')+1);
    d += date;

    return stoi(d);
}

//int main() {


//	vector<Game> result1 = alg2(games, { games["Rust"], games["Total War: ATTILA"], games["Prison Architect"], games["Eco"] }, true);


//	for (int i = 0; i < result1.size(); i++) {
//		cout << "NAME: "  << endl;
//		cout << result1.at(i).name << endl;
//		cout << "DESCRIPTION: " << endl;
//		cout << result1.at(i).description << endl;
//	}




//}
