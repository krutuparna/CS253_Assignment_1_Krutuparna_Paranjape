# CS253_Assignment_1 : Car Rental System
Car Rental System implemented in C++ using OOP concepts

The assignment implements a car system in C++ using object oriented programming paradigms. The code is present in main.cpp. There are 3 kinds of users and each of them have different functionalities and specifications.All functionalities have been implemented acccording to the Problem Statement. There are 3 csv files which serve as databases.

[Problem Statement]
- [all_users_data.csv]{https://github.com/krutuparna/CS253_Assignment_1_Krutuparna_Paranjape/blob/main/all_users_data.csv} stores the data of all users in the format : [name,user id, password, user_type, user_record]. User_type is '1' for a customer, '2' for an employee and '3' for Manager.
- [all_cars_data.csv]{https://github.com/krutuparna/CS253_Assignment_1_Krutuparna_Paranjape/blob/main/all_cars_data.csv} stores the data of all cars in the format : [model_name,manufacturer, condition, serial_number, is_rented(or not)]. 'Is_rented' is '1' if the car is rented else '0'.
- [rented_cars_data.csv]{https://github.com/krutuparna/CS253_Assignment_1_Krutuparna_Paranjape/blob/main/rented_cars_data.csv}  stores the data of all rented cars in the format :[user_id, model, serial_number, timestamp]. The user id is the id of the user who rented the car and timestamp stores the time when the user rented it. The timestamp will help us later in calculating the fine for users.

To run the system, type the following commands in the console:
```
g++ main.cpp -o main
.\main
```
The system will run on the console. The data modified throughout the program run will be reflected in the csv files.
