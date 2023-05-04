//#ifndef DICT_H
//#define DICT_H
#pragma once
#include<iostream>
#include <memory>
#include <vector>
#include <cstring>
#include "DictMenu.h"
const int ALPHABET_SIZE = 256;
using namespace std;


//класс узлов словаря
class DictNode {
public:
    int isEndOfWord; // Строка, заканчивающаяся этим символом
    DictNode* children[ALPHABET_SIZE];

    DictNode()
    {
        isEndOfWord = 0;
        memset(children, NULL, sizeof(DictNode*) * ALPHABET_SIZE);
    }

};

//класс словаря - дерево Trie
class Dict {
private:
    vector<string>suf_;

public:
    DictNode* root;
    Dict();
    ~Dict();
    void destroy(DictNode* root);
    // Вставляем слово str
    void insert(string str);
    //заполнение словаря из файла Dict.txt
    bool addDictToDict(bool dictOn);
    //заполнение словаря из файла messanges.txt
    void addDictToMessages();
    //Заполнение словаря из уазанного файла txt
    void addDictToTxt();

    //вывод всех посфиксов начиная с указанного узла
    void show();
    void show(DictNode*);
    void show(DictNode*, string, int);

    //метод ввода нового сообщения с помощью автоввода
    string messeng();
    //вспомогательный метод метода messeng()
    string suf(string);
    // Проверяем, появилась ли строка str, и возвращаем как префикс 
    DictNode* search(DictNode*, string);
    // выбираем все суфиксы к переданному префиксу и  возвращаем массив суфиксов
    string choosSuffix(DictNode*, string);
    void choosSuf(DictNode*, string, int);

};





//#endif
