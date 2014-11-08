#include "wxDFeditMain.h"
#include <string>

#define DFEDIT_VERSION "3.0"

using namespace std;

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

wxString wxDFeditFrame::dfeditversion(wxString versionType)
{
    wxString version = wxString();
    if(versionType == wxT("long"))
    {
        version << wxT("Dragon Force Edit ");
        version << wxT(DFEDIT_VERSION);
    } else if(versionType == "short"){
        version << wxT("DFedit ");
        version << wxT(DFEDIT_VERSION);
    } else {
        version << wxT("DFedit ");
        version << wxT(DFEDIT_VERSION);
    }

    return version;
}

BEGIN_EVENT_TABLE(wxDFeditFrame, wxFrame)
    EVT_CLOSE(wxDFeditFrame::OnClose)
    EVT_MENU(idMenuQuit, wxDFeditFrame::OnQuit)
    EVT_MENU(idMenuAbout, wxDFeditFrame::OnAbout)
END_EVENT_TABLE()

wxDFeditFrame::wxDFeditFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title, wxPoint(0, 0), wxSize(800, 600))
{
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(wxT(""));
    fileMenu->Append(idMenuOpen, _("&Open\tCtrl-O"), _("Open a save file"));
    fileMenu->Append(idMenuReload, _("&Reload\tCtrl-R"), _("Reload the current save file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit DFedit"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("About DFedit"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);

    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(1);

    wxString welcome = _("Welcome to ");
    welcome << dfeditversion(wxT("short")) << wxT("!");
    SetStatusText(welcome, 0);

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
    wxString msg = dfeditversion(wxT("short"));
    msg << _("\n\ncreated by ") <<  wxT("Sorinev");
    msg << wxT("\n\nDragonForceEdit@gmail.com");
    msg << _("\n\nDragon Force Edit is a utility that lets you change just about ")
        << _("anything in your Dragon Force save files. Currently, the save ")
        << _("files that it works with are those created by the SSF emulator ")
        << _("with the Hook Backup Library option checked.\n\n");

    wxString aboutTitle = wxT("About ");
    aboutTitle << dfeditversion(wxT("short"));

    wxMessageBox(msg, aboutTitle);
}
