#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Ticket {
public:
    int Price;

public:
    string Source, Destination;
    string Traveller_name;
    int Date_year;
    int ticket_id;

    void bookTicket();
    void cancelTicket();
    void updateTicket();
    int getPrice();

};


class Traveller {
public:
    int Traveller_id;
    vector <Ticket> Tick; 

public:
    string Name;
    int type; // 0 for Astronaut, 1 for Passenger, 2 for Commander

    string getName()
    {
        cout << Name << endl;
        return Name;
    }

    int getId()
    {
        cout << Traveller_id << endl;
        return Traveller_id;
    }
};

vector <Traveller> Tr;

void List_all_traveller(){
    for(int i=0; i<=Tr.size()-1;i++){
        cout << Tr[i].Name << " " << Tr[i].type << " " << Tr[i].Traveller_id << endl;
    }
}

int SetAstronautId(string t_name){
    int sum = 0;
    for (int i=0; i < t_name.length(); i++) sum += t_name[i];
    return sum-50;
}
int SetCommanderId(string t_name){
    int sum = 0;
    for (int i=0; i < t_name.length(); i++) sum += t_name[i];
    return sum+50;
}
int UpdateAstronautId(string t_name){
    int updated_id;
    cout << "Update Id: ";
    cin >> updated_id;
    return updated_id;
}
int UpdateCommanderId(string t_name){
    int updated_id;
    cout << "Update Id: ";
    cin >> updated_id;
    return updated_id;
}
int SetPassengerId(string t_name){
    int sum = 0;
    for (int i=0; i < t_name.length(); i++) sum += t_name[i];
    return sum;
}

void AddTraveller(string t_name, int t_type){
    Traveller tr;
    tr.Name = t_name;
    tr.type = t_type;
    if(t_type == 0) tr.Traveller_id = SetAstronautId(t_name);
    if(t_type == 1) tr.Traveller_id = SetPassengerId(t_name);
    if(t_type == 2) tr.Traveller_id = SetCommanderId(t_name);
    Tr.push_back(tr);
}


class Planet {
public:
    string name;
    int x, y, z;

    int *getCoordinates()
    {
        static int coordinates[3];
        coordinates[0]=x; coordinates[1]=y; coordinates[2]=z;
        cout << coordinates[0] << "," << coordinates[1] << "," << coordinates[2] << endl;
        return coordinates;
    }

    string getName()
    {
        cout << name << endl;
        return name;
    }

};

vector <Planet> Pl;

void List_all_planets(){
    for(int i=0; i<=Pl.size()-1;i++){
        cout << Pl[i].name << " " << Pl[i].x << "," << Pl[i].y << "," << Pl[i].z << endl;
    }
}

void AddPlanet(string p_name, int p_x, int p_y, int p_z){
    Planet p;
    p.name = p_name;
    p.x = p_x; p.y = p_y; p.z = p_z;
    Pl.push_back(p);
}


void ShowPassengerTicket(string name){
    int traveller_exist=0;
    for(int i=0; i<=Tr.size()-1;i++){
        if(name == Tr[i].Name){
            traveller_exist = 1;
            if(Tr[i].Tick.size()==0) cout << "No ticket" << endl;
            else{
                for(int j=0; j<=Tr[i].Tick.size()-1; j++){
                    cout << "Ticket: " << endl;
                    cout << "Ticket Id: " << Tr[i].Tick[j].ticket_id << endl; 
                    cout << "Traveller Name: " << Tr[i].Tick[j].Traveller_name << endl;
                    cout << "Source: " << Tr[i].Tick[j].Source << endl;
                    cout << "Destination: " << Tr[i].Tick[j].Destination << endl;
                    cout << "Traveller Date (year): " << Tr[i].Tick[j].Date_year << endl;
                    cout << "Price: " << Tr[i].Tick[j].Price << endl;
                }
                break;
            }
            break;
        } 
        
    }
    if(traveller_exist != 1){
        cout << "Traveller does not exists" << endl;
    }
}

int getPrice(string Source, string Destination, int Date_year){
    int source_exist = 0, destination_exist=0;
    float Price=0;
    int x_s, y_s, z_s, x_d, y_d, z_d;
    for(int i=0; i<=Pl.size()-1;i++){
        if(Source == Pl[i].name){
            source_exist = 1;
            x_s = Pl[i].x; y_s = Pl[i].y; z_s = Pl[i].z; 
        } 
        if(Destination == Pl[i].name){
            destination_exist = 1;
            x_d = Pl[i].x; y_d = Pl[i].y; z_d = Pl[i].z; 
        } 
    }
    if(source_exist == 0 || destination_exist == 0){
        cout << "Planet doesn't exists" << endl;
    }
    else{
        Price = 100*((x_s-x_d)*(x_s-x_d)+(y_s-y_d)*(y_s-y_d)+(z_s-z_d)*(z_s-z_d))/(Date_year+1);
    }
    return (int)Price;
}

