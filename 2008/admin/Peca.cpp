
/*
 *
 *
 *
 *
 *
 *
 */

#include "Peca.h"



Peca::Peca(QWidget* parent)
: QDialog(parent)
, materiaisModel(new QSqlQueryModel(this))
, programasModel(new QSqlQueryModel(this))
, desenhosModel(new QSqlQueryModel(this))
{
	setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(Utf8("Peça"));

	newMaterialButton->hide();
	materialCombo->setQuery("select cod_materiaprima, nome from materiaprima");

	connect(submitButton, SIGNAL(clicked()), SLOT(submitClicked()));
	connect(closeButton, SIGNAL(clicked()), SLOT(close()));

	connect(addMaterialButton, SIGNAL(clicked()), SLOT(addMaterialClicked()));
	connect(removeMaterialButton, SIGNAL(clicked()), SLOT(removeMaterialClicked()));
	connect(newMaterialButton, SIGNAL(clicked()), SLOT(newMaterialClicked()));
	connect(addDesenhoButton, SIGNAL(clicked()), SLOT(addDesenhoClicked()));
	connect(removeDesenhoButton, SIGNAL(clicked()), SLOT(removeDesenhoClicked()));
	connect(addProgramaButton, SIGNAL(clicked()), SLOT(addProgramaClicked()));
	connect(removeProgramaButton, SIGNAL(clicked()), SLOT(removeProgramaClicked()));

	connect(materialView, SIGNAL(doubleClicked(QModelIndex)), SLOT(materialViewClicked()));
	connect(desenhoView, SIGNAL(doubleClicked(QModelIndex)), SLOT(desenhoViewClicked()));
	connect(programaView, SIGNAL(doubleClicked(QModelIndex)), SLOT(programaViewClicked()));
}

void Peca::setParam(const ParameterList& param)
{
	nomeEdit->clear();
	totalSpin->clear();

	cod_peca = param["cod"].toInt();

	query.clear();

	populate();

	materiaisModel->setHeaderData(0, Qt::Horizontal, Utf8("Cod"));
	materiaisModel->setHeaderData(1, Qt::Horizontal, Utf8("Nome"));
	materiaisModel->setHeaderData(2, Qt::Horizontal, Utf8("Quantidade"));
	materiaisModel->setHeaderData(3, Qt::Horizontal, Utf8("Preço"));

	materialView->setModel(materiaisModel);
	materialView->setColumnWidth(1, 485);
	materialView->setColumnWidth(2, 80);
	materialView->setColumnWidth(3, 80);
	materialView->setColumnHidden(0, true);
	materialView->setColumnHidden(4, true);

	desenhoView->setModel(desenhosModel);
	desenhosModel->setHeaderData(0, Qt::Horizontal, Utf8("Cod"));
	desenhosModel->setHeaderData(1, Qt::Horizontal, Utf8("Nome"));
	desenhoView->setColumnWidth(0, 50);
	desenhoView->setColumnWidth(1, 590);

	programaView->setModel(programasModel);
	programasModel->setHeaderData(0, Qt::Horizontal, Utf8("Cod"));
	programasModel->setHeaderData(1, Qt::Horizontal, Utf8("Nome"));
	programaView->setColumnWidth(0, 50);
	programaView->setColumnWidth(1, 590);
	
	if (param["mode"] != "new")
	{
		QSqlQuery sql;

		sql.prepare("select cod_peca, nome, preco from pecas where cod_peca = :cod limit 1");
		sql.bindValue(":cod", cod_peca);

		if (sql.exec())
		{
			sql.first();

			setWindowTitle(Utf8("Peça (%1)").arg(sql.value(sql.record().indexOf("nome")).toString()));

			nomeEdit->setText(sql.value(sql.record().indexOf("nome")).toString());
			totalSpin->setValue(sql.value(sql.record().indexOf("preco")).toDouble());

			submitButton->setText("&Gravar");

			query.prepare("update pecas set nome = :nome, preco = :preco where cod_peca = :cod");
			query.bindValue(":cod", cod_peca);

			if (param["mode"] == "view")
			{
				submitButton->hide();

				nomeEdit->setEnabled(false);
				addMaterialButton->setEnabled(false);
				addProgramaButton->setEnabled(false);
				addDesenhoButton->setEnabled(false);
				removeMaterialButton->setEnabled(false);
				removeProgramaButton->setEnabled(false);
				removeDesenhoButton->setEnabled(false);
			}

		}

		else {
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao executar a requisição\n%1").arg(sql.lastError().text()));
		}
	}

	else {
		submitButton->setText("I&nserir");

		query.prepare("insert into pecas (nome, preco) values (:nome, :preco)");
	}
}

