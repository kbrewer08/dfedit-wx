#include "GeneralsTab.h"

GeneralsTab::GeneralsTab(void)
{
    
}

GeneralsTab::GeneralsTab(wxWindow* parent, int id)
    : wxPanel(parent, id)
{
    masterSizer = new wxGridSizer(2, 3, 50, 50);

    basicsStaticBox = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Basic"));

    masterSizer->Add(basicsStaticBox, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    basicsGroupBox = new wxGridBagSizer();
    basicsStaticBox->Add(basicsGroupBox);

    //DFTab* dftab = (DFTab*)GetParent();
    //wxAuiNotebook* mt = (wxAuiNotebook*)(dftab->GetParent());

    generalsListLabel = new wxStaticText(basicsStaticBox->GetStaticBox(), idGeneralsListLabel, _("Generals"));
    
    generalsListComboBox = new wxComboBox(basicsStaticBox->GetStaticBox(), idGeneralsListComboBox);
    generalsListComboBox->Append(_T("Wein"));
    generalsListComboBox->Append(_T("Goldark"));
    generalsListComboBox->Append(_T("Teiris"));

    basicsGroupBox->Add(generalsListLabel, wxGBPosition(0, 0));
    basicsGroupBox->Add(generalsListComboBox, wxGBPosition(0, 1));
}
