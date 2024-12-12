#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdio>
using namespace std;
using namespace sf;
void create(string cnicInput);
void view(string cnicInput);
void update(string cnicInput);
void deleteProfile(string cnicInput);
void menuifcnicexist(string cnicInput);
void menuifcnicdoesnotexist(string cnicInput);

int width = 150;

int main()
{

	RenderWindow window(VideoMode(800, 600), "Main Menu");
	Font font;
	if (!font.loadFromFile("C:\\Users\\user\\source\\repos\\sfml practice\\Debug\\arial.ttf")) {
		cerr << "Could not load font\n";
		return -1;
	}
	Texture Backgroundlogo;
	if (!Backgroundlogo.loadFromFile("C:\\Users\\user\\Downloads\\Untitled design (1).png"))
	{
		cerr << "Could not load image\n";
		return -1;
	}
	Sprite backgroundSprite;
	backgroundSprite.setTexture(Backgroundlogo);
	float scaleX = static_cast<float>(window.getSize().x) / backgroundSprite.getLocalBounds().width;
	float scaleY = static_cast<float>(window.getSize().y) / backgroundSprite.getLocalBounds().height;
	backgroundSprite.setScale(scaleX, scaleY);



	Text companyLabel("Welcome to Our Solar Cost Estimator", font, 36);
	companyLabel.setPosition(100, 150);
	Text nameLabel("Enter your Name : ", font, 30);
	nameLabel.setPosition(100, 250);
	Text cnicLabel("Enter your CNIC:", font, 30);
	cnicLabel.setPosition(100, 350);
	string nameInput = " ";
	string cnicInput = "  ";

	Text nameField(nameInput, font, 30);
	nameField.setPosition(350, 250);
	nameField.setFillColor(sf::Color::White);

	Text cnicField(cnicInput, font, 30);
	cnicField.setPosition(350, 350);
	cnicField.setFillColor(sf::Color::White);
	Text instruction("Press Enter to submit", font, 20);
	instruction.setPosition(250, 400);
	instruction.setFillColor(sf::Color::Yellow);
	bool editingName = true;
	RectangleShape enterBox(Vector2f(200, 50)); // 2d size with 200 width and 50 height
	enterBox.setPosition(300, 450);
	enterBox.setFillColor(Color::Yellow);


	Text enterText("Enter", font, 24);
	enterText.setFillColor(Color::Black);
	enterText.setPosition(
		enterBox.getPosition().x + (enterBox.getSize().x / 2) - 30,//center of the box horizontally which is half the width and subtracting 30 to align it in centre of box
		enterBox.getPosition().y + (enterBox.getSize().y / 2) - 15);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}


			if (event.type == Event::TextEntered) {

				if (event.text.unicode == '\b') {
					if (editingName && !nameInput.empty()) {
						nameInput.pop_back();
					}
					else if (!editingName && !cnicInput.empty()) {
						cnicInput.pop_back();
					}
				}

				else if (event.text.unicode == '\r') {
					if (editingName) {
						editingName = false;
					}
					else if (cnicInput.length() == 15) {
						cout << "Name: " << nameInput << "\n";
						cout << "CNIC: " << cnicInput << "\n";
						window.close();
					}
					else {
						cout << "CNIC must be 13 digits long.\n";
					}
				}

				else if (event.text.unicode < 128) {
					if (editingName) {

						nameInput += static_cast<char>(event.text.unicode);
					}
					else {

						if (isdigit(event.text.unicode) && cnicInput.length() < 15) {
							cnicInput += static_cast<char>(event.text.unicode);
						}
					}
				}
			}
		}

		nameField.setString(nameInput);
		cnicField.setString(cnicInput);


		window.clear();
		window.draw(backgroundSprite);
		window.draw(companyLabel);
		window.draw(nameLabel);
		window.draw(cnicLabel);
		window.draw(nameField);
		window.draw(cnicField);
		window.draw(instruction);
		window.draw(enterBox);
		window.draw(enterText);
		window.display();
	}
	int space = (width - 47) / 2; //47 is the length of heading
	cout << setw(space + 47) << "SOLAR PANEL MANAGMENT & COST ESTIMATION PROGRAM" << setw(width - space - 47) << "" << endl;
	int option;

	cout << "\n\nHi " << nameInput << "! This is the Solar Panel Management and Estimation program! \nWhat do you want to do today? " << endl;
	fstream check(cnicInput + ".txt", ios::in | ios::out);
	if (!check)
	{
		check.close();
		menuifcnicdoesnotexist(cnicInput);
	}
	else
	{
		check.close();
		menuifcnicexist(cnicInput);
	}
	check.close();
	space = (width - 33) / 2; //33 is the length of thank you message
	cout << right;
	cout << "\n\n" << setw(space + 33) << "THANK YOU FOR USING THIS PROGRAM!" << setw(width - space - 33) << "" << endl;
	return 0;
}


void menuifcnicexist(string cnicInput)
{
	int option;
	cout << "Enter one of the following options: " << endl;
	cout << "Option 1: View your Profile\n"
		<< "Option 2 : Update Profile\n"
		<< "Option 3 : Delete Profile\n"
		<< "Option 4 : Exit" << endl;
	do {
		cout << "\nEnter option number: ";
		cin >> option;
		if (option < 1 || option > 4)
			cout << "Enter only any number from 1 to 4" << endl;
	} while (option < 1 || option > 4);
	if (option == 1)
	{
		view(cnicInput);
	}
	else if (option == 2)
	{
		update(cnicInput);
	}
	else if (option == 3)
	{
		deleteProfile(cnicInput);
	}
}

