/** @brief Description rapide de MaClasse
*
* Classe utilisée pour le dépot des capteurs de la listboxcapteur sur des zones
* Ici le déposer est opérationnelle
*
* @test
* @see
*/
#ifndef Listboxport_H
#define Listboxport_H
class Listboxport ;

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class Listboxport; }
QT_END_NAMESPACE

class Listboxport : public QListWidget
{
    Q_OBJECT

public:
    Listboxport(QLabel * pLeLabel,QWidget *parent = nullptr);         // Creation de point de QLabel
    ~Listboxport();
    QString text();                                     //Retourne le texte d'un élément
    bool    setLabel(QLabel * pLeLabelAssocie) ;        // Associe le texte d'un label
    QString GetTextLabel();                             //Retourne le texte d'un label
protected:
    void dragMoveEvent(QDragMoveEvent* event);              //Quand un mouvement de l'évenement glisser est détecté
    void dropEvent(QDropEvent* event);                      // Action quand le dépot d'un élément est détecté
    void startDrag(Qt::DropActions supportedActions);       // Action à effectuer quand un glisser est détecté
    void dragEnterEvent(QDragEnterEvent* event);           //Quand l'évenement glisser est détecté
    Qt::DropAction supportedDropActions();                  // Vérification des événements suporté
signals:
    void itemDroped();                              // Signal permettant la détection quand un élément est déposer
private:
    Ui::Listboxport *ui;
    QLabel * pLeLabel;                                        //Pointeur de QLABEL
};
#endif // Listboxport_H
