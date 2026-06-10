#include<iostream>
#include <string>
using namespace std;

class Cake{
    
    public :
      string name;
      string flavor;
      double price;
      int quantity;

      Cake(){

          name = "" ;
          flavor = "";
          price = 0;
          quantity = 0; 

      }

      Cake(string n , string f ,double p , int q){
          name = n;
          flavor = f;
          price = p;
          quantity = q;
      }

      void display(int number){

          cout << "+--------------------------+\n";
          cout << " | ["<< number << "]" <<name <<"\n ";
          cout <<" | Flavor : "<< flavor << "\n";
          cout << "| Price : Rs. " <<price << "\n";
          cout << "| In stock :" << quantity << "piece\n";
          cout <<"+---------------------------------+\n"; 
          
      }
};

class Order{
    public  : 
    string customerName;
    string cakeName;
    int quantity;
    double totalPrice ;

    Order(){
        customerName ="";
        cakeName = "";
        quantity =0;
        totalPrice = 0;
    }

    void display(int number){
        cout << "+------------------------------------+\n";
        cout << "| Order No : #" <<number <<"\n";
        cout << "| Cake  : " <<cakeName << "\n";
        cout << "| Qty :" << quantity << "\n";
        cout <<"| Total : Rs." <<totalPrice <<"\n";
        cout <<"+-------------------------------------+\n";
    } 
};

class CakeShop{
    public :
     Cake menu[20];
     Order orders[50];
     int totalCakes;
     int totalOrders;

     CakeShop(){
         totalCakes = 0;
         totalOrders = 0;
         loadDefaultCakes();

     }

     void loadDefaultCakes(){

         menu[0] =Cake ("Classic Choklate" , "Chocolate" , 850.00, 10);
         menu[1] = Cake("Vanilla Dream"  , "Vanilla", 750.00, 8);
         menu[2] =Cake("Strawberry Bliss", "Strawberry" ,1100.00, 6);
         menu[3] = Cake("Red Velvet Royal" , "Red Velvet" , 1200.00,5);
         menu[4] =Cake("Butterscotch Swril " , "Butterscotch", 950.00,7);
         totalCakes =5;
     }

     void printline(){

         cout << "-----------------------------\n";

     }

     void showMenu(){

         cout <<"\n";
         printline();
         cout << " 🎂SWEET BITES CAKE SHOP🎂\n";
         cout << "1. View All Cakes\n";
         cout << "2. Add New Cakes\n";
         cout << "3. Place an Order\n";
         cout << "4. View All Orders\n";
         cout<<"5. Exit\n";
         printline();
         cout << "Enter choice :";

     }

     void viewAllCakes(){
         cout << "\n";
         printline();
         cout << "All Cakes In Shop\n";
         printline();

         if(totalCakes == 0){
             cout << "No Cakes Available!\n";
             return ;
         }

         for(int i = 0 ; i <totalCakes; i++){
             menu[i].display(i+1);
         }

         printline();
     }

     void addCake(){
         if(totalCakes >= 20){
             cout << "Sorry! Menu is Full.\n";
             return ;
         }

         string name , flavor ;
         double price;
         int qty;

         cout << "\n";
         printline();
         cout << "ADD NEW CAKE\n";
         printline();

         cin.ignore();
         cout<<"Cake Name :" ;
         getline(cin ,name);

         cout<<" Flavor :";
         getline(cin ,flavor);

         cout << "Price : Rs.";
         cin >> price;

         cout <<"Quantity : ";
         cin >> qty;

         menu[totalCakes] =Cake(name , flavor , price , qty);
         totalCakes++;

         cout << "\n Cake Added Successfully!\n" ; 
     }

     void placeOreder() {
         if(totalCakes == 0){
             cout << "No Cakes Available!\n";
             return;
         }

         viewAllCakes();
         cout << "Enter cake Number :";
         int choice ;
         cin >> choice;

         if(choice < 1 || choice > totalCakes){
             cout << "invalid Choice!\n";
             return; 
         }

         int index = choice-1;

         cout << "How Many Pieces ? : ";
         int qty ;
         cin >> qty;

         if(qty > menu[index] .quantity){
             cout<< "Sorry ! Only " << menu[index].quantity << "in stock.\n";
             return ; 
         }

         cin.ignore();
         cout << "Your Name :";

         Order newOrder;
         getline(cin , newOrder.customerName);
         newOrder.cakeName = menu[index].name;
         newOrder.quantity = qty;
         newOrder.totalPrice =menu[index].price *qty;

         orders[totalOrders] = newOrder ;
         totalOrders++;
         menu[index].quantity-=qty;


         cout << "\n";
         printline();
         cout<< "ORDER CONFIRMED!\n";
         printline();
         newOrder.display(totalOrders);
         cout<<"Thank You ! Enjoy your cake!\n";

     }

     void viewAllOrders(){

         cout <<"\n";
         printline();
         cout << "All Orders\n";
         printline();

         if(totalOrders == 0){
             cout<< "No Oders yet!\n";
             return ;
         }

         for(int i =0 ; i <totalOrders ; i++){
             orders[i].display(i+1);   
         }
         printline();
         
     }

     void run(){

         cout <<"\n Welcome to Sweet Bites Cake Shop!\n";
         int choice;

         do{

             showMenu();
             cin >> choice ;

             if(choice ==1 ) viewAllCakes();
             else if(choice == 2) addCake();
             else if(choice ==3 )placeOreder();
             else if(choice ==4 )viewAllOrders();
             else if(choice == 5) cout << "\n Goodbye! Have a sweet day!\n\n";
             else                 
             cout<< "Invalid Choice ! Try Again.\n";
         }while(choice!=5);
     }

};

int main(){

    CakeShop shop;
    shop.run();
    return 0;
}