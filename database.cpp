#include "database.h"

// 엔트리를 생성한다. (Entry's init)
Entry *create(Type type, std::string key, void *value) {
    Entry *entry = new Entry;
    entry->type = type;
    entry->key = key;
    entry->value = value;
    return entry;
}

// 데이터베이스를 초기화한다.
void init(Database &database) {
    database.entries = nullptr;
    database.size = 0;
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry) {
    int index = -1;
    for (int i = 0; i < database.size; i++) { // 중복 검사
        if (database.entries[i].key == entry->key) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        database.entries[index] = *entry; // 중복된 키의 값을 덮어씌움
    } else {
        Entry *temp = new Entry[database.size + 1]; // 새로운 배열을 사이즈를 늘려 만듦
        for (int i = 0; i < database.size; i++) {
            temp[i] = database.entries[i]; // 값을 복사, n번째는 비어있음
        }
        delete[] database.entries;
        database.entries = temp; // n-1번째 데이터가 들어있는 temp 포인터(배열)를 database.entries로 이동 (크기는 n)
        // delete[] temp; // 포인터가 가르키는 배열의 주소가 같으므로 삭제할 수 없음.
        database.entries[database.size] = *entry; // n번째 데이터 ex) entries[0] = [1,int,100] ... entries[1] = [2,int,500]
        database.size++;
    }
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key){
    for (int i = 0; i < database.size; i++) {
        if (database.entries[i].key == key) {
            return &database.entries[i];
        }
    }
    return nullptr; // 키를 찾지 못한 경우 nullptr 반환
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key){
    for (int i = 0; i < database.size; i++) {
        if (database.entries[i].key == key) {
            for (int j = i; j < database.size - 1; ++j) {
                database.entries[j] = database.entries[j + 1];
            }
            --database.size;
            return;
        }
    }
}

// 데이터베이스를 해제한다.
void destroy(Database &database){
    delete[] database.entries; // 배열 삭제, free
    database.size = 0; // size 0으로 초기화
}