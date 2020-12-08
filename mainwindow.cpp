#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QMessageBox>
#include <fstream>
#include <vector>
#include <QLabel>
#include <QDebug>
#include <QDir>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < 10; i++)
    {
        genreButtons[i] = this->findChild<QPushButton *>("Genre" + QString::number(i + 1));
        connect(genreButtons[i], &QPushButton::clicked, this,&MainWindow::onGenreButtonClicked);
    }
    for (int i = 0; i < 5; i++)
    {
        tagButtons[i] = this->findChild<QPushButton *>("Tag" + QString::number(i + 1));
        connect(tagButtons[i], &QPushButton::clicked, this,&MainWindow::onTagButtonClicked);
    }
    for (int i = 0; i < 5; i++)
    {
        gameButtons[i] = this->findChild<QPushButton *>("Game" + QString::number(i + 1));
        connect(gameButtons[i], &QPushButton::clicked, this,&MainWindow::onGameButtonClicked);
    }
    for (int i = 0; i < 5; i++)
    {
        resultFrames[i] = this->findChild<QFrame *>("Result" + QString::number(i + 1));
        resultButtons[i] = this->findChild<QPushButton *>("Result" + QString::number(i + 1) + "Button");
        connect(resultButtons[i], &QPushButton::clicked, this,&MainWindow::onResultButtonClicked);
    }

    fstream file;
    const auto path = QDir::current().absolutePath() + QLatin1String("/steamGames.txt");
    file.open("D:/Documents/untitled2/steamGames.txt");
    string line, url, description, name, review, price, date, tags, genres;
    int counter = 0;


    if (file.is_open()) {
        getline(file, line);
        while (!file.eof()) {
            counter++;
            getline(file, line);
            url = line.substr(0, line.find_first_of('\t'));

            line = line.substr(line.find_first_of('\t') + 1);
            name = line.substr(0, line.find_first_of('\t'));

            line = line.substr(line.find_first_of('\t')+1);
            description = line.substr(0, line.find_first_of('\t'));

            line = line.substr(line.find_first_of('\t') + 1);
            review = line.substr(0, line.find_first_of('\t'));
            line = line.substr(line.find_first_of('\t') + 1);
            review = line.substr(0, line.find_first_of('\t'));

            line = line.substr(line.find_first_of('\t') + 1);
            date = line.substr(0, line.find_first_of('\t'));

            line = line.substr(line.find_first_of('\t') + 1);
            tags = line.substr(0, line.find_first_of('\t'));

            line = line.substr(line.find_first_of('\t') + 1);
            genres = line.substr(0, line.find_first_of('\t'));
            line = line.substr(line.find_first_of('\t') + 1);
            genres = line.substr(0, line.find_first_of('\t'));

            line = line.substr(line.find_first_of('\t') + 1);
            price = line;

            Game *g1 = new Game(name, url, description, reviewF(review), 0.0, tagF(tags), genreF(genres), dateF(date), priceF(price));

            if (games.count(g1->name) == 0) {
                games[g1->name] = g1;
            }


        }

    }
}

void MainWindow::onGenreButtonClicked()
{
    QPushButton *button = (QPushButton *)sender();
    int index = 99999;
    for (int i = 0; i < 10; i++)
    {
        if (button == genreButtons[i] && !currentGenres[i].empty())
        {
            index = i;
            currentGenres[i].clear();
            button->setStyleSheet("font: 63 20pt;"
                                            "Yu Gothic UI Semibold;"
                                            "color: rgb(0,0,0);"
                                            "background-color: rgb(38, 38, 38);"
                                            "border: 1px;");
            button->setText("");
            numOfGenres--;
        }
        else if(i > index)
        {
            if (!currentGenres[i].empty())
            {
                currentGenres[i - 1] = currentGenres[i];
                genreButtons[i - 1]->setStyleSheet("font: 63 8pt;"
                                                   "Yu Gothic UI Semibold;"
                                                   "color: rgb(255, 255, 255);"
                                                   "background-color: rgb(45, 45, 45);"
                                                   "border: 1px;");
                genreButtons[i - 1]->setText(QString::fromStdString(currentGenres[i - 1]));
                genreButtons[i]->setStyleSheet("font: 63 8pt;"
                                                   "Yu Gothic UI Semibold;"
                                                   "color: rgb(255, 255, 255);"
                                                   "background-color: rgb(38, 38, 38);"
                                                   "border: 1px;");
                currentGenres[i] = "";
                genreButtons[i]->setText("");
            }
            else
            {
                break;
            }
        }
    }
}

