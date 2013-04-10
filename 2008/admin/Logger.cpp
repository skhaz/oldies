
/*
 *
 *
 *
 *
 *
 *
 */

#include "Logger.h"



Logger::Logger()
: format("[%d] %m")
, file("log.txt")
{
	if (file.open(QIODevice::Append | QIODevice::Text))
	{
		log.setDevice(&file);
	}

	else {
		qInstallMsgHandler(0);
	}
}

Logger::~Logger()
{
	file.close();
}

Logger* Logger::instance()
{
	static Logger instance;
	return &instance;
}

void Logger::logEvent(QtMsgType type, const char* message)
{
	QMutexLocker locker(&mutex);

	QDateTime dateTime = QDateTime::currentDateTime();
	QString level;
	level.reserve(8);

	switch (type)
	{
		case QtDebugMsg:
			level = " [DEBU] ";
			break;

		case QtWarningMsg:
			level = " [WARN] ";
			break;

		case QtCriticalMsg:
			level = " [CRIT] ";
			break;

		case QtFatalMsg:
			level = " [FATA] ";
			break;

		default:
			level = " [INVA] ";
			break;
	}

	log << dateTime.toString("dd/MM/yyyy hh:mm:ss.zzz") << level << message << endl;
}

