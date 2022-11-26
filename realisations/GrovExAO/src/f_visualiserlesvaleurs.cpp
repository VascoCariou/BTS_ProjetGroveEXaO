//------------------------------------------------------------------------------
/** @file Arduino.cpp
*
* @brief Paramétrage et lancement d'une acquisition de valeur
*
* @author CHARRON Dylan
* @author BTS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
* @since 2022-02-02
* @version 2.0
* @date 2022-05-24
*
*
* Fabrication GrovExAO.pro
*
* @bug Deux valeurs s'affiche en même temps dans l'historique.
* @bug Le mode automatique fait planter le programme
*/
//------------------------------------------------------------------------------

#include <QCloseEvent>

#include "f_visualiserlesvaleurs.h"
#include "ui_f_visualiserlesvaleurs.h"
#include "F_Principale.h"
#include "Arduino.h"
#include <QTimer>
#include <QString>

#include <QListWidgetItem>
#include <QListWidget>
#include <QMessageBox>
#include <windows.h>

F_VisualiserLesValeurs::F_VisualiserLesValeurs(Arduino *oArduino, QString Nom,QString unitee, QString Port , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::F_VisualiserLesValeurs)
{
    ui->setupUi(this);

    HeureFinDefini = false;
    TempsDefini = false;
    this->oArduino = oArduino;

    this->Port = Port;

    ui->dateTimeAuto->setMinimumDate(QDate::currentDate());
    ui->dateTimeAuto->setMinimumTime(QTime::currentTime());

    Mode=false;
    ui->BtMode->setText("Manuel");
    ui->dateTimeAuto->setDisabled(true);

    setWindowTitle(Nom+ " Port "+Port);

    Historique = nullptr;

    this->timer = new QTimer (this) ;
    connect (   timer,  SIGNAL(timeout()) ,
                this,   SLOT(LancerAcquisition())) ;
    ui->NomAChanger->setText(Nom+" "+unitee);


    connect (&(static_cast<F_Principale *>(parent)->oArduino), SIGNAL (NouvelleDonneeMesuree(QString, double)),
                                                         this, SLOT   (AfficherValeur(QString, double)));
}

F_VisualiserLesValeurs::~F_VisualiserLesValeurs()
{
    delete ui;
}/** Description détaillée de la méthode LancerAcquisition
*
* @pre l'acquisition soit lancer
*
* @see VerificationSiEcriturePossible() de la classe Arduino
*      EcrireSurLePort() de la classe Arduino
*/
void F_VisualiserLesValeurs::LancerAcquisition()
{
    F_Principale * pPtrFen (nullptr) ;

    pPtrFen = static_cast<F_Principale *>(this->parent()) ;
    QMessageBox msgBox;

    qDebug()<<"Mode Acquistion"<<Mode;

       ui->BtMode->setDisabled(true);
       if (Mode == false)//Mode manuelle
       {
           if ( HeureFinDefini == false)
           {
               /*Choisir le temps total d'acquisition*/
               HeureFin=ChoisirTempsAcquisition();
               qDebug()<<"HeureFin"<<HeureFin;
                HeureFinDefini = true;
           }

            if (QTime::currentTime() <= HeureFin)
            {
                if (this->oArduino->VerificationSiEcriturePossible())
                {
                    this->oArduino -> EcrireSurLePort((this->Port).toStdString().c_str());
                    qDebug() << "fenetre " << this->Port;
                }
                else
                {
                    qDebug() << "Ecriture impossible";
                }
            }
            else
            {
                 qDebug() << "Fin d'experience";
                 msgBox.setText("Expérience terminée"+ Port);
                 msgBox.exec();
                 this->timer -> stop();
            }
       }

       if (Mode == true)//Mode Auto
       {

           DateAutomatique = ui->dateTimeAuto->dateTime();
            qDebug()<<DateAutomatique;
           qDebug()<<"acquistionLance"<<acquistionLance;
            qDebug()<<"HeureFin"<<HeureFin;


            if (QDateTime::currentDateTime() > DateAutomatique)
           {
                if ( HeureFinDefini == false)
                {
                    /*Choisir le temps total d'acquisition*/
                    HeureFin=ChoisirTempsAcquisition();
                    qDebug()<<"HeureFin"<<HeureFin;
                     HeureFinDefini = true;
                }

               if (QTime::currentTime()<=HeureFin)
               {
                   if (this->oArduino->VerificationSiEcriturePossible())
                   {
                       this->oArduino -> EcrireSurLePort((this->Port).toStdString().c_str());
                       qDebug() << "fenetre " << this->Port;
                   }
                   else
                   {
                       qDebug() << "Ecriture impossible";
                   }
               }
               else
               {
                    qDebug() << "Fin d'experience";
                    this->timer -> stop();


                    msgBox.setText("Expérience terminée");
                    msgBox.exec();

               }
           }
       }
}


