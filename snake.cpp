#include <QPainter> //подключение директива QPainter(отвечает за рисунок)
#include <QTime>//подключение директива QTime(работает с часами. Он имеет методы для сравнения, определения и манипулирования временем)
#include "snake.h"//подключение директива snake.h
Snake::Snake(QWidget *parent) : QWidget(parent) {

leftDirection = false;
rightDirection = true;
upDirection = false;
downDirection = false;
inGame = true;

m_player_gameOver = new QMediaPlayer(this); //установка звука смерти
m_playlist_gameOver = new QMediaPlaylist(m_player_gameOver);
m_player_gameOver->setPlaylist(m_playlist_gameOver);
m_playlist_gameOver->addMedia(QUrl("file:///C:/Users/111/Documents/untitled1/death.mp3"));
m_playlist_gameOver->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

m_player_apple = new QMediaPlayer(this); //установка звука поедания яблока
m_playlist_apple = new QMediaPlaylist(m_player_apple);
m_player_apple->setPlaylist(m_playlist_apple);
m_playlist_apple->addMedia(QUrl("file:///C:/Users/111/Documents/untitled1/apple_eating.mp3"));
m_playlist_apple->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

m_player_orange = new QMediaPlayer(this); //установка звука поедания апельсина
m_playlist_orange = new QMediaPlaylist(m_player_orange);
m_player_orange->setPlaylist(m_playlist_orange);
m_playlist_orange->addMedia(QUrl("file:///C:/Users/111/Documents/untitled1/orange_eating.mp3"));
m_playlist_orange->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

resize(B_WIDTH, B_HEIGHT);//возможность изменить размер вектора
loadImages(); //процедура загрузки изображений
initGame(); //процедура входа в игру
}

void Snake::loadImages() { //возможность загрузки изображений, которыми будут пользоваться в игре

dot.load(":/dot.png"); //загрузка изображения тела змейки
head.load(":/head.png");//загрузка изображения головы змейки
apple.load(":/apple.png"); //загрузка изображения яблока
orange.load(":/orange.png"); //загрузка изображеня апельсина
place.load(":/place.png"); //загрузка изображения поля игры
counter.load(":/counter.png"); //загрузка поля счетчика
}

void Snake::initGame() {
dots = 1;

for (int z = 0; z < dots; z++) {
x[z] = 50 - z * 10;
y[z] = 50;
}

locateApple();
locateOrange();
timerId = startTimer(DELAY);
}  //создаем змею, случайным образом определям позицию на игровом поле, где будет распологаться яблоко и апельсин, запускаем таймер


void Snake::paintEvent(QPaintEvent *e) {

Q_UNUSED(e);

doDrawing();
}

//отрисовка изображений
void Snake::doDrawing() {

QPainter qp(this);

if (inGame) {

QPainter q(this);
if (inGame){ q.drawImage(0,0,place);}

QPainter p(this);
if (inGame){ p.drawImage(700,0,counter);}
qp.drawImage(apple_x, apple_y, apple);
qp.drawImage(orange_x,orange_y,orange);
for (int z = 0; z < dots; z++) {
if (z == 0) {
qp.drawImage(x[z], y[z], head);

} else {
qp.drawImage(x[z], y[z], dot);
}
}
} else {

gameOver(qp);
}
}
//процедура проигрыша
void Snake::gameOver(QPainter &qp) {

m_player_gameOver->play();

QString message = "Game over";
QFont font("Courier", 15, QFont::DemiBold);
QFontMetrics fm(font);
int textWidth = fm.width(message);

qp.setFont(font);
int h = height();
int w = width();

qp.translate(QPoint(w/2, h/2));
qp.drawText(-textWidth/2, 0, message);
}

