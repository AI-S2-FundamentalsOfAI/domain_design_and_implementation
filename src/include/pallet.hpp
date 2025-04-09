
class Pallet : public IContainer {

    std::string item_name;
    int         item_capacity;
    int         item_count;

public:


    /**
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
