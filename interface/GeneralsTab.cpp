#include "GeneralsTab.h"

GeneralsTab::GeneralsTab(void)
{
    
}

GeneralsTab::GeneralsTab(wxWindow* parent, int id)
    : wxPanel(parent, id)
{
    wxStaticText* generalsNameBoxLabel = new wxStaticText(this, wxID_ANY, "Generals");
    generalNamesList = new wxComboBox(this, wxID_ANY);
    generalNamesList->Append(_("Wein"));
    generalNamesList->Append(_("Goldark"));
    generalNamesList->Append(_("Teiris"));
}
