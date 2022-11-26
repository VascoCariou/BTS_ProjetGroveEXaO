#include "Listboxport.h"
#include <QMouseEvent>
#include <QDrag>
#include <QWidget>

#include <QMimeData>
Listboxport::Listboxport(QLabel * pLeLabel,QWidget *parent)
    : QListWidget(parent),
      pLeLabel(pLeLabel)

{
    this->setViewMode(QListView::IconMode);
    this->setIconSize(QSize(55, 55));
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragEnabled(true);
    this->setDefaultDropAction(Qt::MoveAction);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);

}

Listboxport::~Listboxport()
{
    delete ui;
}

bool    Listboxport::setLabel(QLabel * pLeLabelAssocie)
{
    this->pLeLabel =  pLeLabelAssocie ;

}

/* Description détaillée de la méthode startDrag
* @note Remarques simples sur la méthode startDrag
* Quand on commence à prendre un widget on encode en UTF8 le texte selectionner
*Si il y'a execution d'un mouvement on emet un signal de drop d'item
* Permet aussi de supprimer l'élément de la case après le drag
*/
void Listboxport::startDrag(Qt::DropActions supportedActions)
{

   QListWidgetItem* item = currentItem();
   QMimeData* mimeData = new QMimeData;
   QByteArray Taboctet;
   Taboctet = item->text().toUtf8().data();
   mimeData->setData("application/x-item", Taboctet);
   QDrag* drag = new QDrag(this);
   drag->setMimeData(mimeData);

   if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
   {
       emit itemDroped();
   }


   for (int i = 0; i < this->count() ; i++ )
   {
       QListWidgetItem * item = this->item(i) ;
       this->removeItemWidget(item);
       delete item ;
       item = nullptr ;
   }
}
/* Description détaillée de la méthode dragEnterEvent
* @note Remarques simples sur la méthode dragEnterEvent
* Ce qui va être effectuer quand le glisser est détecter on vérifie si c'est bien notre item on l'accepte ou pas
*/
void Listboxport::dragEnterEvent(QDragEnterEvent* event) {

   if (event->mimeData()->hasFormat("application/x-item"))      // Vérification du format : si c'est bien un item de notre application
    {
       event->accept();                                         //On l'accepte
   }
   else

       event->ignore();                                         //On l'ignore ( rien  ne ce passe)

}

/* Description détaillée de la méthode dragMoveEvent
* @note Remarques simples sur la méthode dragMoveEvent
* Quand le glisser à du mouvement on vérifie le format et la source puis on l'accepte ou pas
*/
void Listboxport::dragMoveEvent(QDragMoveEvent* event) {

   if (event->mimeData()->hasFormat("application/x-item") && event->source() != this) // Verification du format et de la source
   {
       event->setDropAction(Qt::MoveAction);
       event->accept();
   }
   else

       event->ignore();

}

/* Description détaillée de la méthode dropEvent
* @note Remarques simples sur la méthode dropEvent
* Quand le déposer est détecter et qu'il possède le bon format on l'accepte et on vide la case avant pour un effet de remplacement
*/
void Listboxport::dropEvent(QDropEvent* event) {

   if (event->mimeData()->hasFormat("application/x-item"))
   {
       event->accept();
       event->setDropAction(Qt::MoveAction);

       for (int i = 0; i < this->count() ; i++ ) // Permet de remplacer un éléments déjà présent dans une case par un autre
       {
           QListWidgetItem * item = this->item(i) ;
           this->removeItemWidget(item);
           delete item ;
           item = nullptr ;
       }

       QListWidgetItem *item = new QListWidgetItem;
       QString name = event->mimeData()->data("application/x-item");
       item->setText(name);
       addItem(item);                   // Affichage du nom de l'item
   }
   else

       event->ignore();

}

Qt::DropAction Listboxport::supportedDropActions()
{


   return Qt::MoveAction;
}
/* Description détaillée de la méthode text
* @note Remarques simples sur la méthode text
*  Permet de retourner le texte d'un élément
*/
QString  Listboxport::text()
{
    QString sRetour ("") ;
    if(this->item(0) != nullptr)
    {
        sRetour = this->item(0)->text() ;
    }

    return (sRetour) ;
}
/* Description détaillée de l'Accesseur GetTextLabel
* @note Remarques simples sur l'Accesseur GetTextLabel
*  Permet de retourner le texte d'un élément
*/
QString  Listboxport::GetTextLabel()
{
    return(pLeLabel->text());
}
