#include "profilewindow.h"
#include "ui_profilewindow.h"
#include "Config.h"
#include "GameCard.h"
#include "purchasedgamesdbmanager.h"
#include <QCloseEvent>

ProfileWindow::ProfileWindow(User* user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Foxlike Games");
    this->setWindowIcon(QIcon(pathToUIElements + "Logo.ico"));

    if (user != nullptr) {
        this->user = user;

        ui->nicknameLabel->setText(user->getNickname());

        ui->profilePhoto->setPixmap(QPixmap(pathToProfilesImages + user->getProfilePhoto()));
        ui->profilePhoto->setMinimumSize(200, 200);

        if (user->getAccountType() != AccountType::developer && user->getAccountType() != AccountType::contentManager) {
            ui->addGameButton->hide();
        }

        ui->GamesScrollArea->setMinimumSize(sizeOfGameCard[0] + 50, sizeOfGameCard[1] + 20);

        refreshGames();
    }
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}

void ProfileWindow::refreshGames()
{
    QLayoutItem *item;
    while ((item = ui->GamesGrid->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        }
        delete item;
    }

    if (this->user->getAccountType() != AccountType::guest) {
        PurchasedGamesDBManager *purchasedGamesDBManager = PurchasedGamesDBManager::getInstance();
        int counter = 0;

        for (Game game : purchasedGamesDBManager->getGamesOfUserById(user->getId())) {
            GameCard *gameCardWidget = new GameCard(game);
            ui->GamesGrid->addWidget(gameCardWidget, counter, 0);
            counter++;
        }
    }
}

void ProfileWindow::on_gameAdded()
{
    delete this->gameAddingWindow;
    this->close();
}

void ProfileWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    emit hidden();
    event->accept();
}

void ProfileWindow::on_addGameButton_clicked()
{
    this->gameAddingWindow = new GameAddingWindow();

    connect(this->gameAddingWindow, &GameAddingWindow::gameAdded, this, &ProfileWindow::on_gameAdded);
    connect(this->gameAddingWindow, &GameAddingWindow::hidden, this, &ProfileWindow::show);

    this->hide();

    gameAddingWindow->show();
}

void ProfileWindow::on_logOutButton_clicked()
{
    emit loggedOut();
    this->hide();
    emit hidden();
}

