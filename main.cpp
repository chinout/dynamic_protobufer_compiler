#include<iostream>
#include<string>
#include<assert.h>

#include "person.pb.h"

const int Num = 5;
void Reader(std::string* str){
    tutorial::AddressBook address_book;
    address_book.ParseFromString(*str);

    for(int i = 0;i<address_book.persons_size();i++){
        const tutorial::Person& person = address_book.persons(i);
        std::cout<<"person_id : "<<person.id()<<std::endl;
        std::cout<<"person_name : "<<person.name()<<std::endl;
        for(int j = 0;j<person.phones_size();j++){
            const tutorial::Person_phone_number& ph_num = person.phones(j);
            std::cout<<"person_phone_num : "<<ph_num.number()<<std::endl;
            std::cout<<"person_phone_type : "<<ph_num.type()<<std::endl;
        }
    }
}
void Writer(tutorial::AddressBook& address_book, std::string* str){
    for(int i = 0;i<Num;i++){
        tutorial::Person *person = address_book.add_persons();
        person->set_id(i);
        person->set_name("Timy");

        tutorial::Person::phone_number * ph_num = person->add_phones();
        ph_num->set_number("123456");
        ph_num->set_type(tutorial::Person::PHONE_TYPE::Person_PHONE_TYPE_HOME);
    }
    assert(address_book.SerializeToString(str));
}
int main(){
    tutorial::AddressBook address_book;
    std::string str;

    Writer(address_book,&str);
    Reader(&str);
    return 0;
}