Ticket createTicket(string Source, string Destination, string Traveller_name, int Date_year, int Price){
    Ticket ti;
    ti.Source = Source;
    ti.Destination = Destination;
    ti.Traveller_name = Traveller_name;
    ti.Date_year = Date_year;
    ti.Price = getPrice(Source,Destination,Date_year);
    ti.ticket_id = rand();
    return ti;
}

void bookTicket(){
    string traveller_name;

    string source, destination;
    int date_year;

    cout << "Enter Name: " << endl;
    cin >> traveller_name;

    cout << "Enter Source Planet: " << endl;
    cin >> source;
    cout << "Enter Destination Planet: " << endl;
    cin >> destination;
    cout << "Enter Journey Date (Year): " << endl;
    cin >> date_year;


    Ticket t1 = createTicket(source,destination,traveller_name,date_year,getPrice(source,destination,date_year));

    int traveller_exist = 0;
    for(int i=0; i<=Tr.size()-1;i++){
        if(traveller_name == Tr[i].Name){
            traveller_exist = 1;
            Tr[i].Tick.push_back(t1);
            break;
        } 
    }
    if(traveller_exist != 1){
        AddTraveller(traveller_name,1);
        Tr.back().Tick.push_back(t1);
    }

    ShowPassengerTicket(traveller_name);

    int return_ticket = 0, return_year = 0;
    cout << "Do you want to book return ticket? (0 or 1)" << endl;
    cin >> return_ticket;

    if(return_ticket==0){
        cout << "Thanks" << endl;
    }
    else{
        cout << "Enter Return date (year): " << endl;
        cin >> return_year;
        Ticket t2 = createTicket(destination,source,traveller_name,return_year,getPrice(source,destination,return_year));
        for(int i=0; i<=Tr.size()-1;i++){
            if(traveller_name == Tr[i].Name){
                Tr[i].Tick.push_back(t2);
                break;
            } 
        }
        ShowPassengerTicket(traveller_name);
    }
}

void cancelTicket(){
    string traveller_name;
    cout << "Enter Name: " << endl;
    cin >> traveller_name;
    int traveller_exist = 0;
    for(int i=0; i<=Tr.size()-1;i++){
        if(traveller_name == Tr[i].Name){
            traveller_exist = 1;
            Tr[i].Tick.pop_back();
            cout << "Ticket Cancelled" << endl;
            ShowPassengerTicket(traveller_name);
            break;
        } 
    }
    if(traveller_exist != 1){
        cout << "Traveller does not exits" << endl;
    }
}

void updateTicket(){
    string traveller_name;
    string source, destination;
    int date_year;
    cout << "Enter Name: " << endl;
    cin >> traveller_name;
    int traveller_exist = 0;
    for(int i=0; i<=Tr.size()-1;i++){
        if(traveller_name == Tr[i].Name){
            traveller_exist = 1;
            if(Tr[i].Tick.size()==0){
                cout << "No ticket found" << endl;
            }
            else{
                cout << "Update Source Planet: " << endl;
                cin >> source;
                cout << "Update Destination Planet: " << endl;
                cin >> destination;
                cout << "Update Journey Date (Year): " << endl;
                cin >> date_year;

                Tr[i].Tick.back().Source = source;
                Tr[i].Tick.back().Destination = destination;
                Tr[i].Tick.back().Date_year = date_year;
                Tr[i].Tick.back().Price = getPrice(source,destination,date_year);

                ShowPassengerTicket(traveller_name);
            }

            break;
        } 
    }
    if(traveller_exist != 1){
        cout << "Traveller does not exits" << endl;
    }
}

int main(){

    // 0 for Astronaut, 1 for Passenger, 2 for Commander
    AddTraveller("Ayush", 0);
    AddTraveller("Shubh",0);
    AddTraveller("Amit", 1);
    AddTraveller("Anay",1);
    AddTraveller("Nitin",1);
    AddTraveller("Rajeev",1);
    AddTraveller("Prateek", 1);
    AddTraveller("Piyush",1);
    AddTraveller("Abhijeet",1);
    AddTraveller("Ishan",1);
    AddTraveller("Dharam", 1);
    AddTraveller("Harish",1);
    AddTraveller("Akarsh",1);
    AddTraveller("Harshit",2);
    AddTraveller("Harsh",2);
    // List_all_traveller();

    AddPlanet("Earth", 0, 0, 0);
    AddPlanet("Moon", 200, 400, 600);
    AddPlanet("Mars", 1000, 2000, 3000);
    // List_all_planets();

    int press;
    cout << "Press 1 to Book ticket, Press 2 to Cancel ticket, Press 3 to Update ticket, Press 4 to View ticket" << endl;
    cin >> press;
    if(press == 1) bookTicket();
    if(press == 2) cancelTicket();
    if(press == 3) updateTicket();
    if(press == 4){
        string traveller_name;
        cout << "Enter Name: " << endl;
        cin >> traveller_name;
        ShowPassengerTicket(traveller_name);
    }
    
    main();
    return 0;
}