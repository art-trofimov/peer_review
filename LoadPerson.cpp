struct DBSettings
{
    string_view db_name;
    int db_connection_timeout;
    bool db_allow_exceptions,
    DBLogLevel db_log_level;
                           
};

struct QueryOptions {
    int min_age;
    int max_age;
    string_view name_filter;
}



vector<Person> LoadPersons(const DBSettings& db_settings, const QueryOptions& query) {
    DBConnector connector(db_settings.db_allow_exceptions, db_settings.db_log_level);
    DBHandler db;
    if (db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_settings.db_name, db_settings.db_connection_timeout);
    } else {
        db = connector.Connect(db_settings.db_name, db_settings.db_connection_timeout);
    }
    if (!db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << query.min_age << " and "s << query.max_age << " "s
              << "and Name like '%"s << db.Quote(query.name_filter) << "%'"s;
    DBQuery query(query_str.str());
    if (query.empty()) {
        return { };
    }

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}