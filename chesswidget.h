#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "checkers.h"

class chessWidget : public QWidget
{
    Q_OBJECT

public:
    //-- ��������� ������ - ������� ��������� ������
    //-------------------------------------------------------------------------------------
    // �����������
    explicit chessWidget(QWidget *parent = 0);

    // � ���� ��������� ����������� ��� ��������� �������
    // ��� ���������� �� ������� ���������
    void draw( QPainter  *painter);

    // ���������� �������� ��� ��������� ���� (������)
    // ���� checkers ������� ����� ������������
    // ������ ��������� ������ ��� ��������
    void setCheckers(Checkers * checkers)
    {
        this->checkers = checkers;
    }

protected:
    //-- ���������������� ������ - ��������� ������ �������
    //-------------------------------------------------------------------------------------

    // ���������� ������� ��������� - ����������� ������� �������
    void paintEvent(QPaintEvent *event);

    // ���������� ������� ���� - ������� �� �������� ������������
    void mousePressEvent(QMouseEvent *);

private:
    //-- �������� ���� � ��������� - ���������� ��������� �������
    //-------------------------------------------------------------------------------------

    static const int FONT_SZ = 32;  // ������ � ��������, ��������� �� ������

    // �����, ������������ ��� ��������� ��������� ��������� ����������
    QBrush dark;        // ��� ������ ������
    QBrush light;       // ��� ����� ������
    QBrush selected;    // ��� ��������� ������
    QBrush black;       // ��� ������ �����
    QBrush white;       // ��� ����� �����

    // ������� ��������� ��������� ��������� ����������
    int WGap;           // ������ ����� �� ���� ������� �� �����
    int HGap;           // ������ ������ �� ���� ������� �� �����
    int Ceil;           // ������ ������ �����

    // ��������� �� ������ ������ ����
    Checkers * checkers;

signals:
    
public slots:
    
};

#endif // CHESSWIDGET_H
