#include <iostream>
#include <Windows.h>
using namespace std;

class Product {
private:
	int id = 0;
	char* name;
	char* description;
	double price = 0;
	double discount = 0;
public:
	Product()
	{
		SetID(1);
		SetName("no name");
		SetDescription("no description");
		SetPrice(0);
		SetDiscount(0);
	}
	Product(const int& id, const char* name, const char* description, const double& price, const double& discount)
	{
		SetID(id);
		SetName(name);
		SetDescription(description);
		SetPrice(price);
		SetDiscount(discount);
	}
	inline int GetID() { return id; }
	inline char* GetName() { return name; }
	inline char* GetDescription() { return description; }
	inline double GetPrice() { return price; }
	inline double GetDiscount() { return discount; }

	inline void SetID(const int& id) {
		if (id > 0) {
			this->id = id;
		}
		else cout << "ID must be greater than 0" << endl;
	}
	inline void SetName(const char* name) {
		if (name != nullptr) {
			int l = strlen(name);
			this->name = new char [l + 1] {};
			strcpy_s(this->name, l + 1, name);
		}
	}
	inline void SetDescription(const char* description) {
		if (description != nullptr) {
			int l = strlen(description);
			this->description = new char [l + 1] {};
			strcpy_s(this->description, l + 1, description);
		}
	}
	inline void SetPrice(const double& price) {
		if (price >= 0) {
			this->price = price;
		}
		else cout << "Price must be greater than 0" << endl;
	}
	inline void SetDiscount(const double& discount) {
		if (discount >= 0) {
			this->discount = discount;
		}
		else cout << "Discount value must be greater than 0" << endl;
	}
	inline double GetPriceWithDiscount() {
		return price - ((discount * price) / 100);
	}
	inline void ShowProduct() {
		cout << "ID : " << id << endl;
		cout << "Name : " << name << endl;
		cout << "Description : " << description << endl;
		cout << "Price : " << price << " $ " << endl;
		cout << "Discount : " << discount << " % " << endl;
		cout << "Discounted price of the product : " << GetPriceWithDiscount() << " $ " << endl << endl;
	}
	~Product() {
		delete[]name;
		delete[]description;
	}
};
class Stock {
private:
	char* address;
	Product** products;
	unsigned int count = 0;
public:
	Stock()
	{
		SetAddress("no adress");
		SetProducts(NULL);
		SetCount(0);
	}
	Stock(const char* adress, Product** product, const int& count)
	{
		SetAddress(adress);
		SetProducts(product);
		SetCount(count);
	}
	char* GetAddress() { return address; }
	Product** GetProducts() { return products; }
	unsigned int GetCount() { return count; }
	void SetAddress(const char* address) {
		if (address != nullptr) {
			int l = strlen(address);
			this->address = new char [l + 1] {};
			strcpy_s(this->address, l + 1, address);
		}
	}
	void SetProducts(Product** products) {
		if (products != nullptr) {
			this->products = products;
		}
		else cout << "Can not find products" << endl;
	}
	void SetCount(const int& count) {
		if (count > 0) {
			this->count = count;
		}
		else cout << "The stock is empty" << endl;
	}
	void ShowStock() {
		cout << "\t\t\t= = = Product Info = = =" << endl << endl;
		for (size_t i = 0; i < count; i++)
		{
			products[i]->ShowProduct(); cout << endl;
		}
	}
	Product* GetProduct() {
		cout << "Enter id : ";
		int id = 0;
		cin >> id;
		if (id <= 0) { cout << "Id must be greater than 0" << endl; return nullptr; }
		for (size_t i = 0; i < count; i++)
		{
			if (id == products[i]->GetID()) {
				cout << "Id must be unique" << endl; return nullptr;
			}
		}
		cin.ignore();
		cin.clear();
		cout << "Enter Product name : ";
		char* name = new char[30] {};
		cin.getline(name, 30);
		cout << "Enter Product description : ";
		char* discription = new char [100] {};
		cin.getline(discription, 100);
		cout << "Enter Product price : ";
		double price = 0;
		cin >> price;
		cout << "Enter Product discount : ";
		double discount = 0;
		cin >> discount;
		cout << "Product Added Succesfully" << endl;
		return new Product(id, name, discription, price, discount);
	}
	Product* GetProductFromStock(int id) {
		for (size_t i = 0; i < count; i++)
		{
			if (id == products[i]->GetID()) return products[i];
		}
		return nullptr;
	}
	void AddProduct(const Product* product) {
		auto temp = new Product * [count + 1] {};
		for (size_t i = 0; i < count; i++)
		{
			temp[i] = products[i];
		}
		temp[count] = new Product(*product);
		products = temp;
		count++;
		temp = nullptr;
	}
	void UpdateProduct(Product* product) {
		cout << "Change id : ";
		unsigned int id = 0;
		cin >> id;
		cin.ignore();
		cin.clear();
		cout << "Change Product name : ";
		char* name = new char[30] {};
		cin.getline(name, 30);
		cout << "Change Product description : ";
		char* discription = new char [100] {};
		cin.getline(discription, 100);
		cout << "Change Product price for : ";
		double price = 0;
		cin >> price;
		cout << "Change Product discount : ";
		double discount = 0;
		cin >> discount;
		product->SetID(id);
		product->SetName(name);
		product->SetDescription(discription);
		product->SetPrice(price);
		product->SetDiscount(discount);
		delete[]name;
		delete[] discription;
	}
	void DeleteProductById(int id) {
		auto temp = new Product * [count - 1] {};
		int index = 0;
		for (size_t i = 0; i < count; i++)
		{
			if (id == products[i]->GetID()) {
				continue;
			}
			temp[index] = products[i];
			index++;
		}
		count--;
		products = temp;
		temp = nullptr;
	}
	~Stock() {
		delete[]address;
		for (size_t i = 0; i < count; i++)
		{
			delete products[i];
		}
		delete[]products;
	}
};
void ShowMenu() {
	cout << "\t\t\t= = = Welcome Store = = =" << endl << endl;
	cout << "Show Products             [1]" << endl;
	cout << "Add Product               [2]" << endl;
	cout << "Update Product Info       [3]" << endl;
	cout << "Delete Product From Stock [4]" << endl;
	cout << "Exit App                  [5]" << endl;
}



