#include "debugerwindow.h"
#include "ui_debugerwindow.h"
#include <QListWidgetItem>

DebugerWindow::DebugerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugerWindow)
{
    ui->setupUi(this);
    connect(ui->actionfilters, SIGNAL(triggered(bool)), &filterEditor, SLOT(show()));
}

DebugerWindow::~DebugerWindow()
{
    delete ui;
}

void DebugerWindow::putMessadge(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    //Creating a new list widget item whose parent is the listwidget itself
    QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget_messadges);

    //Adding the item to the listwidget
    ui->listWidget_messadges->addItem (listWidgetItem);

    //Creating an object of the designed widget which is to be added to the listwidget
    DebugMessadge *theWidgetItem = new DebugMessadge(type, context, msg, this);

    //Making sure that the listWidgetItem has the same size as the TheWidgetItem
    listWidgetItem->setSizeHint (theWidgetItem->sizeHint ());

    //Finally adding the itemWidget to the list
    ui->listWidget_messadges->setItemWidget (listWidgetItem, theWidgetItem);
}
