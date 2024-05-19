#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Price {
    string productName;
    string shopName;
    double price;
    Price* next;
};

void addPrice(Price*& head, const string& productName, const string& shopName, double price) {
    Price* newPrice = new Price;
    newPrice->productName = productName;
    newPrice->shopName = shopName;
    newPrice->price = price;
    newPrice->next = nullptr;

    if (head == nullptr) {
        head = newPrice;
    }
    else {
        Price* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newPrice;
    }
    cout << "Product added successfully.\n";
}

void displayPrices(Price* head) {
    if (head == nullptr) {
        cout << "No products available.\n";
    }
    else {
        Price* current = head;
        while (current != nullptr) {
            cout << "Product: " << current->productName << ", Shop: " << current->shopName << ", Price: " << current->price << " UAH\n";
            current = current->next;
        }
    }
}

void sortPricesByShopName(Price*& head) {
    if (head == nullptr || head->next == nullptr) {
        return; 
    }

    Price* current = head;
    Price* index = nullptr;
    string tempProductName, tempShopName;
    double tempPrice;

    while (current != nullptr) {
        index = current->next;

        while (index != nullptr) {
            if (current->shopName > index->shopName) {
                tempProductName = current->productName;
                tempShopName = current->shopName;
                tempPrice = current->price;

                current->productName = index->productName;
                current->shopName = index->shopName;
                current->price = index->price;

                index->productName = tempProductName;
                index->shopName = tempShopName;
                index->price = tempPrice;
            }
            index = index->next;
        }
        current = current->next;
    }
}

void deletePriceByProductName(Price*& head, const string& productName) {
    if (head == nullptr) {
        cout << "No products available.\n";
        return;
    }

    Price* current = head;
    Price* previous = nullptr;

    while (current != nullptr) {
        if (current->productName == productName) {
            if (previous == nullptr) {
                head = current->next;
            }
            else {
                previous->next = current->next;
            }
            delete current;
            cout << "Product " << productName << " deleted successfully.\n";
            return;
        }
        previous = current;
        current = current->next;
    }

    cout << "Product " << productName << " not found.\n";
}

void deletePriceList(Price*& head) {
    while (head != nullptr) {
        Price* temp = head;
        head = head->next;
        delete temp;
    }
}

void saveToFile(Price* head) {
    string filename;
    cout << "Enter filename to save: ";
    cin >> filename;

    ofstream file(filename);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    Price* current = head;
    while (current != nullptr) {
        file << current->productName << " " << current->shopName << " " << current->price << "\n";
        current = current->next;
    }

    file.close();
    cout << "Data saved to " << filename << ".\n";
}

void loadFromFile(Price*& head) {
    string filename;
    cout << "Enter filename to load: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    deletePriceList(head);

    head = nullptr;
    Price* last = nullptr;
    Price temp;

    while (file >> temp.productName >> temp.shopName >> temp.price) {
        Price* newPrice = new Price{ temp.productName, temp.shopName, temp.price, nullptr };
        if (head == nullptr) {
            head = newPrice;
        }
        else {
            last->next = newPrice;
        }
        last = newPrice;
    }

    file.close();
    cout << "Data loaded from " << filename << ".\n";
}


void searchProductByName(Price* head, const string& productName) {
    bool found = false;
    Price* current = head;
    while (current != nullptr) {
        if (current->productName == productName) {
            cout << "Product: " << current->productName << ", Shop: " << current->shopName << ", Price: " << current->price << " UAH\n";
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Product with name \"" << productName << "\" not found.\n";
    }
}

int main() {
    Price* priceList = nullptr;
    int choice;

    do {
        cout << "1. Add product\n";
        cout << "2. Display all products\n";
        cout << "3. Sort products by shop name\n";
        cout << "4. Delete product by name\n";
        cout << "5. Search product by name\n";
        cout << "6. Save to file\n";
        cout << "7. Load from file\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string productName, shopName;
            double price;
            cout << "Enter product name: ";
            cin >> productName;
            cout << "Enter shop name: ";
            cin >> shopName;
            cout << "Enter price in UAH: ";
            cin >> price;
            addPrice(priceList, productName, shopName, price);
            break;
        }
        case 2:
            displayPrices(priceList);
            break;
        case 3:
            sortPricesByShopName(priceList);
            cout << "Products sorted by shop name.\n";
            break;
        case 4: {
            string productName;
            cout << "Enter the product name to delete: ";
            cin >> productName;
            deletePriceByProductName(priceList, productName);
            break;
        }
        case 5: {
            string productName;
            cout << "Enter the product name to search: ";
            cin >> productName;
            searchProductByName(priceList, productName);
            break;
        }
        case 6:
            saveToFile(priceList);
            break;
        case 7:
            loadFromFile(priceList);
            break;
        case 8:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    deletePriceList(priceList);

    return 0;
}