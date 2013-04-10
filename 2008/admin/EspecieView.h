
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _EspecieView_h
#define _EspecieView_h

#include <QWidget>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QModelIndex>
#include <QItemSelection>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlQueryModel>

#include "Global.h"
#include "Especie.h"
#include "AbstractItemView.h"



class EspecieView : public AbstractItemView
{
	public:
		EspecieView(QWidget* parent = 0);

	protected slots:
		void newClicked();
		void editClicked();
		void viewClicked();
		void deleteClicked();
		void printClicked();
		void closeClicked();

		void select();

	private:
		Q_OBJECT

		QSqlTableModel* model;
};

#endif

