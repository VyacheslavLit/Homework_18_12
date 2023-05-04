#include "Dict.h"



Dict::Dict()
{
    root = new DictNode();
}
Dict::~Dict()
{
//    destroy(root);
}
void Dict::destroy(DictNode* root)
{
    if (root == nullptr)
        return;
    delete root;
    root = nullptr;
}


// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void Dict::insert(string key)
{
    if (key == "") return;
    DictNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        //прверка на знаки припинания в слове
        if (key[i] == '.' || key[i] == ',' || key[i] == '?' || key[i] == '!' || key[i] == '-' || key[i]=='(' || key[i] == ')' ||key[i] == '"' ||key[i] == ':' || key[i] == '/') break;
        // вычисляем индекс в алфите через смещение относитьельно первой буквы
        int index = key[i] + 128;//267
        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = new DictNode();
        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}



bool Dict::addDictToDict(bool dictOn)
{
    char tmp;
    string word;
    while (true)
    {
        system("clear");
        ifstream inf("Dict.txt");
        /*
            Проверяем, считался ли файл, и если он не считался даем возможность
        повторить операцию, чтобы обеспечить обязательность загрузки базы пользователей.
        */
        if (!inf)
        {
            while (true)
            {
                cout << "Неудачная загрузка словаря, наберите любой символ для повтора или \n0 - для продолжения без загрузки словаря.: ";
                cin >> tmp;
                if (cin.fail())
                {
                    expCin();
                    inf.close();
                    continue;
                }
                break;
            }
            if (tmp == '0') break;
            continue;
        }

        while (inf)
        {
            inf >> word;
            if (!inf) break;
            insert(word);
        }
        inf.close();
        dictOn = { true };
        break;
    }
    return dictOn;
}

void Dict::addDictToMessages()
{
    char tmp;
    string word;
    while (true)
    {
        ifstream inf("./Messages.txt");
        system("clear");
        /*
            Проверяем, считался ли файл, и если он не считался даем возможность
        повторить операцию, чтобы обеспечить обязательность загрузки базы пользователей.
        */
        if (!inf)
        {
            while (true)
            {
                cout << "Неудачная загрузка словаря, наберите любой символ для повтора или \n0 - для продолжения без загрузки словаря.: ";
                cin >> tmp;
                if (cin.fail())
                {
                    expCin();
                    inf.close();
                    continue;
                }
                break;
            }
            if (tmp == '0') break;
            continue;
        }

        while (inf)
        {
            inf >> word;
	    insert(word);
        }
        inf.close();
        break;
    }
}

void Dict::addDictToTxt()
{
    string word;
    while (true)
    {
        system("clear");
        cout << "Введите название файла для загрузки словаря (в папке присутствует файл Kramer.txt): ";
        string tmp;
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> tmp;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\nОшибка ввода, повторите ввод файла. ";
	    cout << cin.get();
	    cin.clear();
	    cin.ignore(32767, '\n');
            continue;
        }
	tmp = "./"+tmp;
        ifstream inf(tmp);
        /*
            Проверяем, считался ли файл, и если он не считался даем возможность
        повторить операцию, чтобы обеспечить обязательность загрузки базы пользователей.
        */
        if (!inf.is_open())
        {
            while (true)
            {
                cout << "Неудачная загрузка словаря, наберите любой символ для повтора или \n0 - для продолжения без загрузки словаря.: ";
                cin >> tmp;
                if (cin.fail())
                {
                    expCin();
                    inf.close();
                    continue;
                }
                break;
            }
            if (tmp == "0") break;
            continue;
        }

        while (inf)
        {
            inf >> word;
	    insert(word);
        }
        inf.close();
        break;
    }
}


void Dict::show()
{
    class DictNode* node = root;

    string str;
    int ind = 0;
    str += ' ';
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            str[ind] = i - 128;
            show(root->children[i], str, ind + 1);
        }
    }
    cin.clear();
    cin.ignore(32767, '\n');
    cout << cin.get();
}

void Dict::show(DictNode* root)
{
    string str;
    int ind = 0;
    str += ' ';
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            str[ind] = i - 128;
            show(root->children[i], str, ind + 1);
        }
    }
}

void Dict::show(DictNode* root, string str, int ind)
{
    if (root->isEndOfWord)
    {
        cout << str << endl;
        return;
    }
    str += ' ';
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            str[ind] = i - 128;
            show(root->children[i], str, ind + 1);
        }
    }
}

string Dict::messeng()
{
    string mes{};
    string pref;
    while (true)
    {
        pref = "";
        cout << "Ваше сообщение: " << mes << endl;
        cout << "Введите префикс добавляемого слова или: 1 обновить переписку, 0 закончить сообщение.\n";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> pref;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\nОшибка ввода, повторите ввод превифкса: ";
            continue;
        }
        if (pref == "1")continue;
        if (pref == "0")break;
        if (pref != "") mes += suf(pref) + ' ';

    }
    return mes;
}

string Dict::suf(string txt)
{
    class DictNode* node = root;
    return choosSuffix(search(node, txt), txt);
}

// Возврашает узел на котором закончился поиск 
DictNode* Dict::search(DictNode* node, string key)
{
    for (int i = 0; i < key.length(); i++)
    {
        if (key[i] < 'а' || key[i]>'я') nullptr;
        int index = key[i] + 128;
        if (!node->children[index])
            return nullptr;
        node = node->children[index];
    }
    return node;
}

// выбираем все суфиксы к переданному префиксу и  возвращаем массив суфиксов
string Dict::choosSuffix(DictNode* root, string pref)
{
    if (root == nullptr) return pref;
    cout << "Вы ввели префикс: " << pref << endl;
    cout << "В словаре есть следующие слова с таким префиксом:\n";
    string suffix;
    int ind = 0;
    suf_.clear();

    choosSuf(root, suffix, ind);
    ind = 0;
    for (auto element : suf_)
    {
        ind += 1;
        cout << ind << ". (" << pref << element << ") ";
    }
    cout << "\nКакое слово вы имели в виду (выберите номер, или " << 0 << " оставить без изменений, " << ind + 1 << " добавить суфикс вручную): ";
    int tmp;
    while (true)
    {
        cin >> tmp;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\nОшибка ввода, повторите выбор: ";
            continue;
        }
        if (tmp<0 || tmp>ind + 1)
        {
            cout << "Вне диапазонв выбора, повторите выбор: ";
            continue;
        }
        break;
    }
    if (tmp == 0)return (pref);
    if (tmp > 0 && tmp <= ind) return (pref + suf_[tmp - 1]);
    cout << "\nЗакончите слово: " << pref;
    while (true)
    {
        cin >> suffix;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\nОшибка ввода, повторите окончание слова: " << pref;
            continue;
        }
        break;
    }
    return (pref + suffix);
}

void Dict::choosSuf(DictNode* root, string suffix, int ind)
{

    if (root != nullptr) if (root->isEndOfWord) suf_.push_back(suffix);
    string tmp;
    suffix += ' ';
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i])
        {
            suffix[ind] = i - 128;
            choosSuf(root->children[i], suffix, ind + 1);
        }
    }

}
