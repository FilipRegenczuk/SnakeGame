#include "game.h"
#include <QLabel>
Game::Game(QWidget *parent):QGraphicsView(parent)
{
    //making the view or window
    setFixedSize(1000, 720);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //making the game scene
    gameScene = new QGraphicsScene(this);
    gameScene->setSceneRect(0,0,1000,720);
    QGraphicsPixmapItem *bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/images/bg.png").scaled(1000,720));
    gameScene->addItem(bg);
    //adding the gameScene to the view
    setScene(gameScene);
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

void Game::displayMainMenu(QString title,QString play)
{
//Create the title
    titleText = new QGraphicsTextItem(title);
    QFont titleFont("arial" , 36);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::white);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 260;
    titleText->setPos(xPos,yPos);
    gameScene->addItem(titleText);

    QPixmap logo(":/images/images/Logo.png");
    logoLabel = new QLabel();
    logoLabel->setPixmap(logo);
    logoLabel->setGeometry(297,150,406,107);
    gameScene->addWidget(logoLabel);

    //create Button
    Button * playButton = new Button(play, titleText);
    int pxPos = titleText ->boundingRect().width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 100;
    playButton->setPos(pxPos,pyPos);

    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    //gameScene->addItem(playButton);


    //Create Quit Button
    Button * quitButton = new Button("QUIT", titleText);
    int qxPos = titleText ->boundingRect().width()/2 - playButton->boundingRect().width()/2;
    int qyPos = 300;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    //gameScene->addItem(quitButton);

    Button * helpButton = new Button("HELP", titleText);
    int hxPos = titleText ->boundingRect().width()/2 - playButton->boundingRect().width()/2;
    int hyPos = 200;
    helpButton->setPos(hxPos,hyPos);
    connect(helpButton, SIGNAL(clicked()),this,SLOT(help()));

}
void Game::start()
{
    snake = new MoveSnake();
    snake->setFlag(QGraphicsItem::ItemIsFocusable);
    snake->setFocus();
    score->setVisible(true);
    score->setScore(0);
    gameScene->addItem(snake);
    logoLabel->hide();
    gameScene->removeItem(titleText);

    delete titleText;
    delete logoLabel;

    if (snake2)
        snake2->deleteLater();

    snake2 = snake;
}

void Game::help()
{

}

void Game::gameOver()
{
    displayMainMenu("Game Over!","AGAIN?");
    gameScene->removeItem(snake);
    //delete snake;
}
