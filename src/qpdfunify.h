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

#ifndef QPDFUNIFY_H
#define QPDFUNIFY_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "pdfunite.h"
#include "about.h"

namespace Ui {
class QPdfUnify;
}

class QPdfUnify : public QMainWindow
{
    Q_OBJECT

public:
    explicit QPdfUnify(QWidget *parent = nullptr);
    ~QPdfUnify();

protected:
    void addNewFileEntry();
    void adjustWindow(int window_growth);
    void createUnifiedPdf();
    void resizeEvent(QResizeEvent* event);
    void openAbout();
    void openWithDefaultApp();
    void saveOutput();
    void showUnifyStatus(UnifyState state);

private:
    Ui::QPdfUnify *ui;
    PdfUnite unifier;
    About* info;

    struct PdfInput {
      QLabel* lbl;
      QLineEdit* le;
      QPushButton* btn;
    };

    void connectButtons();
    void connectMenu();

    void addInputLines(QLabel* lbl, QLineEdit* le, QPushButton* btn);
    void connectOpenPdf(QPushButton* btn, QLineEdit* le);
    QList<PdfInput> m_entryList;

    int m_pdfEntries = 2;
};

#endif // QPDFUNIFY_H