void MainWindow::onGameButtonClicked()
{
    QPushButton *button = (QPushButton *)sender();
    int index = 99999;
    for (int i = 0; i < 5; i++)
    {
        if (button == gameButtons[i] && !currentGames[i].empty())
        {
            index = i;
            currentGames[i].clear();
            button->setStyleSheet("font: 63 20pt;"
                                            "Yu Gothic UI Semibold;"
                                            "color: rgb(0,0,0);"
                                            "background-color: rgb(38, 38, 38);"
                                            "border: 1px;");
            button->setText("");
            numOfGames--;
        }
        else if(i > index)
        {
            if (!currentGames[i].empty())
            {
                currentGames[i - 1] = currentGames[i];
                gameButtons[i - 1]->setStyleSheet("font: 63 8pt;"
                                                   "Yu Gothic UI Semibold;"
                                                   "color: rgb(255, 255, 255);"
                                                   "background-color: rgb(45, 45, 45);"
                                                   "border: 1px;");
                gameButtons[i - 1]->setText(QString::fromStdString(currentGames[i - 1]));
                gameButtons[i]->setStyleSheet("font: 63 8pt;"
                                                   "Yu Gothic UI Semibold;"
                                                   "color: rgb(255, 255, 255);"
                                                   "background-color: rgb(38, 38, 38);"
                                                   "border: 1px;");
                currentGames[i] = "";
                gameButtons[i]->setText("");
            }
            else
            {
                break;
            }
        }
    }
}

