#include "debugerfiltermodel.h"
#include <QDebug>

DebugerFilterModel::DebugerFilterModel(QVector<DebugerFilter> *filetrs, QObject *parent)
    : QAbstractTableModel{parent}, filetrs(filetrs)
{

}

int DebugerFilterModel::rowCount(const QModelIndex &parent) const
{
    return filetrs->size();
}

int DebugerFilterModel::columnCount(const QModelIndex &parent) const
{
    return 11;
}

QVariant DebugerFilterModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= filetrs->size())
    {
        return QVariant();
    }
    if (role == Qt::CheckStateRole && index.isValid())
    {
        switch(index.column())
        {
            case 0:
                return filetrs->at(index.row()).en ? Qt::Checked : Qt::Unchecked; break;
            case 1:
                return filetrs->at(index.row()).enDebug ? Qt::Checked : Qt::Unchecked; break;
            case 2:
                return filetrs->at(index.row()).enInfo ? Qt::Checked : Qt::Unchecked; break;
            case 3:
                return filetrs->at(index.row()).enWarnings ? Qt::Checked : Qt::Unchecked; break;
            case 4:
                return filetrs->at(index.row()).enCritical ? Qt::Checked : Qt::Unchecked; break;
            case 5:
                return filetrs->at(index.row()).enFatal ? Qt::Checked : Qt::Unchecked; break;
            default:
                return QVariant();
        }
    }
    else if(role == Qt::DisplayRole && index.isValid())
    {
        switch(index.column())
        {
            case 0:
                return QVariant(filetrs->at(index.row()).name); break;
            case 6:
                return QVariant(filetrs->at(index.row()).file); break;
            case 7:
                return QVariant(filetrs->at(index.row()).function); break;
            case 8:
                return QVariant(filetrs->at(index.row()).lineBegin); break;
            case 9:
                return QVariant(filetrs->at(index.row()).lineEnd); break;
            case 10:
                return QVariant(filetrs->at(index.row()).text); break;
            default:
                return QVariant("");
                break;
        }
    }
    return QVariant();
}

QVariant DebugerFilterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        if (section == 0)
            return QVariant("Name");
        else if(section == 1)
            return QVariant("Debug");
        else if(section == 2)
            return QVariant("Info");
        else if(section == 3)
            return QVariant("Warning");
        else if(section == 4)
            return QVariant("Critical");
        else if(section == 5)
            return QVariant("Fatal");
        else if(section == 6)
            return QVariant("File");
        else if(section == 7)
            return QVariant("Function");
        else if(section == 8)
            return QVariant("LineBegin");
        else if(section == 9)
            return QVariant("LineEnd");
        else if(section == 10)
            return QVariant("Text");
    }

    return QVariant();
}

bool DebugerFilterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() >= filetrs->size())
    {
        return false;
    }

    if (role == Qt::CheckStateRole && index.isValid())
    {
        switch(index.column())
        {
            case 0:
                filetrs->data()[index.row()].en = value.toBool(); break;
            case 1:
                filetrs->data()[index.row()].enDebug = value.toBool(); break;
            case 2:
                filetrs->data()[index.row()].enInfo = value.toBool(); break;
            case 3:
                filetrs->data()[index.row()].enWarnings = value.toBool(); break;
            case 4:
                filetrs->data()[index.row()].enCritical = value.toBool(); break;
            case 5:
                filetrs->data()[index.row()].enFatal = value.toBool(); break;
            default:
                return false;
                break;
        }

        return true;
    }
    else if(role == Qt::EditRole && index.isValid())
    {
        value.toString();

        switch(index.column())
        {
            case 0:
                filetrs->data()[index.row()].name = value.toString(); break;
            case 6:
                filetrs->data()[index.row()].file = value.toString(); break;
            case 7:
                filetrs->data()[index.row()].function = value.toString(); break;
            case 8:
                filetrs->data()[index.row()].lineBegin = value.toInt(); break;
            case 9:
                filetrs->data()[index.row()].lineEnd = value.toInt(); break;
            case 10:
                filetrs->data()[index.row()].text = value.toString(); break;
            default:
                return false;
                break;
        }
        return true;

    }


    return QAbstractTableModel::setData(index, value, role);
}

Qt::ItemFlags DebugerFilterModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.column() >= 11)
        return QAbstractTableModel::flags(index);

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    if(index.column() == 0)
        flags |= Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    else if((index.column() >= 1) && (index.column() <= 5))
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    else if((index.column() >= 6) && (index.column() <= 10))
        flags |= Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return flags;
}
