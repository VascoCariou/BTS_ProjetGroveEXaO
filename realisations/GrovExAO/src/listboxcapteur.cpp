#include "listboxcapteur.h"
#include <QMouseEvent>
#include <QDrag>
#include <QWidget>

#include <QMimeData>
Listboxcapteur::Listboxcapteur(QLabel * pUnLabel,QWidget *parent):
    QListWidget(parent),
    pUnLabel(pUnLabel)

{
    this->setViewMode(QListView::IconMode);
        this->setIconSize(QSize(55, 55));
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->setDragEnabled(true);
        this->setDefaultDropAction(Qt::MoveAction);
        this->setAcceptDrops(true);
        this->setDropIndicatorShown(true);
}
/* Description détaillée de la méthode startDrag
* @note Remarques simples sur la méthode startDrag
* Quand on commence à prendre un widget on encode en UTF8 le texte selectionner
*/
void Listboxcapteur::startDrag(Qt::DropActions supportedActions)
{

   QListWidgetItem* item = currentItem();
   QMimeData* mimeData = new QMimeData;
   QByteArray ba;
   ba = item->text().toUtf8().data();
   mimeData->setData("application/x-item", ba);
   QDrag* drag = new QDrag(this);
   drag->setMimeData(mimeData);
   drag->exec(Qt::MoveAction);

}
/* Description détaillée de la méthode dragEnterEvent
* @note Remarques simples sur la méthode dragEnterEvent
* Ce qui va être effectuer quand le glisser est détecter on vérifie si c'est bien notre item on l'accepte ou pas
*/
void Listboxcapteur::dragEnterEvent(QDragEnterEvent* event)
{

   if (event->mimeData()->hasFormat("application/x-item"))
    {
       event->accept();
   }
   else

       event->ignore();

}

/* Description détaillée de la méthode dragMoveEvent
* @note Remarques simples sur la méthode dragMoveEvent
* Quand le glisser à du mouvement on vérifie le format et la source puis on l'accepte ou pas
*/
void Listboxcapteur::dragMoveEvent(QDragMoveEvent* event)
{

   if (event->mimeData()->hasFormat("application/x-item") && event->source() != this)
   {
       event->setDropAction(Qt::MoveAction);
       event->accept();
   }
   else


       event->ignore();

}
/* Description détaillée de la méthode dropEvent
* @note Remarques simples sur la méthode dropEvent
* Quand le déposer est détecter on l'ignore car on ne veut pas de drop dans la liste de capteurs donc on ignore tout drop
*/
void Listboxcapteur::dropEvent(QDropEvent* event)
{

      event->ignore();
}

Qt::DropAction Listboxcapteur::supportedDropActions()
{
   return Qt::MoveAction;
}
