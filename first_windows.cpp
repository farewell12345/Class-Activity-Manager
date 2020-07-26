#include "first_windows.h"
#include"QApplication"
#include<QByteArray>
#include<QJsonDocument>
#include<QJsonArray>
#include <QStringListModel>
#include <QStandardItemModel>
#include<QJsonObject>
#include<QFile>
#include<QDebug>
#include <QString>
#include"student.h"
#include<QException>
#include<QMessageBox>
#include<change_student.h>
#include<error.h>
#include<widget.h>
#include<QMouseEvent>
#include<QDateTime>
#include"password_set.h"
using namespace std;
first_windows::first_windows(QWidget *parent) : QMainWindow(parent)
{
    DIY_palette.setColor(QPalette::Background, QColor(192,253,123,50));
    menu_right=new QListWidget(this);
    change=new Change_student;
    this->setAutoFillBackground(true);
    QPalette palette;
    QImage backgroud(":/new/p/0.jpg");
    QImage fitImage=backgroud.scaled(1600,900,Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Window,QBrush(fitImage));
    this->setPalette(palette);
    font.setPixelSize(16);
    qlistView=new QListWidget(this);
    qlistView->setStyleSheet("background-color:rgba(244,244,244,0.8)");
    menu_right->setPalette(palette);
    set_list_Onclick();
    this->setWindowTitle("班级");
    this->setFixedSize(1600,900);
    font.setPixelSize(23);
    font.setFamily("_GB2312 KaiTi_GB2312");
    menu_right->setFont(font);
    font.setPixelSize(18);
    menu_right->resize(1600,50);
    menu_right->move(0,0);
    menu_right->setWindowFlags(Qt::WindowStaysOnTopHint);
    menu_right->setFlow(QListWidget::LeftToRight);
    qlistView->move(1300,50);
    qlistView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlistView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menu_right->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menu_right->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menu_right->setFrameShape(QListWidget::NoFrame);
}
void first_windows::init_menu() {
    menu_right->setStyleSheet("QListWidget{border:1px solid gray; color:black; }"
                              "QListWidget::Item:hover{border-image: url(:/new/p/button_img.png) 0 0 0 0;border:none;color:rgba(255, 255, 255,1);}"
                              "QListWidget::item:selected{border-image: url(:/btn_img.png) 0 0 0 0;border:none;color:rgba(255, 255, 255,1);}"
                              "QListWidget::item:selected:!active{border-width:1px; background-color:rgba(244,244,244,0.5); }"
                              );
    QPalette pll=menu_right->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(255,255,255)));
    menu_right->setPalette(pll);
    QListWidgetItem*item=init_item();
    read_class();
    item->setText(this_class.class_name+"班\n"+"人数："+QString::number( Students.size()));
    item=init_item();
    item->setText("首页");
    item=init_item();
    item->setText("新建活动"); item=init_item();
    item->setText("抽取成员");
    connect(this->menu_right,&QListWidget::itemClicked,this,&first_windows::menu_onclick);
}
QListWidgetItem *first_windows::init_item()
{
    QListWidgetItem*item=new QListWidgetItem;
    item->setSizeHint(QSize(200,50));
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    menu_right->addItem(item);
    QPixmap pixmap(":/new/p/item_img.png");
    item->setBackground(QBrush(pixmap));
    return item;
}
void first_windows::set_students(QString &p)
{
    this->no_md=p;
    this->class_num=PassWord_set::encrypt( p);
    QFile js(Widget::path+class_num+"students.json");
    if(js.open(QIODevice::ReadOnly | QIODevice::Text))//读取文件到STudents列表里
    {
        QByteArray data=js.readAll();
        QJsonDocument jsonD(QJsonDocument::fromJson(data));
        if(jsonD.isObject())
        {
            QJsonObject job=jsonD.object();
            QJsonArray arr=job.value("students").toArray();
            if(!jsonD.isEmpty())
            {
                Student *temp;
                for (int i=0;i<arr.size();i++) {
                    if(arr[i].isObject())
                    {
                        //成功读出！
                        temp=new Student();
                        QJsonObject t=arr[i].toObject();
                        temp->ID=t.value("id").toString();
                        temp->name=t.value("name").toString();
                        temp->sex=t.value("sex").toString();
                        Students.append(temp);
                    }
                }
            }else {
                qDebug()<<"1出错啦！！";
            }
        }else {
            qDebug()<<"2出错啦！！";
        }
    }
    QStringList data;
    for (int i =0 ;i<Students.size();i++) {
        if(Students[i]->sex!=nullptr){
        data<<Students[i]->ID+"\t"+Students[i]->name+"("+Students[i]->sex+")";
        }else {
            data<<Students[i]->ID+"\t"+Students[i]->name;
        }
    }
    qlistView->addItems(data);
    qlistView->setFont(font);
    qlistView->setLineWidth(50);
    qlistView->setFixedSize(300,850);
    for (int i=0;i<qlistView->count();i++) {
        QListWidgetItem *p=qlistView->item(i);
        p->setSizeHint(QSize(60,30));
    }
    for (int i=0;i<3;i++) {
        init_PW(i);
    }
    js.close();
    init_menu();
    read_class();
    init_first();
    init_second();
    init_third();
    PW[1]->hide();
    PW[2]->hide();
}
void first_windows::read_class()
{
    QFile jss(Widget::path+class_num+".json");
    if(jss.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray datas=jss.readAll();
        QJsonDocument jsonDs(QJsonDocument::fromJson(datas));
        if(jsonDs.isObject())
        {
            QJsonObject jobs=jsonDs.object();
            this_class.class_name=this->no_md;
            this_class.class_num=jobs.value("StudentNum").toInt();
            this_class.root=jobs.value("root").toString();
            this_class.PassWord=jobs.value("Password").toString();
        }else {
            qDebug()<<"出错啦！！";
        }
    }
    jss.close();
}
void first_windows::set_list_Onclick()
{
    qlistView->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    menu_right->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    popMenu=new QMenu(this);

    delet =new QAction("删除",this);
    Change=new QAction("修改信息",this);
    Add=new QAction("添加",this);
    popMenu->addAction(Add);
    popMenu->addAction(delet);
    popMenu->addAction(Change);
    connect(&change->ok,&QPushButton::released,this,&first_windows::get_index);
    connect(this->qlistView,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(onMenuRequested(const QPoint &)));
    connect(this->delet,SIGNAL(triggered()),this,SLOT(delete_Students()));
    connect(this->Change,SIGNAL(triggered()),this,SLOT(Change_Students()));
    connect(this->Add,SIGNAL(triggered()),this,SLOT(add_Students()));

}
void first_windows::set_meet_menu(const QPoint &pos)
{
    meet_menu->exec(QCursor::pos());
}
void first_windows::onMenuRequested(const QPoint &pos)
{

    popMenu->exec(QCursor::pos());
}
void first_windows::delete_Students()
{
    QList<QListWidgetItem*> items=this->qlistView->selectedItems();//获取当前选中item
    if(items.count()>0)
    {
        if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("删除"),
                                                      QStringLiteral("确定删除这个成员的所有信息吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes))
        {
            foreach(QListWidgetItem* v,items)
            {
                Students.removeAt(qlistView->currentRow());
                qlistView->removeItemWidget(v);
                items.removeOne(v);
                --this_class.class_num;
                save();
                menu_right->clear();
                init_menu();
                delete v;
            }
        }
    }
}
void first_windows::save()
{
    QFile js(Widget::path+class_num+"students.json");
    if(js.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonArray qjsonArray;
        QJsonObject obj;
        foreach(Student* st,Students)
        {
            QJsonObject qb;
            qb.insert("id",st->ID);
            qb.insert("sex",st->sex);
            qb.insert("name",st->name);
            qjsonArray.append(qb);
        }
        obj.insert("students",qjsonArray);
        QJsonDocument QsD;
        QsD.setObject(obj);
        js.write(QsD.toJson());
        js.close();
    }
    save_class();
}
first_windows::~first_windows()
{
}
void first_windows::Change_Students()
{
    QList<QListWidgetItem*> items=this->qlistView->selectedItems();//获取当前选中item

    if(items.count()>0)
    {
        if(Students[qlistView->currentRow()]->name==nullptr)
        {
            change->setWindowTitle("修改学生信息");
        }else{
            change->setWindowTitle(Students[qlistView->currentRow()]->name);
        }
        change->ID.setText(Students[qlistView->currentRow()]->ID);
        change->name.setText(Students[qlistView->currentRow()]->name);
        change->sex.setText(Students[qlistView->currentRow()]->sex);
        if(change->sex.text()==nullptr)
        {
            change->sex.setPlaceholderText("请输入“男”或者“女”");
        }
        change->show();
        now_item=qlistView->currentRow();
    }
}
void first_windows::menu_onclick()
{
    QList<QListWidgetItem*> items=this->menu_right->selectedItems();//获取当前选中item
    if(items.count()>=0)
    {
        int position=menu_right->currentRow();
        switch (position) {
        case 1:
            this->PW[1]->hide();
            this->PW[2]->hide();
            this->PW[0]->show();
            break;
        case 2:
            this->PW[0]->hide();
            this->PW[2]->hide();
            this->PW[1]->show();
            break;
        case 3:
            this->PW[0]->hide();
            this->PW[1]->hide();
            this->PW[2]->show();
            break;
        }
    }
}
void first_windows::init_PW(int i)
{
    PW[i]=new primeWidget;
    PW[i]->setParent(this);
    PW[i]->move(0,50);
    PW[i]->setFont(font);
}
void first_windows::save_class()
{
    QFile jss(Widget::path+class_num+".json");
    QJsonObject obj;
    if(jss.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"准备写入";
        obj.insert("className",this_class.class_name);
        obj.insert("StudentNum",Students.size());
        obj.insert("root",this_class.root);
        obj.insert("Password",this_class.PassWord);
        QJsonDocument jd;
        jd.setObject(obj);
        jss.write(jd.toJson());
        jss.close();
    }
}
void first_windows::add_Students()
{
    add=new Change_student;
    add->sex.setPlaceholderText("输入性别“男”或”女“");
    QList<QListWidgetItem*> items=this->qlistView->selectedItems();
    //获取当前选中item
    if(items.count()>0)
    {
        add->setWindowTitle("添加成员");
        add->show();
        connect(&add->ok,&QPushButton::released,this,&first_windows::get_add_students);
    }
}
void first_windows::get_add_students()
{
    Student *t=new Student;
    t->ID=add->ID.text();
    if(t->ID==nullptr)
    {
        if(QMessageBox::Yes==QMessageBox::question(add,QStringLiteral("error"),
                                                      QStringLiteral("请输入学生ID"),QMessageBox::Yes,QMessageBox::Yes))
        {
        }
        return;
    }else {
        foreach(Student *s,Students)
        {
            if(s->ID==t->ID)
            {
                if(QMessageBox::Yes==QMessageBox::question(add,QStringLiteral("error"),
                                                              QStringLiteral("此ID已存在"),QMessageBox::Yes,QMessageBox::Yes))
                {
                }
                return;
            }
        }
    }
    t->name=add->name.text();
    t->sex=add->sex.text();
    if(t->sex!="男"&&t->sex!="女")
    {
        if(QMessageBox::Yes==QMessageBox::question(add,QStringLiteral("error"),
                                                      QStringLiteral("请正确输入性别"),QMessageBox::Yes,QMessageBox::Yes))
        {
        }
        return;
    }
    int i= qlistView->currentRow();
    Students.insert(i,t);
    QListWidgetItem *p=new QListWidgetItem;
    if(t->sex!=nullptr){
        p->setText(Students[i]->ID+"\t"+Students[i]->name+"("+Students[i]->sex+")");
    }else {
        p->setText(Students[i]->ID+"\t"+Students[i]->name);
    }
    qlistView->insertItem(i,p);
    save();
    menu_right->clear();
    init_menu();
    add->close();
}
void first_windows::get_index()
{
    Students[now_item]->ID=change->ID.text();
    Students[now_item]->name=change->name.text();
    Students[now_item]->sex=change->sex.text();
    if(change->sex.text()=="男" || change->sex.text()=="女")
    {
        QListWidgetItem* item=qlistView->item(now_item);
        if(Students[now_item]->sex!=nullptr)
        {
                item->setText(Students[now_item]->ID+"\t"+Students[now_item]->name+"("+Students[now_item]->sex+")");
        }else{
            item->setText(Students[now_item]->ID+"\t"+Students[now_item]->name);

        }
        save();
        change->close();
    }else {
        if(QMessageBox::Yes==QMessageBox::question(change,QStringLiteral("error"),
                                                      QStringLiteral("请正确输入性别!（输入男或女）"),QMessageBox::Yes,QMessageBox::Yes))
        {}
        return;
    }
}
void first_windows::init_edit(QLineEdit &p)
{
    p.setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-size:20px");
    p.resize(500,50);
    p.show();
}
void first_windows::init_button(QPushButton &p)
{
    font.setPixelSize(30);
    p.setFixedSize(250,50);
    p.setFont(font);
    p.setStyleSheet("QPushButton{border-image: url(:/new/p/button_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}"
                    "QPushButton:hover{border-image: url(:/btn_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}"
                    "QPushButton:hover{border-image: url(:/btn_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}");
    font.setPixelSize(20);
}
void first_windows::init_first()
{
    meet_list=new QListWidget(PW[0]);
    meet_list->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    meet_list->setStyleSheet("background-color:rgba(244,244,244,0.65)");
    meet_menu=new QMenu(this);
    deletemeet=new QAction("删除",this);
    meet_menu->addAction(deletemeet);
    connect(this->meet_list,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(set_meet_menu(const QPoint &)));
    connect(deletemeet,SIGNAL(triggered()),this,SLOT(delete_meet()));
    PW[0]->setAutoFillBackground(true);
    QPalette palette;
    QImage backgroud(":/new/p/background.png");
    QImage fitImage=backgroud.scaled(PW[0]->width(),PW[0]->height(),Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Window,QBrush(fitImage));
    PW[0]->setPalette(palette);
    PW[0]->temp[0].setText(this_class.class_name+"班活动记录");
    font.setPixelSize(60);
    font.setFamily("华文彩云");
    PW[0]->temp[0].setStyleSheet("color:#ffffff;");
    PW[0]->temp[0].setFont(font);
    font.setFamily("楷体");
    font.setPixelSize(16);
    PW[0]->temp[0].move(400,50);
    meet_list->setFont(font);
    meet_list->setFixedSize(950,630);
    meet_list->move(170,150);
    read_meet();
}
void first_windows::delete_meet()
{
    QList<QListWidgetItem*> items=this->meet_list->selectedItems();//获取当前选中item
    if(items.count()>0)
    {
        if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("删除"),
                                                      QStringLiteral("确定删除这个活动记录吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes))
        {
            foreach(QListWidgetItem* v,items)
            {
                meet.removeAt(meet_list->currentRow());
                meet_list->removeItemWidget(v);
                items.removeOne(v);
                save_meet();
                delete v;
            }
        }
    }
}
void first_windows::init_text(QLabel &p)
{
    p.resize(90,50);
    p.setFont(font);
    p.setStyleSheet("background-color:transparent");
}
void first_windows::init_second()
{
    PW[1]->setAutoFillBackground(true);
    QPalette palette;
    QImage backgroud(":/new/p/back2.png");
    QImage fitImage=backgroud.scaled(PW[1]->width(),PW[1]->height(),Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Window,QBrush(fitImage));
    PW[1]->setPalette(palette);
    init_button(PW[1]->creat);
    PW[1]->creat.show();
    init_button(PW[1]->ok);
    init_button(PW[1]->closees);
    connect(&PW[1]->creat,&QPushButton::released,this,&first_windows::create_meet);
    connect(&PW[1]->ok,&QPushButton::released,this,&first_windows::Sign);
    connect(&PW[1]->closees,&QPushButton::released,this,&first_windows::restar_second);

    init_edit(PW[1]->get_meet[0]);
    init_edit(PW[1]->get_meet[1]);
    init_edit(PW[1]->get_meet[2]);
    init_text(PW[1]->temp[4]);
    font.setFamily("华文彩云");
    for (int i=0;i<=5;i++) {
        init_text(PW[1]->temp[i]);
    }
    for (int i=0;i<5;i++) {
        PW[1]->temp[i].setPalette(DIY_palette);
    }
    PW[1]->temp[4].setStyleSheet("color:#ffffff;");
    PW[1]->temp[5].setStyleSheet("color:#ffffff;");
    font.setPixelSize(50);
    PW[1]->temp[4].setFont(font);
    font.setPixelSize(16);
    font.setFamily("楷体");
    PW[1]->get_meet[0].move(350,250);
    PW[1]->get_meet[1].move(350,310);
    PW[1]->get_meet[2].move(350,370);
    qDebug()<<"ok1";

    PW[1]->creat.move(500,450);
    PW[1]->creat.setText("完成");
    PW[1]->temp[0].setText("未签到");

    PW[1]->temp[0].hide();

    PW[1]->temp[1].setText("会议名称:");
    PW[1]->temp[2].setText("主持人:");
    PW[1]->temp[3].setText("参与人数:");
    PW[1]->temp[4].setText("创建活动");
    PW[1]->temp[4].resize(200,50);

    PW[1]->temp[4].move(500,150);
    PW[1]->temp[1].move(260,250);
    PW[1]->temp[2].move(260,310);
    PW[1]->temp[3].move(260,370);
    PW[1]->temp[0].setStyleSheet("color:#ffffff;");
    PW[1]->temp[5].setStyleSheet("color:#ffffff;");
    PW[1]->no_Sign=new QListWidget;
    PW[1]->alredy_Sign=new QListWidget;
    PW[1]->alredy_Sign->setParent(PW[1]);
    PW[1]->alredy_Sign->setFixedSize(400,400);
    PW[1]->alredy_Sign->move(100,400);
    PW[1]->no_Sign->setParent(PW[1]);
    PW[1]->no_Sign->setFixedSize(400,400);
    PW[1]->no_Sign->move(600,400);

    PW[1]->get_meet[3].setPlaceholderText("输入学号进行签到");

    PW[1]->temp[5].hide();
    PW[1]->alredy_Sign->hide();
    PW[1]->no_Sign->hide();
    PW[1]->ok.hide();
    PW[1]->get_meet[3].hide();
}
void first_windows::init_third()
{
    PW[2]->setAutoFillBackground(true);
    PW[2]->setAutoFillBackground(true);
    QPalette palette;
    QImage backgroud(":/new/p/back.png");
    QImage fitImage=backgroud.scaled(PW[2]->width(),PW[2]->height(),Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Window,QBrush(fitImage));
    PW[2]->setPalette(palette);
    init_button(PW[2]->ok);
    init_edit(PW[2]->get_meet[0]);
    init_text(PW[2]->temp[0]);

    PW[2]->temp[0].setText("随机抽取");
    PW[2]->temp[0].setStyleSheet("color:#ffffff;");
    font.setPixelSize(65);
    PW[2]->temp[0].setFont(font);
    PW[2]->temp[0].resize(300,70);
    font.setPixelSize(16);
    PW[2]->temp[0].move(400,100);
    PW[2]->get_meet[0].setPlaceholderText("输入需要抽取的人数");
    PW[2]->get_meet[0].move(400,450);
    PW[2]->get_meet[0].setFixedSize(200,50);

    PW[2]->ok.setText("确定");
    PW[2]->ok.setFixedSize(70,50);
    PW[2]->ok.move(600,450);

    PW[2]->temp[0].show();
    PW[2]->ok.show();

    connect(&PW[2]->ok,&QPushButton::released,this,&first_windows::rand_students);

}
void first_windows::rand_students()
{

    if(isDightStr(PW[2]->get_meet[0].text())&&PW[2]->get_meet[0].text()!=nullptr)
    {
        if(PW[2]->get_meet[0].text().toInt()<Students.size()){
            PW[3]=new primeWidget;
            PW[3]->setFixedSize(300,300);
            PW[3]->alredy_Sign=new QListWidget;
            PW[3]->alredy_Sign->setParent(PW[3]);
            PW[3]->alredy_Sign->setFixedSize(300,300);
            qsrand((unsigned)time(NULL));
            QListWidgetItem *p;
            QList<Student*> temp=Students;
            int num=PW[2]->get_meet[0].text().toInt();
            for (int i =0;i<num;i++) {
                int randn;
                randn=qrand()%temp.size();
                p=new QListWidgetItem;
                p->setText("ID:"+temp[randn]->ID+"\t姓名："+temp[randn]->name);
                PW[3]->alredy_Sign->addItem(p);
                temp.removeAt(randn);
            }
            PW[3]->show();
        }else{
            if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                          QStringLiteral("抽取人数不能多于班级人数！"),QMessageBox::Yes,QMessageBox::Yes))
            {}
        }
    }else{
        if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                      QStringLiteral("请输入数字！"),QMessageBox::Yes,QMessageBox::Yes))
        {}
        return;
    }
}
void first_windows::read_meet()
{
    QFile f(Widget::path+this_class.class_name+"meeting.json");
    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray datas=f.readAll();
        QJsonDocument jsonDs(QJsonDocument::fromJson(datas));
        if(jsonDs.isObject()&&datas!=nullptr)
        {
            meet.clear();
            meet_list->clear();
            QJsonObject job=jsonDs.object();
            QListWidgetItem *p;
            QJsonArray js;
            meeting *mt;
            js=job.value("meet").toArray();
            for (int i= 0;i<js.size();i++) {
                mt=new meeting;
                p=new QListWidgetItem;
                QJsonObject jb=js[i].toObject();
                mt->time=jb.value("时间").toString();
                mt->title=jb.value("主题").toString();
                mt->number=jb.value("人数").toString();
                mt->master=jb.value("主持人").toString();
                mt->already_sign=jb.value("签到人数").toInt();
                meet.append(mt);
                p->setText("会议："+mt->title+"\t\t"+"主持人："+mt->master+"\t参与人数："+QString::number(mt->already_sign)+"/"+mt->number+"\t"+mt->time);
                meet_list->addItem(p);
            }
        }else {
            QListWidgetItem *p=new QListWidgetItem;
            p->setText("暂无活动数据！可以去新建一个哦");
            p->setSizeHint(QSize(160,300));
            p->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            meet_list->addItem(p);
        }
    }else{

    }

}
bool first_windows::isDightStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;//遍历虚幻一个个判断是否为纯数字

    if (*s)//如果s到null了，说明其是纯数字，否则不是纯数字
    { //不是纯数字
        return false;
    }
    else
    { //纯数字
        return true;
    }
}
void first_windows::create_meet()
{
    QString meet_name= PW[1]->get_meet[0].text();
    QString meet_master= PW[1]->get_meet[1].text();
    QString meet_num= PW[1]->get_meet[2].text();

    if(meet_name!=nullptr&&meet_master!=nullptr&&meet_num!=nullptr)
    {
        if(!isDightStr(meet_num))
        {
            if(QMessageBox::Yes==QMessageBox::question(PW[1],QStringLiteral("error"),
                                                          QStringLiteral("参与人数必须是纯数字！"),QMessageBox::Yes,QMessageBox::Yes))
            {}
            return;
        }
    }else {
        if(QMessageBox::Yes==QMessageBox::question(PW[1],QStringLiteral("error"),
                                                      QStringLiteral("请将信息填完整！"),QMessageBox::Yes,QMessageBox::Yes))
        {}
        return;
    }
    meets=new meeting;
    QDateTime time=QDateTime::currentDateTime();
    meets->time=time.toString("yyyy-MM-dd hh:mm:ss");
    meets->title=meet_name;
    meets->number=meet_num;
    meets->master=meet_master;
    meets->no_Sign=this_class.class_num;
    meets->already_sign=0;
    meet.append(meets);

    PW[1]->temp[5].setText("已签到");
    PW[1]->temp[5].move(100,350);
    PW[1]->temp[5].show();
    PW[1]->temp[4].setText("活动签到");
    font.setPixelSize(70);
    PW[1]->temp[4].resize(400,70);
    PW[1]->temp[4].setFont(font);
    font.setPixelSize(16);
    PW[1]->temp[4].move(450,100);
    init_edit(PW[1]->get_meet[3]);

    PW[1]->get_meet[3].resize(350,60);
    PW[1]->get_meet[3].move(350,300);
    PW[1]->get_meet[3].show();

    PW[1]->closees.setFixedSize(120,60);
    PW[1]->closees.move(830,300);
    PW[1]->closees.setText("结束活动");
    PW[1]->closees.show();

    init_button(PW[1]->ok);
    PW[1]->ok.setFixedSize(100,60);
    PW[1]->ok.move(700,300);
    PW[1]->ok.setText("签到");
    PW[1]->ok.show();
    PW[1]->creat.hide();
    for (int i = 0;i<3;i++) {

        PW[1]->get_meet[i].hide();
        PW[1]->temp[i+1].hide();
    }
    PW[1]->temp[0].move(600,350);
    PW[1]->alredy_Sign->show();
    QListWidgetItem *p;
    for (int i = 0;i<Students.size();i++) {
        p=new QListWidgetItem;
        p->setText(Students[i]->ID);
        PW[1]->no_Sign->addItem(p);
    }
    PW[1]->no_Sign->show();
    PW[1]->temp[0].show();
    save_meet();
    read_meet();
}
void first_windows::save_meet()
{
    QFile js(Widget::path+this_class.class_name+"meeting.json");
    if(js.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QJsonArray QJA;
        foreach(meeting *p,meet){
            QJsonObject job;
            job.insert("时间",p->time);
            job.insert("主题",p->title);
            job.insert("人数",p->number);
            job.insert("主持人",p->master);
            job.insert("签到人数",p->already_sign);
            QJA.append(job);
        }
        QJsonObject QJ;
        QJ.insert("meet",QJA);
        QJsonDocument QD;
        QD.setObject(QJ);
        js.write(QD.toJson());
        js.close();
    }
    //写入之后更新首页会议list
}
void first_windows::Sign()
{
    QString student_name=PW[1]->get_meet[3].text();
    try {
        if(student_name==nullptr||!isDightStr(student_name))
        {
            if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                          QStringLiteral("请输入成员学号"),QMessageBox::Yes,QMessageBox::Yes))
            {}
            return;
        }
        for (int i =0;i<PW[1]->no_Sign->count();i++) {
            if(PW[1]->no_Sign->item(i)->text()==student_name)
            {
                QListWidgetItem *p=PW[1]->no_Sign->item(i)->clone();
                PW[1]->alredy_Sign->addItem(p);
                meet[meet.size()-1]->already_sign+=1;
                save_meet();
                read_meet();
                PW[1]->no_Sign->removeItemWidget(PW[1]->no_Sign->item(i)->clone());
                delete PW[1]->no_Sign->item(i);
                PW[1]->get_meet[3].clear();
                return;
            }
        }
        qDebug()<<"emmmm";
        qDebug()<<PW[1]->alredy_Sign->count();
        for (int i = 0;i<PW[1]->alredy_Sign->count();i++) {
            if(PW[1]->alredy_Sign->item(i)->text()==student_name)
            {
                if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                              QStringLiteral("这个成员已签到"),QMessageBox::Yes,QMessageBox::Yes))
                {
                    PW[1]->get_meet[3].clear();
                }
                return;
            }
        }
        if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                      QStringLiteral("没有找到这个成员的信息"),QMessageBox::Yes,QMessageBox::Yes))
        {}
    } catch (exception e) {
        if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                      QStringLiteral("没有找到这个成员的信息"),QMessageBox::Yes,QMessageBox::Yes))
        {}
    }
    return;
}
void first_windows::restar_second()
{
    PW[1]->creat.show();
    PW[1]->get_meet[0].show();
    PW[1]->get_meet[1].show();
    PW[1]->get_meet[2].show();
    PW[1]->temp[0].close();
    PW[1]->temp[5].close();
    for (int i= 1;i<=4;i++) {
        PW[1]->temp[i].show();
        PW[1]->get_meet[i-1].clear();
    }
    PW[1]->closees.close();
    PW[1]->no_Sign->clear();
    PW[1]->alredy_Sign->clear();
    PW[1]->no_Sign->close();
    PW[1]->alredy_Sign->close();
    PW[1]->ok.hide();
    PW[1]->get_meet[3].hide();
}
