//------------------------------------------------------------------------------
/** @file main.cpp
*
* @brief Programme de mise au point et de test des diverses fonctionnalités.
*
* @author CHARRON Dylan - KANAÏE ATTRIAN Sami - CARIOU Vasco
* @author STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
* @since 2015-02-02
* @version 1.0
* @date 2022-05-24
*
* Description détaillée du fichier
*
* Fabrication GrovExAO.pro
*
* @todo Rien
*
* @bug Aucun
*/
//------------------------------------------------------------------------------
#include <QGraphicsWidget>

#include <windows.h>
#include <iostream>
#include <QString>
#include <fstream>
#include <QVector>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <chrono>
#include <thread>
#include <QInputDialog>

#include "F_Principale.h"
#include "ui_F_Principale.h"
#include "f_selectionnerlescapteurs.h"
#include "f_visualiserlesvaleurs.h"
#include "Arduino.h"

#include <iomanip>
#include <QDir> // Pour avoir la taille du fichier de l'exe

using namespace std ;

F_Principale::F_Principale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) ,
    CheminDesCapteurs ("./release/INI")
{
    ui->setupUi(this);
    oArduino.OuvrirConnection();
    SelectionCapteur = new F_SelectionnerLesCapteurs(&this->ListeCapteur, this);
}

F_Principale::~F_Principale()
{
    delete ui;
}
/** Description détaillée de la méthode genererFenetre
*
* @pre L'utilisateur doit avoir choisi les capteurs
*

**/
void F_Principale::genererFenetre()
{
    int NbreCapteur (0);
    QString Port ;
    QString Nom;
    QString unitee;

   /*lire le nombre de valeurs présente dans la liste*/
    NbreCapteur = ListeCapteur.size();

    oArduino.Set_CopierListeTCapteur(ListeCapteur);

    qDebug()<< "Nombre de capteur " << NbreCapteur;

    /*pour i inférieur a NbreCapteur*/
    for (int i=0; i<NbreCapteur; i++)
    {
        /*lire le Port, le nom et l'unité d'un capteur*/
        Port = ListeCapteur[i].Port;
        Nom  = ListeCapteur[i].Nom;
        unitee = ListeCapteur [i].Unites;
        qDebug()<< Port;
        /*création dynamique d'un objet F_VisualiserLesValeurs*/
        PetiteFenetre = new F_VisualiserLesValeurs (&oArduino,Nom,unitee, Port, this);
        /*Stocker l'objet dans le vecteur TFenetre*/
        TFenetre.push_back( PetiteFenetre );
        /*le définir en tant que sous fenêtre de la zone MDI*/
        ui->mdiArea->addSubWindow(PetiteFenetre);
        /*définir la taille maximale*/
        PetiteFenetre->setMaximumSize(323,370);
        /*afficher la fenêtre*/
        PetiteFenetre->show();


    }
}
//pour fermer TFenetre[i].close();
void F_Principale::on_btChargerExperience_clicked()
{  
    ChargerLesParametres(sNomFichier,ListeCapteur,ListeCapteur.size());

}




void F_Principale::on_btNouvelleExperience_clicked()
{
NouvelleExperience();

}

void F_Principale:: NouvelleExperience ()
{
    SelectionCapteur->RemplirListesCapteurs(CheminDesCapteurs);
    SelectionCapteur->RazListe();
    SelectionCapteur->show();
}


void F_Principale::on_BtSauvegarder_clicked()
{
   SauverLesParametres(sNomFichier,ListeCapteur,ListeCapteur.size());
}

