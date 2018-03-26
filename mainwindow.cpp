#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/monif/Documents/Qt/Snake/Logo.png");
    ui->title_pic->setPixmap(pix);

    QPixmap bkgnd("C:/Users/monif/Documents/Qt/Snake/snakeskin.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_helpButton_clicked()
{
    QMessageBox::about(this, "POMOC", "Wężem steruje się poprzez klawisze WASD. "
                                      "Wąż rośnie i zdobywa punkty poprzez jedzenie owoców. "
                                      "Jabłko daje jeden punkt, gruszka dwa punkty. "
                                      "Wąż przejeżdża przez ściany - gra odbywa się, dopóki wąż nie ugryzie samego siebie.");

}
