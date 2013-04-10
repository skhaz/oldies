
/*
 *
 *
 *
 *
 *
 */

#ifndef _Application_h
#define _Application_h

#include <QFile>
#include <QString>
#include <QTimer>
#include <QCoreApplication>
#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QPixmapCache>
#include "SplashScreen.h"
#include "Logger.h"



class Application : public QApplication
{
	public:
		Application(int& argc, char** argv);
		~Application();

	protected slots:
		void postLaunch();

	private:
		Q_OBJECT
};

#endif

