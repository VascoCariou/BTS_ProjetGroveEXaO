/**
* @struct Capteur
* @brief
*   Structure permetant de stocker les donn�es utile au autre fonction du programmes  ( Parser et afficheur )
*
*/

#ifndef STRUCTCAPTEUR_H
#define STRUCTCAPTEUR_H

#include <QObject>

typedef struct Capteur
{
    QString     Nom;               /// Nom du capteur
    QString     Unites;            /// Unit�s renvoy� par le capteur
    QString     FormuleMath;       /// Formule utile pour transformer la tension en valeur lisible et compr�hensible
    QString     Type;              /// Type de port ( Analogique / Num�rique / I2C
    QString     Port;              /// Num�ro du port rempli selon l'utilisateur
    //QPixmap *   Image;

} TCapteur;

#endif // STRUCTCAPTEUR_H
