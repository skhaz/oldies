
/*
 *
 *
 *
 *
 *
 *
 */

#include "SqlComboBox.h"



SqlComboBox::SqlComboBox(QWidget* parent)
: QComboBox(parent)
{
}

void SqlComboBox::setQuery(const QSqlQuery& query)
{

}

void SqlComboBox::setQuery(const QString& query)
{
	QSqlQuery sql;

	if (sql.exec(query)) {
		while (sql.next())
		{
			addItem(sql.value(1).toString(),
				sql.value(0).toInt());
		}
	}

	setCurrentIndex(-1);
}

