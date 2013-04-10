
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _LoggerEngine_h
#define _LoggerEngine_h

#include <QString>
#include <QMutex>
#include <QHash>
#include <QDateTime>



class LoggerEngine
{
	public:
		LoggerEngine();

	private:
		QHash<QString, QString> loggers;
};

#endif

