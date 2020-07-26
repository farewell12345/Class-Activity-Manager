#ifndef FIRST_WINDOWS_H
#define FIRST_WINDOWS_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QObject>
#include<QString>
#include<classes.h>
#include<QAction>
#include<QMenu>
#include<QListWidget>
#include"student.h"
#include"classes.h"
#include"change_student.h"
#include"primewidget.h"
#include"meeting.h"
class first_windows : public QMainWindow
{
    Q_OBJECT
private:
    QPalette DIY_palette;
    bool isDightStr(QString src);
    classes this_class;
    QListWidgetItem* init_item();
    primeWidget *PW[4];
    void init_first();
    void init_second();
    void init_third();
    QString class_num,no_md;
    meeting *meets;
    QList<meeting*> meet;
public:
    QListWidget *qlistView,*menu_right,*meet_list;
    QStringListModel *Model;
    QStandardItemModel *ItemModel;
    QStringListModel *model;
    explicit first_windows(QWidget *parent = nullptr);
    QMenu *popMenu,*meet_menu;
    QAction *delet,*deletemeet;
    QAction *Change,*Add;
    QList<Student*> Students;
    Change_student *change,*add;
    QFont font;
    int now_item;
    int postion_item(QListWidget &);
    void read_meet();
    void save_meet();
    void set_list_Onclick();
    void save();
    void get_index();
    ~first_windows();
    void init_menu();
    void init_edit(QLineEdit &);
    void init_text(QLabel &);
    void save_class();
    void read_class();
    void init_button(QPushButton &p);
    void init_PW(int i);
signals:void listItemClicked(int);
public slots:
    void rand_students();
    void Sign();
    void restar_second();
    void delete_meet();
    void set_meet_menu(const QPoint &);
    void create_meet();
    void get_add_students();
    void add_Students();
    void menu_onclick();
    void delete_Students();
    void Change_Students();
    void set_students(QString &);
    void onMenuRequested(const QPoint &);
};

#endif // FIRST_WINDOWS_H
