#ifndef _GENERALS_TAB_H_
#define _GENERALS_TAB_H_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>

class GeneralsTab : public wxPanel
{
public:
    GeneralsTab  (void);
    GeneralsTab  (wxWindow* parent, int id);
    ~GeneralsTab (void){}

private:
    enum
    {
        idBasicsStaticBox = 1000,
        idGeneralsListLabel,
        idGeneralsListComboBox
    };

    wxStaticBoxSizer* basicsStaticBox;
    wxGridBagSizer*   basicsGroupBox;
    
    wxStaticText* generalsListLabel;
    wxComboBox*   generalsListComboBox;
};

#endif // _GENERALS_TAB_H_
