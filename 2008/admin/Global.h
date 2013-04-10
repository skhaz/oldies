
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _Global_h
#define _Global_h

#include <QtDebug>
#include <QtGlobal>
#include <QMap>
#include <QString>
#include <QVariant>

#define Utf8(s) QString::fromUtf8(s)

typedef QMap<QString, QString> ParameterList;

#define DEBUG qDebug << __FILE__ << '(' << __LINE__ << ") : "


// QRegExp emailRegex("^[a-zA-Z][\\w\\.-]*[a-zA-Z0-9]@[a-zA-Z0-9][\\w\\.-]*[a-zA-Z0-9]\\.[a-zA-Z][a-zA-Z\\.]*[a-zA-Z]$");
// Pingar no dominio

#endif

