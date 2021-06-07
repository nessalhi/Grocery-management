#include <iostream>
#include <memory>
#include <vector>
#include <cstdio>
#include <fstream>
using namespace std;

//------------------------


class item {
	
protected:
char EXP_Date[100];
//int ID;
string type;	
double price;
int Quantity;
bool availability ;


public:

item(): Quantity(0), availability (false) {}


//item(bool dispo = false, int quantity = 0 ):  Quantity(quantity), availability(dispo) {};
virtual ~item(){};	


virtual string set_Type(){
	
	cout << " Please enter the item type " ;
	cin >> type;
	
	return type;
}


virtual double set_prix(){
	
	cout << " Please enter the item price " ;
	cin >> price;
	
	return price;
	
	
}


virtual void set_Quantity(){
	int n;
	cout << " enter the item quantity " << ": " ;
	cin >> n;
	Quantity += n;
	
}

virtual string get_type(){
	
	cout << "\n";
	cout << "-----------------------\n" ;
	cout << " test file reports " << endl;
	return type;
	
}

double get_price(){
	
	return price;
	
}

int get_quantity(){
	
	return Quantity;
}

virtual bool get_Stock()const{
	
	if (Quantity != 0){
	cout << " available " ;
	return true;}
	
	else if (Quantity == 0)
	cout << "  no longer available " ;
	return false;
	
}

string get_expdate(){
	
	return EXP_Date;
}

virtual void set_expirationDate(){}

virtual void set_brand(){}

virtual void set_reference(){}


virtual ostream& affichage(ostream& out)const{   // item display using << 
	
	out << "-------------- Grocery stock : Item informations----------- : " << endl;
	out << type <<", " << price <<", " << Quantity << ", " << get_Stock() << endl;
	
	return out;
	
}

virtual void item_infos()const{       // item info ( virtual)
	cout << "\n" ;
	cout << "---------- Item informations-----------\n ";
	cout << " the item : " << type << " costs " << price << " euros" <<  " is " << get_Stock();
	cout << "\n" ;	
	
}


};

ostream& operator << (ostream& out,  item const& ITEM){
	
	return ITEM.affichage(out);
	
}


class Foods: public item {
	
protected:
//char EXP_Date[100];


public:
Foods () { 
	       cout << " You have added a new Foods " << endl;
	       cout << "-------------------------------------------" << endl;
	       cout << "\n";
	  }
//Foods(int quantite , string expdate) : item(quantite) , EXP_Date(expdate) {};
//Foods(int quantite, string expdate, bool disponibilite = false ): item(disponibilite ), Quantity(quantite), EXP_Date(expdate) {};	
	

virtual void set_expirationDate()override{

	cout << " enter the expiration date " ;
	
	cin.getline(EXP_Date, 100);
	
	cout <<  EXP_Date;
	
}

virtual void set_Quantity()override{
	
	cout << " enter the foods quantity in Kg " << ": " ;
	item::set_Quantity();
	
}

virtual void item_infos()const override{

 item::item_infos();
 
 cout << Quantity << " kg " << endl;
 cout << "  expires on  : " << EXP_Date << endl;
 cout << "\n" ;
 cout << "-----------------------------------" << endl;
 
}

	
};


class Electronics: public item{
	
protected:
int  reference;
char manufactured_date[100];
char brand[100];	
	
public:
Electronics(): item() { cout << " you have added a new electronic product " << endl;
	            cout << "-------------------------------------------" << endl;
	            cout << "\n";
	           }	
	
virtual void set_reference(){
	
	
	cout << " enter the product" << type    << "reference " ;
	cin >> reference;
	cout << reference<< endl;
	
}

virtual void set_brand(){
	
	cout << " enter the brand name " ;
	cin.getline(brand, 100);
	cout << brand << endl;
		
}

virtual void set_expirationDate()override{
	
cout << " Please enter the manufactured date " ;
cin.getline(manufactured_date, 100);

cout << manufactured_date << endl;	
	
	
}

virtual void item_infos()const override{
	
  item::item_infos();
 cout << " the product :  " << type << " from " << brand << " manufacturer " << " which referred with " << reference << " number " ; 
 cout << " was  manufactured on : " << manufactured_date << endl;
 
}
	
	
};

