#include <QApplication> //подключение директива QApplication(управляет ресурсами приложения, например, задавая тип шрифта или курсора)
#include "snake.h" //подключение директива snake.h
#include "mainwindow.h"
#include <QFile>
int main(int argc, char *argv[]) { //эта строка сообщает компилятору, что есть функция с именем main, и что функция возвращает целое число типа int. Функция main() является точкой входа в вашу программу. Параметр argc — число аргументов командной строки, а argv — массив этих аргументов

QApplication app(argc, argv); //Объект app является экземплятором QApplication. В этой строчке мы его создаем. Мы передаём параметры argc и argv в конструктор QApplication, чтобы он мог обработать стандартные аргументы командной строки

MainWindow w; //создание собственного виджета
w.show();  //виджет скрыт до момента вызова метода show

QFile file(":/stylesheet.css"); //подключения файла для фона стартового окна
file.open(QFile::ReadOnly);
QString stylesheet = QLatin1String(file.readAll());
app.setStyleSheet(stylesheet);



return app.exec(); //в этом месте main() передаёт управление Qt
}
