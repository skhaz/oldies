
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _MateriaPrima_h
#define _MateriaPrima_h

#include <QDialog>
#include <QWidget>
#include <QMessageBox>
#include <QString>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQueryModel>

#include <QRegExp>
#include <QRegExpValidator>
#include <QDoubleValidator>
#include <QStringListModel>

#include <QList>
#include <QColor>
#include <QPixmap>
#include <QPixmapCache>
#include <QBitmap>
#include <QLocale>

#include "Global.h"
#include "ui_MateriaPrima.h"



class MateriaPrima : public QDialog, private Ui_MateriaPrima
{
	public:
		MateriaPrima(QWidget* parent = 0);

		void setParam(const ParameterList& param);

	signals:
		void dataChanged();

	protected:

	protected slots:
		void buildMaterialString();
		void submitClicked();
		void cancelClicked();

		void materialIndexChanged(int index);
		void tipoIndexChanged(int index = 0);

		void calculaPesoLinear();

	private:
		Q_OBJECT

		QSqlQuery query;
		QPixmapCache cache;
};

#endif

