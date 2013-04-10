
/*
 *
 *
 *
 *
 *
 *
 */

#include "PictureView.h"



PictureView::PictureView(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);

	label = new QLabel(this);
	label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(label);

	connect(submitButton, SIGNAL(clicked()), SLOT(submitClicked()));
	connect(importButton, SIGNAL(clicked()), SLOT(importClicked()));
	connect(exportButton, SIGNAL(clicked()), SLOT(exportClicked()));
	connect(closeButton, SIGNAL(clicked()), SLOT(close()));
}

void PictureView::setParam(const ParameterList& param)
{
	query.clear();
	uint cod = param["cod"].toUInt();

	if (cod != 0)
	{
		QSqlQuery sql1, sql2;

		query.prepare("update desenhos set nome = :nome, desenho = :desenho where cod_desenho = :cod");
		query.bindValue(":cod", cod);

		sql1.prepare("select nome, desenho from desenhos where cod_desenho = :cod limit 1");
		sql1.bindValue(":cod", cod);

		sql2.prepare(Utf8(
					" select p.nome as nome from pecas p, desenhopecas d   "
					" where d.cod_peca = p.cod_peca and d.cod_desenho = %1 "
				).arg(cod)
			);

		if (sql2.exec())
		{
			sql2.first();

			setWindowTitle(Utf8("Desenho [%1]").arg(
						sql2.value(sql2.record().indexOf("nome")).toString()));
		}

		if (sql1.exec())
		{
			sql1.first();

			nomeEdit->setText(sql1.value(sql1.record().indexOf("nome")).toString());

			QPixmap pixmap;
			pixmap.loadFromData(sql1.value(sql1.record().indexOf("desenho")).toByteArray());
			label->setPixmap(pixmap);
		}

		else
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Erro na consulta\n%1").arg(sql1.lastError().text()));
		}

		if (param["mode"] == "view")
		{
			nomeEdit->setReadOnly(true);
			submitButton->setVisible(false);
			importButton->setEnabled(false);
			exportButton->setEnabled(false);
		}
	}

	else {
		QMessageBox::warning(this, "Admin",
			Utf8("Não foi passado nenhum argumento"));
	}
}

void PictureView::submitClicked()
{
	QByteArray bytes;
	QBuffer buffer(&bytes);
	buffer.open(QIODevice::ReadWrite);
	label->pixmap()->save(&buffer, "PNG");

	QMessageBox messageBox;
	messageBox.setWindowTitle("Admin");
	messageBox.setText(Utf8("Deseja substituir o desenho?"));
	messageBox.setIcon(QMessageBox::Question);
	messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

	switch(messageBox.exec())
	{
		case QMessageBox::Yes:
			query.bindValue(":nome", nomeEdit->text());
			query.bindValue(":desenho", buffer.data());

			if (query.exec())
			{
				emit dataChanged();
				close();
			}

			else {
				QMessageBox::warning(this, "Admin",
						Utf8("Houve um erro ao inserir\n%1").arg(query.lastError().text()));
			}
			break;

		default:
			break;
	}
}

void PictureView::importClicked()
{
	QString filename = QFileDialog::getOpenFileName(this, "Selecione um arquivo", "",
			"Arquivos de Imagem (*.png *.jpg *.jpeg *.bmp *.gif)");

	if (file.isOpen()) {
		file.close();
	}

	file.setFileName(filename);
	if (file.open(QIODevice::ReadOnly))
	{
		label->setPixmap(filename);
	}

	else
	{

	}
}

void PictureView::exportClicked()
{
	label->pixmap()->save(
			QFileDialog::getSaveFileName(this,
				"Selecione um arquivo", "", "Arquivos de Imagem (*.png *.jpg)")
		);
}

