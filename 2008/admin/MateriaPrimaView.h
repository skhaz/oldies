
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _MateriaPrimaView_h
#define _MateriaPrimaView_h

#include <QWidget>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QModelIndex>
#include <QList>
#include <QItemSelection>
#include <QRadioButton>
#include <QLayout>
#include <QCheckBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QStringList>
#include <QCompleter>

#include "Global.h"
#include "AbstractItemView.h"
#include "MateriaPrima.h"



class MateriaPrimaView : public AbstractItemView
{
	public:
		MateriaPrimaView(QWidget* parent = 0);

	protected slots:
		void newClicked();
		void editClicked();
		void viewClicked();
		void deleteClicked();
		void printClicked();
		void filterChanged(const QString& text);

		void select();

	private:
		Q_OBJECT

		QSqlTableModel* model;
		QCompleter* completer;
		QSqlQueryModel* filterModel;
		QModelIndex currentIndex;
		QItemSelection currentSelection;
};

#endif

