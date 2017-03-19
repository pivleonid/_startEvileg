/*
 * А вот теперь приступаем к программному коду,
 * который отвечает за графический объект, которым
 * мы будем управлять. Класс наследуется от QObject
 *  для работы с сигналами и слотами, а также от
 * QGraphicsItem.

Именно в этом файле подключается заголовочный файл windows.h
 для работы с функционалом
 * */
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

/* Подключаем библиотеку, отвечающую за использование WinAPI
 * Данная библиотека необходима для асинхронной проверки состояния клавиш
 * */
#include <windows.h>
class Triangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Triangle(QObject *parent = 0);
    ~Triangle();

signals:
    /* Сигнал, который передаётся в ядро игры с элементом QGraphicsItem,
     * на который наткнулась муха, и требуется принять решение о том,
     * что с этим элементом делать.
     * */
    void signalCheckItem(QGraphicsItem *item);

public slots:
    void slotGameTimer(); // Слот, который отвечает за обработку перемещения треугольника

protected:
    //эти два метода необходимо переопределить
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;    // Угол поворота графического объекта
    int steps;          // Номер положения ножек мухи
    int countForSteps;  // Счётчик для отсчета тиков таймера, при которых мы нажимали на кнопки
};

#endif // TRIANGLE_H