void menuifcnicdoesnotexist(string cnicInput)
{
	ifstream backup(cnicInput + "_b.txt");
	if (!backup)
	{
		int option;
		cout << "Enter one of the following options: " << endl;
		cout << "Option 1: Create New Profile\n"
			<< "Option 2: View your Profile\n"
			<< "Option 3 : Update Profile\n"
			<< "Option 4 : Delete Profile\n"
			<< "Option 5 : Exit" << endl;
		do {
			cout << "\nEnter option number: ";
			cin >> option;
			if (option < 1 || option > 5)
				cout << "Enter only any number from 1 to 5" << endl;
		} while (option < 1 || option > 5);

		if (option == 1)
		{
			create(cnicInput);
		}
		else if (option == 2)
		{
			view(cnicInput);
		}
		else if (option == 3)
		{
			update(cnicInput);
		}
		else if (option == 4)
		{
			deleteProfile(cnicInput);
		}
	}
	else
	{
		char ans;
		cout << "A file under your cnic was deleted previously, would you like to restore it? ";
		do {
			cin >> ans;
			if (ans != 'N' && ans != 'Y')
				cout << "Enter only Y or N : ";
			else
				break;
		} while (true);
		if (ans == 'Y')
		{
			ofstream out(cnicInput + ".txt");
			ifstream backup(cnicInput + "_b.txt");
			string read;
			while (!backup.eof())
			{
				getline(backup, read);
				out << read << endl;
			}
			out.close();
			backup.close();
			cout << "\nYour file has been restored successfully! " << endl;
			menuifcnicexist(cnicInput);
		}
		else
		{
			int option;
			cout << "Enter one of the following options: " << endl;
			cout << "Option 1: Create New Profile\n"
				<< "Option 2: View your Profile\n"
				<< "Option 3 : Update Profile\n"
				<< "Option 4 : Delete Profile\n"
				<< "Option 5 : Exit" << endl;
			do {
				cout << "\nEnter option number: ";
				cin >> option;
				if (option < 1 || option > 5)
					cout << "Enter only any number from 1 to 5" << endl;
			} while (option < 1 || option > 5);

			if (option == 1)
			{
				create(cnicInput);
			}
			else if (option == 2)
			{
				view(cnicInput);
			}
			else if (option == 3)
			{
				update(cnicInput);
			}
			else if (option == 4)
			{
				deleteProfile(cnicInput);
			}
		}
	}

}


