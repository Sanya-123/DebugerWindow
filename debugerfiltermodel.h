#ifndef DEBUGERFILTERMODEL_H
#define DEBUGERFILTERMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "debugerfilter.h"

class DebugerFilterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DebugerFilterModel(QVector<DebugerFilter> *filetrs, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
    void updateViewport();

private:
    QVector<DebugerFilter> *filetrs;
};

#endif // DEBUGERFILTERMODEL_H
