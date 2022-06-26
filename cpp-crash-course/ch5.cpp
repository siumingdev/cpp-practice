#include <iostream>
#include <unordered_map>

struct AccountDatabase
{
    virtual ~AccountDatabase() = default;
    virtual double get_amount(long const&) const = 0;
    virtual void set_amount(long const&, double) = 0;
};

class InMemoryAccountDatabase : public AccountDatabase
{
public:
    InMemoryAccountDatabase() : store{std::unordered_map<long, double>()} {}

    double get_amount(long const& id) const override
    {
        return store.at(id);
    }

    void set_amount(long const& id, double amount) override
    {
        store[id] = amount;
    }

private:
    std::unordered_map<long, double> store;
};

class Logger
{
public:
    Logger(char const* name) : name{name} {}

    void log_transfer(long from, long to, double amount)
    {
        std::cout << "[" << name << "] " << from << "," << to << "," << amount << std::endl;
    }

    void log_account(long id, double amount)
    {
        std::cout << "[" << name << "] " << id << "," << amount << std::endl;
    }

private:
    std::string name;
};

class Bank
{
public:
    Bank(AccountDatabase& db, Logger& logger) : db{db} , logger{logger} {}
    
    void make_transfer(long from, long to, double amount)
    {
        db.set_amount(from, db.get_amount(from) - amount);
        db.set_amount(to, db.get_amount(to) + amount);
        logger.log_transfer(from, to, amount);
    }

    double get_amount(long const& id) const
    {
        auto amount = db.get_amount(id);
        logger.log_account(id, amount);
        return amount;
    }

    void set_amount(long const& id, double amount)
    {
        logger.log_account(id, amount);
        db.set_amount(id, amount);
    }

private:
    AccountDatabase& db;
    Logger& logger;
};

int main(void) {
    // using std::string_literals;
    InMemoryAccountDatabase db {};
    Logger logger {"bank_logger"};
    Bank bank {db, logger};

    bank.set_amount(1, 1000);
    bank.set_amount(2, 2000);
    bank.make_transfer(1, 2, 300);
    bank.get_amount(1);
    bank.get_amount(2);
}