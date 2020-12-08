#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <QPushButton>
#include <QMainWindow>
#include <QFrame>
#include <unordered_map>
#include "Game.h"
#pragma once
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onGenreButtonClicked();
    void onTagButtonClicked();
    void onGameButtonClicked();
    void onResultButtonClicked();
    unordered_map<string, Game*> games;
    vector<Game> result1;
    QPushButton* genreButtons[10];
    QPushButton* gameButtons[5];
    string currentGenres[10];
    string currentGames[5];
    string currentTags[5];
    QPushButton* tagButtons[5];
    QFrame* resultFrames[5];
    QPushButton* resultButtons[5];
    int numOfGenres = 0;
    int numOfGames = 0;
    int numOfTags = 0;
    int maxPrice = INT_MAX;
    int minPrice = 0;
    int maxYear = INT_MAX;
    int minYear = 0;
    bool searchByGames = false;
    bool useMaxHeap = true;

private slots:

    void on_GenreSearchBox_returnPressed();

    void on_TagSearchBox_returnPressed();

    void on_MinPrice_returnPressed();

    void on_MaxPrice_returnPressed();

    void on_BeginSearch_clicked();

    void on_MinYear_returnPressed();

    void on_MaxYear_returnPressed();


    void on_SearchByFavorites_clicked();

    void on_SearchByGenre_clicked();

    void on_GameSearchBox_returnPressed();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
