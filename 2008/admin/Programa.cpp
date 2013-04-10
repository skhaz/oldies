
/*
 *
 *
 *
 *
 *
 *
 */

#include "Programa.h"



Programa::Programa(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);

	connect(submitButton, SIGNAL(clicked()), SLOT(submitClicked()));
	connect(importButton, SIGNAL(clicked()), SLOT(importClicked()));
	connect(exportButton, SIGNAL(clicked()), SLOT(exportClicked()));
	connect(closeButton, SIGNAL(clicked()), SLOT(close()));
}

void Programa::setParam(const ParameterList& param)
{
	int cod = param["cod"].toInt();

	if (param["mode"] != "new" && cod != 0)
	{
		query.prepare("update programas set nome = :nome, programa = :programa where cod_programa = :cod");
		query.bindValue(":cod", cod);

		QSqlQuery sql;
		sql.prepare("select nome, programa from programas where cod_programa = :cod limit 1");
		sql.bindValue(":cod", cod);

		if (sql.exec())
		{
			sql.first();
			nomeEdit->setText(sql.value(sql.record().indexOf("nome")).toString());
			textEdit->appendPlainText(sql.value(sql.record().indexOf("programa")).toString());
		}

		else
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Erro na consulta\n%1").arg(sql.lastError().text()));
		}
	}

	else {
		query.prepare("insert into programas (nome, programa) values (:nome, :programa)");
	}

	setWindowTitle(Utf8("%1").arg(nomeEdit->text().isEmpty() ? "Sem nome" : nomeEdit->text()));
}

void Programa::submitClicked()
{
	QString programa = textEdit->toPlainText();

	QMessageBox messageBox;
	messageBox.setWindowTitle("Admin");
	messageBox.setText(Utf8("Deseja substituir o programa?"));
	messageBox.setIcon(QMessageBox::Question);
	messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

	switch(messageBox.exec())
	{
		case QMessageBox::Yes:
			if (programa.isEmpty())
			{
				QMessageBox::warning(this, "Admin",
						Utf8("Não é possivel inserir items vazios"));
			}

			else {
				query.bindValue(":nome", nomeEdit->text());
				query.bindValue(":programa", programa);

				if (query.exec())
				{
					emit dataChanged();
				}

				else {
					QMessageBox::warning(this, "Admin",
							Utf8("Houve um erro ao inserir\n%1").arg(query.lastError().text()));
				}
			}

		default:
			break;
	}
}

void Programa::importClicked()
{
	QString filename = QFileDialog::getOpenFileName(this,
				"Selecione um arquivo", "",	"Programas (*.txt)");

	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		textEdit->appendPlainText(file.readAll());
	}

	else {
		QMessageBox::warning(this, "Admin",
				Utf8("Houve um erro ao tentar abrir o arquivo: <b>%1</b>").arg(filename));
	}
}

void Programa::exportClicked()
{
}

