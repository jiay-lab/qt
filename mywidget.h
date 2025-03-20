#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPixmap>


class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e) override;

private:
    QPixmap mp;
};

#endif // MYWIDGET_H
