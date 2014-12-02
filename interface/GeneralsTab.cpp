#include "GeneralsTab.h"

GeneralsTab::GeneralsTab(void)
{
    
}

GeneralsTab::GeneralsTab(wxWindow* parent, int id)
    : wxPanel(parent, id)
{
    basicsStaticBox = new wxStaticBoxSizer(wxVERTICAL, this, idBasicsStaticBox);
    basicsGroupBox = new wxGridBagSizer();

    wxStaticText* generalsListLabel = new wxStaticText(this, idGeneralsListLabel, "Generals");
    generalsListComboBox = new wxComboBox(this, idGeneralsListComboBox);
    generalNamesList->Append(_("Wein"));
    generalNamesList->Append(_("Goldark"));
    generalNamesList->Append(_("Teiris"));
}