void create(string cnicInput)
{
	int space;
	ofstream out(cnicInput + ".txt");
	cout << "\nEnter building name: ";
	string bname;
	cin.clear();
	cin.ignore();
	getline(cin, bname);
	out << "Building name: " << bname << '\n' << endl;
	int fan, exhaust, ac1, ac1_5, ac2, cooler, fridge, iron, washing, micro, heater, motor, tv, bulb;
	float sum = 0;
	cout << "\nEnter content for your profile: " << endl;
	cout << "\nEnter the appliances that you want to use at a time at peak time of sun: \n";//sun time wether api
	out << "Number of appliances used at peak time of sun: \n";
	do {
		cout << "Enter number of fans (80W): ";
		cin >> fan;
		if (cin.fail() || fan < 0 || fan>15)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Fans (80W): " << fan << endl;
			break;
		}
	} while (true);
	sum += fan * 80;
	do {
		cout << "Enter number of 1 ton inverter ac (900W): ";
		cin >> ac1;

		if (cin.fail() || ac1 < 0 || ac1>3)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "AC 1 ton inverter (900W): " << ac1 << endl;
			break;
		}
	} while (true);
	sum += ac1 * 900;
	do {
		cout << "Enter number of 1.5 ton inverter ac (1500W): ";
		cin >> ac1_5;
		if (cin.fail() || ac1_5 < 0 || ac1_5>2)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "AC 1.5 ton inverter (1500W): " << ac1_5 << endl;
			break;
		}
	} while (true);
	sum += ac1_5 * 1500;
	do {
		cout << "Enter number of 2 ton ac inverter (1900W): ";
		cin >> ac2;
		if (cin.fail() || ac2 < 0 || ac2>2)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "AC 2 ton inverter (1900W): " << ac2 << endl;
			break;
		}
	} while (true);
	sum += ac2 * 1900;
	do {
		cout << "Enter number of room cooler (750W): ";
		cin >> cooler;
		if (cin.fail() || cooler < 0 || cooler>5)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Room Cooler (750W): " << cooler << endl;
			break;
		}
	} while (true);
	sum += cooler * 750;
	do {
		cout << "Enter number of fridge and freezer (180W each): ";
		cin >> fridge;
		if (cin.fail() || fridge < 0 || fridge>5)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Fridge and Freezer (180W each): " << fridge << endl;
			break;
		}
	} while (true);
	sum += fridge * 180;
	do {
		cout << "Enter number of iron (1000W): ";
		cin >> iron;
		if (cin.fail() || iron < 0 || iron>2)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Iron (1000W): " << iron << endl;
			break;
		}
	} while (true);
	sum += iron * 1000;
	do {
		cout << "Enter number of washing machines (900W): ";
		cin >> washing;
		if (cin.fail() || washing < 0 || washing>2)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Washing Machine (900W): " << washing << endl;
			break;
		}
	} while (true);
	sum += washing * 900;
	do {
		cout << "Enter number of microwaves (1200W): ";
		cin >> micro;
		if (cin.fail() || micro < 0 || micro>3)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Microwave (1200W): " << micro << endl;
			break;
		}
	} while (true);
	sum += micro * 1200;
	do {
		cout << "Enter number of heaters and geyser (2000W each): ";
		cin >> heater;
		if (cin.fail() || heater < 0 || heater>3)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Heater and Geyser (2000W each): " << heater << endl;
			break;
		}
	} while (true);
	sum += heater * 2000;
	do {
		cout << "Enter number of pump motor (1horsepower and 750W): ";
		cin >> motor;
		if (cin.fail() || motor < 0 || motor>2)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Pump motor (1hp and 750W): " << motor << endl;
			break;
		}
	} while (true);
	sum += motor * 750;
	do {
		cout << "Enter number of LCD TV (100W): ";
		cin >> tv;
		if (cin.fail() || tv < 0 || tv>7)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "TV (100W): " << tv << endl;
			break;
		}
	} while (true);
	sum += tv * 100;
	do {
		cout << "Enter number of light bulbs (12W): ";
		cin >> bulb;
		if (cin.fail() || bulb < 0 || bulb>200)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Light Bulbs (12W): " << bulb << endl;
			break;
		}
	} while (true);
	sum += bulb * 12;
	do {
		cout << "Enter number of exhaust fans (60W): ";
		cin >> exhaust;
		if (cin.fail() || exhaust < 0 || exhaust>20)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter correct input\n";
		}
		else
		{
			out << "Exhaust Fans (60W): " << exhaust << endl;
			break;
		}
	} while (true);
	sum += exhaust * 60;

	string appname;
	int appwatt;
	int appnum;
	cin.clear();
	cin.ignore();
	char other;
	do {
		cout << "Do you want to add another appliance that is not mentioned above?(Y/N) ";
		do {
			cin >> other;
			if (other != 'N' && other != 'Y')
				cout << "\nEnter only Y or N: ";
			else
				break;
		} while (true);
		if (other == 'Y')
		{
			cout << "Enter the name of any other appliance that is not mentioned above: ";
			cin.clear();
			cin.ignore();
			getline(cin, appname);
			cout << "Enter power of " << appname << " in watts: ";
			do {
				cin >> appwatt;
				if (cin.fail() || appwatt < 0)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Please enter correct input\n";
				}
				else
				{
					break;
				}
			} while (true);
			cout << "Enter number of " << appname << " : ";
			do {
				cin >> appnum;
				if (cin.fail() || appnum < 0)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Please enter correct input\n";
				}
				else
				{
					break;
				}
			} while (true);
			sum += appnum * appwatt;
			out << appname << " (" << appwatt << ") : " << appnum << endl;
		}
		else
			break;
	} while (true);
	//20% add loss due to 80% efficiency
	float addloss = sum * 0.2;
	sum += addloss;
	//calculating number of plates
	float numplates = sum / 575;
	int numplates2 = sum / 575;
	numplates = (numplates - numplates2 == 0) ? (numplates2) : (numplates2 + 1);
	//calculating number of stands
	float stands = numplates / 3;
	int stands2 = numplates / 3;
	stands = (stands - stands2 == 0) ? (stands2) : (stands2 + 1);
	//for KW system:
	float kw_sum = sum / 1000;
	//extra capacity for inverter
	float inverter = kw_sum + 2;
	int inverter2 = kw_sum + 2;
	inverter = (inverter - inverter2 == 0) ? (inverter2) : (inverter2 + 1);
	inverter *= 35000;
	//extra capacity for batteries
	float batteries = kw_sum + 2;
	int batteries2 = kw_sum + 2;
	batteries = (batteries - batteries2 == 0) ? (batteries2) : (batteries2 + 1);
	//cost of installation
	float install = (numplates * 17250) + inverter + (batteries * 35500) + (30 + 300) + 10000 + (stands * 9500);
	install *= 0.03;

	cout << "\n\nYour total required watts are: " << sum << endl;
	cout << "Your total required kilo watts are: " << kw_sum << endl;
	space = (width - 9) / 2; //9 is the length of heading
	cout << endl << setw(space + 9) << "QUOTATION" << setw(width - space - 9) << "" << endl;
	out << "\n\n" << setw(space + 9) << "QUOTATION" << setw(width - space - 9) << "" << endl;
	//table of expenses
	cout << "\n" << left << setw(7) << "No." << setw(27) << "Item" << setw(24) << "Quantity" << setw(24) << "Rate (PKR)" << setw(24) << "Cost (PKR)" << endl;
	out << "\n" << left << setw(7) << "No." << setw(27) << "Item" << setw(24) << "Quantity" << setw(24) << "Rate (PKR)" << setw(24) << "Cost (PKR)" << endl;
	cout << string(100, '-') << endl;
	out << "\n" << string(100, '-') << endl;
	cout << left << setw(7) << "1." << setw(27) << "Panels" << setw(24) << numplates << setw(24) << "17250" << setw(24) << numplates * 17250 << endl;
	out << "\n" << left << setw(7) << "1." << setw(27) << "Panels" << setw(24) << numplates << setw(24) << "17250" << setw(24) << numplates * 17250 << endl;
	cout << left << setw(7) << "2." << setw(27) << "Inverter" << setw(24) << "1" << setw(24) << "35000/kW" << setw(24) << inverter << endl;
	out << "\n" << left << setw(7) << "2." << setw(27) << "Inverter" << setw(24) << "1" << setw(24) << "35000/kW" << setw(24) << inverter << endl;
	cout << left << setw(7) << "3." << setw(27) << "Batteries" << setw(24) << batteries << setw(24) << "35500" << setw(24) << 35500 * batteries << endl;
	cout << left << setw(7) << " " << setw(27) << "(5 hours backup)" << endl;
	out << "\n" << left << setw(7) << "3." << setw(27) << "Batteries" << setw(24) << batteries << setw(24) << "35500" << setw(24) << 35500 * batteries << endl;
	out << left << setw(7) << " " << setw(27) << "(5 hours backup)" << endl;
	cout << left << setw(7) << "4." << setw(27) << "DC Wires" << setw(24) << "30 yards" << setw(24) << "300 per yard" << setw(24) << 30 * 300 << endl;
	out << "\n" << left << setw(7) << "4." << setw(27) << "DC Wires" << setw(24) << "30 yards" << setw(24) << "300 per yard" << setw(24) << 30 * 300 << endl;
	cout << left << setw(7) << "5." << setw(27) << "Protection DB - Breakers" << setw(24) << "1" << setw(24) << "10000" << setw(24) << "10000" << endl;
	out << "\n" << left << setw(7) << "5." << setw(27) << "Protection DB - Breakers" << setw(24) << "1" << setw(24) << "10000" << setw(24) << "10000" << endl;
	cout << left << setw(7) << "6." << setw(27) << "Stands (L-3)" << setw(24) << stands << setw(24) << "9500" << setw(24) << stands * 9500 << endl;
	out << "\n" << left << setw(7) << "6." << setw(27) << "Stands (L-3)" << setw(24) << stands << setw(24) << "9500" << setw(24) << stands * 9500 << endl;
	cout << left << setw(7) << "7." << setw(27) << "Installation" << setw(24) << " " << setw(24) << " " << setw(24) << install << endl;
	out << "\n" << left << setw(7) << "7." << setw(27) << "Installation" << setw(24) << "-" << setw(24) << "-" << setw(24) << install << endl;
	cout << left << setw(7) << "8." << setw(27) << "Miscellaneous Expenses" << setw(24) << "-" << setw(24) << "-" << setw(24) << "15000" << endl;
	out << "\n" << left << setw(7) << "8." << setw(27) << "Miscellaneous Expenses" << setw(24) << "-" << setw(24) << "-" << setw(24) << "15000" << endl;
	cout << string(100, '-') << endl;
	out << "\n" << string(100, '-') << endl;

	int t_cost = (numplates * 17250) + inverter + (35500 * batteries) + (30 + 300) + 10000 + (stands * 9500) + install + 15000;
	cout << "\nTotal cost: " << t_cost << " PKR" << endl;
	out << "\nTotal cost: " << t_cost << " PKR" << endl;
	cout << "Required area: " << (numplates / 3) * 12 << "ft by " << (numplates / 3) * 6 << "ft" << endl;
	out << "Required area: " << (numplates / 3) * 12 << "ft by " << (numplates / 3) * 6 << "ft" << endl;

	int reduction_20 = sum * 0.2;
	float totalsolarsum = 0;
	for (int i = 1; i < 5; i++)
	{
		totalsolarsum += (sum - (reduction_20 * i));
	}
	totalsolarsum *= 2;
	float totalsolarwin = totalsolarsum;
	totalsolarsum += (2 * 45);
	totalsolarsum += (sum * 3);
	totalsolarwin += sum;
	float totalrequired = 13 * sum;

	cout << right;
	space = (width - 7) / 2; //7 is the length of heading
	cout << endl << setw(space + 7) << "SAVINGS" << setw(width - space - 7) << "" << endl;
	out << right;
	out << "\n\n" << setw(space + 7) << "SAVINGS" << setw(width - space - 7) << "" << endl;
	cout << "\n" << string(150, '-') << endl;
	out << "\n" << string(150, '-') << endl;
	cout << left << setw(12) << "SUMMER" << setw(8) << "6 am" << setw(8) << "7 am" << setw(8) << "8 am" << setw(8) << "9 am" << setw(8) << "10 am" << setw(8) << "11 am" << setw(8) << "12 am" << setw(8) << "1 pm" << setw(8) << "2 pm" << setw(8) << "3 pm" << setw(8) << "4 pm" << setw(8) << "5 pm" << setw(10) << "6 pm" << setw(15) << "TOTAL" << endl;
	out << "\n" << left << setw(12) << "SUMMER" << setw(8) << "6 am" << setw(8) << "7 am" << setw(8) << "8 am" << setw(8) << "9 am" << setw(8) << "10 am" << setw(8) << "11 am" << setw(8) << "12 am" << setw(8) << "1 pm" << setw(8) << "2 pm" << setw(8) << "3 pm" << setw(8) << "4 pm" << setw(8) << "5 pm" << setw(10) << "6 pm" << setw(15) << "TOTAL" << endl;
	cout << string(150, '-') << endl;
	out << "\n" << string(150, '-') << endl;
	cout << left << setw(12) << "Solar" << setw(8) << "45" << setw(8) << sum - (reduction_20 * 4) << setw(8) << sum - (reduction_20 * 3) << setw(8) << sum - (reduction_20 * 2) << setw(8) << sum - (reduction_20) << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum - (reduction_20) << setw(8) << sum - (reduction_20 * 2) << setw(8) << sum - (reduction_20 * 3) << setw(8) << sum - (reduction_20 * 4) << setw(10) << "45" << setw(15) << totalsolarsum << setw(8) << totalsolarsum / totalrequired * 100 << setw(2) << "%" << setw(8) << "saving" << endl;
	out << "\n" << left << setw(12) << "Solar" << setw(8) << "45" << setw(8) << sum - (reduction_20 * 4) << setw(8) << sum - (reduction_20 * 3) << setw(8) << sum - (reduction_20 * 2) << setw(8) << sum - (reduction_20) << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum - (reduction_20) << setw(8) << sum - (reduction_20 * 2) << setw(8) << sum - (reduction_20 * 3) << setw(8) << sum - (reduction_20 * 4) << setw(10) << "45" << setw(15) << totalsolarsum << setw(8) << totalsolarsum / totalrequired * 100 << setw(2) << "%" << setw(8) << "saving" << endl;
	cout << left << setw(12) << "Required" << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(10) << sum << setw(15) << totalrequired << endl;
	out << "\n" << left << setw(12) << "Required" << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(10) << sum << setw(15) << totalrequired << endl;
	cout << left << setw(12) << "Wapda" << setw(8) << sum - 45 << setw(8) << sum - (sum - (reduction_20 * 4)) << setw(8) << sum - (sum - (reduction_20 * 3)) << setw(8) << sum - (sum - (reduction_20 * 2)) << setw(8) << sum - (sum - reduction_20) << setw(8) << sum - sum << setw(8) << sum - sum << setw(8) << sum - sum << setw(8) << sum - (sum - reduction_20) << setw(8) << sum - (sum - (reduction_20 * 2)) << setw(8) << sum - (sum - (reduction_20 * 3)) << setw(8) << sum - (sum - (reduction_20 * 4)) << setw(10) << sum - 45 << setw(15) << totalrequired - totalsolarsum << setw(8) << (totalrequired - totalsolarsum) / totalrequired * 100 << setw(2) << "%" << setw(8) << "wapda" << endl;
	out << "\n" << left << setw(12) << "Wapda" << setw(8) << sum - 45 << setw(8) << sum - (sum - (reduction_20 * 4)) << setw(8) << sum - (sum - (reduction_20 * 3)) << setw(8) << sum - (sum - (reduction_20 * 2)) << setw(8) << sum - (sum - reduction_20) << setw(8) << sum - sum << setw(8) << sum - sum << setw(8) << sum - sum << setw(8) << sum - (sum - reduction_20) << setw(8) << sum - (sum - (reduction_20 * 2)) << setw(8) << sum - (sum - (reduction_20 * 3)) << setw(8) << sum - (sum - (reduction_20 * 4)) << setw(10) << sum - 45 << setw(15) << totalrequired - totalsolarsum << setw(8) << (totalrequired - totalsolarsum) / totalrequired * 100 << setw(2) << "%" << setw(8) << "wapda" << endl;
	cout << string(150, '-') << endl;
	out << "\n" << string(150, '-') << endl;

	cout << "\n\n" << string(150, '-') << endl;
	out << "\n" << string(150, '-') << endl;
	cout << left << setw(12) << "WINTER" << setw(8) << "6 am" << setw(8) << "7 am" << setw(8) << "8 am" << setw(8) << "9 am" << setw(8) << "10 am" << setw(8) << "11 am" << setw(8) << "12 am" << setw(8) << "1 pm" << setw(8) << "2 pm" << setw(8) << "3 pm" << setw(8) << "4 pm" << setw(8) << "5 pm" << setw(10) << "6 pm" << setw(15) << "TOTAL" << endl;
	out << "\n" << left << setw(12) << "WINTER" << setw(8) << "6 am" << setw(8) << "7 am" << setw(8) << "8 am" << setw(8) << "9 am" << setw(8) << "10 am" << setw(8) << "11 am" << setw(8) << "12 am" << setw(8) << "1 pm" << setw(8) << "2 pm" << setw(8) << "3 pm" << setw(8) << "4 pm" << setw(8) << "5 pm" << setw(10) << "6 pm" << setw(15) << "TOTAL" << endl;
	cout << string(150, '-') << endl;
	out << "\n" << string(150, '-') << endl;
	cout << left << setw(12) << "Solar" << setw(8) << "0" << setw(8) << "0" << setw(8) << sum - (reduction_20 * 4) << setw(8) << sum - (reduction_20 * 3) << setw(8) << sum - (reduction_20 * 2) << setw(8) << sum - (reduction_20) << setw(8) << sum << setw(8) << sum - (reduction_20) << setw(8) << sum - (reduction_20 * 2) << setw(8) << sum - (reduction_20 * 3) << setw(8) << sum - (reduction_20 * 4) << setw(8) << "0" << setw(10) << "0" << setw(15) << totalsolarwin << setw(8) << totalsolarwin / totalrequired * 100 << setw(2) << "%" << setw(8) << "saving" << endl;
	out << "\n" << left << setw(12) << "Solar" << setw(8) << "0" << setw(8) << "0" << setw(8) << sum - (reduction_20 * 4) << setw(8) << sum - (reduction_20 * 3) << setw(8) << sum - (reduction_20 * 2) << setw(8) << sum - (reduction_20) << setw(8) << sum << setw(8) << sum - (reduction_20) << setw(8) << sum - (reduction_20 * 2) << setw(8) << sum - (reduction_20 * 3) << setw(8) << sum - (reduction_20 * 4) << setw(8) << "0" << setw(10) << "0" << setw(15) << totalsolarwin << setw(8) << totalsolarwin / totalrequired * 100 << setw(2) << "%" << setw(8) << "saving" << endl;
	cout << left << setw(12) << "Required" << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(10) << sum << setw(15) << totalrequired << endl;
	out << "\n" << left << setw(12) << "Required" << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(8) << sum << setw(10) << sum << setw(15) << totalrequired << endl;
	cout << left << setw(12) << "Wapda" << setw(8) << sum << setw(8) << sum << setw(8) << sum - (sum - (reduction_20 * 4)) << setw(8) << sum - (sum - (reduction_20 * 3)) << setw(8) << sum - (sum - reduction_20 * 2) << setw(8) << sum - (sum - reduction_20) << setw(8) << sum - sum << setw(8) << sum - (sum - reduction_20) << setw(8) << sum - (sum - reduction_20 * 2) << setw(8) << sum - (sum - (reduction_20 * 3)) << setw(8) << sum - (sum - (reduction_20 * 4)) << setw(8) << sum << setw(10) << sum << setw(15) << totalrequired - totalsolarwin << setw(8) << (totalrequired - totalsolarwin) / totalrequired * 100 << setw(2) << "%" << setw(8) << "wapda" << endl;
	out << "\n" << left << setw(12) << "Wapda" << setw(8) << sum << setw(8) << sum << setw(8) << sum - (sum - (reduction_20 * 4)) << setw(8) << sum - (sum - (reduction_20 * 3)) << setw(8) << sum - (sum - reduction_20 * 2) << setw(8) << sum - (sum - reduction_20) << setw(8) << sum - sum << setw(8) << sum - (sum - reduction_20) << setw(8) << sum - (sum - reduction_20 * 2) << setw(8) << sum - (sum - (reduction_20 * 3)) << setw(8) << sum - (sum - (reduction_20 * 4)) << setw(8) << sum << setw(10) << sum << setw(15) << totalrequired - totalsolarwin << setw(8) << (totalrequired - totalsolarwin) / totalrequired * 100 << setw(2) << "%" << setw(8) << "wapda" << endl;
	cout << string(150, '-') << endl;
	out << "\n" << string(150, '-') << endl;

	//units of wapda considering total watt required
	cout << "\nUnits (1000 x 1hr = 1 unit): " << sum / 1000 << " kWh";
	out << "\nUnits (1000 x 1hr = 1 unit): " << sum / 1000 << " kWh";
	cout << "\nDaily unit (6am - 6pm):" << sum / 1000 * 13 << " kWh";
	out << "\nDaily unit (6am - 6pm): " << sum / 1000 * 13 << " kWh";
	cout << "\nMonthly unit (30 days): " << sum / 1000 * 13 * 30 << " kWh";
	out << "\nMonthly unit (30 days): " << sum / 1000 * 13 * 30 << " kWh";
	cout << "\nMonthly cost at 60Rs per unit: " << sum / 1000 * 13 * 30 * 60 << " PKR";
	out << "\nMonthly cost at 60Rs per unit: " << sum / 1000 * 13 * 30 * 60 << " PKR";
	cout << "\nMinimum saving at " << totalsolarwin / totalrequired * 100 << "%: " << (sum / 1000 * 13 * 30) * (totalsolarwin / totalrequired) << " kWh & " << (sum / 1000 * 13 * 30) * (totalsolarwin / totalrequired) * 60 << " PKR";
	cout << "\nSolar cost: " << t_cost << " PKR";
	out << "\nMinimum saving at " << totalsolarwin / totalrequired * 100 << "%: " << (sum / 1000 * 13 * 30) * (totalsolarwin / totalrequired) << " kWh & " << (sum / 1000 * 13 * 30) * (totalsolarwin / totalrequired) * 60 << " PKR";
	out << "\nSolar cost: " << t_cost << " PKR";
	cout << "\nMonths to recover cost of solar: " << t_cost / ((sum / 1000 * 13 * 30) * (totalsolarwin / totalrequired) * 60) << endl;
	out << "\nMonths to recover cost of solar: " << t_cost / ((sum / 1000 * 13 * 30) * (totalsolarwin / totalrequired) * 60) << endl;

	space = (width - 12) / 2; //12 is the length of heading
	cout << right;
	cout << "\n\n" << setw(space + 12) << "INSTRUCTIONS" << setw(width - space - 12) << "" << endl;
	out << right;
	out << "\n\n" << setw(space + 12) << "INSTRUCTIONS" << setw(width - space - 12) << "" << endl;
	cout << "\nMake sure to follow these instructions to get maximum output: " << endl;
	out << "\nMake sure to follow these instructions to get maximum output: " << endl;
	cout << "\n1. Keep solar panels out of shade as energy production becomes inefficient when they are kept from absorbing any sunlight." << endl;
	out << "\n1. Keep solar panels out of shade as energy production becomes inefficient when they are kept from absorbing any sunlight." << endl;
	cout << "\n2. Each L3 stand can only have 3 panels" << endl;
	out << "\n2. Each L3 stand can only have 3 panels" << endl;
	cout << "\n3. Do periodic light cleaning to make sure dirt, leaves, and other debris aren't obstructing the sun's rays" << endl;
	out << "\n3. Do a periodic light cleaning to make sure dirt, leaves, and other debris aren't obstructing the sun's rays" << endl;
	cout << "\n4. Use a soft-bristled cleaning brush and a non-abrasive cleaner. Be sure to clean the panels early in the morning before they get too hot from the sun. The panels are made of tempered glass, and the extreme temperature disparity between hot water and cold panels can crack them." << endl;
	out << "\n4. Use a soft-bristled cleaning brush and a non-abrasive cleaner. Be sure to clean the panels early in the morning before they get too hot from the sun. The panels are made of tempered glass, and the extreme temperature disparity between hot water and cold panels can crack them." << endl;
	cout << "\n5. When the temperature gets over 77F (or 25C), panels lose efficiency approximately 1% per degree. However, by elevating them a few inches above the ground or roof,\nyou allow for air circulation, which can help cool them down and maintain energy production." << endl;
	out << "\n5. When the temperature gets over 77F (or 25C), panels lose efficiency approximately 1% per degree. However, by elevating them a few inches above the ground or roof, \nyou allow for air circulation, which can help cool them down and maintain energy production." << endl;
	cout << "\n6.  It is vital that you work with a professional to have them installed. Improper roof anchor installation can damage your roof tiles, or leave the panel insecurely \n attached." << endl;
	out << "\n6.  It is vital that you work with a professional to have them installed. Improper roof anchor installation can damage your roof tiles, or leave the panel insecurely \n attached." << endl;
	cout << "\n7. The panels have to be wired to an inverter. The panels themselves are pre wired but should still be wired up by an MCS-certified installer; problems include \n dangerous earthing or exposed cabling." << endl;
	out << "\n7. The panels have to be wired to an inverter. The panels themselves are pre wired but should still be wired up by an MCS-certified installer; problems include \n dangerous earthing or exposed cabling." << endl;
	cout << "\n8. If the support legs are installed too low on the panel, it may be at an angle that causes wind load stress." << endl;
	out << "\n8. If the support legs are installed too low on the panel, it may be at an angle that causes wind load stress." << endl;
	cout << "\n9. Plan for 10-20 square meters of open roof space per 1 kW of solar capacity. A 5 kW system needs about 100 square meters." << endl;
	out << "\n9. Plan for 10-20 square meters of open roof space per 1 kW of solar capacity. A 5 kW system needs about 100 square meters." << endl;
	cout << "\n10.It is a good idea to have your panels cleaned every 1-2 weeks, to get maximum output." << endl;
	out << "\n10.It is a good idea to have your panels cleaned every 1-2 weeks, to get maximum output." << endl;


	space = (width - 30) / 2; //30 is the length of heading
	cout << right;
	cout << "\n\n" << setw(space + 30) << "SUGGESTIONS & RECOMMENDATIONS" << setw(width - space - 30) << "" << endl;
	out << right;
	out << "\n\n" << setw(space + 30) << "SUGGESTIONS & RECOMMENDATIONS" << setw(width - space - 30) << "" << endl;
	cout << "\n1. Solar panels require very little maintenance, especially if they are on a tilt, as rain can wash away any debris." << endl;
	out << "\n1. Solar panels require very little maintenance, especially if they are on a tilt, as rain can wash away any debris." << endl;
	cout << "\n2. By integrating a solar panel monitoring system into your setup, you can track how much energy your panels produce on any given day and how much they produce over \n time." << endl;
	out << "\n2. By integrating a solar panel monitoring system into your setup, you can track how much energy your panels produce on any given day and how much they produce over \n time." << endl;
	cout << "\n3. You might want to avoid having solar panels installed in the shadow of a tree or nearby roosting birds. Not only would the shadow reduce the effectiveness of the \n panels, but it may encourage birds to fly over and land in the trees, which you don't want." << endl;
	out << "\n3. You might want to avoid having solar panels installed in the shadow of a tree or nearby roosting birds. Not only would the shadow reduce the effectiveness of the \n panels, but it may encourage birds to fly over and land in the trees, which you don't want." << endl;
	cout << "\n4. Solar panels typically last 25+ years. Installing them on an aging roof that needs replacement soon won’t maximize the investment. Newer roofs are ideal." << endl;
	out << "\n4. Solar panels typically last 25+ years. Installing them on an aging roof that needs replacement soon won’t maximize the investment. Newer roofs are ideal." << endl;
	cout << "\n5. Pitched, sloped roofs are best suited for solar panel mounting. Flat roofs can work but require additional racking equipment." << endl;
	out << "\n5. Pitched, sloped roofs are best suited for solar panel mounting. Flat roofs can work but require additional racking equipment." << endl;
	cout << "\n6. Check roof orientation. Ideal orientations are for Northern Hemisphere: South-facing roof and for Southern Hemisphere: North-facing roof." << endl;
	out << "\n6.Check roof orientation. Ideal orientations are for Northern Hemisphere: South-facing roof and for Southern Hemisphere: North-facing roof." << endl;
	cout << "\n7. Some external sources you can refer to are: \n\thttps://tahirenergylinks.com/solar-power-at-home/#:~:text=Keeping%20Your%20System%20Performing%20at,panel%20shading%20and%20soiling%20losses\n\thttps://www.itsmysun.com/residential-solar-11-things-keep-mind-installing-residential-solar-system/\n\thttps://www.itsmysun.com/residential-solar-11-things-keep-mind-installing-residential-solar-system/" << endl;
	out << "\n7. Some external sources you can refer to are: \n\thttps://tahirenergylinks.com/solar-power-at-home/#:~:text=Keeping%20Your%20System%20Performing%20at,panel%20shading%20and%20soiling%20losses\n\thttps://www.itsmysun.com/residential-solar-11-things-keep-mind-installing-residential-solar-system/\n\thttps://www.itsmysun.com/residential-solar-11-things-keep-mind-installing-residential-solar-system/" << endl;
	cout << "\n8. Panel(LONGI 5) is the brand we used for out calculations. Some other brands you may consider are Jinko N-type and Canadian Bifacial." << endl;
	out << "\n8. Panel(LONGI 5) is the brand we used for our calculations. Some other brands you may consider are Jinko N-type and Canadian Bifacial." << endl;
	cout << "\n9. We have used Inverex's inverter for our calculations. You may also consider FoxEss, SolarMax or MaxPower for inverter" << endl;
	out << "\n9. We have used Inverex's inverter for our calculations. You may also consider FoxEss, SolarMax or MaxPower for inverter" << endl;
	cout << "\n11. We have used Exide's N-250 31 plates lead acid batteries, considering 5 hours backup. You may also use Atlas batteries, and may reduce backup to reduce \n cost" << endl;
	out << "\n11. We have used Exide's N-250 31 plates lead acid batteries, considering 5 hours backup. You may also use Atlas batteries, and may reduce backup to reduce \n cost" << endl;
	cout << "\n12. Many companies in Pakistan are dedicated to advancing solar energy as a sustainable source. The following are the best solar companies: \n\tAlpha Solar \n\tSympl Energy \n\tPremier Energy \n\tPantera \n\tReon \n\tSky Electric" << endl;
	out << "\n12. Many companies in Pakistan are dedicated to advancing solar energy as a sustainable source. The following are the best solar companies: \n\tAlpha Solar \n\tSympl Energy \n\tPremier Energy \n\tPantera \n\tReon \n\tSky Electric" << endl;
	cout << "\n13. For latest market rates, visit: \n\thttps://solarpricepakistan.com/\n\thttps://priceware.pk/solar-panel-price-in-pakistan/" << endl;
	out << "\n13. For latest market rates, visit: \n\thttps://solarpricepakistan.com/\n\thttps://priceware.pk/solar-panel-price-in-pakistan/" << endl;
	out.close();

	update(cnicInput);

	ifstream in(cnicInput + ".txt");
	ofstream backup(cnicInput + "_b.txt");
	string read;
	while (!in.eof())
	{
		getline(in, read);
		backup << read << endl;
	}
	in.close();
	backup.close();

}

