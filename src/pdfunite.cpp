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
