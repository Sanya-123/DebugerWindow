#ifndef DEBUGERWINDOW_H
#define DEBUGERWINDOW_H

#include <QMainWindow>
#include "debugmessadge.h"
#include "debugerfilterseditor.h"

namespace Ui {
class DebugerWindow;
}

class DebugerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugerWindow(QWidget *parent = nullptr);
    ~DebugerWindow();

    void saveSettings(QSettings *settings);
    void restoreSettings(QSettings *settings);

    static bool checkConditionHideByFile(DebugMessadge *msg, DebugerFilter filter);
    static bool checkConditionHideByFunction(DebugMessadge *msg, DebugerFilter filter);
    static bool checkConditionHideByLine(DebugMessadge *msg, DebugerFilter filter);
    static bool checkConditionHideByText(DebugMessadge *msg, DebugerFilter filter);
    static bool checkConditionHideString(QString str, QString ref);
//    static bool checkConditionHideByContext(DebugMessadge *msg, DebugerFilter filter);
    static bool checkConditionHide(DebugMessadge *msg, QVector<DebugerFilter> *filters);

public slots:
    void putMessadge(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    void execFilters();

private slots:
    void addNewMessadges(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    void addNewMessadges();

signals:
    //local signal
    void newMessadge();

private:
    Ui::DebugerWindow *ui;
    DebugerFiltersEditor filterEditor;
    QVector<DebugerFilter> *filters;
    struct NewMessadge{
        QtMsgType type; /*QMessageLogContext context; */ QString msg;
        //contextt
        QByteArray file;
        int line;
        QByteArray function;
        QByteArray category;
    };
    QVector<struct NewMessadge> newMessadges;

};

#endif // DEBUGERWINDOW_H
