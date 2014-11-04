#include "wxDFeditApp.h"
#include "wxDFeditMain.h"

IMPLEMENT_APP(wxDFeditApp);

bool wxDFeditApp::OnInit()
{
    wxDFeditFrame* frame = new wxDFeditFrame(0L, _("wxWidgets Application Template"));

    frame->Show();

    return true;
}
