/*
 * В данном файле всего лишь объявляем графическую сцену, объект треугольника,
 *  которым будем управлять, а также таймер, по отсчетам которого будет
 *  производиться проверка состояния клавиш клавиатуры, которыми мы будем управлять
 *  треугольником на графической сцене.*/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>

#include <triangle.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;     /// Объявляем графическую сцену
    Triangle        *triangle;  /// и треугольник
    QTimer          *timer;     /* Объявляем игровой таймер, благодаря которому
                                 * будет производиться изменения положения объекта на сцене
                                 * При воздействии на него клавишами клавиатуры
                                 * */
};

#endif // WIDGET_H
