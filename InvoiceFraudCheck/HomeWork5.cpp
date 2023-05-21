
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <memory>

//-------------------------------------------------------------------------------------------------
/**
 * @brief The class represents a date
 *
 * @var m_Year The year of the date
 * @var m_Month The month of the date
 * @var m_Day The day of the date
 */
class CDate {
public:
    //---------------------------------------------------------------------------------------------
    CDate(int y,
          int m,
          int d)
            : m_Year(y),
              m_Month(m),
              m_Day(d) {}

    //---------------------------------------------------------------------------------------------
    int compare(const CDate &x) const {
        if (m_Year != x.m_Year)
            return m_Year - x.m_Year;
        if (m_Month != x.m_Month)
            return m_Month - x.m_Month;
        return m_Day - x.m_Day;
    }

    //---------------------------------------------------------------------------------------------
    int year() const {
        return m_Year;
    }

    //---------------------------------------------------------------------------------------------
    int month() const {
        return m_Month;
    }

    //---------------------------------------------------------------------------------------------
    int day() const {
        return m_Day;
    }

    //---------------------------------------------------------------------------------------------
    friend std::ostream &operator<<(std::ostream &os,
                                    const CDate &x) {
        char oldFill = os.fill();
        return os << std::setfill('0') << std::setw(4) << x.m_Year << "-"
                  << std::setw(2) << static_cast<int> ( x.m_Month ) << "-"
                  << std::setw(2) << static_cast<int> ( x.m_Day )
                  << std::setfill(oldFill);
    }
    //---------------------------------------------------------------------------------------------
private:
    int16_t m_Year;
    int8_t m_Month;
    int8_t m_Day;
};
//---------------------------------------------------------------------------------------------
/**
 * @brief It removes leading and trailing whitespaces, converts all characters to lowercase
 * and remove repetitive whitespaces
 *
 *  @param str The string to be normalised
 *  @var newStr The normalised copy of str
 *  @return The normalised copy of str
 */
std::string normalise(const std::string &str) {
    std::string newStr;

    // Remove whitespaces at the beginning
    auto start = str.begin();
    while (start != str.end() && *start == ' ') {
        start++;
    }
    // Remove whitespaces at the end
    auto end = str.end();
    do {
        --end;
    } while (end != start && *end == ' ');
    // Convert to lowercase and remove repetitive whitespaces
    bool space = false;
    for (auto it = start; it <= end; ++it) {
        char i = *it;
        if (i == ' ') {
            if (space) {
                continue;
            } else {
                newStr += i;
                space = true;
            }
        } else {
            space = false;
            newStr += tolower(i);
        }
    }
    return newStr;
}
//---------------------------------------------------------------------------------------------
/**
 * @brief Stores data of invoice and flags indicating whether the invoice is issued and/or accepted.
 *
 * The class provides various methods to access the invoice details and
 * overloads the << operator to enable printing of invoice information.
 * It also overloads the != operator to compare two invoices for inequality based on their attributes.
 *
 * @var m_invoiceNumber is a parameter representing order of inserting of invoice. Is used for later sorting.
 */
class CInvoice {
public:
    friend class CVATRegister;

    CInvoice(const CDate &date,
             const std::string &seller,
             const std::string &buyer,
             unsigned int amount,
             double vat,
             bool issued = false,
             bool accepted = false,
             int invoiceNumber = 0) :
            m_date(date),
            m_seller(seller),
            m_buyer(buyer),
            m_amount(amount),
            m_vat(vat),
            m_issued(issued),
            m_accepted(accepted),
            m_invoiceNumber(invoiceNumber) {}

    friend std::ostream &operator<<(std::ostream &os, const CInvoice &x) {
        os << "Datum:'" << x.m_date << "' seller:'" << x.m_seller << "' buyer:'" << x.m_buyer << "' amount:'"
           << x.m_amount << "' vat:'"
           << x.m_vat << "' isd:'" << x.m_issued << "' acpt:'" << x.m_accepted << "';" << std::endl;
        return os;
    }

