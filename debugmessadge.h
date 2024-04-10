#ifndef DEBUGMESSADGE_H
#define DEBUGMESSADGE_H

#include <QWidget>

namespace Ui {
class DebugMessadge;
}

class DebugMessadge : public QWidget
{
    Q_OBJECT

public:
    explicit DebugMessadge(QtMsgType type, const QMessageLogContext &context, const QString &msg, QWidget *parent = nullptr);
    ~DebugMessadge();

    QtMsgType getMsgType() const;
    QString getFile() const;
    QString getFunction() const;
    int getLine() const;

private:
    Ui::DebugMessadge *ui;
    QtMsgType msgType;
    QString file;
    QString function;
    int line;
};

#endif // DEBUGMESSADGE_H
