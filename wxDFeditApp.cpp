#include "wxDFeditApp.h"
#include "wxDFeditMain.h"

IMPLEMENT_APP(wxDFeditApp);

bool wxDFeditApp::OnInit()
{
    wxDFeditFrame* frame = new wxDFeditFrame(0L, wxDFeditFrame::dfeditversion("long"));

    frame->Show();

    return true;
}
