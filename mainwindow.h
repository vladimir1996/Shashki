#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "checkers.h"   // ������������ ���� ��� ������� ������ ����������

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);   // �����������
    ~MainWindow();                              // ����������
    
private slots:
    void on_newGame_triggered();    // ����� ��� ��������� ������� ����
    void on_exit_triggered();
    void on_about_triggered();

private:
    Ui::MainWindow *ui;
    Checkers* checkers;     // ���� ��� ������� ������ ����������
};

#endif // MAINWINDOW_H
