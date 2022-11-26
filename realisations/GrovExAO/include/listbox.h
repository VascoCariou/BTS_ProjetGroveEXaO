#ifndef LISTBOX_H
#define LISTBOX_H

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class Listbox; }
QT_END_NAMESPACE

class Listbox : public QListWidget
{
    Q_OBJECT

public:
    Listbox(QLabel * pLeLabel,QWidget *parent = nullptr);         // Creation de point de QLabel
    ~Listbox();
    QString text();
    bool    setLabel(QLabel * pLeLabelAssocie) ;
    QString GetTextLabel();
protected:
    void dragMoveEvent(QDragMoveEvent* e);
    void dropEvent(QDropEvent* event);
    void startDrag(Qt::DropActions supportedActions);
    void dragEnterEvent(QDragEnterEvent* event);
    Qt::DropAction supportedDropActions();
signals:
    void itemDroped();
private:
    Ui::Listbox *ui;
    QLabel * pLeLabel;                                        //Pointeur de QLABEL
};
#endif // LISTBOX_H
