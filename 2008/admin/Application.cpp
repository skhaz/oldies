
/*
 *
 *
 *
 *
 *
 */

#include "Application.h"


#include <QtDebug>

Application::Application(int& argc, char** argv)
: QApplication(argc, argv)
{
	qInstallMsgHandler(logHandler);

	Q_INIT_RESOURCE(Media);

	QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL");
	database.setHostName("localhost");
	database.setDatabaseName("admin");
	database.setUserName("postgres");
	database.setPassword("postgres");

	if (database.open())
	{
	}

	else {
		QSqlError error(database.lastError());
		QMessageBox messageBox;
		messageBox.setWindowTitle("Admin");
		messageBox.setText(QString::fromUtf8("Não foi possível conectar-se ao banco de dados!"));
		messageBox.setIcon(QMessageBox::Critical);
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setDetailedText(error.text());

		switch(messageBox.exec())
		{
			case QMessageBox::Ok:
				break;

			default:
				break;
		}
	}

	//QTimer::singleShot(0, this, SLOT(postLaunch()));
}

Application::~Application()
{
}

void Application::postLaunch()
{
	QFile file(":/media/style/dark.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());

	qApp->setStyleSheet(styleSheet);
}

