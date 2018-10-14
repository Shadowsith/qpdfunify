#ifndef PDFUNITE_H
#define PDFUNITE_H

#include <QList>

enum UnifyState {
    SUCCESS = 0,
    FNF,
    ERROR,
};

class PdfUnite {

private:
    const std::string pdf_unite = "pdfunite ";

public:
    PdfUnite();
    ~PdfUnite();

    UnifyState unifyPdf(QList<QString>& pdfFiles, QString output);
};

#endif // PDFUNITE_H