void Peca::submitClicked()
{
	query.bindValue(":nome", nomeEdit->text());
	query.bindValue(":preco", totalSpin->value()); 

	if (query.exec())
	{
		emit dataChanged();

		ParameterList param;
		param["mode"] = "new";
		setParam(param);
	}

	else {
		QMessageBox::warning(this, "Admin",
			Utf8("Houve um erro ao inserir\n%1").arg(query.lastError().text()));
	}
}

void Peca::addMaterialClicked()
{
	if (materialCombo->currentIndex() != -1)
	{
		QSqlQuery sql;

		sql.prepare(
				" insert into materiaprimapecas (cod_peca,    "
				" cod_materiaprima, quantidade) values        "
			    " (:cod_peca, :cod_materiaprima, :quantidade) "
			);

		sql.bindValue(":cod_peca", cod_peca);
		sql.bindValue(":cod_materiaprima", materialCombo->itemData(materialCombo->currentIndex()).toUInt());
		sql.bindValue(":quantidade", quantidadeSpin->value());

		if (!sql.exec())
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Houve um erro ao inserir\n%1").arg(sql.lastError().text()));
		}

		quantidadeSpin->setValue(1);
		materialCombo->setCurrentIndex(-1);

		populate();
	}

	else {
		QMessageBox::warning(this, "Admin", Utf8("Nenhum item selecionado"));
	}
}

void Peca::removeMaterialClicked()
{
	if (materialView->currentIndex().row() < 0)
	{
		return;
	}

	QSqlRecord record = materiaisModel->record(materialView->currentIndex().row());
	int cod_materiaprimapecas = record.value("cod_materiaprimapecas").toInt();
	QString nome = record.value("nome").toString();

	QMessageBox messageBox(QMessageBox::Question, "Admin",
			Utf8("Confirma a exclusão do registro <b>%1</b>?").arg(nome),
					QMessageBox::Yes | QMessageBox::No, this);

	if (messageBox.exec() == QMessageBox::Yes)
	{
		QSqlQuery sql;
		sql.prepare("delete from materiaprimapecas where cod_materiaprimapecas = :cod");

		sql.bindValue(":cod", cod_materiaprimapecas);

		if (sql.exec())
		{
			populate();
		}

		else {
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao deletar o registro\n%1").arg(sql.lastError().text()));
		}
	}
}

void Peca::newMaterialClicked()
{
	MateriaPrima* detail = new MateriaPrima(this);
	connect(detail, SIGNAL(dataChanged()), SLOT(populate()));

	ParameterList param;
	param["mode"] = "new";

	detail->setParam(param);
	detail->show();
}

