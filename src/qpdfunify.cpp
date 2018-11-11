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

#include "qpdfunify.h"
#include "ui_qpdfunify.h"
#include "pdfunite.h"
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlist.h>
#include <qrect.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <iostream>
#include <QHash>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QAction>
#include <QDesktopServices>
#include "lib/qdocker/qdocker.h"

QPdfUnify::QPdfUnify(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QPdfUnify)
{
    ui->setupUi(this);

    connectButtons();
    connectMenu();

    this->resize(600, 300);
}

QPdfUnify::~QPdfUnify()
{
    delete ui;
}


void QPdfUnify::connectButtons() {
    connect(ui->btnAdd, &QPushButton::clicked, [=] {
        addNewFileEntry();
    });

    connect(ui->btnUnify, &QPushButton::clicked, [=] {
        createUnifiedPdf();
    });

    connect(ui->btnClose, &QPushButton::clicked, [=] {
        m_entryList.clear();
        QApplication::instance()->exit();
    });

    this->connectOpenPdf(ui->btnFile1, ui->leFile1);
    this->connectOpenPdf(ui->btnFile2, ui->leFile2);

    connect(ui->btnOutput, &QPushButton::clicked, [=] {
        this->saveOutput();
    });
}

void QPdfUnify::connectMenu() {
    connect(ui->actionOpen, &QAction::triggered, [=] {
        this->openWithDefaultApp();
    });

    connect(ui->actionAbout, &QAction::triggered, [=] {
        this->openAbout();
    });
}

void QPdfUnify::addInputLines(QLabel* lbl, QLineEdit* le, QPushButton* btn) {
    PdfInput in;
    in.lbl = lbl;
    in.le = le;
    in.btn = btn;

    m_entryList.append(in);
}

void QPdfUnify::addNewFileEntry() {
    QLabel* fileLabel = new QLabel(ui->tabMerge);
    QLineEdit* filePath = new QLineEdit(ui->tabMerge);
    QPushButton* fileBtn = new QPushButton(ui->tabMerge);
    QDocker qd(14);

    fileLabel->resize(ui->lblFile2->size());
    fileLabel->setText(tr("File")+" "+std::to_string(m_pdfEntries+1).c_str()+":");
    filePath->resize(ui->leFile2->size());
    fileBtn->resize(ui->btnFile2->size());
    fileBtn->setText("...");

    if (m_pdfEntries <= 2) {
        qd.dockBelow(fileLabel, ui->lblFile2, qd.AlignLeft);
        qd.dockBelow(filePath, ui->leFile2, qd.AlignLeft);
        qd.dockBelow(fileBtn, ui->btnFile2, qd.AlignLeft);
    } else {
        qd.dockBelow(fileLabel, m_entryList.last().lbl, qd.AlignLeft);
        qd.dockBelow(filePath, m_entryList.last().le, qd.AlignLeft);
        qd.dockBelow(fileBtn, m_entryList.last().btn, qd.AlignLeft);
    }

    this->connectOpenPdf(fileBtn, filePath);
    addInputLines(fileLabel, filePath, fileBtn);
    m_pdfEntries++;

    fileLabel->show();
    filePath->show();
    fileBtn->show();

    adjustWindow(qd.getDistance());
}

void QPdfUnify::adjustWindow(int adjust) {
    this->resize(this->width(),this->height()+ui->btnOutput->height()+adjust);
    ui->btnOutput->move(ui->btnOutput->x(), ui->btnOutput->y()+ui->btnOutput->height()+adjust);
    ui->lblOutput->move(ui->lblOutput->x(), ui->lblOutput->y()+ui->lblOutput->height()+adjust);
    ui->leOutput->move(ui->leOutput->x(), ui->leOutput->y()+ui->leOutput->height()+adjust);
}

void QPdfUnify::connectOpenPdf(QPushButton* pb, QLineEdit* le) {
    connect(pb, &QPushButton::clicked, [=] {
        QString filePath = QFileDialog::getOpenFileName(this, tr("Select PDF"), QDir::homePath(),
                            tr("Pdf files") + "( *.pdf)");
        QFileInfo finfo(filePath);
        if(finfo.exists() && finfo.isFile()) {
            le->setText(filePath);
        }
    });
}

