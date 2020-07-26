#include "primewidget.h"

primeWidget::primeWidget(QWidget *parent) : QWidget(parent)
{
    for (int i = 0;i<10;i++) {
        temp[i].setParent(this);
    }
    for (int i=0;i<4;i++) {
        get_meet[i].setParent(this);
        get_meet[i].hide();
    }
    creat.setParent(this);
    creat.hide();
    ok.setParent(this);
    creat.hide();
    ok.hide();
    closees.setParent(this);
    closees.hide();
    this->setFixedSize(1300,850);
}
