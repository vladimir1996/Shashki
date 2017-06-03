#include "chesswidget.h"

// �����������
//---------------------------------------------------------------
chessWidget::chessWidget(QWidget *parent) :
    QWidget(parent)
{
    // ������������� ���������� ������� �������
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);

    // ������������� ������������ ������
    dark = QBrush(Qt::darkGray);
    light = QBrush(Qt::white);
    selected = QBrush(Qt::yellow);
    black = QBrush(QColor(60,60,60));
    white = QBrush(Qt::white);

    // ������������� ������������� ������
    QFont fnt = this->font();       // �������� ������������ �����
    fnt.setPointSize(FONT_SZ/2);    // �������� ��� ������
    this->setFont(fnt);             // ������������� ����� �������
}

// ���������� ������� ��������� - ����������� ������� �������
//---------------------------------------------------------------
void chessWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);         // ������� ������ �������
    draw(&painter);                 // �������� ���������
}

// � ���� ��������� ����������� ��� ��������� �������
// ��� ���������� �� ������� ���������
//---------------------------------------------------------------
void chessWidget::draw( QPainter  *painter)
{
    // ������������� ���������� �������
    painter->setRenderHint( QPainter ::Antialiasing, true);

    // ������� ����������� ��������
    int W = this->width();              // ������ ����� � ������ ����
    int H = this->height() - FONT_SZ;   // ������ ���������� �� ������ �������
    int Min = W < H ? W : H;            // ����� ����������� ��������

    Ceil = Min / 9;                     // ������ ������ (� ������� � ���������)
    WGap = (W - 8*Ceil)/2;              // ������������ ������
    HGap = (H - 8*Ceil)/2 + FONT_SZ;    // �������������� ������

    int delta1 = Ceil/8;        // ������� ��� ��������� ����� � ������
    int delta2 = Ceil/4;

    // ���������� ��������� ����, ������ �� �������
    for (int i=0; i<8; i++)             // ������� ���� �� �����������
    {
        for (int k=0; k<8; k++)
        {
            // �������� �������� ������� ������
            int type = checkers->getType(i, k);

            // �������� ����� ��� ��������� ���� ������
            // ��� ����� ����������� �� �������� ������ �����
            // � �� ����������� �������� ������ �����
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

            // ������ ������������� ������
            painter->drawRect(WGap + i*Ceil, HGap + k*Ceil, Ceil, Ceil);

            // ��� ������� ������ ������������� ������������ �����
            if (type & Checkers::occupied_field)
            {
                // �������� ����� ��� ��������� �����
                // ��� ����� ����� ����������� �� �������� �����
                // � �� ����������� �������� ������ �����
                if (type & Checkers::white_checker)
                {
                    painter->setBrush(white);
                }
                else
                {
                    painter->setBrush(black);
                }

                // ��������� ������� ��� ��������� ������� ����� � �����
                if (type & Checkers::dame)
                {
                    // �����:
                    // ������ ����
                    painter->drawEllipse(WGap + i*Ceil + delta1, HGap + k*Ceil + delta1,
                                         Ceil - 2*delta1, Ceil - 2*delta1);
                    // ������� ����
                    painter->drawEllipse(WGap + i*Ceil + delta1, HGap + k*Ceil,
                                         Ceil - 2*delta1, Ceil - 2*delta1);
                    // ���������� ����
                    painter->drawEllipse(WGap + i*Ceil + delta2, HGap + k*Ceil + delta2 - delta1,
                                         Ceil - 2*delta2, Ceil - 2*delta2);
                }
                else
                {
                    // ������� �����:
                    // ������� ����
                    painter->drawEllipse(WGap + i*Ceil + delta1, HGap + k*Ceil + delta1,
                                         Ceil - 2*delta1, Ceil - 2*delta1);
                    // ���������� ����
                    painter->drawEllipse(WGap + i*Ceil + delta2, HGap + k*Ceil + delta2,
                                         Ceil - 2*delta2, Ceil - 2*delta2);
                }

                // ������, �� ��� �� ������ � ����� ����� ������������� �����������
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

    // ����� �������, ���������� �� ������ ����
    painter->drawText(FONT_SZ, FONT_SZ, checkers->getMessage());
}

// ���������� ������� ���� - ������� �� �������� ������������
//---------------------------------------------------------------
void chessWidget::mousePressEvent(QMouseEvent * me)
{
    // ��������� ���������� ���� � ���������� ���������� ������
    // ���� ���� �� �������� � ����� - ����� �������
    int X = (me->pos().x() - WGap) / Ceil;
    if ((X < 0) || (X > 7)) return;
    int Y = (me->pos().y() - HGap) / Ceil;
    if ((Y < 0) || (Y > 7)) return;

    // �������� ���� �� ��������� � ������ ������ ����
    checkers->click(X, Y);

    // ������ ������ ��������������, ����� ������� ���������
    update();
}


