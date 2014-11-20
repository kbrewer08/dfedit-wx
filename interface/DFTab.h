#ifndef _DFTAB_H_
#define _DFTAB_H_

#include <wx/wx.h>
#include <wx/notebook.h>

class DFTab : public wxNotebook
{
public:
    DFTab  (void) {}
    DFTab  (wxWindow* parent);
    ~DFTab (void) {}

private:
        enum
        {
            idGeneralsTab = 1000,
            idCastlesTab,
            idDivisionsTab,
            idItemsTab,
            idMassEditTab,
            idKingdomsTab
        };

    wxNotebook* dftab;
};

#endif
