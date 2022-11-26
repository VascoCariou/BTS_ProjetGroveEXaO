//------------------------------------------------------------------------------
/** @file main.cpp
*
* @brief Programme de mise au point et de test des diverses fonctionnalités.
*
* @author S. Kanaie Atrian
* @author STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
* @since 2022-01-01
* @version 1.0
* @date 2022-30-03
*
* Description détaillée du fichier
*
* Fichier servant à selectionner les capteurs pour l'utilisateur.
*
* @todo
* Pas possible de lacher quand c'est non compatible
*/
//------------------------------------------------------------------------------
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <iostream>
//Pour le contenant QlistWidget et son contenu QlistwidgetItem
#include <QListWidget>
#include <QListWidgetItem>
//Pour l'utilisation de fonction relatif au fichier ( Ici pour trouver le chemin des fichiers ini)
#include <QDir>
//Pour lire les fichiers ini
#include <QSettings>
//Lien avec les autres fichiers
#include "f_selectionnerlescapteurs.h"
#include "ui_f_selectionnerlescapteurs.h"
#include "StructCapteur.h"
#include "F_Principale.h"
using namespace std;
F_SelectionnerLesCapteurs::F_SelectionnerLesCapteurs(QList <TCapteur> * PList, F_Principale * FenPrinc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::F_SelectionnerLesCapteurs),
    FenPrinc (FenPrinc)
{
    ui->setupUi(this);
    pListCapteurConnecte= PList;
    //QLabel * LabelNumCapteur [35];
    //-----------------------------------Variable pour décrementer ou incrementer la création des labels / listes widgets--------------------
    int k (0);
    int l (0);
    int w (0);
    int D( 0);
    int U (3);
    QString NomLabel;


    // ----------------------------------------------Création des labels associé ---------------------------------------------

    for (int i=0;i<=34;i++)
    {
        LabelNumCapteur [i]=new QLabel (this);

    }
    k=110;
    for (int i=0;i<=4;i++)   //1ere rangée du bas
    {

        LabelNumCapteur [i]->setGeometry(280+k*i,525,100,50);

        LabelNumCapteur [i]->setText("A0"+NomLabel.number(D,10));
        D=D+2;
    }
    for (int i=5;i<=7;i++)   //les 3 derniers de la 1ere rangée du bas
    {

        LabelNumCapteur [i]->setGeometry(280+k*i,525,100,50);

        LabelNumCapteur [i]->setText("A"+NomLabel.number(D,10));
        D=D+2;
    }
    D=1;
    for (int i=8;i<=12;i++)     //2eme rangée du bas
    {
        LabelNumCapteur [i]->setGeometry(280+k*(i-8),600,100,50);

        LabelNumCapteur [i]->setText("A0"+NomLabel.number(D,10));
        D=D+2;

    }
    for (int i=13;i<=15;i++)     //3 derniers de la 2eme rangée du bas
    {
        LabelNumCapteur [i]->setGeometry(280+k*(i-8),600,100,50);

        LabelNumCapteur [i]->setText("A"+NomLabel.number(D,10));
        D=D+2;

    }

    l=80;                       //Rangée I2C Gauche
    for (int i=16;i<=19;i++)
    {
        LabelNumCapteur [i]->setGeometry(280,180+l*(i-16),100,50);
        LabelNumCapteur [i]->setText("UART"+NomLabel.number(U,10));
        U=U-1;

    }
    w=120;
    LabelNumCapteur [20]->setGeometry(280,10,100,50);
    LabelNumCapteur [20]->setText("I2C");
    for (int i=21;i<=22;i++)    //Rangée I2C Haut gauche
    {
    LabelNumCapteur [i]->setGeometry(380+w*(i-21),70,100,50);
    LabelNumCapteur [i]->setText("I2C");
    }
    D=12;
    for (int i=23;i<=24;i++)            // 1 Rangée numérique  haut
    {
        LabelNumCapteur [i]->setGeometry(620+k*(i-23),0,100,50);
        LabelNumCapteur [i]->setText("D"+NomLabel.number(D,10));
        D=D-2;

    }
    for (int i=25;i<=28;i++)            // 4 dernier de la 1 Rangée numérique  haut
    {
        LabelNumCapteur [i]->setGeometry(620+k*(i-23),0,100,50);
        LabelNumCapteur [i]->setText("D0"+NomLabel.number(D,10));
        D=D-2;

    }
    D=13;
    for (int i=29;i<=30;i++)         // 2 Rangée numérique  haut
    {
        LabelNumCapteur [i]->setGeometry(620+k*(i-29),70,100,50);
        LabelNumCapteur [i]->setText("D"+NomLabel.number(D,10));
        D=D-2;
    }
    for (int i=31;i<=34;i++)         // 2 Rangée numérique  haut
    {
        LabelNumCapteur [i]->setGeometry(620+k*(i-29),70,100,50);
        LabelNumCapteur [i]->setText("D0"+NomLabel.number(D,10));
        D=D-2;
    }
    for (int i=0;i<=34;i++)
    {
        LabelNumCapteur [i]->show();
    }
    //------------------------------------------------------------Creation des Listwidgets----------------------------
    for (int i=0;i<=34;i++)
    {
        PtrListBox [i]=new Listboxport (nullptr, this);

    }
    k=110;
    for (int i=0;i<=7;i++)   //1ere rangée du bas
    {

        PtrListBox [i]->setLabel(LabelNumCapteur [i]);
        PtrListBox [i]->setGeometry(280+k*i,560,100,50);

    }
    for (int i=8;i<=15;i++)     //2eme rangée du bas
    {
        PtrListBox [i]->setLabel(LabelNumCapteur [i]);
        PtrListBox [i]->setGeometry(280+k*(i-8),640,100,50);

    }
    l=80;                       //Rangée I2C Gauche
    for (int i=16;i<=19;i++)
    {
        PtrListBox [i]->setLabel(LabelNumCapteur [i]);
        PtrListBox [i]->setGeometry(280,210+l*(i-16),100,50);

    }
    w=120;
    PtrListBox [20]->setLabel(LabelNumCapteur [20]);
    PtrListBox [20]->setGeometry(280,40,100,50);
    for (int i=21;i<=22;i++)    //Rangée I2C Haut gauche
    {
        PtrListBox [i]->setLabel(LabelNumCapteur [i]);
        PtrListBox [i]->setGeometry(380+w*(i-21),100,100,50);
    }
    for (int i=23;i<=28;i++)// 1 Rangée numérique  haut
    {
        PtrListBox [i]->setLabel(LabelNumCapteur [i]);
        PtrListBox [i]->setGeometry(620+k*(i-23),30,100,50);
    }
    for (int i=29;i<=34;i++)        // 2 Rangée numérique  haut
    {
        PtrListBox [i]->setLabel(LabelNumCapteur [i]);
        PtrListBox [i]->setGeometry(620+k*(i-29),100,100,50);
    }

    for (int i=0;i<=34;i++)
    {
        PtrListBox [i]->show();
    }
    ListINI=new Listboxcapteur (nullptr,this);
    ListINI->setGeometry(0,0, 270,680);
    this->ListINI->setIconSize(   QSize(150,150) );
}

