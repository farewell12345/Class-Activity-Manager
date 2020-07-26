#include "change_widget.h"

change_widget::change_widget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500,150);
    font.setPixelSize(18);
    font.setBold(true);
    init_edit(ID);
    init_edit(name);
    init_edit(sex);
    ID.move(200,30);
    name.move(200,65);
    sex.move(200,95);
}
void change_widget::init_edit(QLineEdit &p)
{
    p.setFont(font);
    p.setParent(this);
    p.setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;font-size:20px");
    p.resize(80,30);
}
