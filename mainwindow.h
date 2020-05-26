#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "snake.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui; //создание приватного поля для отрисовки стартового окна
    Snake snake_game_window;

private slots:
    void on_start_button_clicked(); //процедура, отвечающая за характеристики кнопки старта
    void on_exit_button_clicked(); //процедура, отвечающая за характеристики кнопки выхода

};


#endif // MAINWINDOW_H
