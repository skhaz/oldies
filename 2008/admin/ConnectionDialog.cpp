
/*
 *
 *
 *
 *
 *
 */

#include "ConnectionDialog.h"



ConnectionDialog::ConnectionDialog(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	QStringList drivers = QSqlDatabase::drivers();
	drivers.removeAll("QMYSQL3");
	drivers.removeAll("QOCI8");
	drivers.removeAll("QODBC3");
	drivers.removeAll("QPSQL7");
	drivers.removeAll("QTDS7");

	comboDriver->addItems(drivers);
}

