// ConvertirValeurMesure.h 3 11/05/2022 CARIOU Vasco

#ifndef ARDUINO_H
#define ARDUINO_H

class Arduino ;

#include <QObject>
#include <QSerialPort>
#include <windows.h>

#include "StructCapteur.h"

/** @brief Création et gestion de liaison série avec la carte
*
* Construteur : Paramètre la communication liaison série
* Destruteur : Ferme la communication
*
* Ecrire : Ecrit à la carte une chaine de caratère
* FermeConnection : Méthode ouverte par le destruteur pour fermer la communication
* OuvrirConnetion : Démarre la connection avec la carte. Ouverture faite dans
*                   "f_visualierlesvaleurs.cpp"
* VerificationSiOuvert : Vérification si "OuvrirConnetion" à bien effectué correctement
* VerificationSiEcriturePossible : Vérification si rien d'autre n'utilise déjà la carte
*
* DonneMesure : Lis la valeur retournée par la carte. Met en forme la valeur sous
*               forme d'un tableau d'octet et le retour ensuite la valeur avec un type double
*               et un emit.
* NouvelleDonneDisponible : Signal dans lequel sera contenu la tableau d'octet mis en forme
*                           par "DonneMesure"
* Set_CopierListeTCapteur : Sert à copier la liste des structures TCapteur contenu dans F_Principale dans la classe.
*                           Ce Mutateur sera utilisé pour connaître la formule d'un capteur grâce au port utilisé
*
*
* Serie : Objet de type "QSerialPort" qui sera fera la communication avec la carte.
* float Mesure
*
* @see f_visualiserlesvaleurs
* @see F_Principale
*/
class Arduino : public QObject
{
    Q_OBJECT

    public:        
        // CONSTRUCTEURS et DESTRUCTEURS
        /// Paramétrage de la liaison série avec l'ensemble des paramètres requis
        Arduino(QObject *parent = nullptr);
        /// Ferme la communication avec la carte arduino
        ~Arduino();

        //Liste des méthodes métier necessaires pour la communication série
        /// Ecrit sur le Port série
        void EcrireSurLePort                (const char *MessageAEcrire);

        ///  Ferme le port
        void FermerConnection               ();

        /// Ouvre la connection
        void OuvrirConnection               ();

        /// Vérifie l'ouverture du port
        bool VerificationSiOuvert           ();

        /// Vérifier l'utilisation du port
        bool VerificationSiEcriturePossible ();

        ///Convertissement de la valeur
        double ConvertirValeur(double Mesure, QString Formule);

        //Mutateur
        /// Copie la liste de F_Principale.cpp vers Arduino.cpp
        void Set_CopierListeTCapteur (QList<TCapteur> ListeCapteurF_Principale);

    public slots:
        /// Slots permettant de recuillir la valeur mesuré
        void DonneMesure();

    signals:
        /// Signal permettant d'emmetre la donnée mesurée vers f_visualiserlesvaleurs.cpp
        /// @see f_visualierlesvaleur.cpp
        void NouvelleDonneeMesuree(QString sPort, double Data);

        /// Signal permettant d'emmetre la donnée à convertir
        /// Elle ne sera pas convertis s'il n'y a pas besoins
        /// @see f_visualierlesvaleur.cpp
        double MesureAConvertir (double Data, QString FormuleMathCapteur);

    private:        
        /// @brief Valeur mesurée sous forme de QString
        QString     Valeur;
        /// @brief Sémaphore permettant de gérer la communication série
        HANDLE      hSemaphore;
        /// @brief Contient la valeur du port du shield Arduino du capteur actuellement utilisé
        QString     sPort ;
        /// @brief Objet de type QSerialPort permettant la gestion de la liaison série
        QSerialPort Serie;
        /// @brief Liste des structures utilisés lors de l'expérience
        QList <TCapteur> ListeCapteur;
};

#endif // ARDUINO_H
