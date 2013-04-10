
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _Programa_h
#define _Programa_h

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "Global.h"

#include "ui_Programa.h"



class Programa : public QDialog, private Ui_Programa
{
	public:
		Programa(QWidget* parent = 0);

	signals:
		void dataChanged();

	public slots:
		void setParam(const ParameterList& param);

	protected slots:
		void submitClicked();
		void importClicked();
		void exportClicked();

	private:
		Q_OBJECT

		QSqlQuery query;
};

#endif

