#include <string>
#include "database.h"

std::string get_command();
void print_error(int code);
void print_list(Database &database);
void add_entry(Database &database);
void get_entry(Database &database);
void del_entry(Database &database);

/**
 * @brief Database System
 * int, double, string, array와 같이 다양한 타입의 정보를 저장할 수 있는
 * 데이터 베이스 프로그램
 * @version 1.0
 * @author leebarang
 */
int main() {
    Database database;
    init(database);

    std::string command;
    while (true) {
        command = get_command();

        if (command == "list") {
            print_list(database);
        } else if (command == "add") {
            add_entry(database);
        } else if (command == "get") {
            get_entry(database);
        } else if (command == "del") {
            del_entry(database);
        } else if (command == "exit") {
            break;
        } else {
            print_error(1); // invalied command error
        }
    }
    destroy(database);
    return 0;
}