//процедура, которая контролирует поедание фруктов + счетчик фруктов + добавление новых частей змейки + звук поедания фруктов + новую отрисовку фруктов после поедания
void Snake::checkFruit() {

if ((x[0] == apple_x) && (y[0] == apple_y)) {

apple_counter++;

m_player_apple->play();

dots++;
locateApple();
} //при столкновении головы с яблоком мы увеличиваем количество «частей» тела змеи, потом вызываем метод locateApple(), который случайным образом позиционирует новое яблок

if ((x[0] == orange_x) && (y[0] == orange_y)){

orange_counter++;

m_player_orange->play();

dots++;
locateOrange();
}
}

//процедура передвижения змейки
void Snake::move() {

for (int z = dots; z > 0; z--) {
x[z] = x[(z - 1)];
y[z] = y[(z - 1)];
} //перемещение частей тела змеи друг за другом

if (leftDirection) {
x[0] -= DOT_SIZE;
} //перемещение влево

if (rightDirection) {
x[0] += DOT_SIZE;
} //перемещение вправо

if (upDirection) {
y[0] -= DOT_SIZE;
} //перемещение вверх

if (downDirection) {
y[0] += DOT_SIZE;
} //перемещение вниз
}

//в методе checkCollision() мы определяем, столкнулась ли змея со стеной или со своим телом
void Snake::checkCollision() {

for (int z = dots; z > 0; z--) {

if ((z > 1) && (x[0] == x[z]) && (y[0] == y[z])) {
inGame = false;
}
} //если змея ударится головой о какую-то часть своего тела, то игра зе енд

if (y[0] >= 700) {
inGame = false;
} //если змея ударится головой о нижнюю часть доски, то игра зе енд

if (y[0] < 0) {
inGame = false;
}

if (x[0] >= 700) {
inGame = false;
}

if (x[0] < 0) {
inGame = false;
}

if(!inGame) {
killTimer(timerId);
}
}

//координаты яблока
void Snake::locateApple() {

QTime time = QTime::currentTime();
qsrand((uint) time.msec());

int a = qrand() % RAND_POS_APPLE;
apple_x = (a * DOT_SIZE);

a = qrand() % RAND_POS_APPLE;
apple_y = (a * DOT_SIZE);
}

//координаты апельсина
void Snake::locateOrange() {

QTime time = QTime::currentTime();
qsrand((uint) time.msec());

int o = qrand() % RAND_POS_ORANGE;
orange_x = (o * DOT_SIZE);

o = qrand() % RAND_POS_ORANGE;
orange_y = (o * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {

Q_UNUSED(e);

if (inGame) {

checkFruit();
checkCollision();
move();
}

repaint(); //перерисовка окна
} //метод timerEvent формирует игровой цикл. при условии, что игра еще не закончена, мы выполняем обнаружение столкновений змеи с препятствиями и выполняем ее дальнейшие перемещения

void Snake::keyPressEvent(QKeyEvent *e) {

int key = e->key();
if ((key == Qt::Key_Left) && (!rightDirection)) {
leftDirection = true;
upDirection = false;
downDirection = false;
} //если пользователь нажимает стрелочку влево, то тру для leftDirection(когда змея направляется вправо, мы не можем сразу повернуть налеово)


if ((key == Qt::Key_Right) && (!leftDirection)) {
rightDirection = true;
upDirection = false;
downDirection = false;
}
//если пользователь нажимает стрелочку вправо, то тру для rightDirection(когда змея направляется влево, мы не можем сразу повернуть направо)

if ((key == Qt::Key_Up) && (!downDirection)) {
upDirection = true;
rightDirection = false;
leftDirection = false;
}
//если пользователь нажимает стрелочку вверх, то тру для upDirection(когда змея направляется вниз, мы не можем сразу повернуть вверх)

if ((key == Qt::Key_Down) && (!upDirection)) {
downDirection = true;
rightDirection = false;
leftDirection = false;
}
//если пользователь нажимает стрелочку вниз, то тру для downDirection(когда змея направляется вверх, мы не можем сразу повернуть вниз)

QWidget::keyPressEvent(e);
} //этот обработчик события event может быть переопределён в подклассе для получения событий нажатия клавиш для виджета
