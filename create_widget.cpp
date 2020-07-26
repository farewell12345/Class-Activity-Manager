#include "create_widget.h"
#include<QPalette>
#include<QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include<QDir>
#include<QDebug>
#include<QIODevice>
#include"password_set.h"
#include<QMessageBox>
using namespace std;
create_Widget::create_Widget()
{
    this_class=new classes();
    font.setPixelSize(18);
    font.setBold(true);
    this->setWindowTitle("创建班级");
    init_lable(class_name);
    init_lable(Password_name);
    init_lable(root_name);
    init_lable(student_num);
    init_lable(confirm);
    init_pushButton(Sign_OK);
    init_lable(wrong);
    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::red);
    Password.setEchoMode(QLineEdit::Password);
    confirm_Password.setEchoMode(QLineEdit::Password);
    wrong.resize(200,50);
    wrong.setPalette(pal);
    wrong.move(250,10);
    wrong.setVisible(false);

    Sign_OK.setText("完成");
    Sign_OK.move(215,350);
    root_name.setText("管理员账号");
    Password_name.setText("管理员密码");
    student_num.setText("班级人数");
    class_name.setText("班级名称/班级编号");
    confirm.setText("确认密码");
    class_name.move(85,65);
    root_name.move(150,125);
    Password_name.move(150,185);
    confirm.move(170,245);
    student_num.move(170,305);


    init_edit(get_class_name);
    init_edit(root);
    init_edit(Password);
    init_edit(confirm_Password);
    init_edit(get_class_num);
    get_class_name.move(250,50);
    root.move(250,110);
    Password.move(250,170);
    confirm_Password.move(250,230);
    get_class_num.move(250,290);
    connect(&Sign_OK,&QPushButton::released,this,&create_Widget::sign_Ok_onclicked);
}
void create_Widget::init_pushButton(QPushButton &p)
{
    QFont t=font;
    t.setPixelSize(20);
    p.setParent(this);
    p.setFont(t);
    p.resize(200,50);
    p.setStyleSheet("QPushButton{border-image: url(:/new/p/button_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}"
                    "QPushButton:hover{border-image: url(:/btn_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}"
                    "QPushButton:hover{border-image: url(:/btn_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}");
}
bool isDightStr(QString src)
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
void create_Widget::init_lable(QLabel &p)
{
    p.setFont(font);
    p.setParent(this);
}
void create_Widget::init_edit(QLineEdit &p)
{
    p.setFont(font);
    p.setParent(this);
    p.setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-size:20px");
    p.resize(200,50);
}
void create_Widget::sign_Ok_onclicked()
{
    QString password=Password.text();
    QString confirm=confirm_Password.text();
    QString classname=get_class_name.text();
    QString roots=root.text();
    QString classnum=get_class_num.text();
    bool isDight=isDightStr(classnum);
    if(password==confirm && confirm!=nullptr && password!=nullptr && roots!=nullptr && classnum!=nullptr && isDight)
    {
        QString no_md_classname=classname;
        classname=PassWord_set::encrypt(classname);
        roots=PassWord_set::encrypt(roots);
        password=PassWord_set::encrypt( password);
        this_class->class_name=no_md_classname;
        this_class->root=roots;
        this_class->PassWord=password;
        this_class->class_num=classnum.toInt();
        path=QDir::currentPath();
        QDir dir(path);
        if(!dir.exists("data"))
        {
            dir.mkdir(QString::fromLocal8Bit("data"));
        }
        dir.cd("./data");
        path+="/data/";
        QFile files(path+classname+".json");

        if(!files.exists())
        {
            files.open(QIODevice::WriteOnly);
            files.close();
        }else{
            if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                          QStringLiteral("该班级已存在！"),QMessageBox::Yes,QMessageBox::Yes))
            {}
            return;
        }
        if(!files.open(QIODevice::ReadWrite))
        {
            qDebug()<<"File open error";
            return;
        }else {
            qDebug()<<"File class"+classname+" open";
        }
        QJsonObject jsonObject;
        jsonObject.insert("className",classname);
        jsonObject.insert("StudentNum",classnum);
        jsonObject.insert("root",roots);
        jsonObject.insert("Password",password);
        QJsonDocument QD;
        QD.setObject(jsonObject);
        files.write(QD.toJson());
        files.close();

        qDebug()<<"file write!";
        QFile file(path+classname+"students.json");
        if(!file.exists())
        {
            file.open(QIODevice::WriteOnly);
            file.close();
        }
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug()<<"File open error";
        }else {
            qDebug()<<"File class"+classname+" open";
        }
        QJsonArray qjsonArray;
        QJsonObject obj;
        for(int i =0;i<this_class->class_num;i++)
        {
            Student *temp;
            QJsonObject qb;
            temp=new Student(this);
            temp->sex="";
            temp->name="";
            if(i<9){
                temp->ID=this_class->class_name+'0'+QString::number(i+1);
            }else {
                temp->ID=this_class->class_name+QString::number(i+1);
            }
            qb.insert("id",temp->ID);
            qb.insert("sex",temp->sex);
            qb.insert("name",temp->name);
            qjsonArray.append(qb);
        }
        obj.insert("students",qjsonArray);
        QJsonDocument QsD;
        QsD.setObject(obj);
        file.write(QsD.toJson());
        file.close();
        qDebug()<<"write"+file.objectName();
        this->close();
    }else if(password!=confirm){
        wrong.setVisible(true);
        wrong.setText("两次密码输入不一致！");
    }else if (!isDight) {
        wrong.setVisible(true);
        wrong.setText("班级人数必须为数字！");
    }else {
        wrong.setVisible(true);
        wrong.setText("输入有空！");
    }
}
