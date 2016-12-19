#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;
using boost::property_tree::ptree;

class single_t{
    int             sID;
    string          sName;
public:
    void            setID(int ID){sID=ID;}
    int             getID(){return sID;}
    void            setName(string Name){sName=Name;}
    string          getName(){return sName;}
};

typedef vector<single_t*> multiple_t;

class foo{
    string          fTitle;
    multiple_t      fItems;
public:
    string          getTitle(){return fTitle;}
    void            setTitle(string Title){fTitle=Title;}
    multiple_t      getItems(){return fItems;}
    void            setItems(multiple_t Items){fItems = Items;}
    void            setItems(single_t Item){fItems.push_back(&Item);}
};

int main () 
{
    try{
        string response = "{\"title\":\"Foo\",\"items\":[{\"id\":123,\"name\":\"test1\"},{\"id\":456,\"name\":\"test2\"}], \"hobby\":[\"sleeping\", \"ops\", \"eating\"]}";

        ptree pt;
        stringstream ss; ss << response;
        read_json(ss, pt);
        foo results;
        results.setTitle(pt.get<string>("title"));
		cout << pt.get_child("items").size() << endl;
		cout << pt.get_child("hobby").size() << endl;

        BOOST_FOREACH(ptree::value_type &v,pt.get_child("items"))
		{
			cout << v.first << endl;
		}

        BOOST_FOREACH(ptree::value_type &v,pt.get_child("hobby"))
		{
            single_t result;
            result.setID(v.second.get<int>("id"));
            result.setName(v.second.get<string>("name"));
            results.setItems(result);
        }

	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

