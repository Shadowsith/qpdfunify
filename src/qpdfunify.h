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
