#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>

struct SqlSelectQuery 
{

    std::vector<std::string> column;
    std::string from;
    std::map<std::string, std::string> where;

};

class SqlSelectQueryBuilder {
public:

    constexpr bool BuildQuery() 
    {
        return true;
    }

    const std::string getQuery() 
    {
        std::string result = getSelect() + getFrom() + getWhere() + ";\n";
        return result;
    }

    const std::string getSelect() 
    {
        std::string select;
        std::stringstream ss;
        for (auto i = query.column.begin(); i != query.column.end(); i++) {
            if (i != query.column.begin())
                ss << ", ";
            ss << *i;
        }
        if (query.column.empty() && !query.from.empty()) select = "SELECT * ";
        else select = "SELECT " + ss.str() + " ";
        return select;
    }

    const std::string getFrom() 
    {
        std::string from = "FROM " + query.from + " ";
        return from;
    }

    const std::string getWhere() 
    {
        std::string where;
        std::stringstream mm;
        for (auto i = query.where.begin(); i != query.where.end(); i++) 
        {
            if (i != query.where.begin())
                mm << " AND ";
            mm << i->first + "=" + i->second;
            where = "WHERE " + mm.str();
        }
        return where;
    }

    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept 
    {
        query.column.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept
    {
        query.column = columns;
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept 
    {
        query.from = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) noexcept 
    {
        query.where[key] = value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept
    {
        query.where = kv;
        return *this;
    }

private:
    SqlSelectQuery query;
};

int main() 
{
    SqlSelectQueryBuilder query_builder;

    query_builder.AddColumns({ "name", "phone" });
    query_builder.AddFrom("students");
    query_builder.AddWhere({ { "id", "42" }, { "name", "John" } });
    std::cout << query_builder.getQuery();
    static_assert(query_builder.BuildQuery(),
        "SELECT name, phone FROM students WHERE id=42 AND name=John;");
}