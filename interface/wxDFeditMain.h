#ifndef WXDFEDITMAIN_H
#define WXDFEDITMAIN_H

#include <string>

#include <wx/wx.h>
#include <wx/aui/auibook.h>

#include "wxDFeditApp.h"
#include "DFTab.h"

using namespace std;

class wxDFeditFrame: public wxFrame
{
    public:
        wxDFeditFrame(wxFrame *frame, const wxString& title);
        ~wxDFeditFrame();

        static wxString dfeditversion(wxString versionType);

    private:

        bool           noTabs;
        wxAuiNotebook* masterTab;

        enum
        {
            idMenuOpen = 1000,
            idMenuReload,
            idMenuQuit,
            idMenuAbout,

            idMasterTab,
        };

        void onOpen  (wxCommandEvent& event);
        void OnClose (wxCloseEvent& event);
        void OnQuit  (wxCommandEvent& event);
        void OnAbout (wxCommandEvent& event);

        void createMasterTab(void);

        DECLARE_EVENT_TABLE()
};


#endif // WXDFEDITMAIN_H
