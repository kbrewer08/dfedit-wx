#include "GeneralsTab.h"

GeneralsTab::GeneralsTab(void)
{
    
}

GeneralsTab::GeneralsTab(wxWindow* parent, int id)
    : wxPanel(parent, id)
{
    masterSizer = new wxGridSizer(2, 3, 2, 2);
    SetSizerAndFit(masterSizer);

    basicsStaticBox       = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Basics"));
    weaknessesStaticBox   = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Weakness Against"));
    statusInfoStaticBox   = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Status"));
    medalsStaticBox       = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Medals"));
    locationStaticBox     = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Location"));
    unknownStatsStaticBox = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Unknown"));

    masterSizer->Add(basicsStaticBox,       0, wxALIGN_LEFT | wxEXPAND);
    masterSizer->Add(weaknessesStaticBox,   0, wxALIGN_LEFT | wxEXPAND);
    masterSizer->Add(statusInfoStaticBox,   0, wxALIGN_LEFT | wxEXPAND);
    masterSizer->Add(medalsStaticBox,       0, wxALIGN_LEFT | wxEXPAND);
    masterSizer->Add(locationStaticBox,     0, wxALIGN_LEFT | wxEXPAND);
    masterSizer->Add(unknownStatsStaticBox, 0, wxALIGN_LEFT | wxEXPAND);

    generalsListLabel = new wxStaticText(basicsStaticBox->GetStaticBox(), idGeneralsListLabel, _("General: "));
    basicsStaticBox->Add(generalsListLabel);
    
    generalsListComboBox = new wxComboBox(basicsStaticBox->GetStaticBox(), idGeneralsListComboBox,
                                          wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL,
                                          wxCB_READONLY | wxTE_PROCESS_ENTER);
    generalsListComboBox->Append(_T("Wein"));
    generalsListComboBox->Append(_T("Goldark"));
    generalsListComboBox->Append(_T("Teiris"));
    generalsListComboBox->SetSelection(0);
    basicsStaticBox->Add(generalsListComboBox);
}
