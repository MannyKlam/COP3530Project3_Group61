

#ifndef GAMECONNECT_GAME_H
#define GAMECONNECT_GAME_H
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
using namespace std;



class Game {
public:
    Game(string name, string url, string description, double reviews, double simIndex, set<string> tags, set<string> genres, int dateNum, double price) {
        this->name = name;
        this->url = url;
        this->description = description;
        this->reviews = reviews;
        this->tags = tags;
        this->genres = genres;
        this->dateNum = dateNum;
        this->price = price;
        this->simIndex = 0.0;
    }
    Game() {
        this->name = "";
        this->url = "";
        this->description = "";
        this->reviews = 0.0;
        this->tags = {};
        this->genres = {};
        this->dateNum = 0;
        this->price = 0.0;
        this->simIndex = 0.0;

    }
    Game( const Game* g) {
        this->name = g->name;
        this->url = g->url;
        this->description = g->description;
        this->reviews = g->reviews;
        this->tags = g->tags;
        this->genres = g->genres;
        this->dateNum = g->dateNum;
        this->price = g->price;
        this->simIndex = g->simIndex;
    }
    Game& operator=( Game g) {
        std::swap(name, g.name);
        std::swap(url, g.url);
        std::swap(description, g.description);
        std::swap(reviews, g.reviews);
        std::swap(tags, g.tags);
        std::swap(genres, g.genres);
        std::swap(dateNum, g.dateNum);
        std::swap(price, g.price);
        std::swap(simIndex, g.simIndex);
        return *this;
    }
    bool operator>(const Game& rhs) const{
        return simIndex > rhs.simIndex;
    }
    bool operator<(const Game& rhs) const{
        return reviews < rhs.reviews;
    }
    string name, url, description;
    double reviews, simIndex, price;
    int dateNum;
    set<string> tags, genres;


};

struct simI
{
    bool operator()( Game const& lhs, Game const& rhs) {
        return lhs.simIndex < rhs.simIndex;
}
};
class Param {
public:
    set<string> tags;
    set<string> genres;

    pair<int, int> date;
    pair<double, double> price;
};

string nameF(string Name);
double reviewF(string reviewP);
double priceF(string price);
set<string> tagF(string tags);
set<string> genreF(string genres);
int dateF(string date);
vector<Game> alg1(unordered_map<string, Game*> games, Param &toggles);
vector<Game> alg2(unordered_map<string, Game*> games, vector<Game> given, bool flag);
#endif //GAMECONNECT_GAME_H
