#include "error.h"
#include<QPushButton>
error::error()
{
    class_name.setParent(this);
    class_user.setParent(this);
    class_num.setParent(this);

    this->setFixedSize(300,150);
    error_text.resize(150,50);
    error_text.move(90,50);

    error_text.setParent(this);
}
