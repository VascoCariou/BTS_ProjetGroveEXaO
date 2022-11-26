/** @brief Description rapide de MaClasse
*
* Description détaillée de MaClasse.
*
* @test Voir la [procédure de test](chemin/NomFicheDeTest).
* @see AutreClasse
*/




#ifndef F_VISUALISERLESVALEURS_H
#define F_VISUALISERLESVALEURS_H

class F_VisualiserLesValeurs ;

#include <QWidget>
#include <QTime>
// Pour l'affichage de l'historique
#include <QListWidgetItem>
#include <QListWidget>

#include "Arduino.h"
#include "F_Principale.h"

namespace Ui
{
class F_VisualiserLesValeurs;
}

class F_VisualiserLesValeurs : public QWidget
{
    Q_OBJECT

public:
        F_VisualiserLesValeurs(Arduino *oArduino , QString Nom = ("") ,QString unitee = ("") ,QString Port = ("")  , QWidget *parent = nullptr);
        ~F_VisualiserLesValeurs();

        //Méthode Métier
        void    SauvegardeHistorique        (double Valeur);
        bool    ModeAcquisition             ();
        int     ChoisirIntervalleAcquisition();
        QTime   ChoisirTempsAcquisition     ();

        void Set_CopierVecteurHistorique (QVector <QString> &tTabExportationHistorique);

public slots:
        void    on_BtLancerAcquisition_clicked  ();
        void    LancerAcquisition           ();

private slots:
        void on_BtMode_clicked();
        void AfficherValeur     (QString     sPort, double ValeurAAfficher);

private:
        //Attributs

        Ui::F_VisualiserLesValeurs *ui;
        bool        Mode;
        bool        acquistionLance ;
        bool        TempsDefini ;
        bool        HeureFinDefini;
        int         intervalleAcquisition;
        float       MesureAffiche;
        QString Port;
        QListWidgetItem *Historique;
        QVector <F_VisualiserLesValeurs *> TListFenetre;
        QVector <QString>     tTabExportation;

        QDateTime   DateAutomatique;
        QTime       DebutAcquisition;
        QTime       HeureFin;
        QTimer      *timer ;
        int       HeureDerniereMesure ;
        Arduino     *oArduino;
};

#endif // F_VISUALISERLESVALEURS_H

