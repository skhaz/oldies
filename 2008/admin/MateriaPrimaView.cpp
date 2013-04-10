
/*
 *
 *
 *
 *
 *
 *
 */

#include "MateriaPrimaView.h"



MateriaPrimaView::MateriaPrimaView(QWidget* parent)
: AbstractItemView(parent)
, model(new QSqlTableModel(this))
, completer(new QCompleter(this))
, filterModel(new QSqlQueryModel(this))
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(Utf8("Matéria Prima"));

	model->setTable("materiaprima");

	model->setHeaderData(0, Qt::Horizontal, Utf8("Cod"));
	model->setHeaderData(1, Qt::Horizontal, Utf8("Nome"));

	tableView->setModel(model);
	tableView->setColumnWidth(0, 50);
	tableView->setColumnWidth(1, 476);

	tableView->setColumnHidden(2, true);
	tableView->setColumnHidden(3, true);
	tableView->setColumnHidden(4, true);
	tableView->setColumnHidden(5, true);
	tableView->setColumnHidden(6, true);
	tableView->setColumnHidden(7, true);
	tableView->setColumnHidden(8, true);
	tableView->setColumnHidden(9, true);
	tableView->setColumnHidden(10, true);
	tableView->setColumnHidden(11, true);
	tableView->setColumnHidden(12, true);
	tableView->setColumnHidden(13, true);

	completer->setModel(filterModel);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setCompletionMode(QCompleter::PopupCompletion);
	completer->setWidget(filterEdit);
	filterEdit->setCompleter(completer);

	select();

	connect(filterEdit, SIGNAL(textChanged(const QString&)), SLOT(filterChanged(const QString&)));
}

void MateriaPrimaView::newClicked()
{
	MateriaPrima* detail = new MateriaPrima(this);
	connect(detail, SIGNAL(dataChanged()), SLOT(select()));

	ParameterList param;
	param["mode"] = "new";

	detail->setParam(param);
	detail->show();
}

void MateriaPrimaView::editClicked()
{
	if (tableView->currentIndex().row() >= 0)
	{
		QSqlRecord record = model->record(tableView->currentIndex().row());

		MateriaPrima* detail = new MateriaPrima(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(select()));

		ParameterList param;
		param["cod"] = record.value("cod_materiaprima").toString();
		param["mode"] = "edit";
		detail->setParam(param);
		detail->show();
	}
}

void MateriaPrimaView::viewClicked()
{
	if (tableView->currentIndex().row() >= 0)
	{
		QSqlRecord record = model->record(tableView->currentIndex().row());

		MateriaPrima* detail = new MateriaPrima(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(select()));

		ParameterList param;
		param["cod"] = record.value("cod_materiaprima").toString();
		param["mode"] = "view";

		detail->setParam(param);
		detail->show();
	}
}

void MateriaPrimaView::deleteClicked()
{
	if (tableView->currentIndex().row() < 0)
	{
		return;
	}

	QSqlRecord record = model->record(tableView->currentIndex().row());
	int cod = record.value("cod_materiaprima").toInt();
	QString nome = record.value("nome").toString();

	QMessageBox messageBox(QMessageBox::Question, "Admin",
			Utf8("Confirma a exclusão do registro <b>%1</b>?").arg(nome),
					QMessageBox::Yes | QMessageBox::No, this);

	if (messageBox.exec() == QMessageBox::Yes)
	{
		QSqlQuery sql;
		sql.prepare("delete from materiaprima where cod_materiaprima = :cod");
		sql.bindValue(":cod", cod);

		if (!sql.exec())
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao deletar o registro\n%1").arg(sql.lastError().text()) );
		}

		model->select();
	}
}

void MateriaPrimaView::printClicked()
{
}

void MateriaPrimaView::filterChanged(const QString& text)
{
	QString filter, query;
	QStringList list = text.split(" ", QString::SkipEmptyParts);

	for (int i = 0; i < list.size(); ++i) {
		filter.append(QString(" %1 nome ILIKE '\%%2\%'").arg(list.size() > 1 && i != 0 ? " AND " : " ").arg(list.at(i)));
	}

	model->setFilter(filter);
}

void MateriaPrimaView::select()
{
	if (model->select())
	{
	}

	else {
		QMessageBox::warning(this, "Admin",
			Utf8("Erro ao executar a requisição\n%1").arg(model->lastError().text()) );
	}

	filterModel->setQuery("SELECT nome FROM materiaprima");
}

