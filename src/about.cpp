#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

About* About::instance = nullptr;

About* About::open() {
    if(!instance) {
        instance = new About();
        return instance;
    } else {
        return instance;
    }
}

bool About::isAlloc() {
    if(instance) {
        return true;
    } else {
        return false;
    }
}