void Peca::addDesenhoClicked()
{
	uint lastInserted = 0;
	QSqlQuery sql1, sql2;

	sql1.prepare(Utf8("insert into desenhos (nome) values ('Sem título') returning cod_desenho"));

	if (sql1.exec())
	{
		if( sql1.isActive())
		{
			sql1.next();
			lastInserted = sql1.record().value("cod_desenho").toUInt();
		}

		sql2.prepare("insert into desenhopecas (cod_desenho, cod_peca) values (:cod_desenho, :cod_peca)");
		sql2.bindValue(":cod_desenho", lastInserted);
		sql2.bindValue(":cod_peca", cod_peca);

		if (sql2.exec())
		{
			ParameterList param;
			param["cod"] = QString::number(lastInserted);
	
			PictureView* detail = new PictureView(this);
			detail->setParam(param);
			detail->show();

			populate();
		}

		else {
			QMessageBox::warning(this, "Admin",
				Utf8("Houve um erro ao inserir\n%1").arg(sql2.lastError().text()));
		}
	}

	else {
		QMessageBox::warning(this, "Admin",
			Utf8("Houve um erro ao inserir\n%1").arg(sql1.lastError().text()));
	}
}

void Peca::removeDesenhoClicked()
{
	if (desenhoView->currentIndex().row() < 0)
	{
		return;
	}

	QSqlRecord record = desenhosModel->record(desenhoView->currentIndex().row());
	uint cod_desenho = record.value("cod_desenho").toUInt();
	QString nome = record.value("nome").toString();

	QMessageBox messageBox(QMessageBox::Question, "Admin",
			Utf8("Confirma a exclusão do registro <b>%1</b>?").arg(nome),
					QMessageBox::Yes | QMessageBox::No, this);

	if (messageBox.exec() == QMessageBox::Yes)
	{
		QSqlQuery sql1, sql2;

		sql1.prepare("delete from desenhopecas where cod_desenho = :cod");
		sql1.bindValue(":cod", cod_desenho);

		if (sql1.exec())
		{
			sql2.prepare("delete from desenhos where cod_desenho = :cod");
			sql2.bindValue(":cod", cod_desenho);

			if (sql2.exec())
			{
				populate();
			}

			else {
				QMessageBox::warning(this, "Admin",
					Utf8("Erro ao deletar o registro\n%1").arg(sql2.lastError().text()));
			}
		}

		else {
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao deletar o registro\n%1").arg(sql1.lastError().text()));
		}
	}
}

void Peca::addProgramaClicked()
{
	uint lastInserted = 0;
	QSqlQuery sql1, sql2;

	sql1.prepare(Utf8(" insert into programas (nome) values ('Sem título') returning cod_programa "));

	if (sql1.exec())
	{
		if( sql1.isActive())
		{
			sql1.next();
			lastInserted = sql1.record().value("cod_programa").toUInt();
		}

		sql2.prepare("insert into programaspecas (cod_programa, cod_peca) values (:cod_programa, :cod_peca)");
		sql2.bindValue(":cod_programa", lastInserted);
		sql2.bindValue(":cod_peca", cod_peca);

		if (sql2.exec())
		{
			ParameterList param;
			param["cod"] = QString::number(lastInserted);
	
			Programa* detail = new Programa(this);
			detail->setParam(param);
			detail->show();

			connect(detail, SIGNAL(dataChanged()), SLOT(populate()));
			populate();
		}

		else {
			QMessageBox::warning(this, "Admin",
				Utf8("Houve um erro ao inserir\n%1").arg(sql2.lastError().text()));
		}
	}

	else {
		QMessageBox::warning(this, "Admin",
			Utf8("Houve um erro ao inserir\n%1").arg(sql1.lastError().text()));
	}
}

