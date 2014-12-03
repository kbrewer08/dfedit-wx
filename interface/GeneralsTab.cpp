#include "GeneralsTab.h"

GeneralsTab::GeneralsTab(void)
{
    
}

GeneralsTab::GeneralsTab(wxWindow* parent, int id)
    : wxPanel(parent, id)
{
    basicsStaticBox = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Generals"));
    basicsGroupBox = new wxGridBagSizer();
    basicsStaticBox->Add(basicsGroupBox);

    generalsListLabel = new wxStaticText(basicsStaticBox->GetStaticBox(), idGeneralsListLabel, _("Generals"));

    generalsListComboBox = new wxComboBox(basicsStaticBox->GetStaticBox(), idGeneralsListComboBox);
    generalsListComboBox->Append(_T("Wein"));
    generalsListComboBox->Append(_T("Goldark"));
    generalsListComboBox->Append(_T("Teiris"));

    basicsGroupBox->Add(generalsListLabel, wxGBPosition(0, 0));
    basicsGroupBox->Add(generalsListComboBox, wxGBPosition(0, 1));
}
