#include "pdfunite.h"
#include <qstring.h>
#include <qlist.h>
#include <qfileinfo.h>
#include <cstdlib>
#include <iostream>

PdfUnite::PdfUnite() {

}

PdfUnite::~PdfUnite() {

}

UnifyState PdfUnite::unifyPdf(QList<QString>& pdfFiles, QString output) {
    std::string save_file = pdf_unite;
    for(QString path : pdfFiles) {
        QFileInfo check_file(path);

        if (check_file.exists() && check_file.isFile()) {
            save_file += path.toStdString() + " ";
        } else {
            return UnifyState::FNF;
        }

    }
    save_file += output.toStdString();
    std::cout << save_file << " " << pdfFiles.size() << std::endl;

    const int status = std::system(save_file.c_str());
    if (status < 0) {
        return UnifyState::ERROR;
    } else {
        if (WIFEXITED(status)) {
            return UnifyState::SUCCESS;
        } else {
            return UnifyState::ERROR;
        }
    }
}
