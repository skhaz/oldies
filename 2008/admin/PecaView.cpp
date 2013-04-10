
/*
 *
 *
 *
 *
 *
 *
 */

#include "PecaView.h"



PecaView::PecaView(QWidget* parent)
: AbstractItemView(parent)
, model(new QSqlTableModel(this))
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(Utf8("Peças"));
	filterEdit->hide();

	model->setTable("pecas");

	tableView->setModel(model);

	model->setHeaderData(0, Qt::Horizontal, Utf8("Cod"));
	model->setHeaderData(1, Qt::Horizontal, Utf8("Nome"));
	model->setHeaderData(2, Qt::Horizontal, Utf8("Preço"));
	tableView->setColumnWidth(0, 50);
	tableView->setColumnWidth(1, 440);
	tableView->setColumnWidth(2, 60);

	populate();

	connect(closeButton, SIGNAL(clicked()), SLOT(close()));
}

void PecaView::newClicked()
{
	Peca* detail = new Peca(this);
	connect(detail, SIGNAL(dataChanged()), SLOT(populate()));

	ParameterList param;
	param["mode"] = "new";

	detail->setParam(param);
	detail->show();
}

void PecaView::editClicked()
{
	if (tableView->currentIndex().row() >= 0)
	{
		QSqlRecord record = model->record(tableView->currentIndex().row());

		Peca* detail = new Peca(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(populate()));

		ParameterList param;
		param["cod"] = record.value("cod_peca").toString();
		param["mode"] = "edit";

		detail->setParam(param);
		detail->show();
	}
}

void PecaView::viewClicked()
{
	if (tableView->currentIndex().row() >= 0)
	{
		QSqlRecord record = model->record(tableView->currentIndex().row());

		Peca* detail = new Peca(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(populate()));

		ParameterList param;
		param["cod"] = record.value("cod_peca").toString();
		param["mode"] = "view";

		detail->setParam(param);
		detail->show();
	}
}

void PecaView::deleteClicked()
{
	if (tableView->currentIndex().row() < 0)
	{
		return;
	}

	QSqlRecord record = model->record(tableView->currentIndex().row());
	uint cod = record.value("cod_peca").toUInt();
	QString nome = record.value("nome").toString();

	QMessageBox messageBox(QMessageBox::Question, "Admin",
			Utf8("Confirma a exclusão do registro <b>%1</b>?").arg(nome), QMessageBox::Yes | QMessageBox::No, this);

	if (messageBox.exec() == QMessageBox::Yes)
	{
		QSqlDatabase database = QSqlDatabase::database();
		database.transaction();

		QSqlQuery sql;

		sql.clear();
		sql.prepare("delete from desenhopecas where cod_peca = :cod");
		sql.bindValue(":cod", cod);

		if (sql.exec())
		{
			sql.clear();
			sql.prepare("delete from desenhos where cod_desenho in (select cod_desenho from desenhopecas where cod_peca = :cod)");
			sql.bindValue(":cod", cod);

			if (sql.exec())
			{
			}

			else {
				QMessageBox::warning(this, "Admin",
					Utf8("Erro ao excluir o registro\n%1").arg(sql.lastError().text()));
			}
		}

		else
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao excluir o registro\n%1").arg(sql.lastError().text()));
		}

		sql.clear();
		sql.prepare("delete from programaspecas where cod_peca = :cod");
		sql.bindValue(":cod", cod);

		if (sql.exec())
		{
			sql.clear();
			sql.prepare("delete from programas where cod_programa in (select cod_programa from programaspecas where cod_peca = :cod)");
			sql.bindValue(":cod", cod);

			if (sql.exec())
			{
			}

			else {
				QMessageBox::warning(this, "Admin",
					Utf8("Erro ao excluir o registro\n%1").arg(sql.lastError().text()));
			}
		}

		else
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao excluir o registro\n%1").arg(sql.lastError().text()));
		}

		sql.clear();
		sql.prepare("delete from materiaprimapecas where cod_peca = :cod");
		sql.bindValue(":cod", cod);

		if (sql.exec())
		{
		}

		else {
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao excluir o registro\n%1").arg(sql.lastError().text()));
		}

		sql.clear();
		sql.prepare("delete from pecas where cod_peca = :cod");
		sql.bindValue(":cod", cod);

		if (sql.exec())
		{
		}

		else {
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao excluir o registro\n%1").arg(sql.lastError().text()));
		}

		QSqlError error = database.lastError();

		if (error.type() != QSqlError::NoError)
		{
			database.rollback();

			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao excluir o registro\n%1").arg(error.text()));
		}

		else {
			database.commit();
			populate();
		}
	}
}

void PecaView::printClicked()
{
}

void PecaView::populate()
{
	if (model->select())
	{
	}

	else {
		QMessageBox::warning(this, "Admin",
			Utf8("Erro ao executar a requisição\n%1").arg(model->lastError().text()));
	}
}

