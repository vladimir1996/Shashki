#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "checkers.h"   // Заголовочный файл для объекта логики приложения

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);   // Конструктор
    ~MainWindow();                              // Деструктор
    
private slots:
    void on_newGame_triggered();    // Слоты для обработки пунктов меню
    void on_exit_triggered();
    void on_about_triggered();

private:
    Ui::MainWindow *ui;
    Checkers* checkers;     // Поле для объекта логики приложения
};

#endif // MAINWINDOW_H
