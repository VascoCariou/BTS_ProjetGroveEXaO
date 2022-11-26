/** @brief Description rapide de MaClasse
*
* Classe utilisé pour toutes les fonctions utile au choix des capteurs : L'affichage des noms / images / remplissage de le structure ...
* Constructeur : Initialise les Listboxport et Listboxcapteur
*/

#ifndef F_SELECTIONNERLESCAPTEURS_H
#define F_SELECTIONNERLESCAPTEURS_H
class F_SelectionnerLesCapteurs ;

#include <QDialog>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QWidget>
#include "StructCapteur.h"
#include "Listboxport.h"
#include "listboxcapteur.h"

#include "F_Principale.h"

namespace Ui
{
    class F_SelectionnerLesCapteurs;
}

class F_SelectionnerLesCapteurs : public QWidget
{
        Q_OBJECT

    public:
        explicit F_SelectionnerLesCapteurs(QList <TCapteur> *, F_Principale * FenPrinc, QWidget *parent = nullptr);
        ~F_SelectionnerLesCapteurs();

        //Méthode metier
        void RemplirListesCapteurs(QString chemin);                //Fonction récursif utilisé pour l'affichage des noms et des images capteurs ainsi que pour remplir la structure
        void RazListe();                                    //Sert à effacer la liste des capteurs déposer
private slots:
        void on_ValiderMaquette_clicked();                  // Ce qui ce passe quand on appuie sur le bouton ValiderMaquette

        void on_AnnulerChoixCapteurs_clicked();              // Ce qui ce passe quand on appuie sur le bouton AnnulerChoixCapteurs

private:
        QList <TCapteur> *pListCapteurConnecte;            // Liste de structure permettant l'utilisation de la structure par les autre fonction
        QPixmap           pImage;                           // Image de la carte
        Listboxport * PtrListBox [35];// pointeur sur list box pour la création de fenetre avec le drag et drop
        Listboxcapteur * ListINI ;
        QLabel * LabelNumCapteur [35];
        Ui::F_SelectionnerLesCapteurs *ui;
        QList <TCapteur> ListeCapteursDisponibles;
        F_Principale * FenPrinc ;
};

#endif // F_SELECTIONNERLESCAPTEURS_H