F_SelectionnerLesCapteurs::~F_SelectionnerLesCapteurs()
{
    delete ui;
}


/* Description détaillée de la méthode FonctionChemin
*
* @pre Le chemin de départ de la recherche de fichier INI
* @post
* @param Chemin Contenant le chemin de départ
* @param[in] Chemin
* @note Il faut en paramettre le chemin pour acceder au dossier INI et l'image de la grove
* Remplit une liste avec les données écrite dans les fichier INI
* @attention Faire attention où le build est créer c'est à partir de la que le chemin commence
*/
void F_SelectionnerLesCapteurs::RemplirListesCapteurs(QString chemin)
{
        QListWidgetItem* listImg (nullptr) ;
        TCapteur RemplissageListe;
        QDir dir(chemin);
        bool bChargement    (false)
                ;
        bChargement = this->pImage.load(    QString ("./release/Carte_Grove.jpg"),"JPG") ; //Photo Maquette
        this->ui->LbMaquette->setPixmap(this->pImage) ;         // Affichage de la photo de la maquette

        qDebug() << "--------------------- Dossier inspecte : " << chemin ;

        foreach(QFileInfo item, dir.entryInfoList() )
        {
            if(item.isDir())            //Vérification si l'item détecté est un dossier

            {
                if( (item.fileName() != ".") && (item.fileName() != ".."))
                {
                    qDebug() << "Changement pour le dossier: " << item.fileName();
                    RemplirListesCapteurs(item.absoluteFilePath()  );
                }
            }
            if(item.isFile())    //Vérification si l'item détecté est un fichier
            {

                qDebug() << "File: " << item.fileName();             //Remplissage de la liste avec l'aide de la structure
                if (item.completeSuffix() == "ini" )
                {
                    QSettings settings(item.absoluteFilePath() , QSettings::IniFormat);  //précision du format du fichier
                    RemplissageListe.Nom = settings.value("TITRE/Nom").toString();
                    RemplissageListe.Unites = settings.value("SUP/Unit").toString();
                    RemplissageListe.FormuleMath = settings.value("SUP/Expression").toString();
                    RemplissageListe.Type = settings.value("PORT/Type").toString();
                    RemplissageListe.Port = "";
                }
                else
                {
                    if (item.completeSuffix() == ("jpg") ||  ("png") ||  ("jpeg"))   //Detection d'un fichier image
                    {
                        QIcon   oIcone      (item.absoluteFilePath()) ;
                        QFont   oPolice ;

                        listImg = new QListWidgetItem(oIcone,  RemplissageListe.Nom, this->ListINI ); //Creation du Widget avec listes des capteurs
                        oPolice = listImg->font() ;         //Gestion de la police
                        oPolice.setPointSize(14) ;
                        listImg->setFont(oPolice) ;
                        listImg->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
                    }
                    else
                    {
                        qDebug() << "PAS COMPATIBLE !";
                    }
                }
            }
            this->ListeCapteursDisponibles.push_back(RemplissageListe);
            qDebug()<<RemplissageListe.Nom<<"------Port : "<<RemplissageListe.Port;
        }
}

