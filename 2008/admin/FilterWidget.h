
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _FilterWidget_h
#define _FilterWidget_h

#include <QWidget>

#include <QString>
#include <QLabel>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <QMessageBox>



class FilterWidget : public QWidget
{
	public:
		FilterWidget(QWidget* parent = 0);

		const QSqlQuery& query() const;

	private:
		Q_OBJECT
};

#endif