class Grocery{

protected:
vector<item*> Stock;

public:

int Add_Items(item* pt){

Stock.push_back(pt);

return (Stock.size()-1) ;

}


item* get_item(unsigned int ID){
	
if (ID < Stock.size())
	
	return Stock[ID];
	else 
	return 0;

}

item* search_item(unsigned int ID){  // A modifier
	
	if (Stock[ID]->get_Stock()==1)
	 
	 return Stock[ID];
	 else
	 cout << Stock[ID] << " is no longer available " << endl;
	
}

void set_item(int id){
	
	get_item(id)->set_Type();  // access through pointer
	get_item(id)->set_prix();
	get_item(id)->set_Quantity();
	get_item(id)->set_expirationDate();
	get_item(id)->set_expirationDate();
	get_item(id)->set_brand();
	get_item(id)->set_reference();
	
	
}

void infos_item(int id){
	
	get_item(id)->item_infos();
	
}

ostream& infos_stock(ostream& out)const{  // Display all item informations + Availability
	
	cout << " Would you want to discover our products ? "  << endl;
	
	for ( const auto& exp:Stock){
		out << "---------- Stock informations ------------" << endl;
		out << "\n";
		out << *exp << endl;
		
	}
	
	return out;
}

void UpdateFile(){

 ofstream myfile( "Stock_Report.txt");
 
 unsigned int exp;
  
  for (exp = 0; exp < Stock.size(); exp++){
	  
	 myfile << " test1 \n " ;
	 myfile <<  get_item(exp)->get_type() << "\n ";
	 myfile <<  get_item(exp)->get_Stock() << "\n ";
	 myfile <<  get_item(exp)->get_price() << "\n ";
	 myfile <<  get_item(exp)->get_quantity() << "\n ";
	 myfile <<  get_item(exp)->get_expdate() << "\n ";
		 	 
 }

}


};

ostream& operator << (ostream& out, Grocery const& autre){
	
	return autre.infos_stock(out);
	
	
}

class User {

protected:
string name;
Grocery& mon_stock;


public:
User(Grocery& ref): mon_stock(ref) {};

	
virtual void display_item(int ID){
	
	cout << *mon_stock.get_item(ID);
	
}

virtual void display_stock(){
	
		cout << mon_stock;
		
	}
	

};

class Admin:public User{
	
public:
Admin(Grocery& Adm): User(Adm) {};


int Add_product(item* id){

        int ide; // contain the item position inside the vector
	    ide =  mon_stock.Add_Items(id);
	 
	 return ide;
}

void set_product(unsigned int product){
	
	mon_stock.set_item(product);
	//mon_stock.get_item(product)->set_brand(); // Set a specific item attribut 
	
}

void delete_product( int id){
	
	
	delete (mon_stock.get_item(id));
	
}

void Updatefile(){
	
	mon_stock.UpdateFile();
	
}


};


class Client: public User{
	
	
public:
 Client(Grocery& cl): User(cl) {cout << "\n" ;
	                           cout << "a client access to the Grocery stock " <<endl;};	
	
	
virtual void display_item(int ID)override{
		
		cout <<" client display " << endl;
		cout << *mon_stock.get_item(ID);
		//User::display_item(mon_stock.get_item (ID));
		
	}
	
	
void display_stock() override{
	
	cout << " Stock display for client " << endl;
	
	User::display_stock();
	
}	

	
};

int main(){
	
  Grocery mon_stock;
 
 Admin proprio( mon_stock);
	
  int item1, item2;
  
 // item1 = mon_stock.Add_Items(new Foods());
  
 item1 = proprio.Add_product(new Foods());
 item2 = proprio.Add_product(new Electronics());
 
 proprio.set_product(item1);
 proprio.set_product(item2);
 
 cout << mon_stock.get_item(item1)->get_type();
 
 proprio.Updatefile();
 
 
 
  //mon_stock.UpdateFile();

 //-------------test functions for Client Ahmed-------------
// item1 = ahmed.Add_product(new Foods());
 
// ahmed.set_product(item1);

//Client ahmed (mon_stock);
 
// ahmed.display_item(item1);

//-----------------------------------------------------------




// 
  
  
  //item1 = new Foods();
 // mon_stock.Add_Items (new Foods());
  // proprio.Add_product(new Foods());
  //item1 = mon_stock.Add_Items(new Foods());
  
  //item1 = Admin.Add_Product(new Foods());
  //Admin.set_product(item1);
  
  //Admin.display_item(item1);
  
  
 // Admin.display_stock();
  
  //mon_stock.set_item(item1);
 
  
  
  /*
  
  cout << " please wait ..." << endl;


  mon_stock.infos_item(item1);
  
  
  item2 = mon_stock.Add_Items(new Electronics());
  
  mon_stock.set_item(item2);
 
  
   cout << " please wait ..." << endl;
   
 
  
   
  mon_stock.infos_item(item2);


 item3 = mon_stock.Add_Items(new Foods());
  
  mon_stock.set_item(item3);

  
   cout << " please wait ..." << endl;
   


   cout << mon_stock;
   
  */
 // cout << item1;
  


return 0;	
	
}










	//User Admin("admin");
	//Admin.set_item();

	
	
	
	//cout << Admin.get_item(1);
	//Admin.produit.item_infos();
	
	
//Foods Legumes ();	
/*	
Foods Legumes (  "23/07/2021");	
//Foods Legumes (2, "Tomatoes");	


Legumes.set_Type();
Legumes.set_prix();
	
Legumes.set_Quantity();

Legumes.item_infos();
	*/