/* Description détaillée de la méthode ValiderMaquette_clicked
*
* @pre Appuie du bouton sur l'interface graphique
* @note Remplit la liste transmise aux autre classe avec cette fois si le numéro du port
*/
void F_SelectionnerLesCapteurs::on_ValiderMaquette_clicked()
{
    TCapteur RemplissageListeAEnvoyer;
    QList <TCapteur>::iterator iEmplacement;
    for (int i=0;i<=34;i++)                         // Parcours des 35 zones de depots de capteurs
    {
        if (PtrListBox[i]->text() != "" )           //Vérification de la case si capteur a ete deposer
        {
            iEmplacement=ListeCapteursDisponibles.begin();// Parcours de la liste de tout les capteurs

            while (iEmplacement != ListeCapteursDisponibles.end())
            {
                if(PtrListBox[i]->text()==iEmplacement->Nom)        //Changer le nom de PtrListbox a
                {
                    RemplissageListeAEnvoyer.Nom=iEmplacement->Nom;
                    RemplissageListeAEnvoyer.Unites=iEmplacement->Unites;
                    RemplissageListeAEnvoyer.FormuleMath=iEmplacement->FormuleMath;
                    RemplissageListeAEnvoyer.Type=iEmplacement->Type;
                    RemplissageListeAEnvoyer.Port=PtrListBox[i]->GetTextLabel();


                    qDebug()<<"------ PORT : "<<PtrListBox[i]->GetTextLabel()<<" ------------";
                    qDebug()<<"------ Capteur : "<<iEmplacement->Nom<<" ------------";

                }

                ++iEmplacement;
            }

           pListCapteurConnecte->push_back(RemplissageListeAEnvoyer);
        }
    }
    this->FenPrinc->genererFenetre(); // Ouvre le nombre de fenetre


    close();  // Ferme la fenetre
}


void F_SelectionnerLesCapteurs::on_AnnulerChoixCapteurs_clicked()
{
    RazListe(); //Nettoie toutes les cases port
    close(); // Ferme la fenetre

}

/* Description détaillée de la méthode RazListe
* @note Remarques simples sur la méthode RazListe
* Nettoie toutes les cases port
*/
void F_SelectionnerLesCapteurs::RazListe() // permet de nettoyer toutes les cases de la liste en remplacant leurs textes
{
    pListCapteurConnecte->erase(pListCapteurConnecte->begin(),pListCapteurConnecte->end());     //Vide la liste
    for (int i=0;i<=34;i++)
    {

        if (PtrListBox [i]->count() != 0)
        {
           PtrListBox [i]->item(PtrListBox [i]->count()-1)->setText("");

         }
    }
}
