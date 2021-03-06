#pragma once //директива, разработанная для контроля за тем, чтобы конкретный исходный файл при компиляции подключался строго один раз.
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget> //подключение директива <QWidget> (получает события мыши, клавиатуры и другие события от оконной системы и рисует свое изображение на экране. Если он равен 0 (по умолчанию), новый виджет будет окном.)
#include <QKeyEvent>//подключение директива QKeyEvent(обработка событий)
#include <QPainter>

class Snake : public QWidget { //применили наследование и на основе класса QWidget создали класс Snake

public:
Snake(QWidget *parent = 0); //доступ открыт всем, кто видит определение данного класса
int apple_counter; //счетчик съеденных яблок
int orange_counter; //счетчик съеденных апельсинов
protected:
void paintEvent(QPaintEvent *);
void timerEvent(QTimerEvent *);
void keyPressEvent(QKeyEvent *); //доступ открыт классам, происходящиям от данного

private:

QImage dot;
QImage head;
QImage apple; //создание переменных для отрисовки игры
QImage orange;
QImage place;
QImage counter;

static const int B_WIDTH = 700; //ширина игрового поля
static const int B_HEIGHT = 700; //высота игрового поля
static const int DOT_SIZE = 50; //размер яюблока и частей тела змейки
static const int ALL_DOTS = 900; //определяет максимальное количество возможных точек на поле
static const int RAND_POS_APPLE = 14; //вычислене случайной позиции яблока
static const int RAND_POS_ORANGE = 13; //вычислене случайной позиции апельсина
static const int DELAY = 300; //скорость игры

int timerId; //время, таймер
int dots; //точки
int apple_x; //расположение по х яблока
int apple_y; //расположение по у яблока
int orange_x; //расположение по х апельсина
int orange_y; //расположение по у апельсина



int x[ALL_DOTS];
int y[ALL_DOTS]; //эти два массива содержат координаты (x;y) всех частей тела змейки

bool leftDirection; //левое направление
bool rightDirection; //правое направление
bool upDirection; //вверх
bool downDirection; //вниз
bool inGame; //в игре

void loadImages(); //загрузка изображений
void initGame(); //вывод о начале игры
void locateApple(); //расположение яблока
void locateOrange(); //расположение апельсина
void checkFruit(); //проверка яблока
void checkCollision(); //столкновение
void move(); //передвижение змеи
void doDrawing(); //отрисовка изображений
void gameOver(QPainter &); //отображение о конце игры

QMediaPlayer * m_player_gameOver; //поле для воспроизведения звука смерти
QMediaPlaylist * m_playlist_gameOver;

QMediaPlayer * m_player_apple; //поле для воспроизведения звука поедания яблока
QMediaPlaylist * m_playlist_apple;

QMediaPlayer * m_player_orange; //поле для воспроизведения звука поедания апельсина
QMediaPlaylist * m_playlist_orange;

};
