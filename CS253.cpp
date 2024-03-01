#include <bits/stdc++.h>
#include <chrono>
using namespace std;

vector<vector<string>> items;
vector<string> new_string; 
void read_database(string fileName) {
    string currentLine, currentWord;
    vector<string> dataRow;

    ifstream fileStream(fileName, ios::in);

    if (fileStream.is_open()) {
        while (getline(fileStream, currentLine)) {
            dataRow.clear();
            stringstream lineStream(currentLine);

            while (getline(lineStream, currentWord, ',')) {
                dataRow.push_back(currentWord);
            }

            items.push_back(dataRow);
        }
    } 
    else {
        cout << "Error: Unable to open the specified file\n";
    }
}
void write_database(vector<vector<string>> par,string fname){  
    fstream fout(fname,ios::out);
    for(auto x:par){
        for(auto y:x){
            fout<<y;
            if(y!=x.back()) fout<<",";
        }
        fout<<"\n";
    }

}
void append_file(vector<string> par, string fname){  
    fstream fout(fname,ios::out | ios::app);
    for(auto x:par){
        fout<<x;
        if(x!=par.back()) fout<<",";
    }
    fout<<"\n";
}
void print_database(vector<vector<string>> par){
    int c=0;
    for(auto x:par){
        c++;
        cout<<c<<"- ";
        for(int i=0;i<x.size();i++){
            cout<<x[i] << " | ";
        }
        cout<<"\n";
    }
}


class User{
    private:
        string password;
    public:
        string name;
        string id;
        vector<string> serial_numbers_rented;
        void show_main_menu();
        void login();
        void see_all_cars(string id);
        void see_cars_rented_by_you(string id);
        void logout();
        void rent_car(string id, string Model_name,string user_type,int record);
        void return_car(string id,string serial_numbercode);
        int calculate_Fine_due(string id);
        void clear_due(string id);
        void car_search(string id);
};
class Car{
    public:
        string model;
        string condition;
        string manufacturer;
        string serial_number;
        int is_rented;
    void Rent_request(string id,string Model_name,string user_type,int record);
    void Show_duedate(string serial_number_no);
    void car_search(string serial_number_no);
};
class Customer : public User{
    public:
        int Rented_Cars;
        int Fine_due;
        int customer_record;
        void show_customer_dropdown_menu(string id);
};
class Employee : public User{
    public:
        int Fine_due;
        int employee_record;
        void show_employee_dropdown_menu(string id);
};
class Manager : public User{
    public:
        void show_manager_dropdown_menu(string id);
        void see_all_users(string id);
        void see_all_cars(string id);
        void modify_users(string id);
        void modify_cars(string id);
        //void see_rented_to_user(string id,string uid);
        void see_all_rented_cars(string id,string serial_number);
        void user_search(string id);
};

