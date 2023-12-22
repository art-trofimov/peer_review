struct Country
{
    string name;
    string iso_code;
    string phone_code;
    string time_zone;
};

struct City : public Country {
    string contry_name;
    string contry_iso_code;
    string contry_phone_code;
    string contry_time_zone;
    vector<Language> languages;   
}

// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
void ParseCitySubjson(vector<City>& cities, const Json& json, const string& country_name,
                      const string& country_iso_code, const string& country_phone_code, const string& country_time_zone,
                      const vector<Language>& languages) {
    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();
        cities.push_back({
            /*.name =*/             city_obj["name"s].AsString(),
            /*.iso_code =*/         city_obj["iso_code"s].AsString(),
            /*.phone_code =*/       country_phone_code + city_obj["phone_code"s].AsString(),
            /*.country_name =*/     country_name,
            /*.country_iso_code =*/ country_iso_code,
            /*.contry_time_zone =*/ country_time_zone,
            /*.languages =*/        languages
        });
    }
}

// ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            /*.name =*/         country_obj["name"s].AsString(),
            /*.iso_code =*/     country_obj["iso_code"s].AsString(),
            /*.phone_code =*/   country_obj["phone_code"s].AsString(),
            /*.time_zone =*/    country_obj["time_zone"s].AsString(),
        });
        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        ParseCitySubjson(cities, country_obj["cities"s], country.name, country.iso_code, country.phone_code,
                         country.time_zone, country.languages);
    }
}