/** Description détaillée de la méthode on_BtLancerAcquisition_clicked
*
* @pre cliquer sur le bouton lancer l'Acquisition
* @pre les paramètres de l'acquisition on été définis
*
* @see ChoisirTempsAcquisition()
*      ChoisirIntervalleAcquisition()
*/

void F_VisualiserLesValeurs::on_BtLancerAcquisition_clicked()
{


    QString text (ui->BtLancerAcquisition->text());
    /*Si lebouton est en mode Lancer Acquisition*/
    if (text =="Lancer l'Acquisition")
    {
        /*Si les paramètres d'acquisition non pas été défini*/
        if (TempsDefini==false)
        {
            /*Choisir l'intervalle entre deux mesures*/
            intervalleAcquisition = ChoisirIntervalleAcquisition();           
            TempsDefini=true;
        }

        LancerAcquisition();
        /*définition du temps et démarrage du timer*/
        this->timer -> setInterval(intervalleAcquisition);
        this->timer -> start();

        /*définir le texte du bouton a pause*/
        ui->BtLancerAcquisition->setText("pause");

    }
    /*Si lebouton est en mode pause*/

    else
    {
        /*définir le texte du bouton a Lancer l'Acquisition*/

        ui->BtLancerAcquisition->setText("Lancer l'Acquisition");
        /*mettre le timer en pause*/
        this->timer -> stop();
        qDebug()<<"Acquistion en pause";

    }
}
/** Description détaillée de la méthode on_BtMode_clicked
*
* @pre cliquer sur bouton choix du mode
*/
void F_VisualiserLesValeurs::on_BtMode_clicked()
{
    QString text (ui->BtMode->text());

    /*si le texte du bouton est défini sur Manuel*/
    if (text =="Manuel")
    {
        /*définir le mode a true*/
        Mode=true;
        /*définir le texte a automatique*/
        ui->BtMode->setText("Automatique");
        /*activé le champs date et heure de début*/
        ui->dateTimeAuto->setEnabled(true);

    }
    /*si le texte du bouton est défini sur Automatique*/
    else
    {
        /*définir le mode a false*/
        Mode=false;
        /*définir le texte a Manuel*/
        ui->BtMode->setText("Manuel");
        /*désactivé le champs date et heure de début*/
        ui->dateTimeAuto->setDisabled(true);
    }


}


/** Description détaillée de la méthode SauvegardeHistorique
*
* @pre une valeur a été mesurée
* @pre la case historique des valeurs a été cochée
*
* @param double Valeur : Valeur mesuré par la carte Arduino à mettre dans l'historique
*/
void F_VisualiserLesValeurs::SauvegardeHistorique(double Valeur)
{
   QTime Heure;
   QDate Date;
   QString HeureAAfficher;
   QString DateAAfficher;
   QString ValeurAAfficher;
   QString FormatDate ("dd.MM.yyyy");

   F_Principale * pPtrFen (nullptr) ;
   pPtrFen = static_cast<F_Principale *>(this->parent()) ;

   /*Lecture de la date et de l'heure de l'ordinateur*/
   Heure= QTime::currentTime();
   Date = QDate::currentDate();

   /*Convertion de l'heure,la date et de la valeur en QString*/
   HeureAAfficher = Heure.toString();
   DateAAfficher = Date.toString(FormatDate);
   ValeurAAfficher = QString::number(Valeur);
   qDebug()<<"DAte : "<<DateAAfficher<<"Heure : "<<HeureAAfficher;

   /*Affichage des information dans le widget LwHistorique si la case historique est coché et que les seconde de la dernière
    mesure est différente des secondes actuelle*/
   if(ui->CbHistorique->isChecked()&& QTime::currentTime().second()!= HeureDerniereMesure )
   {
    Historique = new QListWidgetItem (DateAAfficher+"   "+HeureAAfficher+"   "+ValeurAAfficher,this->ui->LwHistorique);
   }

   /*stockage des informations de l'historique dans le vecteur  tTabExportation pour l'exportation des valeurs*/
   tTabExportation.push_back(DateAAfficher+","+HeureAAfficher+","+ValeurAAfficher);
}

