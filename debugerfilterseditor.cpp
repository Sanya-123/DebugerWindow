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

void DebugerFiltersEditor::on_pushButton_addFilter_clicked()
{
    filters.append(DebugerFilter());
    emit filterModel->layoutChanged();
//    ui->treeView_filters->viewport()->update();
}

void DebugerFiltersEditor::on_pushButton_deleteFilter_clicked()
{
//    qDebug() << ui->treeView_filters->currentIndex().row();
//    ui->treeView_filters->currentIndex().row();
//    ui->treeView_filters->selectedIndexes();
//    ui->treeView_filters->selectRow();
//    QList<QTableWidgetItem*> iteams = ui->tableView_filters->selectedItems();

//    for(int i = 0; i < iteams.size(); i++)
//    {
//        int numberElement = ui->tableWidget_availebleWidgets->row(iteams[i]);
//    }
}