void main() {
	system("color f0");
	enum Operaitons { Show = '1', Add = '2', Update = '3', Delete = '4', Exit = '5' };
	Product** products = new Product * [3] {
		new Product(1, new char [30] {"Coca - Cola"}, new char [30] {"Soyuq Qazli Icki"}, 0.6, 0),
			new Product(2, new char [30] {"Pringles"}, new char [30] {"Qizardilmis Kartof"}, 3.7, 10),
			new Product(3, new char [30] {"Sprite"}, new char [30] {"Soyuq Qazli Icki ( Limonlu )"}, 0.6, 0),
	};
	Stock* stock = new Stock(new char [30] {"Nizami Rayonu , Baku "}, products, 3);
	while (true) {
		system("cls");
		ShowMenu();
		char select = NULL;
		cin >> select;
		system("cls");
		if (select == Exit) {
			cout << "App Closed.." << endl;
			break;
		}
		int count = 0;
		while (true)
		{

			if (select == Show) {
				stock->ShowStock(); system("pause"); break;
			}
			else if (select == Add) {

				auto product = stock->GetProduct();
				if (product != nullptr) {
					stock->AddProduct(product); system("pause");
					break;
				}
				else {
					cout << "Try again.." << endl; Sleep(1000); system("cls"); count++;
					if (count == 3) { cout << "Returning Back" << endl; system("pause"); break; }
				}
			}
			else if (select == Update) {
				stock->ShowStock();
				cout << "Enter product id for update: ";
				int id = 0;
				cin >> id;
				auto product = stock->GetProductFromStock(id);
				if (product != nullptr) {
					cout << "\nUpdating.." << endl << endl;
					stock->UpdateProduct(product); cout << "Product updated successfully.." << endl; system("pause");
					break;
				}
				else { cout << "Product not find.." << endl; system("pause"); break; }
			}
			else if (select == Delete) {
				stock->ShowStock();
				cout << "Enter product id for delete : ";
				int id = 0;
				cin >> id;
				if (stock->GetProductFromStock(id) != nullptr) {
					stock->DeleteProductById(id); cout << "Product deleted successfully.." << endl; system("pause"); break;
				}
				else { cout << "Product not find.." << endl; system("pause"); break; }
			}
			else { cout << "Operation not find ,Incorrect input.." << endl; system("pause"); break; }
		}
	}

	cout << endl << endl << endl; cin.get();
}