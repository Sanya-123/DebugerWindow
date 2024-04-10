#ifndef DEBUGERFILTER_H
#define DEBUGERFILTER_H

#include <QObject>

typedef struct _DebugerFilter{
    _DebugerFilter() {
        enDebug = enInfo = enWarnings = enCritical = enFatal = true;
        en = true;
        lineBegin = -1;
        lineEnd = -1;
    }
    bool enDebug, enInfo, enWarnings, enCritical, enFatal;
    bool en;
    QString file;
    QString function;
    int lineBegin;
    int lineEnd;
    QString name;
    QString text;
}DebugerFilter;

#endif // DEBUGERFILTER_H
