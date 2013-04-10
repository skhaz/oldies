
/*
 *
 *
 *
 *
 *
 *
 */

#include "Orcamento.h"



Orcamento::Orcamento(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);
}

void Orcamento::setParam(const ParameterList& param)
{
	query.clear();

	if (param["mode"] != "new")
	{
		submitButton->setText("&Gravar");

		if (param["mode"] == "view")
		{
			// set read only
		}
	}

	else
	{
		submitButton->setText("&Inserir");
	}
}

void Orcamento::submitClicked()
{
}