/** Description détaillée de la méthode AfficherAttributs
*
* @pre l'acquisition soit lancé
* @pre la communication avec le port série soit ouverte
*
* @param[in] QString sPort : Port de la carte arduino de la valeur mesurée
* @param[in] double ValeurAAfficher : valeur a afficher dans l'afficheur
*
* @see SauvegardeHistorique()
*/
void F_VisualiserLesValeurs::AfficherValeur(QString sPort, double ValeurAAfficher)
{

    qDebug() << ValeurAAfficher<< "==========================================>>>>> " <<this ;

/*si le port de la valeur transmise est égale au port associé a la fenêtre*/
    if(this->Port == sPort)
    {
        /*afficher la valeur dans l'afficheur*/
        this->ui->Afficheur->display(ValeurAAfficher);

        /*appel de la méthode sauvegarde historique*/
        SauvegardeHistorique(ValeurAAfficher);


        /*Stockage des seconde de la dernière mesure*/
        HeureDerniereMesure=QTime::currentTime().second() ;
    }

}

/** Description détaillée de la méthode ChoisirTempsAcquisition
*
* @pre Remplire le temps total d'acquisition dans l'IHM
*
* @return Retourne l'heure a laquel l'acquistion devra s'arreter
*/

QTime F_VisualiserLesValeurs::ChoisirTempsAcquisition()
{
    int Heure (0);
    int Minute (0);
    int Seconde (0);
    int SecondeAAjouter (0);
    QTime TempsAcquisitonTotal ;
    QTime HeureDeFin ;

/* Lecture du temps saisi d'en l'IHM */

    TempsAcquisitonTotal=ui->Tte_TempsAcquistion->time();
    if(TempsAcquisitonTotal==QTime(0,0,0))
    {
        QMessageBox msgBox;
        msgBox.setText("Temps d'acquisition non valide");
        msgBox.exec();
    }

/*Stockage des heures, des minutes etr des secondes dans des variable différente */
    Heure = TempsAcquisitonTotal.hour();
    Minute = TempsAcquisitonTotal.minute();
    Seconde = TempsAcquisitonTotal.second();

/*convertion du temps total d'acquisition en seconde*/
    SecondeAAjouter = ((Heure*3600)+(Minute*60)+Seconde);

/*Ajout du temps u temps total d'acquisition en seconde a l'heure actuel de l'ordinateur */
    HeureDeFin = QTime::currentTime().addSecs(SecondeAAjouter);
    qDebug()<<"heure de fin : "<<HeureDeFin;


/*retourne l'heure a laquel l'expéreince devra s'arreter */
    return HeureDeFin;
}

/** Description détaillée de la méthode ChoisirIntervalleAcquisition
*
* @pre Définir un temps dans le champs associé dans l'IHM
*
* @return retourne l'intervalle entre deux mesures en milliseconde
*/
int F_VisualiserLesValeurs::ChoisirIntervalleAcquisition()
{
    int Heure (0);
    int Minute (0);
    int Seconde (0);
    int tempsRetourne (0);
    QTime TempsLue ;

    /*lire le temps saisis de le champ intervalle*/
    TempsLue=ui->Tte_intervalleMesure->time();
    qDebug()<<TempsLue;

    /*séparation des heures, des minutes et des secondes*/
    Heure = TempsLue.hour();
    Minute = TempsLue.minute();
    Seconde = TempsLue.second();

    /*convertion du temps en milliseconde*/
    tempsRetourne = ((Heure*3600)+(Minute*60)+Seconde)*1000;

    return tempsRetourne;
}


void F_VisualiserLesValeurs::Set_CopierVecteurHistorique(QVector<QString> & tTabExportationVisualiserLesValeurs)
{
    tTabExportationVisualiserLesValeurs = this->tTabExportation;
}
