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

public slots:
    void putMessadge(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    Ui::DebugerWindow *ui;
    DebugerFiltersEditor filterEditor;

};

#endif // DEBUGERWINDOW_H
