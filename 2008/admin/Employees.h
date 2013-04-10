
/*
 *
 *
 *
 *
 *
 */

#ifndef _Employees_h
#define _Employees_h

#include <QWidget>
#include <QMessageBox>
#include <QTableWidgetItem>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "AbstractItemView.h"



class Employees : public AbstractItemView
{
	public:
		Employees(QWidget* parent = 0);

	protected slots:
		void newClicked();
		void editClicked();
		void viewClicked();
		void deleteClicked();
		void printClicked();
		void closeClicked();

	private:
		Q_OBJECT

		QSqlTableModel* model;
};

#endif

