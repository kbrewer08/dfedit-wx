#ifndef _GENERALS_TAB_H_
#define _GENERALS_TAB_H_

#include <wx/wx.h>

class GeneralsTab : public wxPanel
{
public:
    GeneralsTab  (void);
    GeneralsTab  (wxWindow* parent, int id);
    ~GeneralsTab (void){}

private:
    wxComboBox* generalNamesList;
};

#endif // _GENERALS_TAB_H_
