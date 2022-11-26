//------------------------------------------------------------------------------
/** @file Arduino.cpp
*
* @brief Paramétrage et gestion de la communication série avec la carte
*
* @author CARIOU Vasco
* @author BTS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
* @since 2022-02-02
* @version 2.0
* @date 2022-05-13
*
* Constructeur :
*   - SetPortName  : Numéro de port (Si non connu allez à gestionnaire de périphérique -> "Ports (COM et LPT)")
*   - setBaudeRate : La vitesse de communication avec la carte (en bit/s ou en baud)
*   - setDataBits  : Defini le nombre de bits de données
*   - setParity    : Defini s'il y a un controle de parité ou non
*   - setStopBits  : Defini le nombre de bits de stop
*   - setFlowControl : Defini le mode de control de flux
*
*   - connect : Gère la lecture des données. Dès que l'objet "Serie" (la carte arduino) aura des nouvelles données
*               à lire (Signal :  ReadyRead()). La fonction "DonneMesure()" sera ouverte et émettra à la fin
*               le tableau d'octet recu de la carte.
*
* OuvrirConnection : Ouverture de la communcation en mode Lecture/écriture. Si elle est déjà
*                    ouverte, il y a la précence d'un message d'erreur indiquant que le port est
*                    déjà ouvert et donc déjà occupé par un autre élément.
*
* Ecrire : Envoie le message, situé dans les paramètres de la déclaration, à la carte
*
* DonneMesure : Méthode appelé par le connect. Lis les informations donnée par la carte puis les copies dans un tableau d'octet.
*               Ensuite, la trame est traitée puis convertie pour être emise vers la fenêtre de visualisation des valeurs;
*               @see f_visualiserlesvaleurs.cpp -> le connect
*
* VerificationSiOuvert : La méthode vérifie si l'ouverture est faite. Cette méthode retourne un bool :
*                                                                           - true : déjà ouverte
*                                                                           - false : Fermé
*
* Destructeur : Ouverture de la méthode "FermerConnection()"
*
* FermerConnection : Ferme la connection
*
* Fabrication GrovExAO.pro
*
* @bug La valeur retourne deux valeurs au lieux d'une seule. Cette valeur en trop est sois un 0 (format de la trame invalide
*      ou la même que la précédente)
*/
//------------------------------------------------------------------------------

#include <QDebug>
#include <chrono>
#include <thread>
#include <windows.h>
#include <iostream>

#include "Arduino.h"
#include "StructCapteur.h"
#include "mpParser.h"

using namespace mup;

Arduino::Arduino(QObject *parent) :
    QObject (parent),
    sPort   ("")
{
    //PARAMETRAGE DE LA LIAISON SERIE
    Serie.setPortName     ("COM3");
    Serie.setBaudRate     (QSerialPort::Baud19200);
    Serie.setDataBits     (QSerialPort::Data8);
    Serie.setParity       (QSerialPort::NoParity);
    Serie.setStopBits     (QSerialPort::OneStop);
    Serie.setFlowControl  (QSerialPort::NoFlowControl);
    //<----------------------------------------------------------->

    /* Signal connecté à "DonneMesure"
     *    A Chaque fois qu'une donnée est disponible DonneMesure est appelé
     * 1: Pointeur vers l'objet emmeteur
     * 2: Signal emis dès qu'une nouvelle donnée est disponible
     * 3: Pointeur vers l'objet du slot recepteur
     * 4: Nom du slot qui doit être appelé
    */
    connect(&Serie, SIGNAL(readyRead()),
              this, SLOT(DonneMesure()));

    hSemaphore = CreateSemaphore(nullptr,    // Securité de l'héritage
                                 1,          // Valeur initial du compteur
                                 1,          // Valeur maximal du compteur
                                 (LPCTSTR)"PortSerie"); // Nom du sémaphore
}

/** Ouverture et vérification si le port est disponible pour la lecture/écriture
*
* @pre Avoir un objet de type QSerialPort existant, Le port ne doit pas déjà être ouvert
*
* @post Le port est ouvert, s'il ne l'était pas déjà
*
* @note Si le port utilisé est déjà ouvert, par un autre programme ou logiciel il y aura le message d'erreur.
*       Veillez, avant de lancer le logiciel, à ne pas utiliser le port utilisé.
*/
void Arduino::OuvrirConnection ()
{
    if (Serie.open(QIODevice::ReadWrite)) {
        qDebug() << "Port disponible";
    }else {
        qDebug() << "Port non disponible";
    }
}

/** Ecriture sur le port série
*
* @pre Avoir un objet de type QSerialPort existant, une liaison ouverte
*
* @param MessageAEcrire : Message à envoyé à la carte
* @param[in] MessageAEcrire : Message à envoyé à la carte
*            Plage de Valeur : char 0-255
*
* @see f_visualiserlescapteur.cpp
*/
void Arduino::EcrireSurLePort(const char* MessageAEcrire)
{
    Serie.write(MessageAEcrire);
    Serie.flush();
    this->sPort = MessageAEcrire ;
}