    bool operator!=(const CInvoice &x) const {
        if (m_date.compare(x.m_date) != 0) {
            return true;
        }
        if (m_seller != x.m_seller) {
            return true;
        }
        if (m_buyer != x.m_buyer) {
            return true;
        }
        if (m_amount != x.m_amount) {
            return true;
        }
        if (m_vat != x.m_vat) {
            return true;
        }
        return false;
    }

    CDate date() const {
        return m_date;
    }

    const std::string & buyer() const {
        return m_buyer;
    }

    const std::string & seller() const {
        return m_seller;
    }

    unsigned int amount() const {
        return m_amount;
    }

    double vat() const {
        return m_vat;
    }

    int invoiceNumber() const {
        return m_invoiceNumber;
    }

private:
    CDate m_date = CDate(0, 0, 0); //initialization of CDate. (0,0,0) is never used.
    std::string m_seller;
    std::string m_buyer;
    unsigned int m_amount;
    double m_vat;
    bool m_issued = false;
    bool m_accepted = false;
    int m_invoiceNumber = 0;
};
//---------------------------------------------------------------------------------------------
/**
 * @brief Functor for set<CInvoice, CInvoiceCmp>> in CVATRegister
 *  It compares two invoices based on their attributes.
 *  The order of attributes is: date, seller, buyer, amount, vat.
 */
class CInvoiceCmp {
public:
    bool operator()(const CInvoice &x, const CInvoice &y) const {
        if (x.date().compare(y.date()) != 0) {
            return x.date().compare(y.date()) < 0;
        }
        if (x.seller() != y.seller()) {
            return x.seller() < y.seller();
        }
        if (x.buyer() != y.buyer()) {
            return x.buyer() < y.buyer();
        }
        if (x.amount() != y.amount()) {
            return x.amount() < y.amount();
        }
        if (x.vat() != y.vat()) {
            return x.vat() < y.vat();
        }
        return false;
    }
};
//---------------------------------------------------------------------------------------------
/**
 * @brief Class for sorting invoices
 * @var m_SortKeys A vector of pairs. First = key for sorting(one of constants), second = ascending/descending order
 *
 * When sorting, official (ones that we get using registerCompany() function) names
 * are used, but comparison is not case sensitive (spaces are, though)
 */
class CSortOpt {
public:
    static const int BY_DATE = 0;
    static const int BY_BUYER = 1;
    static const int BY_SELLER = 2;
    static const int BY_AMOUNT = 3;
    static const int BY_VAT = 4;

    CSortOpt() = default;

    CSortOpt &addKey(int key, bool ascending = true) {
        m_SortKeys.emplace_back(key, ascending);
        return *this;
    }

    //Functor for sorting invoices. First it sorts by first key, then by second key etc. using for loop
    bool operator()(const CInvoice &a, const CInvoice &b) const {
        for (const auto &m_SortKey: m_SortKeys) {
            //---------------------------------------------------------
            if (m_SortKey.first == BY_DATE) {
                if (a.date().compare(b.date()) != 0) {
                    if (m_SortKey.second) {
                        return a.date().compare(b.date()) < 0;
                    } else {
                        return a.date().compare(b.date()) > 0;
                    }
                }
            }
            //---------------------------------------------------------
            if (m_SortKey.first == BY_BUYER) {
                if (a.buyer() != b.buyer()) {
                    if (m_SortKey.second) {
                        return strcasecmp(&a.buyer()[0], &b.buyer()[0]) < 0;
                    } else {
                        return strcasecmp(&a.buyer()[0], &b.buyer()[0]) > 0;
                    }
                }
            }
            //---------------------------------------------------------
            if (m_SortKey.first == BY_SELLER) {
                if (a.seller() != b.seller()) {
                    if (m_SortKey.second) {
                        return strcasecmp(&a.seller()[0], &b.seller()[0]) < 0;
                    } else {
                        return strcasecmp(&a.seller()[0], &b.seller()[0]) > 0;
                    }
                }
            }
            //---------------------------------------------------------
            if (m_SortKey.first == BY_AMOUNT) {
                if (a.amount() != b.amount()) {
                    if (m_SortKey.second) {
                        return a.amount() < b.amount();
                    } else {
                        return a.amount() > b.amount();
                    }
                }
            }
            //---------------------------------------------------------
            if (m_SortKey.first == BY_VAT) {
                if (a.vat() != b.vat()) {
                    if (m_SortKey.second) {
                        return a.vat() < b.vat();
                    } else {
                        return a.vat() > b.vat();
                    }
                }
            }
            //---------------------------------------------------------
        }
        return a.invoiceNumber() < b.invoiceNumber();   //if CInvoices are equal, sort by order of their insertion
    }

private:
    std::vector<std::pair<int, bool>> m_SortKeys;
};

