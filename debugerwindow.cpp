#include "debugerwindow.h"
#include "ui_debugerwindow.h"
#include <QListWidgetItem>

DebugerWindow::DebugerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugerWindow)
{
    ui->setupUi(this);
    setWindowTitle("DebugerWindow");
    connect(ui->actionfilters, SIGNAL(triggered(bool)), &filterEditor, SLOT(show()));
    connect(ui->actionupdate, SIGNAL(triggered(bool)), this, SLOT(execFilters()));
    connect(&filterEditor, SIGNAL(finished(int)), this, SLOT(execFilters()));
    connect(this, SIGNAL(newMessadge()), this, SLOT(addNewMessadges()), Qt::QueuedConnection);
    filters = filterEditor.getFilters();
}

DebugerWindow::~DebugerWindow()
{
    delete ui;
}

void DebugerWindow::saveSettings(QSettings *settings)
{
    settings->beginGroup("filters");
    filterEditor.saveSettings(settings);
    settings->endGroup();
}

void DebugerWindow::restoreSettings(QSettings *settings)
{
    settings->beginGroup("filters");
    filterEditor.restoreSettings(settings);
    settings->endGroup();

    execFilters();
}

bool DebugerWindow::checkConditionHideByFile(DebugMessadge *msg, DebugerFilter filter)
{
    bool fileCondition = true;

    if(!filter.file.isEmpty())
    {
        fileCondition = checkConditionHideString(msg->getFile(), filter.file);
    }

    return fileCondition;
}

bool DebugerWindow::checkConditionHideByFunction(DebugMessadge *msg, DebugerFilter filter)
{
    bool functionCondition = true;

    if(!filter.function.isEmpty())
    {
        functionCondition = checkConditionHideString(msg->getFunction(), filter.function);
    }

    return functionCondition;
}

bool DebugerWindow::checkConditionHideByLine(DebugMessadge *msg, DebugerFilter filter)
{
    bool lineCondition = true;

    if(filter.lineBegin >= 0 || filter.lineEnd >= 0)
    {
        int line = msg->getLine();
        if((line >= filter.lineBegin) && (line <= filter.lineEnd))
        {
            lineCondition = true;
        }
        else
        {
            lineCondition = false;
        }
    }

    return lineCondition;
}

bool DebugerWindow::checkConditionHideByText(DebugMessadge *msg, DebugerFilter filter)
{
    bool functionCondition = true;

    if(!filter.text.isEmpty())
    {
        functionCondition = checkConditionHideString(msg->getFunction(), filter.text);
    }

    return functionCondition;
}

bool DebugerWindow::checkConditionHideString(QString str, QString ref)
{
    return str.contains(ref);
}

bool DebugerWindow::checkConditionHide(DebugMessadge *msg, QVector<DebugerFilter> *filters)
{
    bool isHide = false;

    if((filters == nullptr) || (msg == nullptr))
        return isHide;

    for(int i = 0; i < filters->size(); i++)
    {
        DebugerFilter _filter = filters->at(i);
        if(_filter.en)
        {
            bool conFile = checkConditionHideByFile(msg, _filter);
            bool conFunction = checkConditionHideByFunction(msg, _filter);
            bool conLine = checkConditionHideByLine(msg, _filter);
            bool conText = checkConditionHideByText(msg, _filter);

            if(conFile && conFunction && conLine && conText)
            {
                switch(msg->getMsgType())
                {
                    case QtDebugMsg:
                        isHide = !_filter.enDebug;
                        break;
                    case QtInfoMsg:
                        isHide = !_filter.enInfo;
                        break;
                    case QtWarningMsg:
                        isHide = !_filter.enWarnings;
                        break;
                    case QtCriticalMsg:
                        isHide = !_filter.enCritical;
                        break;
                    case QtFatalMsg:
                        isHide = !_filter.enFatal;
                        break;
                    default:

                        break;
                }
            }
        }
    }

    return isHide;
}

void DebugerWindow::putMessadge(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    struct NewMessadge newMsg;
    newMsg.type = type;
//    newMsg.context = context;
    newMsg.file = QByteArray(context.file);
    newMsg.line = context.line;
    newMsg.function = QByteArray(context.function);
    newMsg.category = QByteArray(context.category);
    newMsg.msg = msg;
    newMessadges.append(newMsg);
    emit newMessadge();
}

void DebugerWindow::execFilters()
{
    for(int i = 0; i < ui->listWidget_messadges->count(); i++)
    {
        DebugMessadge *theWidgetItem = (DebugMessadge *)ui->listWidget_messadges->itemWidget(
                    ui->listWidget_messadges->item(i));
        bool hiden = checkConditionHide(theWidgetItem, filters);
        ui->listWidget_messadges->item(i)->setHidden(hiden);
    }
}

void DebugerWindow::addNewMessadges(QtMsgType type, const QMessageLogContext &context, const QString &msg)
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


    if(ui->checkBox_enAutoscroll->isChecked())
    {
        ui->listWidget_messadges->scrollToBottom();
    }

    //check hiden condition
    bool hiden = checkConditionHide(theWidgetItem, filters);
    listWidgetItem->setHidden(hiden);
}

void DebugerWindow::addNewMessadges()
{
    while(newMessadges.size() > 0)
    {
        struct NewMessadge msg = newMessadges[0];
        newMessadges.remove(0);

        QMessageLogContext context(msg.file.data(), msg.line, msg.function.data(), msg.category.data());

        addNewMessadges(msg.type, context, msg.msg);
    }
}
