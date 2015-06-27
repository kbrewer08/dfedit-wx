#include "GeneralsTab.h"

BEGIN_EVENT_TABLE(GeneralsTab, wxPanel)
    EVT_BUTTON(idOfficerOwnerSetButton, GeneralsTab::setGeneralOwner)
    EVT_TEXT_ENTER(idOfficerOwnerComboBox, GeneralsTab::setGeneralOwner)
    EVT_BUTTON(idGeneralLevelSetButton, GeneralsTab::setGeneralLevel)
    EVT_TEXT_ENTER(idGeneralLevelEditBox, GeneralsTab::setGeneralLevel)
END_EVENT_TABLE()

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

    wxGridBagSizer* gbs = new wxGridBagSizer(2, 2);
    basicsStaticBox->Add(gbs);

    generalsListLabel = new wxStaticText(basicsStaticBox->GetStaticBox(), idGeneralsListLabel, _("General: "));
    gbs->Add(generalsListLabel, wxGBPosition(0, 0));

    generalsListComboBox = new wxComboBox(basicsStaticBox->GetStaticBox(), idGeneralsListComboBox,
                                          wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL,
                                          wxCB_READONLY | wxTE_PROCESS_ENTER);
    generalsListComboBox->Append(_T("Wein"));
    generalsListComboBox->Append(_T("Goldark"));
    generalsListComboBox->Append(_T("Teiris"));
    generalsListComboBox->SetSelection(0);
    gbs->Add(generalsListComboBox, wxGBPosition(0, 1));

    officerOwnerLabel = new wxStaticText(basicsStaticBox->GetStaticBox(), idOfficerOwnerLabel, _("Owner: "));
    gbs->Add(officerOwnerLabel, wxGBPosition(1, 0));

    officerOwnerComboBox = new wxComboBox(basicsStaticBox->GetStaticBox(), idOfficerOwnerComboBox,
                                          wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL,
                                          wxCB_READONLY | wxTE_PROCESS_ENTER);
    officerOwnerComboBox->Append(_T("Wein"));
    officerOwnerComboBox->Append(_T("Goldark"));
    officerOwnerComboBox->Append(_T("Teiris"));
    officerOwnerComboBox->SetSelection(0);
    gbs->Add(officerOwnerComboBox, wxGBPosition(1, 1));

    officerOwnerSetButton = new wxButton(basicsStaticBox->GetStaticBox(), idOfficerOwnerSetButton, _("Set"));
    gbs->Add(officerOwnerSetButton, wxGBPosition(1, 2));

    generalLevelLabel = new wxStaticText(basicsStaticBox->GetStaticBox(), idGeneralLevelLabel, _("Level: "));
    gbs->Add(generalLevelLabel, wxGBPosition(2, 0));

    generalLevelEditBox = new wxTextCtrl(basicsStaticBox->GetStaticBox(), idGeneralLevelEditBox, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    gbs->Add(generalLevelEditBox, wxGBPosition(2, 1));

    generalLevelSetButton = new wxButton(basicsStaticBox->GetStaticBox(), idGeneralLevelSetButton, _("Set"));
    gbs->Add(generalLevelSetButton, wxGBPosition(2, 2));

}

void GeneralsTab::setGeneralOwner(wxCommandEvent& event)
{
    wxMessageBox(_("The button to set a new owner for this officer was clicked."), _("Set new owner"));
}

void GeneralsTab::setGeneralLevel(wxCommandEvent& event)
{
    wxMessageBox(_("The button to set a General's level was clicked."), _("Set General Level"));
}