/* Description détaillée de la méthode SauverLesParametres
*
* @pre Le nom du fichier qui sera sauvegarder
* @post
* @param Nom du fichier , la liste des capteurs remplie , et la taille du fichier à remplir
* @param[in]  sNomFichier, ListeCapteur , nNbreAEcrire
* @note Permet de sauvegarder dans un fichier sNomfichier de taille nNbreAEcrire la ListCapteur
* @attention Au nom du fichier
*/
void F_Principale::SauverLesParametres(QString sNomFichier,  QList <TCapteur> ListeCapteur, std::streamsize nNbreAEcrire)
{
    QString sNomRepertoire;
    QFileDialog FDiag ;

    sNomFichier =   FDiag.getSaveFileName(this,
                                          tr("Save File"),
                                          "C:/Users/localw");


    bool                bEcritureOK (false) ;
    char RetourChar ;
    RetourChar='\n';
    QString     Nom;               //Nom du capteur
    QString     Unites;            // Unités renvoyé par le capteur
    QString     FormuleMath;       // Formule utile pour transformer la tension en valeur lisible et compréhensible
    QString     Type;              // Type de port ( Analogique / Numérique / I2C
    QString     Port;
    ofstream::pos_type  nTaille     (0) ;
    ofstream            oFichier    (sNomFichier.toStdString(), ios::binary) ;

 if (oFichier)
 {
     oFichier.clear() ;
     for (int i=0; i<nNbreAEcrire; i++)     //Boucle de sauvegarde
     {
         if (   ((ListeCapteur [i].Nom).isEmpty())==false       )
         {
             Nom = ListeCapteur [i].Nom;
             oFichier.write( Nom.toStdString().c_str(), Nom.size()) ;
         }
         else
         {
             oFichier <<   "0";
         }
         oFichier <<   "\t";

         if (   ((Unites = ListeCapteur [i].Unites).isEmpty())==false       )
         {
             Unites = ListeCapteur [i].Unites;

             for (int i =0 ; i < Unites.size() ; i++ )
                    {
                       qDebug() <<   static_cast<unsigned char>(Unites.toLatin1()[i]) ;
                    }


                    oFichier.write( Unites.toLatin1(), Unites.size()) ;

         }
         else
         {
             oFichier <<   "0";
         }
         oFichier <<   "\t";

         if (   ((FormuleMath=ListeCapteur [i].FormuleMath).isEmpty())==false       )
         {
             FormuleMath=ListeCapteur [i].FormuleMath;
             oFichier.write( FormuleMath.toStdString().c_str(), FormuleMath.size());
         }
         else
         {
             oFichier <<   "0";
         }
         oFichier <<   "\t";

         if (   ((Type=ListeCapteur [i].Type).isEmpty())==false       )
         {
             Type=ListeCapteur [i].Type;
             oFichier.write( Type.toStdString().c_str(), Type.size()) ;
         }
         else
         {
             oFichier <<   "0";
         }

         oFichier <<   "\t";


         if (   ((Port = ListeCapteur[i].Port).isEmpty())==false       )
         {
             Port = ListeCapteur[i].Port;
             oFichier.write( Port.toStdString().c_str(), Port.size()    ) ;
         }
         else
         {
             oFichier <<   "0";
         }

         if (i<nNbreAEcrire-1)
         {
             oFichier <<   RetourChar;         //Retour chario pour différencier plusieur capteurs
         }

    }



//     if((oFichier.rdstate() & ifstream::badbit) == 0)
//     {
//         bEcritureOK = true ;
//     }

     oFichier.close() ;

 }
}
/* Description détaillée de la méthode SauverLesParametres
*
* @pre Le nom du fichier qui sera charger
* @post
* @param Nom du fichier , la liste des capteurs remplie , et la taille du fichier à remplir
* @param[in]  sNomFichier, ListeCapteur , nNbreAEcrire
* @note Permet de charger un fichier sNomfichier de taille nNbreAEcrire la ListCapteur
* @attention Au nom du fichier /!\ Méthode non fonctionnelle
*/
void F_Principale::ChargerLesParametres(QString sNomFichier,  QList <TCapteur> ListeCapteur, std::streamsize nNbreAEcrire)
{



    //--------------------------------------Récuperation de la taille de fichier-----------------------------------
    QList <TCapteur> * PList;
    pListCapteurCharger= &this->ListeCapteur;
    qint64 TailleDeLExe (0); //Int sur 64 bit
    QString Lecture ;
    QFile VariableQFile;
    QString Chemindelexe;
    QString CheminCompletDuFichier;
    char * Tabchar ;
    Chemindelexe =  QFileDialog::getOpenFileName(this, "Choisir l'emplacement de sauvagarde du fichier", "C:/Users/localw/Desktop");
    QDir DossierDeRecherche(Chemindelexe);
    QFileInfo item (Chemindelexe);
    DossierDeRecherche.entryInfoList();
    QStringList Listesdeligne("0");
    QStringList ListesdeparamCapteur("0");
    TCapteur RemplissageListeACharger;
    //QList <TCapteur>::iterator iEmplacement;
    QString         CharactereATrouver ('/')    ;
    QString         PetiteChaine;
    unsigned int    IndiceFinChaine     (0);
    ifstream        oUnFichier ;
    CheminCompletDuFichier = Chemindelexe ;
    qDebug()<< "Chemin avant la suppression du surplus :" <<Chemindelexe;
    IndiceFinChaine = Chemindelexe.lastIndexOf(CharactereATrouver);
    PetiteChaine = Chemindelexe.remove(0,IndiceFinChaine+1);
    qDebug()<< "Chemin après la suppression du surplus :"<<Chemindelexe;
    qDebug()<< "Nom de fichier à charger "<<item.fileName();
    if (item.fileName()==Chemindelexe)
    {
        if(item.size()!=0)
        {
            TailleDeLExe=item.size();
        }

    }
    else
    {
        qDebug()<<"Pas le bon fichier ! ";
    }
//---------------------------------------Chargement du fichier -----------------------------------------------------
    if ( TailleDeLExe>0)
    {
       Tabchar = new char [TailleDeLExe];  // Création dynamique d'un tab de la taille du fichier
       memset(Tabchar,'\0',TailleDeLExe*sizeof(char)) ;
       oUnFichier.open(CheminCompletDuFichier.toStdString(), ios::in);
       oUnFichier.read(Tabchar,TailleDeLExe);
       Lecture = QString::fromLatin1(Tabchar,TailleDeLExe);
       Listesdeligne=Lecture.split(QLatin1Char('\n'));
        for (int i=0;  i<Listesdeligne.size();   i++ ) // Probleme de size
        {
            ListesdeparamCapteur=Listesdeligne[i].split(QLatin1Char('\t'));

            RemplissageListeACharger.Nom=ListesdeparamCapteur[0];
            RemplissageListeACharger.Unites=ListesdeparamCapteur[1];
            RemplissageListeACharger.FormuleMath=ListesdeparamCapteur[2];
            RemplissageListeACharger.Type=ListesdeparamCapteur[3];
            RemplissageListeACharger.Port=ListesdeparamCapteur[4];

            qDebug()<<ListesdeparamCapteur[1];
            pListCapteurCharger->push_back(RemplissageListeACharger);

        }
    }
    // delete Tabchar
    this->genererFenetre();
}