void Customer :: show_customer_dropdown_menu(string id){
    cout<<"---------------------------------------------------------------------\n";
    cout << "!! Welcome !!\n";
    cout<<"\nYou have logged into the system as a Customer\n";
    cout<<"Press 1 to see all cars\n";
    cout<<"Press 2 to to view all cars rented by you\n";
    cout<<"Press 3 to rent a car\n";
    cout<<"Press 4 to return a car\n";
    cout<<"Press 5 to view your fine\n";
    cout<<"Press 6 to clear your dues\n";
    cout<<"Press 7 to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    cin>>c;
    string car_name,serial_numbercode;
    Customer s;
    Car b;
    if(c=='1'){
        s.see_all_cars(id);
        s.show_customer_dropdown_menu(id);
    }
    else if(c=='2'){
        s.see_cars_rented_by_you(id);
        s.show_customer_dropdown_menu(id);
    }
    else if(c=='3'){
        cout<<"Enter the model name of the car you want to rent : ";
        cin.ignore();
        getline(cin,car_name);
        b.Rent_request(id,car_name,"1",customer_record);
        s.show_customer_dropdown_menu(id);            
    }
        
    else if(c=='4'){
        cout<<"Enter the serial_number code of the car you want to return : ";
        cin>>serial_numbercode;
        s.return_car(id,serial_numbercode);
        s.show_customer_dropdown_menu(id);
    }
    else if(c=='5'){
        s.calculate_Fine_due(id);
        s.show_customer_dropdown_menu(id);
    }
    else if(c=='6'){
        s.clear_due(id);
        s.show_customer_dropdown_menu(id);
    }           
    else if(c=='7'){
        logout();
    }
}
void Employee :: show_employee_dropdown_menu(string id){
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nYou have been logged into the system as an Employee\n";
    cout<<"Press 1 to see all the cars\n";
    cout<<"Press 2 to view cars rented by you\n";
    cout<<"Press 3 to view the fine\n";
    cout<<"Press 4 to rent a car\n";
    cout<<"Press 5 to return a car\n";
    cout<<"Press 6 to clear your fine\n";
    cout<<"Press 7 to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    cin>>c;
    string Car_name,serial_numbercode;
    Employee s;
    if(c=='1'){
        s.see_all_cars(id);
        s.show_employee_dropdown_menu(id);
    }
    else if(c=='2'){
        s.see_cars_rented_by_you(id);
        s.show_employee_dropdown_menu(id);
    }
    else if(c=='3'){
        s.calculate_Fine_due(id);
        s.show_employee_dropdown_menu(id);
    }
    else if(c=='4'){
        cout<<"Enter the name of the car you want to rent : ";
        cin>>Car_name;
        s.rent_car(id,Car_name,"2",employee_record);
        s.show_employee_dropdown_menu(id);            
    }
    else if(c=='5'){
        cout<<"Enter the serial_number code of the car you want to return : ";
        cin>>serial_numbercode;
        s.return_car(id,serial_numbercode);
        s.show_employee_dropdown_menu(id);
    }
    else if(c=='6'){
        s.clear_due(id);
        s.show_employee_dropdown_menu(id);
    }
    else if(c=='7'){
        logout();
    }
    
}
void Manager :: show_manager_dropdown_menu(string id){
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\n!! Welcome !! You are logged in as manager.\n\n";
    cout<<"Press 1 to modify user details\n";
    cout<<"Press 2 to modify car details\n";
    cout<<"Press 3 to view all users\n";
    cout<<"Press 4 to view all cars\n";
    cout<<"Press 5 to view all rented cars\n";
    cout<<"Press 6 to show due date of a rented car\n";
    cout<<"Press 7 to search for a user\n";
    cout <<"Press 8 to search for a car\n";
    cout<<"Press 9 to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    cin>>c;
    Manager l;
    Car b;
    User u;
    string serial_number,uid,name,s_no;
    switch(c){
        case '1':
            l.modify_users(id);
            l.show_manager_dropdown_menu(id);
            break;
        case '2':
            l.modify_cars(id);
            l.show_manager_dropdown_menu(id);
            break;
        case '3':
            l.see_all_users(id);
            l.show_manager_dropdown_menu(id);
            break;
        case '4':
            l.see_all_cars(id);
            l.show_manager_dropdown_menu(id);
            break;
        case '5':
            l.see_all_rented_cars(id,serial_number);
            l.show_manager_dropdown_menu(id);
            break;
        case '6':
            cout<<"Enter the serial_number number of the car : ";
            cin>>serial_number;
            b.Show_duedate(serial_number);
            l.show_manager_dropdown_menu(id);
            break;
        case '7':
            cout << " Enter name of the user : ";
            cin >> name;
            l.user_search(name);
            l.show_manager_dropdown_menu(id);
            break;
        case '8':
            cout << " Enter serial_number of the car : ";
            cin >> s_no;
            l.car_search(s_no);
            l.show_manager_dropdown_menu(id);
            break;
        case '9':
            logout();
            l.show_manager_dropdown_menu(id);
            break;
    }
}
void User :: show_main_menu(){
    char c;
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\n\nWelcome to the Car Rental System!\n\n";
    cout<<"1. Press 1 to log in : \n";
    cout<<"2. Press 2 to exit\n";
    cout<<"---------------------------------------------------------------------\n";
    cin>>c;
    if(c=='1'){ //logs in a user 
        User u;
        u.login();
    }

    else{
        cout<<"Thanks for using the system !";
        exit(1);
    }
}
void User :: login(){

    string id,password;
    cout<<"Enter User id : ";
    cin>>id;
    cout<<"Enter Password : ";
    cin>>password;
    items.clear();
    int count=0;
    read_database("all_users_data.csv");
    for(int i=0;i<items.size();i++){
        if(items[i][1]==id){
            count=1;
            if(items[i][2]==password){
                Customer s;
                Employee p;
                Manager l;
                if(items[i][3]=="1"){
                    s.show_customer_dropdown_menu(items[i][1]);
                }
                else if(items[i][3]=="2"){
                    p.show_employee_dropdown_menu(items[i][1]);
                }
                else{
                    l.show_manager_dropdown_menu(items[i][1]);
                }
                break;
            }
            else{
                while(password!=items[i][2]){
                    cout<<"You entered wrong password. Press 1 to reenter the password and 2 to exit\n";
                    char c;
                    cin>>c;
                    if(c=='1'){
                        cout<<"Enter password : ";
                        cin>>password;
                        if(password==items[i][2]) {
                            Customer s;
                            Employee p;
                            Manager l;
                            if(items[i][3]=="1"){
                                s.show_customer_dropdown_menu(items[i][1]);
                            }
                            else if(items[i][3]=="2"){
                                p.show_employee_dropdown_menu(items[i][1]);
                            }
                            else{
                                l.show_manager_dropdown_menu(items[i][1]);
                            }
                            break;
                        }
                    }
                    else if(c=='2'){
                        cout<<"Exiting from the system";
                        return;
                    }
                    else{
                        cout<<"Invalid input.!!\n";
                        User u;
                        u.show_main_menu();
                    }
                }
            }
        }            
    }
    if(count==0) {
        cout << "User not found\n";
        User u;
        u.show_main_menu();
    }
}

