
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _SqlComboBox_h
#define _SqlComboBox_h

#include <QString>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <QComboBox>



class SqlComboBox : public QComboBox
{
	public:
		SqlComboBox(QWidget* parent = 0);

	public slots:
		void setQuery(const QSqlQuery& query);
		void setQuery(const QString& query);
};

#endif