void Peca::removeProgramaClicked()
{
	if (programaView->currentIndex().row() < 0)
	{
		return;
	}

	QSqlRecord record = programasModel->record(programaView->currentIndex().row());
	uint cod_programa = record.value("cod_programa").toUInt();
	QString nome = record.value("nome").toString();

	QMessageBox messageBox(QMessageBox::Question, "Admin",
			Utf8("Confirma a exclusão do registro <b>%1</b>?").arg(nome),
					QMessageBox::Yes | QMessageBox::No, this);

	if (messageBox.exec() == QMessageBox::Yes)
	{
		QSqlQuery sql1, sql2;

		sql1.prepare("delete from programaspecas where cod_programa = :cod");
		sql1.bindValue(":cod", cod_programa);

		if (sql1.exec())
		{
			sql2.prepare("delete from programas where cod_programa = :cod");
			sql2.bindValue(":cod", cod_programa);

			if (sql2.exec())
			{
				populate();
			}

			else {
				QMessageBox::warning(this, "Admin",
					Utf8("Erro ao deletar o registro\n%1").arg(sql2.lastError().text()));
			}
		}

		else {
			QMessageBox::warning(this, "Admin",
				Utf8("Erro ao deletar o registro\n%1").arg(sql1.lastError().text()));
		}
	}
}

void Peca::materialViewClicked()
{
	if (materialView->currentIndex().row() >= 0)
	{
		QSqlRecord record = materiaisModel->record(materialView->currentIndex().row());

		MateriaPrima* detail = new MateriaPrima(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(select()));

		ParameterList param;
		param["cod"] = record.value("cod_materiaprima").toString();
		param["mode"] = "edit";

		detail->setParam(param);

		connect(detail, SIGNAL(dataChanged()), SLOT(populate()));
		detail->show();
	}
}

void Peca::desenhoViewClicked()
{
	if (desenhoView->currentIndex().row() >= 0)
	{
		QSqlRecord record = desenhosModel->record(desenhoView->currentIndex().row());

		PictureView* detail = new PictureView(this);

		ParameterList param;
		param["cod"] = record.value("cod_desenho").toString();
		param["mode"] = "edit";

		detail->setParam(param);

		connect(detail, SIGNAL(dataChanged()), SLOT(populate()));
		detail->show();
	}
}

void Peca::programaViewClicked()
{
	if (programaView->currentIndex().row() >= 0)
	{
		QSqlRecord record = programasModel->record(programaView->currentIndex().row());

		Programa* detail = new Programa(this);

		ParameterList param;
		param["cod"] = record.value("cod_programa").toString();
		param["mode"] = "edit";

		detail->setParam(param);

		connect(detail, SIGNAL(dataChanged()), SLOT(populate()));
		detail->show();
	}
}

void Peca::populate()
{
	materiaisModel->setQuery(QString(
				" select r.cod_materiaprimapecas, m.nome, r.quantidade, m.preco,    "
				" m.cod_materiaprima from materiaprimapecas r, materiaprima m       "
				" where r.cod_peca = %1 and r.cod_materiaprima = m.cod_materiaprima "
			).arg(cod_peca)
		);

	if (materiaisModel->lastError().isValid())
	{
		QMessageBox::warning(this, "Admin",
			Utf8("Erro ao executar a requisição\n%1").arg(materiaisModel->lastError().text()));
	}

	desenhosModel->setQuery(QString(
				" select d.cod_desenho, d.nome from desenhos d, desenhopecas p "
				" where d.cod_desenho = p.cod_desenho and p.cod_peca = %1      "
			).arg(cod_peca)
		);

	if (desenhosModel->lastError().isValid())
	{
		QMessageBox::warning(this, "Admin",
			Utf8("Erro ao executar a requisição\n%1").arg(desenhosModel->lastError().text()));
	}

	programasModel->setQuery(QString(
				" select d.cod_programa, d.nome from programas d, programaspecas p "
				" where p.cod_programa = d.cod_programa and p.cod_peca = %1        "
			).arg(cod_peca)
		);

	if (programasModel->lastError().isValid())
	{
		QMessageBox::warning(this, "Admin",
			Utf8("Erro ao executar a requisição\n%1").arg(programasModel->lastError().text()));
	}

	float total = .0f;
	for (int index = 0; index <= materiaisModel->rowCount(); ++index)
	{
		QSqlRecord record = materiaisModel->record(index);
		total += record.value("preco").toDouble() * record.value("quantidade").toDouble();
	}

	materialSubTotalSpin->setValue(total);
}

