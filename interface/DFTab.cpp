#include "DFTab.h"
#include "GeneralsTab.h"

DFTab::DFTab(wxWindow* parent)
    : wxNotebook(parent, wxID_ANY)
{
    this->AddPage(new GeneralsTab(this, idGeneralsTab), "Generals", true);
    this->AddPage(new wxWindow(this, idCastlesTab), "Castles", false);
    this->AddPage(new wxWindow(this, idDivisionsTab), "Divisions", false);
    this->AddPage(new wxWindow(this, idItemsTab), "Items", false);
    this->AddPage(new wxWindow(this, idMassEditTab), "Mass Editing", false);
    this->AddPage(new wxWindow(this, idKingdomsTab), "Kingdoms", false);
}