void User :: rent_car(string id,string Model_name,string user_type,int record){
    items.clear();
    if(user_type=="1"){
        int count=0;
        items.clear();
        int rec;
        read_database("all_users_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][1]==id){
                rec = stoi(items[i][4]);
            }
        }
        items.clear();
        read_database("rented_cars_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][0]==id){
                count++;
            }
        }
        items.clear();
        if(count<rec){
            read_database("all_cars_data.csv");
            bool found=false;
            for(int i=0;i<items.size();i++){
                if(items[i][0]==Model_name && items[i][4]=="0"){
                    found=true;
                    cout<<"Car succesfully rented for 2 days\n";
                    cout << "You will be charged a rental fee of Rs 1000 per day\n";
                    cout << "\n";
                    cout << "A Fine of Rs 500 will be imposed everyday after the due date\n";
                    items[i][4]="1";
                    new_string.clear();
                    new_string.push_back(id);
                    new_string.push_back(Model_name);
                    new_string.push_back(items[i][3]);
                    new_string.push_back(to_string(time(0)));
                    append_file(new_string,"rented_cars_data.csv");
                    new_string.clear();
                    break;
                }
        
            }
            if(!found) cout << "Car not available\n"; 
            write_database(items,"all_cars_data.csv");
            items.clear();
        }
        else{
            cout<<"You can't rent more cars as per your customer record !\n\n";
            cout << "Please clear your dues first !!\n";
        }
            
    }
    if(user_type=="2"){
        int count=0;
        items.clear();
        read_database("rented_cars_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][0]==id){
                count++;
            }
        }
        items.clear();
        int rec;
        read_database("all_users_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][1]==id){
                rec = stoi(items[i][4]);
            }
        }
        items.clear();
        if(count<rec){
            read_database("all_cars_data.csv");
            bool found = false;
            for(int i=0;i<items.size();i++){
                if(items[i][0]==Model_name && items[i][4]=="0"){
                    found = true;
                    cout<<"Car succesfully rented\n";
                    cout << "Congragulations, you are granted a 15% discount on the rental fee\n";
                    cout << "You will be charged a rental fee of Rs 850 per day\n";
                    cout << "A Fine of Rs 500 will be imposed everyday after the due date\n";
                    items[i][4]="1";
                    new_string.clear();
                    new_string.push_back(id);
                    new_string.push_back(Model_name);
                    new_string.push_back(items[i][3]);
                    new_string.push_back(to_string(time(0)));
                    append_file(new_string,"rented_cars_data.csv");
                    new_string.clear();
                    break;
                }
                
            }
            if(!found){ 
                cout<<"Car not available\n";
            }
            write_database(items,"all_cars_data.csv");
            items.clear();
        }
        else {
            cout<<"You can't rent more cars as per your employee_record !\n\n";
        }
    }
    
}
void User :: return_car(string id,string serial_numbercode){
    items.clear();
    bool found=false;
    read_database("rented_cars_data.csv");
    for(int i=0;i<items.size();i++){
        if(items[i][2]==serial_numbercode && items[i][0]==id){
            found=true;
            items.erase(items.begin()+i,items.begin()+i+1);
            cout<<"Your car is being returned\n";
            cout << "Thank You for using our services!!\n";
            write_database(items,"rented_cars_data.csv");
            items.clear();
            read_database("all_cars_data.csv");
            for(int i=0;i<items.size();i++){
                if(items[i][3]==serial_numbercode) items[i][4]="0";
            }
            write_database(items,"all_cars_data.csv");
            items.clear();
            break;
        }
    }
    if(found==false) cout<<"Invalid car details\n";
    items.clear();
}
void User :: see_all_cars(string id){
    cout<<"Displaying all available cars in the format : Model,Manufacturer,Serial_number,is_rented(or not)\n";
    cout << "In the databse, '0' implies car available to rent and '1' implies car is rented\n";
    items.clear();
    read_database("all_cars_data.csv");
    print_database(items);
    items.clear();
}
void User :: see_cars_rented_by_you(string id){
    int count=1;
    items.clear();
    read_database("rented_cars_data.csv");
    for(int i=0;i<items.size();i++){
        if(items[i][0]==id){
            cout<<count<<". ";
            count++;
            for(int k=0;k<items[i].size()-1;k++)
                cout<<items[i][k]<<" | ";
            time_t stamp = stoi(items[i][3]);
            tm *day_date_time = localtime(&stamp);  
            cout<< day_date_time->tm_mday<<"/"<<1 + day_date_time->tm_mon<<"/"<<1900 + day_date_time->tm_year<<"\n";
        }
    }
    if(count==1) cout<<"You have not rented any Cars as of now\n\n";
    items.clear();
}
// void User :: check_available(string id,string Model_name){
//     items.clear();
//     bool found=false;
//     read_database("all_cars_data.csv");
//     int count=1;
//     for(int i=0;i<items.size();i++){
//         if(items[i][0]==Model_name && items[i][4]=="0"){
//             found=true;
//             cout<<count<<". ";
//             count++;
//             cout<<"Car is available!\n";
//             for(auto j:items[i])
//                 cout<<j<<" | ";
//             cout<<"\n";
//             break;
//         }
//     }
//     if(found==false) cout<<"Car not available\n";
//     items.clear();
// }
int User :: calculate_Fine_due(string id){
    items.clear();
    read_database("rented_cars_data.csv");
    int fine=0;
    for(int i=0;i<items.size();i++){
        if(items[i][0]==id){
            int current_timestamp = time(0);
            int rent_timestamp = stoi(items[i][3]);
            if((current_timestamp-rent_timestamp)/86400>2) fine+=500*((current_timestamp-rent_timestamp)/86400 - 2);
        }
    }
    items.clear();
    cout<<"Your fine is : "<<fine<<"\n";
    return fine;
}
void User :: logout(){
    User u;
    cout<<"You are being logged out\n";
    cout << "Thank You for Visiting!!.\n";
    u.show_main_menu();
}
void User :: clear_due(string id){
    int a = calculate_Fine_due(id);
    if(!a){cout<<"You don't have any pending dues\n";}
    else{
        cout<<"Your dues of Rupees "<<a<<" are being cleared.\n";
        items.clear();
        bool found=false;
        read_database("rented_cars_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][0]==id){
                found=true;
                string temp = items[i][2];
                items.erase(items.begin()+i,items.begin()+i+1);
                write_database(items,"rented_cars_data.csv");
                items.clear();
                read_database("all_cars_data.csv");
                for(int j=0;j<items.size();j++){
                    if(items[j][3]==temp) items[j][4]="0";
                }
                write_database(items,"all_cars_data.csv");
                items.clear();
                break;
            }
        }
    }

}
void User :: car_search(string id){
    items.clear();
    read_database("all_cars_data.csv");
    int found=0;
    for(int i=0;i<items.size();i++){
        if(items[i][3]==id){
            cout  << "Car found\n";
            found=1;
            cout << items[i][0]<<" | "<<items[i][1]<<" | "<<items[i][2]<<" | "<<items[i][3]<<" | "<<items[i][4]<<" | \n";
        }
    }
    if(found==0) cout << "Car Not found\n";
}



