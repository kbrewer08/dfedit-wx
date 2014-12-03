#include "DFTab.h"
#include "GeneralsTab.h"

DFTab::DFTab(wxWindow* parent)
    : wxNotebook(parent, wxID_ANY)
{
    this->AddPage(new GeneralsTab(this, idGeneralsTab), _("Generals"), true);
    this->AddPage(new wxWindow(this, idCastlesTab), _("Castles"), false);
    this->AddPage(new wxWindow(this, idDivisionsTab), _("Divisions"), false);
    this->AddPage(new wxWindow(this, idItemsTab), _("Items"), false);
    this->AddPage(new wxWindow(this, idMassEditTab), _("Mass Editing"), false);
    this->AddPage(new wxWindow(this, idKingdomsTab), _("Kingdoms"), false);
}
