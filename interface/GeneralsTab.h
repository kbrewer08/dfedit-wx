#ifndef _GENERALS_TAB_H_
#define _GENERALS_TAB_H_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include <wx/aui/auibook.h>
#include <wx/textctrl.h>

#include "DFTab.h"
#include "wxDFeditMain.h"

class GeneralsTab : public wxPanel
{
public:
    GeneralsTab  (void);
    GeneralsTab  (wxWindow* parent, int id);
    ~GeneralsTab (void){}

private:
    enum
    {
        idMasterSizer = 9000,
        idBasicsStaticBox,
        idWeaknessesStaticBox,
        idStatusInfoStaticBox,
        idMedalsStaticBox,
        idLocationStaticBox,
        idUnknownStatsStaticBox,
        idGeneralsListLabel,
        idGeneralsListComboBox,
        idOfficerOwnerLabel,
        idOfficerOwnerComboBox,
        idOfficerOwnerSetButton,
        idGeneralLevelLabel,
        idGeneralLevelEditBox,
        idGeneralLevelSetButton,
        idGeneralExperienceLabel,
        idGeneralExperienceEditBox,
        idGeneralExperienceSetButton,
        idGeneralCurHpLabel,
        idGeneralCurHpEditBox,
        idGeneralCurHpSetButton,
        idGeneralMaxHpLabel,
        idGeneralMaxHpEditBox,
        idGeneralMaxHpSetButton,
        idGeneralCurMpLabel,
        idGeneralCurMpEditBox,
        idGeneralCurMxpSetButton,
        idGeneralMaxMpLabel,
        idGeneralMaxMpEditBox,
        idGeneralMaxMpSetButton,
        idGeneralStrLabel,
        idGeneralStrEditBox,
        idGeneralStrSetButton,
        idGeneralComLabel,
        idGeneralComEditBox,
        idGeneralComSetButton,
        idGeneralIntLabel,
        idGeneralIntEditBox,
        idGeneralIntSetButton
    };

    wxGridSizer*      masterSizer;
    wxStaticBoxSizer* basicsStaticBox;
    wxStaticBoxSizer* weaknessesStaticBox;
    wxStaticBoxSizer* statusInfoStaticBox;
    wxStaticBoxSizer* medalsStaticBox;
    wxStaticBoxSizer* locationStaticBox;
    wxStaticBoxSizer* unknownStatsStaticBox;

    wxGridBagSizer*   basicsGroupBox;
    
    wxStaticText* generalsListLabel;
    wxComboBox*   generalsListComboBox;
    wxStaticText* officerOwnerLabel;
    wxComboBox*   officerOwnerComboBox;
    wxButton*     officerOwnerSetButton;
    wxStaticText* generalLevelLabel;
    wxTextCtrl*   generalLevelEditBox;
    wxButton*     generalLevelSetButton;

    void setGeneralOwner(wxCommandEvent& event);
    void setGeneralLevel(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif // _GENERALS_TAB_H_
