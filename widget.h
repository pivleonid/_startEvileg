/*
 * В данном файле всего лишь объявляем графическую сцену, объект треугольника,
 *  которым будем управлять, а также таймер, по отсчетам которого будет
 *  производиться проверка состояния клавиш клавиатуры, которыми мы будем управлять
 *  треугольником на графической сцене.

 Ядро игры развивается и усложняется. На этот раз необходимо добавить таймер для
 периодического создания яблок в игре, Список, в котором будут храниться все яблоки
 и счетчик очков. А также необходимо добавить слоты для создания и удаления яблок.
*/
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
    QTimer          *timerCreateApple;  // Таймер для периодического создания яблок в игре

    QList<QGraphicsItem *> apples;  // Список со всеми яблоками, присутствующими в игре
    double count;   // Переменная, которая хранит счёт игре
private slots:
    // Слот для удаления яблок если Муха наткнулая на это яблоко
    void slotDeleteApple(QGraphicsItem * item);
    void slotCreateApple();     // Слот для создания яблок, срабатывает по таймеру

};

#endif // WIDGET_H
