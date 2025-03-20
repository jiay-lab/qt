#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filethread.h"

struct WidgetPrivate;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setFirstMenu();
    void setSecondMenu();
    void setThirdMenu();

    void setTable();

public slots:
    void newPageFunc();
    void handleBtn();
    void handleFileBtn();

private:
    Ui::MainWindow *ui;
    WidgetPrivate *p;
    fileThread *_fileThread=nullptr;
};

#endif // MAINWINDOW_H
