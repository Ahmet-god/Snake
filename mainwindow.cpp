#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snake.h"
MainWindow::MainWindow(QWidget *parent) : //конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() //деструктор
{
    delete ui;
}

void MainWindow::on_start_button_clicked() //характеристика кнопки старта
{
   snake_game_window.setWindowTitle("Snake"); //свойство содержит заголовок окна
   snake_game_window.show();
   snake_game_window.setGeometry(x(),y(),800,700);
   hide();  
}

void MainWindow::on_exit_button_clicked() //характеристика кнопки выхода
{
    MainWindow::close();
}
