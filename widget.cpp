/*
 * В данном файле производится инициализация графической сцены и её размеров,
 *  также в графической сцене отрисовываются границы поля, где будет перемещаться 
 * треугольник. Но ключевым моментом является инициализация таймера, по обработке
 *  сигнала от которого будет производится изменения состояния графической сцены,
 *  а также будут изменяться координаты расположения треугольника, при отслеживании 
 * состояния клавиш клавиатуры.
*/
#include "widget.h"
#include "ui_widget.h"
#include "apple.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(600,640);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(600,640);    /// Фиксируем размеры виджета

    count = 0;

    scene = new QGraphicsScene();   /// Инициализируем графическую сцену
    triangle = new Triangle();      /// Инициализируем треугольник

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(-250,-250,500,500); /// Устанавливаем область графической сцены

    scene->addItem(triangle);   /// Добавляем на сцену треугольник
    triangle->setPos(0,0);      /// Устанавливаем треугольник в центр сцены



    /* Инициализируем таймер и вызываем слот обработки сигнала таймера
     * у Треугольника 100 раз в секунду.
     * Управляя скоростью отсчётов, соответственно управляем скоростью
     * изменения состояния графической сцены
     * */
    timer = new QTimer();
    connect(timer, &QTimer::timeout, triangle, &Triangle::slotGameTimer);
    timer->start(1000 / 100);

    /* Раз в секунду отсылаем сигнал на создание яблока в игре
     * */
    timerCreateApple = new QTimer();
    connect(timerCreateApple, &QTimer::timeout, this, &Widget::slotCreateApple);
    timerCreateApple->start(1000);

    /* Подключаем сигнал от Мухи, в котором передаются Объекты, на которые
     * наткнулась Муха
     * */
    connect(triangle, &Triangle::signalCheckItem, this, &Widget::slotDeleteApple);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotDeleteApple(QGraphicsItem *item)
{
    /* Получив сигнал от Мухи
     * Перебираем весь список яблок и удаляем найденное яблоко
     * */
    foreach (QGraphicsItem *apple, apples) {
        if(apple == item){
            scene->removeItem(apple);   // Удаляем со сцены
            apples.removeOne(item);     // Удаляем из списка
            delete apple;               // Вообще удаляем
            ui->lcdNumber->display(count++);    /* Увеличиваем счёт на единицу
                                                 * и отображаем на дисплее
                                                 * */
        }
    }
}

void Widget::slotCreateApple()
{
    Apple *apple = new Apple(); // Создаём яблоко
    scene->addItem(apple);      // Помещаем его в сцену со случайной позицией
    apple->setPos((qrand() % (251)) * ((qrand()%2 == 1)?1:-1),
                  (qrand() % (251)) * ((qrand()%2 == 1)?1:-1));
    apple->setZValue(-1);       /* Помещаем яблоко ниже Мухи, то есть Муха
                                 * на сцене будет выше яблок
                                 * */
    apples.append(apple);       // Добавляем Яблоко в Список
}
