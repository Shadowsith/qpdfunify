/*
Project:     QPdfUnify
Description: A Qt frontend for merge and split pdf files
Author:      Philip Mayer (Shadowsith) <philip.mayer@shadowsith.de>
Copyright:   2018 Philip Mayer
License:     GPLv3+

QPdfUnify is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QPdfUnify is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with QPdfUnify.  If not, see <http://www.gnu.org/licenses/>.
*/

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
