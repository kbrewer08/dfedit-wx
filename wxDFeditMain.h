#ifndef WXDFEDITMAIN_H
#define WXDFEDITMAIN_H

#include <wx/wx.h>
#include <string>

#include "wxDFeditApp.h"

using namespace std;

class wxDFeditFrame: public wxFrame
{
    public:
        wxDFeditFrame(wxFrame *frame, const wxString& title);
        ~wxDFeditFrame();

        static wxString dfeditversion(string versionType);

    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // WXDFEDITMAIN_H
