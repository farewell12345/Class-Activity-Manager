#include "change_student.h"
#include "widget.h"
#include"first_windows.h"
Change_student::Change_student(QWidget *parent) : QWidget(parent)
{
    ok.setParent(this);
    font.setPixelSize(20);
    ok.setFont(font);
    ok.resize(150,40);
    ok.setParent(this);
    ok.setText("完成");
    ok.move(200,250);
    font.setPixelSize(16);
    this->setFixedSize(500,300);
    init_edit(ID);
    init_edit(name);
    init_edit(sex);
    ID.move(170,30);
    name.move(170,75);
    sex.move(170,120);
    for (int i =0;i<3;i++) {
        init_title(title[i]);
    }
    title[0].setText("ID:");
    title[1].setText("姓名:");
    title[2].setText("性别:");
    title[0].move(120,40);
    title[1].move(120,85);
    title[2].move(120,130);
}
void Change_student::init_title(QLabel &p)
{
    p.setFont(font);
    p.setParent(this);
}
void Change_student::init_edit(QLineEdit &p)
{
    p.setFont(font);
    p.setParent(this);
    p.setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-size:20px");
    p.resize(200,40);
}
