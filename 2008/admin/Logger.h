
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _Logger_h
#define _Logger_h

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QString>
#include <QMutex>
#include <QMutexLocker>

#include "Global.h"



class Logger
{
	public:
		typedef enum
		{
			INFORMATION = 1,
			WARNING = 2,
			CRITICAL = 4,
			FATAL = 6
		} LoggerLevel;

		Logger();
		virtual ~Logger();

		static Logger* instance();

		void logEvent(QtMsgType type, const char* message);

	private:
		QMutex mutex;
		QString format;
		QFile file;
		QTextStream log;
};

static void logHandler(QtMsgType type, const char* message)
{
	Logger* log = Logger::instance();
	log->logEvent(type, message);
}

#endif

