#include <iostream>
#include <fstream>
using namespace std;

class Shopping
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void admin();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void Shopping::menu()
{
    int choice;
    string email;
    string password;

    while (1)
    {
        cout << "\t\t\t\t___________________________\n";
        cout << "\t\t\t\t                            \n";
        cout << "\t\t\t\t    Supermarket Main Menu    \n";
        cout << "\t\t\t\t                            \n";
        cout << "\t\t\t\t___________________________\n";

        cout << "\t\t\t\t|  1) Administrator   |\n";
        cout << "\t\t\t\t|                     |\n";
        cout << "\t\t\t\t|  2) Buyer           |\n";
        cout << "\t\t\t\t|                     |\n";
        cout << "\t\t\t\t|  3) Exit            |\n";
        cout << "\t\t\t\t|_____________________| \n";
        cout << "\n\t\t\t\t Please Select!\t";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\n\t\t\t Please Login \n";
            cout << "\t\t\t Enter Email  \n";
            cin >> email;
            cout << "\t\t\t Password      \n";
            cin >> password;

            if (email == "abc@gmail.com" && password == "abc")
            {
                admin();
            }
            else
            {
                cout << "Invalid email/password\n";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);

        default:
            cout << "Please select from the given options";
            break;
        }
    }
}

void Shopping::admin()
{
m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator menu";
    cout << "\n\t\t\t|___1) Add the product___|\n";
    cout << "\n\t\t\t|                        |\n";
    cout << "\n\t\t\t|__2) Modify the product_|\n";
    cout << "\n\t\t\t|                        |\n";
    cout << "\n\t\t\t|__3) Delete the product_|\n";
    cout << "\n\t\t\t|__4) Back to the main menu__|\n";
    cout << "\n\t\t\t|_________________________|\n";

    cout << "\n\n\t Please enter your choice";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Invalid Choice!";
        break;
    }
    goto m;
}

void Shopping::buyer()
{
    int choice;

    do
    {
        cout << "\t\t\t   Buyer       \n";
        cout << "\t\t\t_______________\n";
        cout << "\t\t\t               \n";
        cout << "\t\t\t1) Buy product \n";
        cout << "\t\t\t               \n";
        cout << "\t\t\t2)  Go back    \n";
        cout << "\t\t\t Enter your choice:\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            receipt();
            break;

        case 2:
            menu();
            break;

        default:
            cout << "Invalid choice";
        }

    } while (choice != 2);
}

void Shopping::add()
{
m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Product code of the product";
    cin >> pcode;
    cout << "\n\n\t Name of the product";
    cin >> pname;
    cout << "\n\n\t Price of the product";
    cin >> price;
    cout << "\n\n\t Discount on product";
    cin >> dis;

    data.open("database.txt", ios::in);

    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if (c == pcode)
            {
                token++;
            }

            data >> c >> n >> p >> d;
        }

        data.close();

        if (token == 1)
            goto m;
        else
        {
            data.open("database.txt", ios::app | ios::out);
            data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
    }

    cout << "\n\n\t\t Record Inserted!";
}

void Shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t\t Product code";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if (!data)
    {
        cout << "\n\nFile doesn't exist!";
    }
    else
    {
        data1.open("database.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> dis;

        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "\n\t\tProduct new code:";
                cin >> c;
                cout << "\n\t\tName of the product:";
                cin >> n;
                cout << "\n\t\tPrice:";
                cin >> p;
                cout << "\n\t\tDiscount";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";

                cout << "\n\n\t\t Record edited";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\nRecord not found sorry";
        }
    }
}

void Shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\n\tDelete product";
    cout << "\n\n\tProduct code";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File doesn't exist";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> dis;

        while (!data.eof())
        {
            if (pcode == pkey)
            {
                cout << "\n\n\tProduct deleted successfully";
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }

        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\nRecord can't be found";
        }
    }
}

void Shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|_________________________________\n";
    cout << "Product No\t\tName\t\tPrice\n";
    cout << "\n\n|_________________________________\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void Shopping::receipt()
{
    fstream data;

    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float total = 0;

    cout << "\n\n\t\t\t RECEIPT";
    data.open("database.txt", ios::in);

    if (!data)
    {
        cout << "\n\nEmpty database";
    }
    else
    {
        data.close();

        list();
        cout << "\n______________________________\n";
        cout << "\n|                            \n";
        cout << "\n    Please place the order   \n";
        cout << "\n______________________________\n";
        cout << "\n|                            \n";

        do
        {
        m:
            cout << "\n\nEnter the product code:";
            cin >> arrc[c];
            cout << "\n\nEnter the product quantity";
            cin >> arrq[c];

            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\nDuplicate product code. Please try again";
                    goto m;
                }
            }

            c++;
            cout << "\n\nDo you want to buy another product? if yes then press y else no";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t___________________RECEIPT__________________\n";
        cout << "\nProduct No\t Product Name\t Product quantity\t price\t Amount\n";

        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;

            while (!data.eof())
            {
                if (pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    float discountAmount = amount - (amount * dis / 100); // Calculate amount with discount
                    total += discountAmount;                              // Update total with discounted amount
                    cout << "\n"
                         << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t\t" << discountAmount;
                }
                data >> pcode >> pname >> price >> dis;
            }

            data.close();
        }
    }

    cout << "\n\n________________________________";
    cout << "\n Total Amount:" << total;
}

int main()
{
    Shopping s;
    s.menu();
}
