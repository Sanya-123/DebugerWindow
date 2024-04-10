#include "debugerfilterseditor.h"
#include "ui_debugerfilterseditor.h"
#include <QDebug>

DebugerFiltersEditor::DebugerFiltersEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebugerFiltersEditor)
{
    ui->setupUi(this);

    filterModel = new DebugerFilterModel(&filters, this);

    ui->treeView_filters->setModel(filterModel);

    connect(filterModel, &DebugerFilterModel::updateViewport,
            ui->treeView_filters->viewport(), QOverload<>::of(&QWidget::update));
}

DebugerFiltersEditor::~DebugerFiltersEditor()
{
    delete filterModel;
    delete ui;
}

void DebugerFiltersEditor::saveSettings(QSettings *settings)
{
    settings->beginWriteArray("filters");
    for (int i = 0; i < filters.size(); i++)
    {
        settings->setArrayIndex(i);
        DebugerFilter fiter = filters[i];

        settings->setValue("en", fiter.en);
        settings->setValue("enDebug", fiter.enDebug);
        settings->setValue("enInfo", fiter.enInfo);
        settings->setValue("enWarnings", fiter.enWarnings);
        settings->setValue("enCritical", fiter.enCritical);
        settings->setValue("enFatal", fiter.enFatal);
    }
    settings->endArray();
}

void DebugerFiltersEditor::restoreSettings(QSettings *settings)
{
    filters.clear();
    int sizeFilters = settings->beginReadArray("filters");
    for(int i = 0; i < sizeFilters; i++)
    {
        DebugerFilter fiter;
        fiter.en = settings->value("en").toBool();
        fiter.enDebug = settings->value("enDebug").toBool();
        fiter.enInfo = settings->value("enInfo").toBool();
        fiter.enWarnings = settings->value("enWarnings").toBool();
        fiter.enCritical = settings->value("enCritical").toBool();
        fiter.enFatal = settings->value("enFatal").toBool();
        filters.append(fiter);
    }
    settings->endArray();

    emit filterModel->layoutChanged();
}

QVector<DebugerFilter> *DebugerFiltersEditor::getFilters()
{
    return &filters;
}

void DebugerFiltersEditor::on_pushButton_addFilter_clicked()
{
    filters.append(DebugerFilter());
    emit filterModel->layoutChanged();
//    ui->treeView_filters->viewport()->update();
}

void DebugerFiltersEditor::on_pushButton_deleteFilter_clicked()
{
//    qDebug() << ui->treeView_filters->currentIndex().row();
    filters.removeAt(ui->treeView_filters->currentIndex().row());
    emit filterModel->layoutChanged();
//    ui->treeView_filters->currentIndex().row();
//    ui->treeView_filters->selectedIndexes();
//    ui->treeView_filters->selectRow();
//    QList<QTableWidgetItem*> iteams = ui->tableView_filters->selectedItems();

//    for(int i = 0; i < iteams.size(); i++)
//    {
//        int numberElement = ui->tableWidget_availebleWidgets->row(iteams[i]);
//    }
}

