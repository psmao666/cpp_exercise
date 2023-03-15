/*
This is to design a shopping cart checkout system.

Functional requirement:
As a user, I should be ...
1. Able to add items, and corresponding quantities.
2. Able to remove items, and partial quantities.
3. Able to calculate the total price, and taxes (GST 10% let's say)
4. Able to have some sort of promotion (discount) on specific items.
As an admin, I should be ...
1. Able to update the price of a specific item
2. Able to modify the promotion of a specific item

Non-Functional Requirment:
1. Normally one customer (one request) at a time, so we don't need to consider scalability
2. Availability, we want it to be available to all customers
3. Consistency, we want it to demonstrate the same content for every user
4. The total number of items shouldn't be too big, so we don't have to consider sharding

Tables:
[Item table]
ItemID: int
ItemName: String
ItemPrice: Double
ItemImage: Blob
----
[Promotion table]
PromotionID: int
ItemID: int
Discount: double
----
[Shopping Cart]
ItemInfo: List<Item>
+updatePrice(ItemID: int, newPrice: double): void
+modifyPromotion(PromotionID: int, newPromotion: double): void
*/
#include <bits/stdc++.h>

class Item {
    std::string itemName;
    double itemPrice;
    //Image itemImage;

public:    
    Item() {}
    Item(std::string name, double price): itemName(name), itemPrice(price){}
    friend bool operator< (const Item& a, const Item& b) {
        return a.itemName < b.itemName;
    }
    std::string getName() const {
        return this->itemName;
    }
    void updatePrice(double newPrice) {
        this->itemPrice = newPrice;
    }
    double getPrice() const {
        return this->itemPrice;
    }
};

class Promotion {
    std::string itemName;
    double discount;

public:
    Promotion() {discount = 1.0;}
    Promotion(std::string iid, double disc): itemName(iid), discount(disc){}
    friend bool operator< (const Promotion& a, const Promotion& b) {
        return a.itemName < b.itemName;
    }
    double getPromo() const {
        return this->discount;
    }
    std::string getName() const {
        return this->itemName;
    }
    void updatePromo(double newDiscount) {
        try{
            if (newDiscount > 1 || newDiscount < 0) {
                throw std::logic_error("invalid discount");
            }
            this->discount = newDiscount;
        }catch(std::exception& e){
            std::cout << "Error: " << e.what() << std::endl;
        }
    } 
};

class ShoppingCart {
    std::set<Item> items;
    std::unordered_map<std::string, double> itemQuantity;
public:
    ShoppingCart() {}
    
    void updateQuantity(std::string itemName, double price, double newQuantity) {
        std::set<Item>::iterator it = items.lower_bound(Item(itemName, 0));
        if (it != items.end() && (*it).getName() == itemName) {
            items.erase(Item(itemName, 0));
        }
        if (newQuantity == 0) {
            this->itemQuantity.erase(itemName);
            return;
        }
        items.insert(Item(itemName, price));
        this->itemQuantity[itemName] = newQuantity;
    }
    void printItems(std::set<Promotion>& promo) {
        std::cout << "-------------------------------\n";
        double totalPrice = 0;
        for (auto p: items) {
            std::string name = p.getName();
            double price = p.getPrice();
            double quantity = itemQuantity[name];
            std::set<Promotion>::iterator it = promo.lower_bound(Promotion(name, 0));
            if (it == promo.end() || (*it).getName() != name) {
                std::cout << name << " Price: " << price << " Quantity: " << quantity << " Total Price:  "<< (price * quantity) << std::endl;
                totalPrice += price * quantity;
            }
            else {    
                double disc = (*it).getPromo();
                std::cout << name << " Price after discount: " << price * disc << " Quantity: " << quantity << " Total Price after discount:  "<< (price * quantity * disc)  << std::endl;
                totalPrice += price * quantity * disc;
            }
        }
        std::cout << "\n";
        std::cout << "Total price: " << totalPrice*1.1 << " Total tax: " << totalPrice*0.1 << std::endl;
        std::cout << "-------------------------------\n";
    }
};

class checkoutController{
    std::set<Item> itemInfo;
    std::set<Promotion> promoInfo;
    ShoppingCart cart;

public:
    checkoutController() {}

    void updatePrice(std::string itemName, double newPrice) {
        std::set<Item>::iterator it = itemInfo.lower_bound(Item(itemName, 0));
        if (it != itemInfo.end() && (*it).getName() == itemName) itemInfo.erase(it);
        itemInfo.insert(Item(itemName, newPrice));
    }
    void modifyPromo(std::string itemName, double newDisc) {
        std::set<Promotion>::iterator it = promoInfo.lower_bound(Promotion(itemName, 0));
        if (it != promoInfo.end() && (*it).getName() == itemName) promoInfo.erase(it);
        promoInfo.insert(Promotion(itemName, newDisc));
    }

    void addItem(std::string itemName, double quantity) {
        std::set<Item>::iterator it = itemInfo.lower_bound(Item(itemName, 0));
        cart.updateQuantity(itemName, (*it).getPrice(), quantity);    
    }
    void removeItem(std::string itemName) {
        cart.updateQuantity(itemName, 0, 0);
    }
    void checkout(){
        cart.printItems(promoInfo);
    }
};

int main() {
    checkoutController sys;
    sys.updatePrice("apple", 1);
    sys.updatePrice("banana", 1.5);
    sys.addItem("apple", 1.5);
    sys.addItem("banana", 2);
    sys.checkout();
    sys.removeItem("banana");
    sys.checkout();
    return 0;
}