void MainWindow::onTagButtonClicked()
{
    QPushButton *button = (QPushButton *)sender();
    int index = 99999;
    for (int i = 0; i < 5; i++)
    {
        if (button == tagButtons[i] && !currentTags[i].empty())
        {
            index = i;
            currentTags[i].clear();
            button->setStyleSheet("font: 63 20pt;"
                                            "Yu Gothic UI Semibold;"
                                            "color: rgb(0,0,0);"
                                            "background-color: rgb(38, 38, 38);"
                                            "border: 1px;");
            button->setText("");
            numOfTags--;
        }
        else if(i > index)
        {
            if (!currentTags[i].empty())
            {
                currentTags[i - 1] = currentTags[i];
                tagButtons[i - 1]->setStyleSheet("font: 63 8pt;"
                                                   "Yu Gothic UI Semibold;"
                                                   "color: rgb(255, 255, 255);"
                                                   "background-color: rgb(45, 45, 45);"
                                                   "border: 1px;");
                tagButtons[i - 1]->setText(QString::fromStdString(currentTags[i - 1]));
                tagButtons[i]->setStyleSheet("font: 63 8pt;"
                                                   "Yu Gothic UI Semibold;"
                                                   "color: rgb(255, 255, 255);"
                                                   "background-color: rgb(38, 38, 38);"
                                                   "border: 1px;");
                currentTags[i] = "";
                tagButtons[i]->setText("");
            }
            else
            {
                break;
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_GenreSearchBox_returnPressed()
{
    int firstFreeBox = 0;
    if (numOfGenres < 10 && !ui->GenreSearchBox->text().isEmpty())
    {
        for (int i = 0; i < 10; i++)
        {
            if (currentGenres[i].empty())
            {
                firstFreeBox = i;
                currentGenres[i] = ui->GenreSearchBox->text().toUtf8().constData();
                break;
            }
        }
        QString objectName = "Genre" + QString::number(firstFreeBox + 1);
        QPushButton* button = this->findChild<QPushButton *>(objectName);
        button->setStyleSheet("font: 63 8pt;"
                                        "Yu Gothic UI Semibold;"
                                        "color: rgb(255, 255, 255);"
                                        "background-color: rgb(45, 45, 45);"
                                        "border: 1px;");
        button->setText(ui->GenreSearchBox->text());
        ui->GenreSearchBox->setText("");
        numOfGenres++;
    }
}

void MainWindow::on_TagSearchBox_returnPressed()
{
    int firstFreeBox = 0;
    if (numOfTags < 5 && !ui->TagSearchBox->text().isEmpty())
    {
        for (int i = 0; i < 5; i++)
        {
            if (currentTags[i].empty())
            {
                firstFreeBox = i;
                currentTags[i] = ui->TagSearchBox->text().toUtf8().constData();
                break;
            }
        }
        QString objectName = "Tag" + QString::number(firstFreeBox + 1);
        QPushButton* button = this->findChild<QPushButton *>(objectName);
        button->setStyleSheet("font: 63 8pt;"
                                        "Yu Gothic UI Semibold;"
                                        "color: rgb(255, 255, 255);"
                                        "background-color: rgb(45, 45, 45);"
                                        "border: 1px;");
        button->setText(ui->TagSearchBox->text());
        ui->TagSearchBox->setText("");
        numOfTags++;
    }
}

void MainWindow::on_MinPrice_returnPressed()
{
    if (ui->MinPrice->text().isEmpty())
    {
      minPrice = 0;
    }
    else
    {
        minPrice = (ui->MinPrice->text().mid(1)).toInt();
    }
}

void MainWindow::on_MaxPrice_returnPressed()
{
    if (ui->MaxPrice->text().isEmpty())
    {
      maxPrice = INT_MAX;
    }
    else
    {
        maxPrice = (ui->MaxPrice->text().mid(1)).toInt();
    }
}

void MainWindow::on_BeginSearch_clicked()
{
    struct timespec spec;
    time_t beginningTime;
    time_t endTime;
    result1.clear();
    if (!searchByGames)
    {
        clock_gettime(CLOCK_REALTIME, &spec);
        beginningTime  = spec.tv_sec;
        for (int i = 0; i < 5; i ++)
        {
            resultFrames[i]->setVisible(false);
        }
        ui->ChosenGameFrame->setVisible(false);
        Param *givenParams = new Param();
        givenParams->date.first = minYear;
        givenParams->date.second = maxYear;
        givenParams->price.first = minPrice;
        givenParams->price.second = maxPrice;
        set<string> tags;
        set<string> genres;
        for (int i = 0; i < numOfTags; i++)
        {
            tags.insert(currentTags[i]);
        }
        for (int i = 0; i < numOfGenres; i++)
        {
            genres.insert(currentGenres[i]);
        }
        givenParams->genres = genres;
        givenParams->tags = tags;
        result1 = alg1(games, (*givenParams));
        clock_gettime(CLOCK_REALTIME, &spec);
        endTime  = spec.tv_sec;
    }
    else
    {
        clock_gettime(CLOCK_REALTIME, &spec);
        beginningTime  = spec.tv_sec;
        vector<Game> given;
        for (int i = 0; i < numOfGames; i++)
        {
            given.push_back(games[currentGames[i]]);
        }
        result1 = alg2(games, given, useMaxHeap);
        clock_gettime(CLOCK_REALTIME, &spec);
        endTime  = spec.tv_sec;
    }
    for (int i = 0; i < result1.size(); i++)
    {
        this->findChild<QLabel *>("Result" + QString::number(i + 1) + "Link")->setText(QString::fromStdString(result1[i].url));
        this->findChild<QLabel *>("Result" + QString::number(i + 1) + "Name")->setText(QString::fromStdString(result1[i].name));
        if (result1[i].price == 0)
        {
            this->findChild<QLabel *>("Result" + QString::number(i + 1) + "Price")->setText("FREE");
        }
        else
        {
            this->findChild<QLabel *>("Result" + QString::number(i + 1) + "Price")->setText("$" + QString::number(result1[i].price));
        }
        resultFrames[i]->setVisible(true);
    }
    if (searchByGames)
    {
        ui->ExecutionTime->setText("Execution time (in seconds): " + QString::number(endTime - beginningTime));
    }
}

void MainWindow::on_MinYear_returnPressed()
{
    if (ui->MinYear->text().isEmpty())
    {
      minYear = 0;
    }
    else
    {
        minYear = (ui->MinYear->text()).toInt();
    }
}

void MainWindow::on_MaxYear_returnPressed()
{
    if (ui->MaxYear->text().isEmpty())
    {
      maxYear = INT_MAX;
    }
    else
    {
        maxYear = (ui->MaxYear->text()).toInt();
    }
}

void MainWindow::onResultButtonClicked()
{
    QPushButton *button = (QPushButton *)sender();
    int id = button->objectName().mid(6, 1).toInt();
    this->findChild<QLabel *>("GameName")->setText(QString::fromStdString(result1[id - 1].name));
    if (result1[id - 1].price == 0)
    {
        this->findChild<QLabel *>("GamePrice")->setText("FREE");
    }
    else
    {
        this->findChild<QLabel *>("GamePrice")->setText("$" + QString::number(result1[id - 1].price));
    }
    this->findChild<QLabel *>("GameDescription")->setText(QString::fromStdString(result1[id - 1].description));
    this->findChild<QLabel *>("GameLink")->setText(QString::fromStdString(result1[id - 1].url));
    ui->ChosenGameFrame->setVisible(true);
}

void MainWindow::on_SearchByFavorites_clicked()
{
    ui->GameSearchBox->setVisible(true);
    ui->FiveGamesLabel->setVisible(true);
    ui->checkBox->setVisible(true);
    ui->ExecutionTime->setVisible(true);
    ui->GenreSearchBox->setVisible(false);
    ui->TenGenresLabel->setVisible(false);
    ui->TenTagLabel->setVisible(false);
    ui->TagSearchBox->setVisible(false);
    ui->DateRange->setVisible(false);
    ui->PriceRange->setVisible(false);
    ui->MinPrice->setVisible(false);
    ui->MaxPrice->setVisible(false);
    ui->MaxYear->setVisible(false);
    ui->MinYear->setVisible(false);
    for (int i = 0; i < 10; i++)
    {
        genreButtons[i]->setVisible(false);
    }
    for (int i = 0; i < 5; i++)
    {
        tagButtons[i]->setVisible(false);
    }
    for (int i = 0; i < 5; i++)
    {
        this->findChild<QPushButton *>("Game" + QString::number(i + 1))->setVisible(true);
    }
    searchByGames = true;
}

void MainWindow::on_SearchByGenre_clicked()
{
    ui->GameSearchBox->setVisible(false);
    ui->FiveGamesLabel->setVisible(false);
    ui->checkBox->setVisible(false);
    ui->ExecutionTime->setVisible(false);
    ui->GenreSearchBox->setVisible(true);
    ui->TenGenresLabel->setVisible(true);
    ui->TenTagLabel->setVisible(true);
    ui->TagSearchBox->setVisible(true);
    ui->DateRange->setVisible(true);
    ui->PriceRange->setVisible(true);
    ui->MinPrice->setVisible(true);
    ui->MaxPrice->setVisible(true);
    ui->MaxYear->setVisible(true);
    ui->MinYear->setVisible(true);
    for (int i = 0; i < 10; i++)
    {
        genreButtons[i]->setVisible(true);
    }
    for (int i = 0; i < 5; i++)
    {
        tagButtons[i]->setVisible(true);
    }
    for (int i = 0; i < 5; i++)
    {
        this->findChild<QPushButton *>("Game" + QString::number(i + 1))->setVisible(false);
    }
    searchByGames = false;
}

void MainWindow::on_GameSearchBox_returnPressed()
{
    int firstFreeBox = 0;
    if (numOfGames < 5 && !ui->GameSearchBox->text().isEmpty())
    {
        for (int i = 0; i < 5; i++)
        {
            if (currentGames[i].empty())
            {
                firstFreeBox = i;
                currentGames[i] = ui->GameSearchBox->text().toUtf8().constData();
                break;
            }
        }
        QString objectName = "Game" + QString::number(firstFreeBox + 1);
        QPushButton* button = this->findChild<QPushButton *>(objectName);
        button->setStyleSheet("font: 63 8pt;"
                                        "Yu Gothic UI Semibold;"
                                        "color: rgb(255, 255, 255);"
                                        "background-color: rgb(45, 45, 45);"
                                        "border: 1px;");
        button->setText(ui->GameSearchBox->text());
        ui->GameSearchBox->setText("");
        numOfGames++;
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    useMaxHeap = ui->checkBox->checkState();
    if (useMaxHeap)
    {
        ui->checkBox->setText("Using Priority Queue");
    }
    else
    {
        ui->checkBox->setText("Using Ordered Map");
    }
}
