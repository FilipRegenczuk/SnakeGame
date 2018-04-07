#include "game.h"

#include <QLabel>

Game::Game(QWidget *parent):QGraphicsView(parent)
{
    setFixedSize(1000, 720);    //ustawianie rozmiaru okna
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   //funkcja, dzięki której nie da się "przewijać" okna poziomo
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //taka sama funkcja jak wyżej, tylko pionowo

    gameScene = new QGraphicsScene(this);   //tworzenie okna gry
    gameScene->setSceneRect(0,0,1000,720);  //ustawianie rozmiaru pola gry
    QGraphicsPixmapItem *bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/images/bg.png").scaled(1000,720));
    gameScene->addItem(bg); //ustawienie tła gry

    setScene(gameScene);    //włączanie pola gry do widoku
    score = new Score();
    gameScene->addItem(score);
    snake2 = NULL;
    snake = NULL;

}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(snake)
        snake->keyPressEvent(event);

    else
        QGraphicsView::keyPressEvent(event);
}

void Game::displayMainMenu(QString text,QString play)
{
    //tworzenie tekstu "Game Over!", na początku gry jest pustym polem tekstowym
    gameOverText = new QGraphicsTextItem(text);
    QFont textFont("arial" , 36);
    gameOverText->setFont(textFont);
    gameOverText->setDefaultTextColor(Qt::white);
    int xPos = width()/2 - gameOverText->boundingRect().width()/2;
    int yPos = 260;
    gameOverText->setPos(xPos,yPos);
    gameScene->addItem(gameOverText);

    //ustawianie obrazu z nazwą gry na tytuł
    QPixmap logo(":/images/images/Logo.png");
    logoLabel = new QLabel();
    logoLabel->setPixmap(logo);
    logoLabel->setGeometry(width()/2-203,150,406,107);
    gameScene->addWidget(logoLabel);

    //tworzenie przycisków, są uzależnione położeniem od tekstu "Game Over!"
    Button * playButton = new Button(play, gameOverText);
    int pxPos = gameOverText ->boundingRect().width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 100;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));

    Button * quitButton = new Button("QUIT", gameOverText);
    int qxPos = gameOverText ->boundingRect().width()/2 - playButton->boundingRect().width()/2;
    int qyPos = 300;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));

    Button * helpButton = new Button("HELP", gameOverText);
    int hxPos = gameOverText ->boundingRect().width()/2 - playButton->boundingRect().width()/2;
    int hyPos = 200;
    helpButton->setPos(hxPos,hyPos);
    connect(helpButton, SIGNAL(clicked()),this,SLOT(help()));
}

void Game::start()
{
    snake = new MoveSnake();
    snake->setFlag(QGraphicsItem::ItemIsFocusable); //dzięki fladze ItemIsFocusable wąż reaguje na naciśnięcie spacji
    snake->setFocus();
    score->setVisible(true);
    score->setScore(0);
    gameScene->addItem(snake);
    logoLabel->hide();
    gameScene->removeItem(gameOverText);

    delete gameOverText;
    delete logoLabel;

    if (snake2)
        snake2->deleteLater();

    snake2 = snake;
}

void Game::help()
{
    gameScene->removeItem(gameOverText);
    logoLabel->hide();

    helpText = new QGraphicsTextItem("HELP");
    QFont textFont("arial", 30);
    helpText->setFont(textFont);
    helpText->setDefaultTextColor(Qt::white);
    int xPos = 500- helpText->boundingRect().width()/2;
    int yPos = 50;
    helpText->setPos(xPos,yPos);
    gameScene->addItem(helpText);

    QPixmap hp(":/images/images/Logo.png");
    helpLabel = new QLabel();
    helpLabel ->setPixmap(hp);
    helpLabel ->setGeometry(width()/2-203,height()/2-54,406,108);
    gameScene->addWidget(helpLabel);

    Button * helpButton = new Button("BACK", helpText);
    int hxPos = helpText ->boundingRect().width()/2 - helpButton->boundingRect().width()/2;
    int hyPos = 550;
    helpButton->setPos(hxPos,hyPos);
    connect(helpButton, SIGNAL(clicked()), this, SLOT(back()));
}

void Game::back()
{
    displayMainMenu("", "PLAY");
    gameScene->removeItem(helpText);
    helpLabel->hide();
}

void Game::gameOver()
{
    displayMainMenu("Game Over!","AGAIN?");
    gameScene->removeItem(snake);
}
