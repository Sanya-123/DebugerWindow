#include "debugmessadge.h"
#include "ui_debugmessadge.h"
#include <QDateTime>

DebugMessadge::DebugMessadge(QtMsgType type, const QMessageLogContext &context, const QString &msg, QWidget *parent) :
    QWidget(parent), msgType(type),
    ui(new Ui::DebugMessadge)
{
    ui->setupUi(this);

    QString header;

    QString styleSheet = "QWidget#widget{background: ";

    switch (type) {
        case QtDebugMsg:
            header = "Debug [";
            //        outputSring = outputSring.asprintf(GREE_BEGIN "Debug: %s (%s:%u, %s)\n" END_COLOR, localMsg.constData(), context.file, context.line, context.function);
            styleSheet.append("rgba(0, 255, 0, 100);");
            break;
        case QtInfoMsg:
            header = "Info [";
            styleSheet.append("rgba(0, 0, 255, 100);");
            break;
        case QtWarningMsg:
            header = "Warning [";
            styleSheet.append("rgba(255, 255, 0, 100);");
            break;
        case QtCriticalMsg:
            header = "Critical [";
            styleSheet.append("rgba(255, 0, 0, 100);");
            break;
        case QtFatalMsg:
            header = "Fatal [";
            styleSheet.append("rgba(255, 0, 0, 100);");
            break;
        default:
            header = "Unnoun [";
            break;
    }

    styleSheet.append("}QLabel{background:rgba(0, 0, 0, 0);}");
    this->setStyleSheet(styleSheet);

    header.append(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz"));
    header.append("]");
    ui->label_header->setText(header);
    //context.file, context.line, context.function
    ui->label_file->setText(QString::asprintf("%s:%s:%d", context.file, context.function, context.line));
    ui->lineEdit_msg->setText(msg);
    file = QString(context.file);
    function = QString(context.function);
    line = context.line;
}

DebugMessadge::~DebugMessadge()
{
    delete ui;
}

QtMsgType DebugMessadge::getMsgType() const
{
    return msgType;
}

QString DebugMessadge::getFile() const
{
    return file;
}

QString DebugMessadge::getFunction() const
{
    return function;
}

int DebugMessadge::getLine() const
{
    return line;
}
