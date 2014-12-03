#include "wxDFeditMain.h"
#include <string>

#define DFEDIT_VERSION "3.0"

using namespace std;

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

BEGIN_EVENT_TABLE(wxDFeditFrame, wxFrame)
    EVT_CLOSE(wxDFeditFrame::OnClose)
    EVT_MENU(wxID_EXIT, wxDFeditFrame::OnQuit)
    EVT_MENU(wxID_ABOUT, wxDFeditFrame::OnAbout)
END_EVENT_TABLE()

wxDFeditFrame::wxDFeditFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, wxID_ANY, title, wxPoint(0, 0), wxSize(800, 600))
{
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(wxT(""));
    fileMenu->Append(wxID_OPEN, _("&Open\tCtrl-O"), _("Open a save file"));
    fileMenu->Append(wxID_REFRESH, _("&Reload\tCtrl-R"), _("Reload the current save file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, _("&Quit\tAlt-F4"), _("Quit DFedit"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(wxID_ABOUT, _("&About\tF1"), _("About DFedit"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);

    CreateStatusBar(1);

    wxString welcome = _("Welcome to ");
    welcome << dfeditversion(_T("short")) << _T("!");
    SetStatusText(welcome, 0);

    createMasterTab();
    masterTab->SetWindowStyleFlag(wxAUI_NB_TAB_MOVE | wxAUI_NB_CLOSE_ON_ALL_TABS);
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
    wxString msg = dfeditversion(_T("short"));
    msg << _("\n\ncreated by ") <<  _T("Sorinev");
    msg << _T("\n\nDragonForceEdit@gmail.com");
    msg << _("\n\nDragon Force Edit is a utility that lets you change just about ")
        << _("anything in your Dragon Force save files. Currently, the save ")
        << _("files that it works with are those created by the SSF emulator ")
        << _("with the Hook Backup Library option checked.\n\n");

    wxString aboutTitle = _("About ");
    aboutTitle << dfeditversion(_T("short"));

    wxMessageBox(msg, aboutTitle);
}

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
        wxbuild << _("-Unicode build");
    }

    return wxbuild;
}

wxString wxDFeditFrame::dfeditversion(wxString versionType)
{
    wxString version = wxString();
    if(versionType == _T("long"))
    {
        version << _T("Dragon Force Edit ");
        version << _T(DFEDIT_VERSION);
    } else if(versionType == "short"){
        version << _T("DFedit ");
        version << _T(DFEDIT_VERSION);
    } else {
        version << _T("DFedit ");
        version << _T(DFEDIT_VERSION);
    }

    return version;
}

void wxDFeditFrame::createMasterTab(void)
{
    masterTab = new wxAuiNotebook(this, idMasterTab, wxDefaultPosition, wxDefaultSize, 0);
    masterTab->AddPage(new DFTab(masterTab), _T("Junon"), true);
    masterTab->AddPage(new DFTab(masterTab), _T("Goldark"), false);
    noTabs = true;

    return;
}
