#ifndef DEBUGERFILTERSEDITOR_H
#define DEBUGERFILTERSEDITOR_H

#include <QDialog>
#include "debugerfiltermodel.h"
#include "debugerfilter.h"

namespace Ui {
class DebugerFiltersEditor;
}

class DebugerFiltersEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DebugerFiltersEditor(QWidget *parent = nullptr);
    ~DebugerFiltersEditor();

private slots:
    void on_pushButton_addFilter_clicked();

    void on_pushButton_deleteFilter_clicked();

private:
    Ui::DebugerFiltersEditor *ui;
    QVector<DebugerFilter> filters;
    DebugerFilterModel *filterModel;
};

#endif // DEBUGERFILTERSEDITOR_H
