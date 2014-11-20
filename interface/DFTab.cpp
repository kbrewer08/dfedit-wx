#include "DFTab.h"

DFTab::DFTab(wxWindow* parent)
    : wxNotebook(parent, wxID_ANY)
{
    //this = new wxNotebook(this, wxID_ANY);
    this->AddPage(new wxWindow(this, idGeneralsTab), "Generals", true);
    this->AddPage(new wxWindow(this, idCastlesTab), "Castles", false);
    this->AddPage(new wxWindow(this, idDivisionsTab), "Divisions", false);
    this->AddPage(new wxWindow(this, idItemsTab), "Items", false);
    this->AddPage(new wxWindow(this, idMassEditTab), "Mass Editing", false);
    this->AddPage(new wxWindow(this, idKingdomsTab), "Kingdoms", false);
}
