#include "chesswidget.h"

// Конструктор
//---------------------------------------------------------------
chessWidget::chessWidget(QWidget *parent) :
    QWidget(parent)
{
    // Инициализация параметров графики виджета
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);

    // Инициализация используемых кистей
    dark = QBrush(Qt::darkGray);
    light = QBrush(Qt::white);
    selected = QBrush(Qt::yellow);
    black = QBrush(QColor(60,60,60));
    white = QBrush(Qt::white);

    // Инициализация используемого шрифта
    QFont fnt = this->font();       // Выбираем используемый шрифт
    fnt.setPointSize(FONT_SZ/2);    // Изменяем его размер
    this->setFont(fnt);             // Устанавливаем шрифт обратно
}

// Обработчик события рисования - собственная графика виджета
//---------------------------------------------------------------
void chessWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);         // Создаем объект графики
    draw(&painter);                 // Вызываем отрисовку
}

// В этой процедуре выполняется вся отрисовка виджета
// Она вызывается из события рисования
//---------------------------------------------------------------
void chessWidget::draw( QPainter  *painter)
{
    // Инициализация параметров графики
    painter->setRenderHint( QPainter ::Antialiasing, true);

    // Рассчет необходимых размеров
    int W = this->width();              // Ширину берем в чистом виде
    int H = this->height() - FONT_SZ;   // Высоту подрправим на высоту надписи
    int Min = W < H ? W : H;            // Берем минимальное значение

    Ceil = Min / 9;                     // Ширина клетки (с запасом в полклетки)
    WGap = (W - 8*Ceil)/2;              // Вертикальный отступ
    HGap = (H - 8*Ceil)/2 + FONT_SZ;    // Горизонтальный отступ

    int delta1 = Ceil/8;        // Отступы для рисования шашки в клетке
    int delta2 = Ceil/4;

    // Собственно отрисовка поля, клетка за клеткой
    for (int i=0; i<8; i++)             // Двойной цикл по координатам
    {
        for (int k=0; k<8; k++)
        {
            // Получаем свойства текущей клетки
            int type = checkers->getType(i, k);

            // Выбираем кисть для рисования фона клетки
            // для этого накладываем на свойство нужную маску
            // и по полученному значению делаем выбор
            switch (type & Checkers::brush_mask)
            {
            case Checkers::white_field:
                painter->setBrush(light);
                break;

            case Checkers::selected_field:
                painter->setBrush(selected);
                break;

            case Checkers::black_empty_field:
                painter->setBrush(dark);
            }

            // Рисуем прямоугольник клетки
            painter->drawRect(WGap + i*Ceil, HGap + k*Ceil, Ceil, Ceil);

            // Для занятых клеток дополнительно отрисовываем шашку
            if (type & Checkers::occupied_field)
            {
                // Выбираем кисть для рисования шашки
                // для этого снова накладываем на свойство маску
                // и по полученному значению делаем выбор
                if (type & Checkers::white_checker)
                {
                    painter->setBrush(white);
                }
                else
                {
                    painter->setBrush(black);
                }

                // Различные участки для рисования простой шашки и дамки
                if (type & Checkers::dame)
                {
                    // Дамка:
                    // Нижний круг
                    painter->drawEllipse(WGap + i*Ceil + delta1, HGap + k*Ceil + delta1,
                                         Ceil - 2*delta1, Ceil - 2*delta1);
                    // Внешний круг
                    painter->drawEllipse(WGap + i*Ceil + delta1, HGap + k*Ceil,
                                         Ceil - 2*delta1, Ceil - 2*delta1);
                    // Внутренний круг
                    painter->drawEllipse(WGap + i*Ceil + delta2, HGap + k*Ceil + delta2 - delta1,
                                         Ceil - 2*delta2, Ceil - 2*delta2);
                }
                else
                {
                    // Простая шашка:
                    // Внешний круг
                    painter->drawEllipse(WGap + i*Ceil + delta1, HGap + k*Ceil + delta1,
                                         Ceil - 2*delta1, Ceil - 2*delta1);
                    // Внутренний круг
                    painter->drawEllipse(WGap + i*Ceil + delta2, HGap + k*Ceil + delta2,
                                         Ceil - 2*delta2, Ceil - 2*delta2);
                }

                // Убитую, но еще не снятую с доски шашку дополнительно перечеркнем
                if (type & Checkers::bited_checker)
                {
                    painter->drawLine(WGap + i*Ceil + delta1, HGap + k*Ceil + delta1,
                                      WGap + (i+1)*Ceil - delta1, HGap + (k+1)*Ceil - delta1);
                    painter->drawLine(WGap + i*Ceil + delta1, HGap + (k+1)*Ceil - delta1,
                                      WGap + (i+1)*Ceil - delta1, HGap + k*Ceil + delta1);
                }
            }
        }
    }

    // Вывод надписи, полученной от логики игры
    painter->drawText(FONT_SZ, FONT_SZ, checkers->getMessage());
}

// Обработчик события мыши - реакция на действия пользователя
//---------------------------------------------------------------
void chessWidget::mousePressEvent(QMouseEvent * me)
{
    // Переводим координаты мыши в логические координаты клеток
    // Если клик не попадает в доску - сразу выходим
    int X = (me->pos().x() - WGap) / Ceil;
    if ((X < 0) || (X > 7)) return;
    int Y = (me->pos().y() - HGap) / Ceil;
    if ((Y < 0) || (Y > 7)) return;

    // Передаем клик на обработку в объект логики игры
    checkers->click(X, Y);

    // Виджет должен перерисоваться, чтобы увидеть результат
    update();
}


