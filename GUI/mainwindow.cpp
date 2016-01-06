#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImageLabel(QImage image)
{
    setFixedHeight(image.height());
    setFixedWidth(image.width());
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(image));
    setCentralWidget(label);
}