//---------------------------------------------------------------------------------------------
class CCompaniesNamesNormaliser {
public:
    CInvoice m_IssuedInvoice;
    std::map<std::string, std::string> m_RegisteredCompanies;

    CCompaniesNamesNormaliser(const CInvoice &invoice, const std::map<std::string, std::string> &RegisteredCompanies) :
            m_IssuedInvoice(invoice),
            m_RegisteredCompanies(RegisteredCompanies) {};

    std::string m_NormalisedSeller = normalise(m_IssuedInvoice.seller());
    std::string m_NormalisedBuyer = normalise(m_IssuedInvoice.buyer());
    std::string m_OffBuyerName = m_RegisteredCompanies[m_NormalisedBuyer];      //official buyer name
    std::string m_OffSellerName = m_RegisteredCompanies[m_NormalisedSeller];    //official seller name
};
//---------------------------------------------------------------------------------------------
/**
 * @brief Class for registering companies and invoices
 *
 * @var m_RegisteredCompanies A map of all registered companies. Key = normalised name, value = original name
 * @var m_RegisteredCompaniesNormalised A map of all registered companies. Key = original name, value = normalised name
 * @var m_AddedIssuedAndAccepted A map of containing: Key = normalised company name, value = set of issued and accepted invoices for that company
 * @var m_InvoiceNumber A variable to store the order of insertion of invoices
 */