void Car :: Show_duedate(string serial_number){
    items.clear();
    string uid;
    time_t stamp;
    read_database("rented_cars_data.csv");
    bool found=false;
    for(int i=0;i<items.size();i++){
        if(items[i][2]==serial_number){
            found=true;
            uid = items[i][0];
            stamp = stoi(items[i][3]);
            break;
        }
    }
    items.clear();
    stamp+=2*86400;
    tm *due_time = localtime(&stamp);  
    if(found==false) cout<<"Car is not rented!\n";
    else{
        cout<<"Due date of the Car is : ";
        cout<< due_time->tm_mday<<"/"<<1 + due_time->tm_mon<<"/"<<1900 + due_time->tm_year<<"\n";
    }
}
void Car :: Rent_request(string id,string Model_name,string user_type,int record){
    User u;
    u.rent_car(id,Model_name,user_type,record);
}
// void Car :: Car_Add(string id){
//     Manager l;
//     l.add_car(id);
// }
// void Car :: Car_delete(string id){
//     Manager l;
//     l.delete_car(id);
// }
// void Car :: Car_update(string id){
//     Manager l;
//     l.update_car(id);
// }



void Manager :: see_all_users(string id){
    cout<<"Displaying all available cars in the format: Model,Manufacturer,Serial_number,is_rented(or not)\n";
    cout << "In the databse, '0' implies car available to rent and '1' implies car is rented\n";
    items.clear();
    read_database("all_users_data.csv");
    int c=0;
    for(auto x:items){
        c++;
        cout<<c<<"- ";
        for(int i=0;i<5;i++){
            if(i==2) continue;
            cout << x[i] << " | ";
        }
        cout<< '\n';
    }
    items.clear();
}
void Manager :: see_all_cars(string id){
    items.clear();
    read_database("all_cars_data.csv");
    cout<<"Below are all the cars. 1 at the end signifies a Customer, 2 means a Employee and 3 means a Manager \n\n";
    cout<<"The data is given in the form of Model_name,manufacturer,serial_number number,and is_rented(1 if caris rented).\n\n";
    print_database(items);
    items.clear();
}
void Manager :: see_all_rented_cars(string id,string serial_number){
    items.clear();
    read_database("rented_cars_data.csv");
    cout<<"Below is the list of all the rented cars. 1 at the end signifies a Customer, 2 means a Employee and 3 means a Manager \n\n";
    cout<<"The data is given in the form of User Id(of renter),model,serial_number,and timestamp.\n\n";
    print_database(items);
    items.clear();
}
void Manager :: modify_users(string id){
    cout << "----------------------------------------------\n";
    cout << "Press 1 to add a user\n";
    cout << "Press 2 to delete a user\n";
    cout << "Press 3 to upadte a user\n";
    cout << "----------------------------------------------\n";
    char c;
    cin>>c;
    string car_name,serial_numbercode;
    Customer s;
    Car b;
    string _name,_id,_password,_type,record,uid;
        if(c=='1'){
            cout<<"Please enter the details of the new user : \n";
            cout<<"Enter name: ";
            cin.ignore();
            getline(cin,name);
            cout<<"Enter id : ";
            cin>>_id;
            cout<<"Enter password : ";
            cin>>_password;
            cout<<"Enter type of the user : 1 if Customer, 2 if Employee, 3 if Manager : ";
            cin>>_type;
            if(_type=="1") {
                items.clear();
                read_database("all_users_data.csv");
                int rec=0,cnt=0;
                for(int i=0;i<items.size();i++){
                    if(items[i][3]=="1"){
                        rec+=stoi(items[i][4]);
                        cnt++;
                    }
                }
                items.clear();
                rec/=cnt;
                record = to_string(rec);
                cout << "Assigning average customer record: "<<record<<'\n';
            }
            else if(_type=="2") {
                items.clear();
                read_database("all_users_data.csv");
                int rec=0,cnt=0;
                for(int i=0;i<items.size();i++){
                    if(items[i][3]=="2"){
                        rec+=stoi(items[i][4]);
                        cnt++;
                    }
                }
                items.clear();
                rec/=cnt;
                record = to_string(rec);
                cout << "Assigning average customer record: "<<record<<'\n';
            }
            fstream fout("all_users_data.csv",ios::out | ios::app);
            fout<<name<<","<<_id<<","<<_password<<","<<_type<<","<<record<<'\n';
            cout<<"New User Added !!\n";
            cout << "-----------------------------------------\n";
        }
        else if(c=='2'){
            cout<<"Enter the user id of the user : ";
            cin>>uid;
            items.clear();
            int found=0;
            read_database("all_users_data.csv");
            for(int i=0;i<items.size();i++){
                if(items[i][1]==uid){
                    cout << "User has been succesfully deleted\n";
                    cout << "-----------------------------------------\n";
                    found=1;
                    items.erase(items.begin()+i,items.begin()+i+1);
                    break;
                }
            }
            write_database(items,"all_users_data.csv");
            items.clear();
            vector<string> serial_numbers;
            read_database("rented_cars_data.csv");
            for(int i=0;i<items.size();i++){
                if(items[i][0]==uid){
                    serial_numbers.push_back(items[i][2]);
                    items.erase(items.begin()+i,items.begin()+i+1);
                    break;
                }
            }
            write_database(items,"rented_cars_data.csv");
            items.clear();

            read_database("all_cars_data.csv");
            for(int i=0;i<items.size();i++){
                for(int j=0;j<serial_numbers.size();j++){
                    if(serial_numbers[j]==items[i][3]){
                        items[i][4]="0";
                    }
                }
            }
            write_database(items,"all_cars_data.csv");
            items.clear();
            if(found==0) cout<<"User not found.\n";
        }
        else{
            string upid;
            cout<<"Enter the id of the user you want to update : ";
            cin>>upid;
            cout<<"Enter the serial number of the field you want to update : \n";
            cout<<"Enter 1 to update name of the user\n";
            cout<<"Enter 2 to update user id\n";
            cout<<"Enter 3 to update Password\n";
            cout<<"Enter 4 to update type of User(Customer/Employee)\n";
            cout<<"Enter 5 to update customer record\n";
            char c;
            cin>>c;
            items.clear();
            bool found=false;
            read_database("all_users_data.csv");
            for(int i=0;i<items.size();i++){
                if(items[i][1]==upid){
                    found=true;
                    string new_field;
                    cout<<"Enter the new value of the field : ";
                    cin.ignore();
                    getline(cin,new_field);
                    if(c=='1'){
                        items[i][0]=new_field;
                    }
                    else if(c=='2'){
                        items[i][1]=new_field;
                    }
                    else if(c=='3'){
                        items[i][2]=new_field;
                    }
                    else if(c=='4'){
                        items[i][1]=new_field;
                    }
                    else{
                        cout<<"Invalid input!\n\n";
                    }
                    break;
                }
            }
            cout<<"User updated\n";
            write_database(items,"all_users_data.csv");
            items.clear();
            if(found==false) cout<<"User was not found.\n\n";
        }
}
void Manager :: modify_cars(string id){
    cout << "-----------------------------------------\n";
    cout << "Press 1 to add a Car\n";
    cout << "Press 2 to delete a Car\n";
    cout << "Press 3 to upadte a Car\n";
    cout << "-----------------------------------------\n";
    char c;
    cin>>c;
    if(c=='1'){
        cout<<"Please enter the details of the new car: \n";
        string model,manufacturer,condition,serial_number;
        cout<<"Enter model: ";
        cin.ignore();
        getline(cin,model);
        cout<<"Enter manufacturer : ";
        cin>>manufacturer;
        cout << "Enter condition of the car(new/used) : ";
        cin >> condition;
        cout<<"Enter serial_number : ";
        cin>>serial_number;
        fstream fout("all_cars_data.csv",ios::out | ios::app);
        fout<<model<<","<<manufacturer<<","<<condition<<","<<serial_number<<",0"<<'\n';
        cout<<"New car has been added.\n";
        cout << "-----------------------------------------\n";
    }
    else if(c=='2'){
        string serial_numberno;
        cout<<"Enter the serial_number number of the car: ";
        cin>>serial_numberno;
        items.clear();
        int found=0;
        read_database("all_cars_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][3]==serial_numberno){
                found=1;
                items.erase(items.begin()+i,items.begin()+i+1);
                break;
            }
        }
        write_database(items,"all_cars_data.csv");
        items.clear();
        read_database("rented_cars_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][2]==serial_numberno){
                items.erase(items.begin()+i,items.begin()+i+1);
                break;
            }
        }
        write_database(items,"rented_cars_data.csv");
        items.clear();
        if(found==0) cout<<"Car not found.\n";
        else cout  << "Car deleted!!\n";
        cout << "-----------------------------------------\n";
    }
    else {
        string serial_number_no;
        cout<<"Enter the serial_number number of the car you want to update : ";
        cin>>serial_number_no;
        cout<<"Enter the serial number of the field you want to update : \n";
        cout<<"1. Name of the car\n";
        cout<<"2. Name of the manufacturer\n";
        char c;
        cin>>c;
        items.clear();
        bool found=false;
        string new_field;
        read_database("all_cars_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][3]==serial_number_no){
                found=true;
                cout<<"Enter the new value of the field : ";
                cin.ignore();
                getline(cin,new_field);
                if(c=='1'){
                    items[i][0]=new_field;
                }
                else if(c=='2'){
                    items[i][1]=new_field;
                }
                else{
                    cout<<"Invalid input!\n\n";
                }
                break;
            }
        }
        write_database(items,"all_cars_data.csv");
        items.clear();

        read_database("rented_cars_data.csv");
        for(int i=0;i<items.size();i++){
            if(items[i][2]==serial_number_no){
                found=true;
                if(c=='1'){
                    items[i][1]=new_field;
                }
                break;
            }
        }
        
        write_database(items,"rented_cars_data.csv");
        items.clear();
        if(found==false) cout<<"car was not found.\n\n";
        else cout<<"Car Updated !!\n";
        cout << "-----------------------------------------\n";
    }
}
void Manager :: user_search(string id){
    items.clear();
    read_database("all_users_data.csv");
    int found=0;
    for(int i=0;i<items.size();i++){
        if(items[i][0]==id){
            cout  << "User found\n";
            found=1;
            cout << items[i][0]<<" | "<<items[i][1]<<" | "<<items[i][2]<<" | "<<items[i][3]<<" | "<<items[i][4]<<" | \n";
        }
    }
    if(found==0) cout << "User Not found\n";
    items.clear();
}
int main(){
    User U;
    U.show_main_menu();
    return 0;
}