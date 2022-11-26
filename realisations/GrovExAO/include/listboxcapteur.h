/** @brief Description rapide de MaClasse
*
* Classe utilisé pour la liste des capteurs avec seulement un Glisser qui doit être fonctionnelle
* Le déposer ne servant à rien.
* @see ListBoxport
*/
#ifndef LISTBOXCAPTEUR_H
#define LISTBOXCAPTEUR_H
class Listboxcapteur ;

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class Listbox; }
QT_END_NAMESPACE


class Listboxcapteur: public QListWidget
{
public:

    Listboxcapteur(QLabel * pUnLabel,QWidget *parent = nullptr);
protected:
    void dragMoveEvent(QDragMoveEvent* event);          //Quand un mouvement de l'évenement glisser est détecté
    void dropEvent(QDropEvent* event);                  // Action quand le dépot d'un élément est détecté
    void startDrag(Qt::DropActions supportedActions);   // Action à effectuer quand un glisser est détecté
    void dragEnterEvent(QDragEnterEvent* event);        //Quand l'évenement glisser est détecté
    Qt::DropAction supportedDropActions();              // Vérification des événements suporté
signals:
    void itemDroped();                          // Signal permettant la détection quand un élément est déposer
    QLabel * pUnLabel;                          //Pointeur de QLABEL
};

#endif // LISTBOXCAPTEUR_H
