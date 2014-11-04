#include "wxDFeditMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif
        wxbuild << _T("-Unicode build");
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(wxDFeditFrame, wxFrame)
    EVT_CLOSE(wxDFeditFrame::OnClose)
    EVT_MENU(idMenuQuit, wxDFeditFrame::OnQuit)
    EVT_MENU(idMenuAbout, wxDFeditFrame::OnAbout)
END_EVENT_TABLE()

wxDFeditFrame::wxDFeditFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);

    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);

}


wxDFeditFrame::~wxDFeditFrame()
{
}

void wxDFeditFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void wxDFeditFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void wxDFeditFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
