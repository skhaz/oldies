
/*
 *
 *
 *
 *
 *
 *
 */

#include "FilterWidget.h"


FilterWidget::FilterWidget(QWidget* parent)
: QWidget(parent)
{
}

const QSqlQuery& FilterWidget::query() const
{
	return QSqlQuery();
}

