#include <iostream>
#include <string>
#include <cstring>
#include "database.h"

std::string get_command() {
    std::string command;
    std::cout << "command (list, add, get, del, exit): ";
    std::cin >> command;
    return command;
}

void print_error(int code) {
    if (code == 1) { // invalid command error
        std::cout << "invalid command" << std::endl;
    }
    else if (code == 2) { // not found error
        std::cout << "not found" << std::endl;
    }
}

void print_array(Array &array) {
    std::cout << "[";
    switch (array.type) {
        case INT: {
            int* items = (int*)(array.items);
            for (int i = 0; i < array.size; ++i) {
                if (i != 0) std::cout << ", ";
                std::cout << items[i];
            }
            break;
        }
        case DOUBLE: {
            double* items = (double*)(array.items);
            for (int i = 0; i < array.size; ++i) {
                if (i != 0) std::cout << ", ";
                std::cout << items[i];
            }
            break;
        }
        case STRING: {
            char** items = (char**)(array.items);
            for (int i = 0; i < array.size; ++i) {
                if (i != 0) std::cout << ", ";
                std::cout << '"' << items[i] << '"';
            }
            break;
        }
        case ARRAY: {
            Array* items = (Array*)(array.items);
            for (int i = 0; i < array.size; ++i) {
                if (i != 0) std::cout << ", ";
                print_array(items[i]);
            }
            break;
        }
    }
    std::cout << "]";
}

void make_array(Array &array) {
    std::cout << "type (int, double, string, array): ";
    std::string type_str;
    std::cin >> type_str;

    std::cout << "size: ";
    std::string input;
    std::cin >> input;
    try {
        int size = std::stoi(input); // int로 변환
        array.size = size;
    } catch (const std::invalid_argument&) { // 자바식 int 변환 오류 catch
        print_error(1);
        return;
    }

    if (type_str == "int") {
        array.type = INT;
        array.items = new int[array.size];
        int* items = (int*)(array.items); // = static_case<int*>(array.items)
        for (int i = 0; i < array.size; i++) {
            std::cout << "item[" << i << "]: ";
            std::cin >> items[i];
        }
    } else if (type_str == "double") {
        array.type = DOUBLE;
        array.items = new double[array.size];
        double* items = (double*)(array.items);
        for (int i = 0; i < array.size; i++) {
            std::cout << "item[" << i << "]: ";
            std::cin >> items[i];
        }
    } else if (type_str == "string") {
        array.type = STRING;
        array.items = new char*[array.size];
        char** items = (char**)(array.items); // char 배열의 배열 (string 배열)
        for (int i = 0; i < array.size; i++) {
            std::cout << "item[" << i << "]: ";
            std::string str;
            std::cin >> str;
            items[i] = new char[str.length() + 1];
            std::strcpy(items[i], str.c_str());
        }
    } else if (type_str == "array") {
        array.type = ARRAY;
        array.items = new Array[array.size];
        Array* items = (Array*)(array.items);
        for (int i = 0; i < array.size; i++) {
            make_array(items[i]);
        }
    } else {
        print_error(1); // invalied command error
        return;
    }
}

void print_list(Database &database) {
    for (int i = 0; i < database.size; i++) {
        std::cout << database.entries[i].key << ": ";
        switch (database.entries[i].type) {
            case INT:
                std::cout << *((int*)(database.entries[i].value)) << std::endl;
                break;
            case DOUBLE:
                std::cout << *((double*)(database.entries[i].value)) << std::endl;
                break;
            case STRING:
                std::cout << (char*)(database.entries[i].value) << std::endl; // 포인터 없는 이유 : char* 이 자체로 "문자열"
                break;
            case ARRAY:
                Array& arr = *(Array*)(database.entries[i].value);
                print_array(arr);
                std::cout << std::endl;
                break;
        }
    }
    std::cout << std::endl;
}

void add_entry(Database &database) {
    Type type;
    std::string key;
    std::string type_str;
    std::string value;

    std::cout << "key: ";
    std::cin >> key;

    std::cout << "type (int, double, string, array): ";
    std::cin >> type_str;

    if (type_str == "int") {
        type = INT;
        std::cout << "value: ";
        int* val = new int;
        std::cin >> *val;
        add(database, create(type, key, val));
    } else if (type_str == "double") {
        type = DOUBLE;
        std::cout << "value: ";
        double* val = new double;
        std::cin >> *val;
        add(database, create(type, key, val));
    } else if (type_str == "string") {
        type = STRING;
        std::cin.ignore();  // newline이 버퍼에 남는것을 무시
        std::cout << "value: ";
        std::getline(std::cin, value);
        value = "\"" + value + "\"";
        char* val = new char[value.length() + 1];
        std::strcpy(val, value.c_str());
        add(database, create(type, key, val));
    } else if (type_str == "array") {
        type = ARRAY;
        Array* arr = new Array;
        make_array(*arr);
        add(database, create(type, key, arr));
    } else {
        print_error(1); // invalied command error
        return;
    }

    std::cout << std::endl;
}

void get_entry(Database &database) {
    std::string key;
    std::cout << "key: ";
    std::cin >> key;

    Entry* entry = get(database, key);
    if (entry) {
        std::cout << entry->key << ": ";
        switch (entry->type) {
            case INT:
                std::cout << *((int*)entry->value) << std::endl;
                break;
            case DOUBLE:
                std::cout << *((double*)entry->value) << std::endl;
                break;
            case STRING:
                std::cout << (char*)entry->value << std::endl;
                break;
            case ARRAY:
                std::cout << "Array" << std::endl;
                break;
        }
    } else {
        print_error(2); // not found error
    }
    std::cout << std::endl;
}

void del_entry(Database &database) {
    std::string key;
    std::cout << "key: ";
    std::cin >> key;

    Entry* entry = get(database, key);
    if (entry) {
        remove(database, key);
    } else {
        print_error(2); // not found error
    }
    std::cout << std::endl;
}
