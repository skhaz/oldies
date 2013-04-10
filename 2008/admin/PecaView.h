
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _PecaView_h
#define _PecaView_h

#include <QWidget>
#include <QMessageBox>
#include <QModelIndex>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "Global.h"
#include "Peca.h"
#include "AbstractItemView.h"



class PecaView : public AbstractItemView
{
	public:
		PecaView(QWidget* parent = 0);

	protected slots:
		void newClicked();
		void editClicked();
		void viewClicked();
		void deleteClicked();
		void printClicked();

		void populate();

	private:
		Q_OBJECT

		QSqlTableModel* model;
		QModelIndex currentIndex;
};

#endif

