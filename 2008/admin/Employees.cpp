
/*
 *
 *
 *
 *
 *
 */

#include "Employees.h"



Employees::Employees(QWidget* parent)
: AbstractItemView(parent)
, model(new QSqlTableModel(this))
{
	setAttribute(Qt::WA_DeleteOnClose);

	model->setTable("employees");
	model->setHeaderData(1, Qt::Horizontal, "Nome");

	tableView->setModel(model);
	tableView->setColumnHidden(0, true);
	tableView->setColumnWidth(1, 400);

	if (!model->select())
	{
		QMessageBox::warning(this, "Admin",
			QString::fromUtf8("Erro ao executar a requisição\1%1").arg(model->lastError().text()) );
	}
}

void Employees::newClicked()
{
}

void Employees::editClicked()
{
}

void Employees::viewClicked()
{
}

void Employees::deleteClicked()
{
}

void Employees::printClicked()
{
}

void Employees::closeClicked()
{
	close();
}

