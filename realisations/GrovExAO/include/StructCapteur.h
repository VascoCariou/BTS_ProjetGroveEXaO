/**
* @struct Capteur
* @brief
*   Structure permetant de stocker les données utile au autre fonction du programmes  ( Parser et afficheur )
*
*/

#ifndef STRUCTCAPTEUR_H
#define STRUCTCAPTEUR_H

#include <QObject>

typedef struct Capteur
{
    QString     Nom;               /// Nom du capteur
    QString     Unites;            /// Unités renvoyé par le capteur
    QString     FormuleMath;       /// Formule utile pour transformer la tension en valeur lisible et compréhensible
    QString     Type;              /// Type de port ( Analogique / Numérique / I2C
    QString     Port;              /// Numéro du port rempli selon l'utilisateur
    //QPixmap *   Image;

} TCapteur;

#endif // STRUCTCAPTEUR_H