void QPdfUnify::createUnifiedPdf() {
    QList<QString> str_list;
    str_list.append(ui->leFile1->text());
    str_list.append(ui->leFile2->text());
    for ( PdfInput in : m_entryList) {
        str_list.append(in.le->text());
    }
    if (!ui->leOutput->text().isEmpty() && !ui->leOutput->text().isNull()) {
        showUnifyStatus(unifier.unifyPdf(str_list, ui->leOutput->text()));
    } else {
        QMessageBox::critical(ui->centralWidget, tr("Error"),tr("The output file is empty"));
    }
}

void QPdfUnify::openAbout() {
    info = About::open();
    if(info != nullptr) {
        const int fHeight = info->height();
        const int fWidth = info->width();
        info->setFixedSize(fWidth, fHeight);
        info->show();
    }
}

void QPdfUnify::openWithDefaultApp() {
   QString filePath = QFileDialog::getOpenFileName(this, tr("Open PDF"), QDir::homePath(),
                                                   tr("Pdf files") + "( *.pdf)");
   QFileInfo finfo(filePath);
   if(finfo.exists() && finfo.isFile()) {
      QDesktopServices::openUrl(filePath);
   }
}

void QPdfUnify::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    if(this->width() >= 360) {
        ui->tabWidget->resize(this->width()-ui->tabWidget->x(),
                              this->height()-ui->tabWidget->y()-100);
        int resizeX = 20;
        int resizeY = 40;
        ui->btnFile1->move(this->width()-resizeX-ui->btnFile1->width(),ui->btnFile1->y());
        ui->btnFile2->move(this->width()-resizeX-ui->btnFile2->width(),ui->btnFile2->y());
        ui->btnOutput->move(this->width()-resizeX-ui->btnOutput->width(),ui->btnOutput->y());

        ui->leFile1->resize(ui->btnFile1->x()-ui->leFile1->x()-resizeX, ui->leFile1->height());
        ui->leFile2->resize(ui->btnFile2->x()-ui->leFile2->x()-resizeX, ui->leFile2->height());
        ui->leOutput->resize(ui->btnFile2->x()-ui->leOutput->x()-resizeX, ui->leOutput->height());

        for(PdfInput in : m_entryList) {
            in.btn->move(this->width()-resizeX-in.btn->width(), in.btn->y());
            in.le->resize(in.btn->x()-in.le->x()-resizeX, in.le->height());
        }

        if(this->height()-ui->btnAdd->height()-resizeY >= ui->lblOutput->y()+ui->lblOutput->height()+20)
        {
            ui->btnAdd->move(ui->btnAdd->x(),this->height()-ui->btnAdd->height()-resizeY);
            ui->btnUnify->move(ui->btnUnify->x(),this->height()-ui->btnAdd->height()-resizeY);
            ui->btnClose->move(this->width()-resizeX-ui->btnClose->width(),
                               this->height()-ui->btnAdd->height()-resizeY);
        }
    }
}

void QPdfUnify::saveOutput() {
    QString filePath = QFileDialog::getSaveFileName(
                this, tr("Save File"), QDir::homePath(),
                tr("Pdf files") + " (*.pdf)");
    ui->leOutput->setText(filePath);
}

void QPdfUnify::showUnifyStatus(UnifyState status) {
    QMessageBox msg;
    switch (status) {
    case UnifyState::SUCCESS: {
        msg.information(ui->centralWidget, tr("Success"), tr("The pdfs where successfully unified!"));
        msg.setFixedSize(300, 100);
    } break;
    // TODO make more error state like file permissions
    case UnifyState::ERROR: {
        msg.critical(ui->centralWidget, tr("Error"), tr("Critical Error, PDF files where not unified!"));
        msg.setFixedSize(300, 100);
    } break;
    case UnifyState::FNF: {
        msg.warning(ui->centralWidget, tr("Warning"), tr("One ore more files does not exist!"));
    } break; }
}