///** Copie du vecteur contenant l'historique des valeurs de f_visualiserlescapteurs vers F_Principale
//* @pre Le vecteur tTabExportationVisualiserLesValeurs est correctemen remplie avec la date et la valeur mesurée
//* @post Le vecteur est bien copié
//* @param[in] tTabExportationVisualiserLesValeurs : Vecteur contenant l'historique la date et la mesure de toutes les mesures faite pendant l'expérience
//* @see F_VisualiserLesValeurs::SauvegardeHistorique
//*/
//void F_Principale::Set_VecteurHistorique(QVector <QString> tTabExportationVisualiserLesValeurs)
//{
//    QVector <QString>::iterator itTabExportation;

//    this->tTabExportation = tTabExportationVisualiserLesValeurs;

//    itTabExportation = tTabExportation.end();
//    qDebug() << *itTabExportation;
//}

/** Création du fichier CSV
* @pre Le mutateur Set_VecteurHistorique à copier le vecteur
* @post La fichier CSV est présent dans le répertoire selectionné et est bien remplie
*/
void F_Principale::on_btExporter_clicked()
{
    fstream MonFlux;
    QString NomFichier;
    QVector <QString>::iterator itTabExportation;
    QString Entete ("Nom,Port,Date de mesure,Heure de Mesure,Mesure,Unite");
    int     NbreCapteur (ListeCapteur.size());
    QFileDialog FDiag ;
    QString     fileName ;

    NomFichier = FDiag.getSaveFileName(this,
                                       tr("Save File"),
                                       "C:/Users/localw");

    MonFlux.open (NomFichier.toStdString(), ios::out);

    MonFlux << Entete.toStdString() << endl;

    for (int i (0) ; i<NbreCapteur ; i++ )
    {
        TFenetre[i] -> Set_CopierVecteurHistorique(tTabExportation);


        for (itTabExportation = this->tTabExportation.begin() ; itTabExportation!=this->tTabExportation.end() ; itTabExportation++)
        {
            MonFlux << ((ListeCapteur[i].Nom).toStdString()) << "," << flush;
            MonFlux << ((ListeCapteur[i].Port).toStdString())<< "," << flush;
            MonFlux << (*itTabExportation).toStdString()<< "," << flush;
            MonFlux << ((ListeCapteur[i].Unites).toStdString())<< endl;

            qDebug() << *itTabExportation;
        }
    }

    MonFlux.close();
}

void F_Principale::on_btRangerFenetre_clicked()
{
    ui->mdiArea->tileSubWindows();
}


void F_Principale::on_btLancerAcquisition_clicked()
{
    int     NbreCapteur (ListeCapteur.size());
    for (int i (0) ; i<NbreCapteur ; i++ )
    {
        TFenetre[i]->on_BtLancerAcquisition_clicked();

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}



void F_Principale::on_btCredit_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Réalisé par \n\rVasco CARIOU\n\rDylan CHARRON\n\rSami KANAIE ATRIAN \n\rBTS SNIR2 2022 \n\rréférant : Sorel William\n\r ");
    msgBox.exec();
}

