#include <iostream>
#include <string>
using namespace std;

class el_t
{
 private:
  string name;  //artwork name
  char location; //warehouse section where art is located 
  double reserve; //min price to be sold for 
  string auctionDate; //date to be auctioned
 public:

  el_t();  // to create a blank el_t object
  el_t(string, char, double, string); // to create an initialized el_t object

  bool operator==(el_t);  // overload == for search
  bool operator!=(el_t);  // overload != for search
  // In search == is used to compare node elements

  bool operator<(el_t&); //overload < for traversal
  bool operator>(el_t&); //overload > for traversal


  
  // this overloads cout for the el_t object
  // This is a friend function since the receiver object is not el_t
  friend ostream& operator<<(ostream&, const el_t&);

  friend class BST;  // client of this class is BST which needs access to the key part of el_t

};
