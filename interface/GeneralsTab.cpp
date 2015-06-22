#include "GeneralsTab.h"

GeneralsTab::GeneralsTab(void)
{
    
}

GeneralsTab::GeneralsTab(wxWindow* parent, int id)
    : wxPanel(parent, id)
{
    masterSizer = new wxGridSizer(2, 3, 5, 5);
    SetSizerAndFit(masterSizer);

    basicsStaticBox       = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Basics"));
    weaknessesStaticBox   = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Weakness Against"));
    statusInfoStaticBox   = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Status"));
    medalsStaticBox       = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Medals"));
    locationStaticBox     = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Location"));
    unknownStatsStaticBox = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Unknown"));

    masterSizer->Add(basicsStaticBox,       0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    masterSizer->Add(weaknessesStaticBox,   0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    masterSizer->Add(statusInfoStaticBox,   0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    masterSizer->Add(medalsStaticBox,       0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    masterSizer->Add(locationStaticBox,     0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    masterSizer->Add(unknownStatsStaticBox, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    generalsListLabel = new wxStaticText(basicsStaticBox->GetStaticBox(), idGeneralsListLabel, _("Generals"));
    basicsStaticBox->Add(generalsListLabel);
    
    generalsListComboBox = new wxComboBox(basicsStaticBox->GetStaticBox(), idGeneralsListComboBox);
    generalsListComboBox->Append(_T("Wein"));
    generalsListComboBox->Append(_T("Goldark"));
    generalsListComboBox->Append(_T("Teiris"));
    basicsStaticBox->Add(generalsListComboBox);
}