/** Lecture de la valeur mesurée, traitement de la donnée puis emission de cette valeur
*
* @pre Avoir un objet de type QSerialPort existant, une liaison ouverte
* @pre Avoir utilisé la méthode Ecrire avant.
* @pre Avoir utilisé le mutateur "Set_CopierListeTCapteur" pour pouvoir utilisé la liste de structure
*
* @post La valeur sera affiché dans la fenêtre de f_visualierlesvaleurs*
*
* @return La valeur retournée est un double dépouillé de toutes informations inutiles
*
* @see connect relié à l'émission : f_visualierlesvaleurs.cpp
*/
void Arduino::DonneMesure()
{
    QByteArray ValeurAAfficher;
    QByteArray TableauARetournee;
    QString    Port (this->sPort) ;
    QString    Formule;

    //Traitement de chaine de Valeur pour garder uniquement la valeur mesurée
    bool            ok                  (false);
    unsigned int    IndiceFinChaine     (0);
    double          ValeurMesurePreParser  (0);
    double          ValeurMesurePostParser  (0);
    QString         CharactereATrouver  ("=");
    QString         PetiteChaine;

    WaitForSingleObject(hSemaphore, INFINITE);

    //Lecture des données sur la liaison série
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    TableauARetournee = Serie.readAll();

    Valeur.append(TableauARetournee);


    ReleaseSemaphore(hSemaphore, 1,nullptr);

    qDebug() << "Valeur reçue : [" << Valeur << "]\n";


    IndiceFinChaine = Valeur.lastIndexOf(CharactereATrouver);

    PetiteChaine = Valeur.remove(0,IndiceFinChaine+1);
    PetiteChaine.chop(2);

    ValeurMesurePreParser = PetiteChaine.toFloat(&ok);

    if(ok)
    {

        //Savoir s'il y a une formule dans la strucuture du capteur utilisé
        for (int i = 0 ; i< ListeCapteur.size(); i++)
        {
            if (ListeCapteur[i].Port == Port)
            {
                Formule = ListeCapteur[i].FormuleMath;
            }
        }

        //S'il y a une formule, le convertissement de la valeur se fait
        if (Formule.isEmpty() == false)
        {
            ValeurMesurePostParser = ConvertirValeur(ValeurMesurePreParser, Formule);
        }else
        {
            ValeurMesurePostParser = ValeurMesurePreParser;
        }

        //emission de la valeur traité
        emit( NouvelleDonneeMesuree(this->sPort, ValeurMesurePostParser) );
    }
}

/** vérification si le port série est ouvert
*
* @pre Avoir un objet de type QSerialPort existant, une liaison ouverte
*
*/
bool Arduino::VerificationSiOuvert()
{
    return Serie.isOpen();
}

/** Vérification si l'écriture est possible
*
* @pre Avoir un objet de type QSerialPort existant, une liaison ouverte
*
*/
bool Arduino::VerificationSiEcriturePossible()
{
    return Serie.isOpen();
}

/** Description détaillée de la méthode AfficherAttributs
*
* @pre Avoir la liste des structures utilisées correctement rempli
*
* @param QList<TCapteur> ListeCapteurF_Principale : Liste de structure provenant de F_Principale
* @param[in] QList<TCapteur> ListeCapteurF_Principale :
*                   - Sert à copier la liste de F_Principale vers Arduino
*                   - Plage d'entré : Une liste de type "QList<TCapteur>"
*
* @warning La liste doit au moins avoir un élément dans celle-ci sinon la méthode "DonneMesure" ne fonctionnera pas.
*
* @see F_Principale.cpp
*/
void Arduino::Set_CopierListeTCapteur(QList<TCapteur> ListeCapteurF_Principale)
{
    this->ListeCapteur = ListeCapteurF_Principale;
}

/** Description détaillée de la méthode ConvertirValeur
*
* @pre  La communication série est bien mise en place, Mesure est bien un double
*       Il y a la formule correspondant au capteur dans Formule
* @post la valeur convertit est retournée à f_visualiserlesvaleurs.cpp
*
* @param Mesure : Valeur retournée par le capteur
*        Formule : QString contenant la formule mathématique de du capteur
* @param[in] Mesure : Valeur retournée par le capteur [0-255]
*        ListeCapteur : QString contenant la formule mathématique de du capteur. C'est une liste de char entre 0-255
*
* @return Retourne la valeur mesurée dans une unité internationale
*
* @see StructCapteur.h
* @see f_visualierlesvaleurs.cpp
*/
double Arduino::ConvertirValeur (double Mesure, QString Formule)
{
    Value   ValeurConverti;
    QString StringFormuleMathematique;

    //Activation des paquets du parser
    /*Installe :
        - Fonction basique
        - Opérateur binaire
        - calcul unaire
        - Valeur complexe 'i'
        - Détection de string
        - Calcul de matrice*/
    ParserX PaquetParser(pckALL_NON_COMPLEX);

    Value   a (Mesure);
    QString ValeurMesure ("a");

    StringFormuleMathematique = Formule;

    PaquetParser.DefineVar(ValeurMesure.toStdWString(), Variable(&a));

    PaquetParser.SetExpr(StringFormuleMathematique.toStdWString());

    ValeurConverti = PaquetParser.Eval();

//    Affichage de la valeur converti
//    console() << ValeurConverti;

    return ValeurConverti;
}

//DESTRUCTEUR-------------------------------->
//S'occupe de la fermeture de la communication
Arduino::~Arduino()
{
    FermerConnection();
}

/** Méthode pour ferme la connection
*
* @pre Avoir un objet de type QSerialPort existant, une liaison ouverte
*/
void Arduino::FermerConnection ()
{
    Serie.close();
}

