// nom.h num.version date de création Développeur
#ifndef F_PRINCIPALE_H
#define F_PRINCIPALE_H

class F_Principale ;

#include <fstream>
#include <QString>
#include <windows.h>
#include <QMainWindow>
#include <QVector>

#include "f_selectionnerlescapteurs.h"
#include "StructCapteur.h"
#include "f_visualiserlesvaleurs.h"
#include "Arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class F_Principale : public QMainWindow
{
            Q_OBJECT

    public:
        F_Principale    (QWidget *parent = nullptr);
        ~F_Principale   ();
        QString sNomFichier;

        void SauverLesParametres(QString sNomFichier, QList <TCapteur> ListeCapteur, std::streamsize nNbreAEcrire);
        void ChargerLesParametres(QString sNomFichier, QList <TCapteur> ListeCapteur, std::streamsize nNbreAEcrire);
        void genererFenetre();
        void NouvelleExperience ();
        friend class F_VisualiserLesValeurs;
        //Liste contenant la strucuture de chaque capteur
        QList <TCapteur> ListeCapteur;

    private slots:
        void on_btChargerExperience_clicked();
        void on_BtSauvegarder_clicked();
        void on_btExporter_clicked();
        void on_btRangerFenetre_clicked();
        void on_btNouvelleExperience_clicked();
        void on_btLancerAcquisition_clicked();

        void on_btCredit_clicked();

private:
        QList <TCapteur> *pListCapteurCharger;
        F_VisualiserLesValeurs *PetiteFenetre;
        Ui::MainWindow *ui;
        QVector<F_VisualiserLesValeurs *>    TFenetre;
        QString                              CheminDesCapteurs ;
        TCapteur                             RemplissageList;

        F_SelectionnerLesCapteurs *SelectionCapteur;

        Arduino oArduino;

        QVector <QString>     tTabExportation;

//        QList <F_VisualiserLesValeurs> ListeFenetre  ;
};
#endif // F_PRINCIPALE_H
