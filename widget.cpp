#include "widget.h"
#include "ui_widget.h"
#include<QFileInfo>
#include<QIODevice>
#include<QJsonDocument>
#include"error.h"
#include<QtDebug>
#include<QJsonParseError>
#include<QJsonObject>
#include"first_windows.h"
#include<QDir>
#include"password_set.h"
#include<QMessageBox>
QString Widget::path=QDir::currentPath()+"/data/";
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(350,400);
    this->setWindowTitle("登录");
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/p/background.png")));
    this->setPalette(palette);
    Init_Sign();
}
void Widget::try_sign(QString classname,QString root,QString password)
{
    no_md=classname;
    classname=PassWord_set::encrypt(classname);
    root=PassWord_set::encrypt(root);
    password=PassWord_set::encrypt(password);
    QFileInfo file(path+classname+".json");
    if(file.exists()==false)
    {
        if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                      QStringLiteral("此班级不存在"),QMessageBox::Yes,QMessageBox::Yes))
        {}
    }else {
        QFile js(path+classname+".json");
        js.open(QIODevice::ReadOnly | QIODevice::Text);
        QString class_index=js.readAll();
        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(class_index.toUtf8(),&parseJsonErr);
        if(!(parseJsonErr.error==QJsonParseError::NoError))
        {
            qDebug()<<"配置错误";
            return;
        }
        QJsonObject jsonObject=document.
                                 object();
        QString root_t=jsonObject.value("root").toString();
        QString password_t=jsonObject.value("Password").toString();
        if(root_t!=root||password!=password_t)
        {
            if(QMessageBox::Yes==QMessageBox::question(this,QStringLiteral("error"),
                                                          QStringLiteral("用户名或密码错误"),QMessageBox::Yes,QMessageBox::Yes))
            {}
            Password.clear();
        }else {
            send_name=classname;
            first=new first_windows();
            connect(this,SIGNAL(__send(QString &)),first,SLOT(set_students(QString &)));
            send();
            first->show();
            this->hide();
            js.close();
        }
    }

}
void Widget::send()
{
    emit __send(this->no_md);
}
void Widget::Sign()
{
    QString className=class_name.text();
    QString roots=root.text();
    QString pass_word=Password.text();
    if(roots==nullptr){
        er_widget.error_text.setText("请输入管理员账号！");
        er_widget.show();
        return;
    }else if (pass_word==nullptr) {
        er_widget.error_text.setText("请输入密码！");
        er_widget.show();
        return;
}
        try_sign(className,roots,pass_word);
}
void Widget::init_edit(QLineEdit &p)
{
    p.setParent(this);
    p.setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-size:20px");
    p.resize(230,50);
}
void Widget::Init_Sign()
{
    CENTER_x=this->height()/4;
    CENTER_y=this->width()/4;
    font.setPixelSize(18);
    font.setBold(true);
    Init_button(SignIn);
    Init_button(sign);
    font.setPixelSize(14);
    SignIn.setFont(font);
    font.setPixelSize(18);
    init_edit(class_name);
    init_edit(root);
    init_edit(Password);
    init_text(classesName);
    init_text(Password_show);
    init_text(User);
    er_widget.error_text.setFont(font);
    classesName.setText("班号");
    Password_show.setText("密码");
    User.setText("账号");
    sign.setText("登录");
    SignIn.setText("创建班级");

    sign.resize(230,40);
    SignIn.resize(90,30);


    User.move(CENTER_x-85,CENTER_y+50);
    root.move(CENTER_x-35,CENTER_y+50);
    class_name.move(CENTER_x-35,CENTER_y-5);
    classesName.move(CENTER_x-85,CENTER_y-5);
    Password.move(CENTER_x-35,CENTER_y+105);
    Password_show.move(CENTER_x-85,CENTER_y+105);

    Password.setEchoMode(QLineEdit::Password);
    sign.move(CENTER_x-35,255);
    SignIn.move(CENTER_x+105,300);
    connect(&SignIn,&QPushButton::released,this,&Widget::create_first_class);
    connect(&sign,&QPushButton::released,this,&Widget::Sign);
}
void Widget::Init_button(QPushButton &p)
{
    font.setPixelSize(20);
    p.setFont(font);
    p.setParent(this);
    p.setStyleSheet("QPushButton{border-image: url(:/new/p/button_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}"
                            "QPushButton:hover{border-image: url(:/btn_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}"
                            "QPushButton:hover{border-image: url(:/btn_img.png) 0 0 0 0;border:none;color:rgb(255, 255, 255);}");
}
void Widget::init_text(QLabel &p)
{
    p.resize(90,50);
    p.setParent(this);
    p.setFont(font);
    p.setStyleSheet("background-color:transparent");
}
void Widget::create_first_class()
{
    sign_widget.resize(600,400);
    sign_widget.show();
}
Widget::~Widget()
{
    delete ui;
}
