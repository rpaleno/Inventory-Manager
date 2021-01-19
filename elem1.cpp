#include "elem1.h"

// blank element
el_t::el_t()
{
  //initialize blank
  name = "";
  location = ' ';
  reserve = 0;
  auctionDate = "";
  
}

// initializing constructor to create an el_t object
el_t::el_t(string aname, char section,  double price, string date)
{
  name = aname;
  location = section;
  reserve = price;
  auctionDate = date;
}

// overloading < operator
bool el_t::operator<(el_t& OtherOne)
{
  if(name < OtherOne.name) return true; else return false;
}

// overloading > operator
bool el_t::operator>(el_t& OtherOne)
{
  if(name > OtherOne.name) return true; else return false;
}


// overload == for search based on the name part only
bool el_t::operator==(el_t OtherOne)
{
  if (name == OtherOne.name) return true; else return false;
}

// overload != for search based on the name part only
bool el_t::operator!=(el_t OtherOne)
{
  if (name != OtherOne.name) return true; else return false;
}


// overload cout
ostream& operator<<(ostream& os, const el_t& E)
{
  os << "Artwork: " << E.name <<  endl << "Warehouse Section: " << E.location << endl << "Reserve: $" << E.reserve << endl << "Auction Date: " << E.auctionDate; 
  
  return os;
}