class CVATRegister {
public:
    CVATRegister() = default;
//---------------------------------------------------------------------------------------------
/**
 * @brief Registers a company
 * @param name Name of the company
 * @return whether the company was successfully registered
 * inserts a normalised name and an original name into maps
 */
    bool registerCompany(const std::string &name) {
        std::string normalisedName = normalise(name);
        if (m_RegisteredCompanies.find(normalisedName) != m_RegisteredCompanies.end()) //company already registered
        {
            return false;
        }
        m_RegisteredCompanies[normalisedName] = name;
        m_RegisteredCompaniesNormalised[name] = normalisedName;
        return true;
    }

//---------------------------------------------------------------------------------------------
    bool checkValidityOfSellerAndBuyer(std::string &normalisedSeller, std::string &normalisedBuyer,
                                       std::string &offSellerName, std::string &offBuyerName) const {
        if (offBuyerName.empty() || offSellerName.empty() || normalisedSeller == normalisedBuyer) {
            return false;
        } else return true;
    }
//---------------------------------------------------------------------------------------------
/**
 * @brief Inserts an invoice
 * @param InvoiceOffName invoice with official name to be inserted
 * @param normalisedName normalised name of the company to which the invoice belongs
 * @return whether the invoice was successfully inserted
 */
    bool insertInvoice(CInvoice InvoiceOffName, std::string &normalisedName) {
        auto setOfInvoices = m_AddedIssuedAndAccepted.find(normalisedName);
        //if company is not in the map, insert the company and create set of invoices for it
        if (setOfInvoices == m_AddedIssuedAndAccepted.end()) {
            m_AddedIssuedAndAccepted.insert({normalisedName, std::set<CInvoice, CInvoiceCmp>({InvoiceOffName})});
        }
            //if company is in the map
        else {
            auto it = setOfInvoices->second.find(InvoiceOffName);
            //if company is in the map and that InvoiceOffName is already in the set for that company
            if (it != setOfInvoices->second.end()) {
                if (InvoiceOffName.m_issued) { //if adding issued invoice
                    if (it->m_issued) {
                        //if company is in the map and InvoiceOffName is already in the set for that company
                        // and has already been issued, return false
                        return false;
                    } else {
                        //if invoice is already in the setOfInvoices but has not already been issued,
                        // set flags issued and accepted to true
                        InvoiceOffName.m_accepted = true;
                        m_AddedIssuedAndAccepted[normalisedName].erase(it);
                        m_AddedIssuedAndAccepted[normalisedName].insert(InvoiceOffName);
                    }
                } else if (InvoiceOffName.m_accepted) { //if adding accepted invoice
                    if (it != setOfInvoices->second.end()) {
                        if (it->m_accepted) {
                            //if company is in the map and InvoiceOffName is already in the set for that company
                            //and has already been accepted, return false
                            return false;
                        } else {
                            //if invoice is already in the setOfInvoices but has not already been accepted,
                            // set flags issued and accepted to true
                            InvoiceOffName.m_issued = true;
                            m_AddedIssuedAndAccepted[normalisedName].erase(it);
                            m_AddedIssuedAndAccepted[normalisedName].insert(InvoiceOffName);
                        }
                    }
                }
            } else {
                //if the company already has a setOfInvoices, but InvoiceOffName is not in the setOfInvoices, insert it
                m_AddedIssuedAndAccepted[normalisedName].insert(InvoiceOffName);
            }
        }
        return true;
    }

//---------------------------------------------------------------------------------------------
    bool addIssued(const CInvoice &issuedInvoice) {
        //class that normalises names and finds official names, that were given when registering companies
        CCompaniesNamesNormaliser names(issuedInvoice, m_RegisteredCompanies);

        if (!checkValidityOfSellerAndBuyer(names.m_NormalisedSeller, names.m_NormalisedBuyer,
                                           names.m_OffSellerName, names.m_OffBuyerName)) {
            return false;
        }

        //create issued invoice with official names
        CInvoice issuedInvoiceOffName(issuedInvoice.date(), names.m_OffSellerName, names.m_OffBuyerName,
                                      issuedInvoice.amount(), issuedInvoice.vat(), true, false, m_InvoiceNumber++);


        //insert invoice into map of issued and accepted invoices for each buyer and seller
        if (!insertInvoice(issuedInvoiceOffName, names.m_NormalisedSeller) ||
            !insertInvoice(issuedInvoiceOffName, names.m_NormalisedBuyer)) {
            return false;
        }

        return true;
    }

//---------------------------------------------------------------------------------------------
    bool addAccepted(const CInvoice &acceptedInvoice) {
        //class that normalises names and finds official names, that were given when registering companies
        CCompaniesNamesNormaliser names(acceptedInvoice, m_RegisteredCompanies);
        if (!checkValidityOfSellerAndBuyer(names.m_NormalisedSeller, names.m_NormalisedBuyer,
                                           names.m_OffSellerName, names.m_OffBuyerName)) {
            return false;
        }

        //create accepted invoice with official names
        CInvoice issuedInvoiceOffName(acceptedInvoice.date(), names.m_OffSellerName, names.m_OffBuyerName,
                                      acceptedInvoice.amount(), acceptedInvoice.vat(),
                                      false, true, m_InvoiceNumber++);

        //insert invoice into map of issued and accepted invoices for each buyer and seller
        if (!insertInvoice(issuedInvoiceOffName, names.m_NormalisedSeller) ||
            !insertInvoice(issuedInvoiceOffName, names.m_NormalisedBuyer)) {
            return false;
        }
        return true;
    }
//---------------------------------------------------------------------------------------------
/**
 * @brief Deletes an issued invoice
 * @param normalisedName name of the company to which the invoice we need to delete belongs
 * @param acceptedInvoice is an invoice we need to delete
 * @param offSellerName official name of the seller of the invoice we need to delete
 * @param offBuyerName official name of the buyer of the invoice we need to delete
 * @return whether the invoice was found and deleted
 */
    bool delAcceptedInvoice(const std::string &normalisedName, const CInvoice &acceptedInvoice,
                            const std::string &offSellerName, const std::string &offBuyerName) {
        auto set = m_AddedIssuedAndAccepted.find(normalisedName);
        //if company does not have a set of invoices return false
        if (set == m_AddedIssuedAndAccepted.end()) {
            return false;
        }
        //create an issued invoice, that has not been accepted, so we can insert it, if we need to make an issued invoice
        //from invoice that is issued and accepted
        CInvoice issuedInvoiceOfficialName(acceptedInvoice.date(), offSellerName, offBuyerName,
                                           acceptedInvoice.amount(), acceptedInvoice.vat(),
                                           true, false, acceptedInvoice.m_invoiceNumber);
        //if company has a set of invoices but does not have this exact one return false
        auto it = set->second.find(issuedInvoiceOfficialName);
        if (it == set->second.end()) {
            return false;
        }
        //if invoice was issued and accepted, insert invoice that is issued and not accepted
        if (it->m_issued && it->m_accepted) {
            set->second.erase(it);
            set->second.insert(issuedInvoiceOfficialName);
            return true;
        }
        //if invoice is just accepted, delete it
        if (!it->m_issued && it->m_accepted) {
            set->second.erase(it);
            return true;
        }
        return false;
    }
//---------------------------------------------------------------------------------------------
/**
 * @brief same thing as delAcceptedInvoice, but for issued invoices. Same parameters
 */
    bool delIssuedInvoice(const std::string &normalisedName, const CInvoice &issuedInvoice,
                          const std::string &offSellerName, const std::string &offBuyerName) {
        auto set = m_AddedIssuedAndAccepted.find(normalisedName);
        if (set == m_AddedIssuedAndAccepted.end()) {
            return false;
        }
        //create an accepted invoice, that has not been issued, so we can insert it, if we need to make an accepted invoice
        //from invoice that is issued and accepted
        CInvoice acceptedInvoiceOfficialName(issuedInvoice.date(), offSellerName, offBuyerName,
                                             issuedInvoice.amount(), issuedInvoice.vat(),
                                             false, true, issuedInvoice.m_invoiceNumber);

        auto it = set->second.find(acceptedInvoiceOfficialName);
        //if company has a set of invoices but does not have this exact one return false
        if (it == set->second.end()) {
            return false;
        }
        //if invoice was issued and accepted, insert invoice that is accepted and not issued
        if (it->m_issued && it->m_accepted) {
            set->second.erase(it);
            set->second.insert(acceptedInvoiceOfficialName);
            return true;
        }
        //if invoice is just issued, delete it
        if (it->m_issued && !it->m_accepted) {
            set->second.erase(it);
            return true;
        }
        return false;
    }
//---------------------------------------------------------------------------------------------
/**
 * @brief Deletes an issued invoice using delIssuedInvoice
 * @param issuedInvoice is an invoice we need to delete
 * @return whether the invoice was found and deleted
 */
    bool delIssued(const CInvoice &issuedInvoice) {
        //class that normalises names and finds official names, that were given when registering companies
        CCompaniesNamesNormaliser names(issuedInvoice, m_RegisteredCompanies);

        if (!checkValidityOfSellerAndBuyer(names.m_NormalisedSeller, names.m_NormalisedBuyer, names.m_OffSellerName,
                                           names.m_OffBuyerName)) {
            return false;
        }

        if (!delIssuedInvoice(names.m_NormalisedBuyer, issuedInvoice, names.m_OffSellerName, names.m_OffBuyerName) ||
            !delIssuedInvoice(names.m_NormalisedSeller, issuedInvoice, names.m_OffSellerName, names.m_OffBuyerName)) {
            return false;
        }
        return true;
    }
//---------------------------------------------------------------------------------------------
/**
 * @brief Deletes an accepted invoice using delAcceptedInvoice
 * @param acceptedInvoice is an invoice we need to delete
 * @return whether the invoice was found and deleted
 */
    bool delAccepted(const CInvoice &acceptedInvoice) {
        //class that normalises names and finds official names, that were given when registering companies
        CCompaniesNamesNormaliser names(acceptedInvoice, m_RegisteredCompanies);

        if (!checkValidityOfSellerAndBuyer(names.m_NormalisedSeller, names.m_NormalisedBuyer, names.m_OffSellerName,
                                           names.m_OffBuyerName)) {
            return false;
        }
        if (!delAcceptedInvoice(names.m_NormalisedBuyer, acceptedInvoice, names.m_OffSellerName, names.m_OffBuyerName)
            ||
            !delAcceptedInvoice(names.m_NormalisedSeller, acceptedInvoice, names.m_OffSellerName, names.m_OffBuyerName))
            return false;

        return true;
    }
//---------------------------------------------------------------------------------------------
/**
 * @brief Function to find invoices with issues
 * @param company name of company we want to check
 * @param sortBy object containing information about how to sort the list
 * @var list list of invoices with issues
 * @return Returns a sorted list of invoices that were only issued or only accepted
 */
    std::list<CInvoice> unmatched(const std::string &company, const CSortOpt &sortBy) const {
        std::list<CInvoice> list;
        auto it = m_AddedIssuedAndAccepted.find(normalise(company));
        //if company does not have a set of invoices return empty list
        if (it == m_AddedIssuedAndAccepted.end()) {
            return list;
        }
        //if company has a set of invoices, add to list every invoice that was only issued or only accepted
        for (const auto &it2: it->second) {
            if (!it2.m_issued || !it2.m_accepted) {
                list.push_back(it2);
            }
        }
        //sort the list using CSortOpt class
        list.sort(sortBy);
        return list;
    }
//---------------------------------------------------------------------------------------------
private:
    std::map<std::string, std::string> m_RegisteredCompanies;           // key = normalised name, value = original name
    std::map<std::string, std::string> m_RegisteredCompaniesNormalised; // key = original name, value = normalised name
    std::map<std::string, std::set<CInvoice, CInvoiceCmp>> m_AddedIssuedAndAccepted;
    int m_InvoiceNumber = 0;
};

