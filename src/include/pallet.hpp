

class Pallet : public IContainer {

    std::string item_name;
    int         item_capacity;
    int         item_count;

public:


    /**
     * Note for educational purpose on passing std::string: Accepts lvalues (variables) and rvalues (temporary values like "Banana"),
     * **Lvalues**: Reference passed, then copied into the attribute because the attribute is not, and should not, be a reference
     * **Rvalues**: reference to temporary memory passed, value stored in attribute
     * @param _item_count
     * @param _item_name
     * @param _item_capacity
     */
    Pallet(const std::string&  _item_name, int _item_capacity, int _item_count);


    friend bool operator<(const Pallet& lhs, const Pallet& rhs) {
        return lhs.item_count < rhs.item_count;
    }

    friend std::ostream & operator<<(std::ostream &os, const Pallet &obj);

    bool isEmpty() override;
    bool isFull() override;
};
