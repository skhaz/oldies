
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _Material_h
#define _Material_h

#include <QWidget>
#include <QDialog>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <QRegExp>
#include <QRegExpValidator>
#include <QDoubleValidator>

#include "Global.h"
#include "ui_Material.h"



class Material : public QDialog, private Ui_Material
{
	public:
		Material(QWidget* parent = 0);

		void setParam(const ParameterList& param);

	signals:
		void dataChanged();

	protected slots:
		void cancelClicked();
		void submitClicked();

	private:
		Q_OBJECT

		bool yetSaved;
		QSqlQuery query;
};

#endif

