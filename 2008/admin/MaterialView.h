
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _MaterialView_h
#define _MaterialView_h

#include <QWidget>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QModelIndex>
#include <QList>
#include <QStringList>
#include <QItemSelection>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "Global.h"
#include "Material.h"
#include "AbstractItemView.h"



class MaterialView : public AbstractItemView
{
	public:
		MaterialView(QWidget* parent = 0);

	protected slots:
		void selectionChanged(const QItemSelection& index);

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
		QModelIndex currentIndex;
};

#endif

