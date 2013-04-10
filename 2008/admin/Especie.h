
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _Especie_h
#define _Especie_h

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "Global.h"

#include "ui_Especie.h"



class Especie : public QDialog, private Ui_Especie
{
	public:
		Especie(QWidget* parent = 0);

		void setParam(const ParameterList& param);

	signals:
		void dataChanged();

	protected slots:
		void cancelClicked();
		void submitClicked();

	private:
		Q_OBJECT

		QSqlQuery query;
};

#endif

