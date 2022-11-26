#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <QMdiSubWindow>

#include "F_Principale.h"
#include "StructCapteur.h"

int main(int argc, char *argv[])
{
    QApplication      a(argc, argv);
    QTranslator       translator;

    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString &locale : uiLanguages)                            //QLINQUIST
    {
        const QString baseName = "GrovExAO_" + QLocale(locale).name();

        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }

    F_Principale w;
    QMdiSubWindow F_VisualiserLesValeurs ;
    w.show();

    return a.exec();
}
