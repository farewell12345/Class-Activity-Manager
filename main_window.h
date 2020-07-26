#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
signals:

};

#endif // MAIN_H