void view(string cnicInput)
{
	int space = (width - 12) / 2; //12 is the length of heading
	cout << right;
	cout << setw(space + 12) << "YOUR PROFILE" << setw(width - space - 12) << "" << endl;
	ifstream in(cnicInput + ".txt");
	if (!in)
	{
		char ans;
		cout << "Your profile does not exist. Do you want to create your profile? (Y/N) : ";
		do {
			cin >> ans;
			if (ans != 'N' && ans != 'Y')
				cout << "Please enter only Y or N:";
		} while (ans != 'N' && ans != 'Y');
		if (ans == 'N')
			return;
		else
			create(cnicInput);
	}
	else
	{
		string read;
		while (!in.eof())
		{
			getline(in, read);
			cout << read << endl;
		}
	}
}
void update(string cnicInput)
{
	ifstream in(cnicInput + ".txt");
	if (!in)
	{
		char ans;
		cout << "Your profile does not exist. Do you want to create your profile? (Y/N) : ";
		do {
			cin >> ans;
			if (ans != 'N' && ans != 'Y')
				cout << "Please enter only Y or N:";
		} while (ans != 'N' && ans != 'Y');
		if (ans == 'N')
			return;
		else
		{
			create(cnicInput);
		}

	}
	else {
		char ans2;
		cout << "\n\nDo you want to update your profile?(Y/N): ";
		do {
			cin >> ans2;
			if (ans2 != 'N' && ans2 != 'Y')
				cout << "Please enter only Y or N:";
		} while (ans2 != 'N' && ans2 != 'Y');
		if (ans2 == 'N')
			return;
		else
		{
			create(cnicInput);
		}

	}

}
void deleteProfile(string cnicInput)
{
	ifstream in(cnicInput + ".txt");
	if (!in)
	{
		cout << "File does not exist." << endl;
		return;
	}
	in.close();
	cout << "Are you sure you want to delete your file? ";
	char ans;
	do {
		cin >> ans;
		if (ans != 'N' && ans != 'Y')
			cout << "Please enter only Y or N:";
	} while (ans != 'N' && ans != 'Y');
	if (ans == 'Y')
	{
		string deletep = cnicInput + ".txt";
		if (remove(deletep.c_str()) == 0)
		{
			cout << "File deleted successfully!" << endl;
		}
		else
		{
			cout << "Error in deleting file " << endl;
		}
	}
	else
		return;

}