//---------------------------------------------------------------------------------------------
bool equalLists(const std::list<CInvoice> &a, const std::list<CInvoice> &b) {
    if (a.size() != b.size())
        return false;
    auto itA = a.begin();
    auto itB = b.begin();
    while (itA != a.end()) {
        if (*itA != *itB)
            return false;
        ++itA;
        ++itB;
    }
    return true;
}

//---------------------------------------------------------------------------------------------
int main() {

    assert(normalise("a") == "a");
    assert(normalise("a      ") == "a");
    assert(normalise(" a") == "a");
    assert(normalise("A") == "a");
    assert(normalise("A ") == "a");
    assert(normalise(" A") == "a");
    assert(normalise("    a    ") == "a");
    assert(normalise("a b") == "a b");
    assert(normalise("a b") == "a b");
    assert(normalise("a b ") == "a b");
    assert(normalise(" a b") == "a b");
    assert(normalise(" a b ") == "a b");
    assert(normalise("a     b") == "a b");
    assert(normalise("    a    b   cd ") == "a b cd");
    CVATRegister test;
    assert(test.registerCompany("a   "));
    assert(test.registerCompany("  b"));
    assert(test.registerCompany("C"));
    assert(test.registerCompany("d"));
    assert(!test.registerCompany("a   "));
    assert(!test.registerCompany("  b"));
    assert(!test.registerCompany("C"));
    assert(!test.registerCompany("d"));
    assert(!test.registerCompany(" A    "));
    assert(!test.registerCompany(" B "));
    assert(!test.registerCompany("c        "));
    assert(!test.registerCompany("    D"));
    assert(!test.addIssued(CInvoice(CDate(2000, 1, 1), "a", " A ", 100, 20)));
    assert(!test.addIssued(CInvoice(CDate(2000, 1, 1), "a", "z", 99, 22)));
    assert(test.addIssued(CInvoice(CDate(2000, 1, 1), " a ", " b ", 100, 20)));
    assert(test.addIssued(CInvoice(CDate(2000, 1, 1), " a ", " b ", 100, 19.999)));
    assert(test.addIssued(CInvoice(CDate(2000, 1, 2), " a ", " b ", 100, 19.999)));
    assert(test.addIssued(CInvoice(CDate(2000, 1, 2), " a ", "d", 100, 19.999)));
    assert(!test.addIssued(CInvoice(CDate(2000, 1, 1), " a ", "  B    ", 100, 20)));
    assert(!test.addIssued(CInvoice(CDate(2000, 1, 1), "a", "   B", 100, 20)));
    assert(!test.addIssued(CInvoice(CDate(2000, 1, 1), "A", "B", 100, 20)));

    CVATRegister r;
    assert (r.registerCompany("first Company"));
    assert (!r.registerCompany("First Company"));
    assert (r.registerCompany("Second     Company"));
    assert (r.registerCompany("ThirdCompany, Ltd."));
    assert (r.registerCompany("Third Company, Ltd."));
    assert (!r.registerCompany("Third Company, Ltd."));
    assert (!r.registerCompany(" Third  Company,  Ltd.  "));

    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 20)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "Second Company ", "First Company", 300, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
    assert (!r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
    assert (!r.addIssued(CInvoice(CDate(2000, 1, 4), "First Company", "First   Company", 200, 30)));
    assert (!r.addIssued(CInvoice(CDate(2000, 1, 4), "Another Company", "First   Company", 200, 30)));

    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER,
                                                                                       false).addKey(CSortOpt::BY_DATE,
                                                                                                     false)),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000)
                               }));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(
                                           CSortOpt::BY_BUYER, true)),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000)
                               }));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_VAT, true).addKey(CSortOpt::BY_AMOUNT, true).addKey(
                                           CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(
                                           CSortOpt::BY_BUYER, true)),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000)
                               }));
    assert (equalLists(r.unmatched("First Company", CSortOpt()),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000)
                               }));
    assert (equalLists(r.unmatched("second company", CSortOpt().addKey(CSortOpt::BY_DATE, false)),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Third Company, Ltd.", "Second     Company", 400,
                                                34.000000)
                               }));

    assert (equalLists(r.unmatched("last company", CSortOpt().addKey(CSortOpt::BY_VAT, true)),
                       std::list<CInvoice>
                               {
                               }));
    assert (r.addAccepted(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company ", 200, 30)));
    assert (r.addAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (r.addAccepted(CInvoice(CDate(2000, 1, 1), "Second company ", "First Company", 300, 32)));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
                                           CSortOpt::BY_DATE, true)),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                32.000000)
                               }));
    assert (!r.delIssued(CInvoice(CDate(2001, 1, 1), "First Company", "Second Company ", 200, 30)));
    assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "A First Company", "Second Company ", 200, 30)));
    assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Hand", 200, 30)));
    assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 1200, 30)));
    assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 200, 130)));
    assert (r.delIssued(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company", 200, 30)));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
                                           CSortOpt::BY_DATE, true)),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                32.000000)
                               }));
    assert (r.delAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
                                           CSortOpt::BY_DATE, true)),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                32.000000)
                               }));
    assert (r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
                                           CSortOpt::BY_DATE, true)),
                       std::list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                32.000000)
                               }));
    return EXIT_SUCCESS;
}


