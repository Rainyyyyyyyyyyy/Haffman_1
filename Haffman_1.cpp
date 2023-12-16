// Haffman_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include <malloc.h>
#include <fstream>
#include <Windows.h>



class String
{
    unsigned char* str;
    int len;

public:
    String(int l = 0) { str = new unsigned char[l + 1]; len = l; str[len] = '\0'; }
    String(char symb) { str = new unsigned char[2]; len = 1; str[0] = symb; str[len] = '\0'; }
    String(const char* s) {
        len = 0;
        while (s[len] != '\0')len++;
        str = new unsigned char[len + 1];
        for (int i = 0; i < len; str[i] = s[i], i++);
        str[len] = '\0';
    }

   

    ~String() { if (str) delete[]str; str = NULL; }
    int Len() { return len; }



    String& operator = (const String&);
    String& operator = (char);


    unsigned char& operator[](int);

   

    String operator+(const String& s);
    String operator+(const char*);
    String operator+(char);


    friend istream& operator>>(istream&, String&);
    friend ostream& operator<<(ostream&, String&);


    int find_symbol(char);
};



int String::find_symbol(char symb) {
    for (int i = 0; i < len; i++) {
        if (symb == str[i])return i;
    }
    return -1;
}
unsigned char& String::operator[](int k) {
    try {
        if (k < 0)throw (long long)0;
        if (k >= len)throw len - 1;
    }
    catch (long long arg) {
        cout << "Errora with index! Returned " << arg << " index" << endl;
        return str[arg];
    }
    return str[k];

}

String& String::operator = (char s) {
    if (str) delete[] str;
    len = 1;
    str = new unsigned char[2];
    str[0] = s;
    str[1] = '\0';
    return *this;
}
String& String::operator =(const String& s) {
    if (this == &s)return *this;
    if (str)delete[] str;
    len = s.len;
    str = new unsigned char[len + 1];
    for (int i = 0; i < len; str[i] = s.str[i], i++);
    str[len] = '\0';
    return *this;
}



ostream& operator<<(ostream& out, String& s) {
    for (unsigned char* i = s.str; i < s.str + s.len; i++) {
        if (*i == '\n')out << "/n";
        else out << *i;
    }
    return out;
}
istream& operator>>(istream& in, String& s) {
    if (s.str) {
        delete[] s.str;
        s.str = nullptr;
    }
    s.len = 0;
    unsigned char t = 10;
    unsigned char* l = (unsigned char*)(malloc(0));
    int l_size = 0;

    ///             input string
    while ((t = unsigned char(getchar())) != '\n') {
        l = (unsigned char*)realloc(l, (l_size + 1) * sizeof(unsigned char));
        l[l_size++] = t;
    }

    s.len = l_size;
    //for(s.len=0; l[s.len]!='\0'; s.len++); //s.str[s.len] = t[s.len], s.len++);
    s.str = new unsigned char[s.len + 1];
    for (int i = 0; i < s.len; s.str[i] = l[i], i++);
    s.str[s.len] = '\0';
    free(l);
    return in;

}

String String::operator+(const String& s) {
    int i = 0;

    String local(len + s.len);

    for (i = 0; str[i] != '\0'; local.str[i] = str[i], i++);
    for (i = 0; s.str[i] != '\0'; local.str[i + len] = s.str[i], i++);
    local.str[local.len] = '\0';

    return local;
}

String String::operator+(const char* s) {
    int i = 0;
    while (s[i] != '\0')i++;
    String local(len + i);
    for (i = 0; str[i] != '\0'; local.str[i] = str[i], i++);
    for (i = 0; s[i] != '\0'; local.str[len + i] = s[i], i++);
    local.str[local.len] = '\0';

    return local;
}

String String::operator+(char s) {
    String local(len + 1);
    for (int i = 0; i < len; local.str[i] = str[i], i++);
    local.str[local.len - 1] = s;
    local.str[local.len] = '\0';

    return local;

}


template <class T> void Swap(T& a, T& b) {
    T c = a;
    a = b;
    b = c;
}

template <typename T> void reverse(T* a, int size) {
    int medi = size / 2;
    for (int i = 0; i < medi; i++) {
        Swap(a[i], a[size - i - 1]);
    }
}

void Sort(int*& a, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (a[j] < a[j + 1])Swap(a[j], a[j + 1]);
        }
    }
}




typedef struct COD {
    int code;   // битовый код  // max 010...0101       32 бита(4 байта)
    char lena; // длина кода    // max - 128
    int counter;

    friend ostream& operator << (ostream& out, COD& a) {
        //out << " lena " << int(a.lena) << " counter " << a.counter << " code ";
        for (int i = a.lena-1; i >=0; out << ((a.code & (1<<i))!=0), i--);
        return out;
    }
}COD;

void Haffman2(int local_len, COD *&codes) {
    if (local_len > 2) {
        codes[local_len - 2].counter += codes[local_len - 1].counter;
        int j = local_len - 2;
        //COD y = codes[j];
        while (j && codes[j-1].counter < codes[j].counter) {
            Swap(codes[j - 1], codes[j]);
             j--;       
            //if(!j)break;
        }
        //codes[j] = y;

        Haffman2(local_len - 1, codes);
        COD x = codes[j];
        for (int i = j; i < local_len-1; i++){
            codes[i] = codes[i + 1];
        }
        codes[local_len - 2].code = x.code<<1;
        codes[local_len - 1].code = x.code<<1;

        codes[local_len - 2].lena = x.lena + 1;

        codes[local_len - 1].code |= 1;

        codes[local_len - 1].lena = x.lena + 1;
        

    }
    else {
        codes[0].code = false;
        codes[1].code = true;
        codes[0].lena = codes[1].lena = 1;
    }
    
}
int main()
{   
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    //setlocale(LC_ALL, "RUS");
    char* path = new char[200];
    cout << "Enter path(C://ProgramFiles//...//file.txt" << endl;
    cin >> path;
    
    ifstream file_in(path);


    bool code_or_decode = false;
    cout << "what do we do? (0 - encode, 1 - decode): ";
    cin >> code_or_decode;

    if (!code_or_decode) {
        cout << "encoding..." << endl;
        String a;
        //cin >> a;
        char t;
        while (file_in.get(t)) {
            //t = file_in.get();
            a = a + t;
        }
        
        file_in.close();
        cout << a << endl;


        COD* codes = new COD[1024];          /// создание таблицы кодов на всю ASCII
        for (int i = 0; i < 1024; codes[i].counter = codes[i].lena = codes[i].code = 0, i++);
        String alphabet;
        for (int i = 0; i < a.Len(); i++) {
            if (alphabet.find_symbol(a[i]) == -1) {
                alphabet = alphabet + a[i];
                //cout << a[i];
                //counters = (int*)realloc(counters, (j + 1) * sizeof(int));
                codes[a[i]].counter = 1;
                //j++;
            }
            else codes[a[i]].counter++;
        }
        //for (int i = 0; i < alphabet.Len(); cout << counters[alphabet[i]], i++);
        cout << endl;   /// сокращение таблицы кодов в соответствии с алфавитом
        int k = 0;
        for (int i = 0; i < alphabet.Len(); i++) {
            if (codes[alphabet[i]].counter) {
                Swap(codes[k].counter, codes[alphabet[i]].counter);
                k++;
            }
        }
        cout << endl << "========"<<k << alphabet.Len() << endl<<"========="<<endl;

        codes = (COD*)realloc(codes, k * sizeof(COD));
        //cout << alphabet.Len() << "--" << k << endl;
        //////////////////////for (int i = 0; i < k; cout << codes[i].counter, i++);
        ///////////////////////cout << endl << alphabet << endl;
        //return 0;

        for (int i = 0; i < k - 1; i++) {
            for (int j = 0; j < k - 1 - i; j++) {
                if (codes[j].counter < codes[j + 1].counter) {
                    Swap(alphabet[j], alphabet[j + 1]);
                    Swap(codes[j].counter, codes[j + 1].counter);
                }
            }
        }

        for (int i = 0; i < k; i++) {
            cout << alphabet[i] << " : " << (codes[i].counter) << endl;
        }

        ///////////////////////cout << alphabet << endl;
        /////////////////////////for (int i = 0; i < k; cout << codes[i].counter, i++);
        //cout << k << endl;
        //return 0;
        cout << endl;
        //return 0;
        Haffman2(k, codes);
        for (int i = 0; i < k; i++) {
            cout << alphabet[i] << ": ";
            cout << codes[i];
            cout << endl;
        }


        ofstream file_out(path);
        delete[] path;
        file_out << '1';
        file_out << a.Len();
        file_out << '.';
        
        int counter8 = 0;
        char iterator_per_code = 0;
        int iterator_per_alphabet = 0;
        unsigned char crypt = 0;

        //unsigned char crypt = 0;

        unsigned char** crypts = new unsigned char*[k];
        for (int i = 0; i < k; i++) {
            int i_size_crypt = ((codes[i].lena % 8) ? codes[i].lena / 8 + 1 : codes[i].lena / 8);
            crypts[i] = new unsigned char[i_size_crypt];
            for (int j = 0; j < i_size_crypt; crypts[i][j] = 0, j++);
            
        }
        
        for (int i = 0; i < k; i++) {

            file_out << alphabet[i];
            file_out << (int(codes[i].lena));
            file_out << '.';        /// разделитель между длиной кода и самим кодом
            char counter_per_char = 0;

            while (counter8 < 8) {
                if (iterator_per_code < codes[i].lena) {
                    //////crypts[i][counter_per_char] = (crypts[i][counter_per_char] << 1) | ((codes[i].code >> (codes[i].lena - 1 - iterator_per_code)) & 1);
                    crypt = (crypt << 1) | (codes[i].code >> ((codes[i].lena - 1 - iterator_per_code) & 1));
                    iterator_per_code++;
                    counter8++;
                }
                else {
                    ////////////////////////////////if (counter8)crypt = crypt << (8 - counter8);////crypts[i][counter_per_char] = crypts[i][counter_per_char] << (8 - counter8);
                    //file_out << (char(codes[i].lena));
                    file_out << crypt;////crypts[i][counter_per_char];
                    crypts[i][counter_per_char] = crypt;
                    crypt = 0;
                    iterator_per_code = 0;
                    counter8 = 0;
                    counter_per_char = 0;
                    break;
                }
                if (counter8 == 8) {
                    file_out << crypt;////crypts[i][counter_per_char];
                    crypts[i][counter_per_char] = crypt;
                    counter_per_char++;
                    crypt = 0;
                    counter8 = 0;
                    if (iterator_per_code == codes[i].lena) {
                        iterator_per_code = 0;  break;
                    }
                }              
            }
            //file_out << '.';
            file_out << endl;
        }
        file_out << '*';        /// флажок на то, что начинаем выводить шифр
        file_out << '*';        /// потом при разшифровке ловим случай, когда после <symb> идёт не число <len_code>
                                /// (значит отсюда начинается шифр, а не продолжается таблица
        unsigned char crypt_out = 0;
        counter8 = 0;
        char this_lena = 0;
        for (long long i = 0; i < a.Len(); i++) {
            for (int j = 0; j < k; j++) {
                if (alphabet[j] == a[i]){
                    this_lena = codes[j].lena;
                    while (counter8 < 8){
                        if (this_lena) {
                            crypt_out = (crypt_out << 1) | ((codes[j].code >> (this_lena-1)) & 1);//(crypt_out) | ((codes[j].code >> this_lena-1) & 1)<<counter8
                            counter8++;
                            this_lena--;
                        }
                        else {
                            if(counter8<8)break;
                        }
                        if (counter8 == 8) {  
                            file_out << crypt_out;
                            crypt_out = 0;
                            counter8 = 0;
                        }

                    }
                    if(!this_lena)break;

                }
            }
        }

        file_out.close();



        for (int i = 0; i < k; delete[] crypts[i], i++);
        delete[] crypts;
        delete[] codes;
        return 0;
    }

    if (code_or_decode == 1){
           /// ====================================================================
           /// *********** Начинаем обрабатывать оглавление таблицы кодов ************
           /// ====================================================================
           /// 
           ///  /// <flag><len_str>.<symb><len_code>.<code> \n
           ///  ...
        //ifstream file_in("D://C_projs_Visual_studio_2022//2_Kurs_1_semestr//Kodirovanie//Haffman_1//Haffman_1//file.txt.txt");
        int size_of_input = 0;
        unsigned char t = file_in.get();
        while (t!='.') {
            size_of_input = size_of_input * 10 + t - 48;
            t = file_in.get();
        }       /// считываем длину входной строки (после закодирования она записывается после флага действия в виде int)
        cout << "Len of input: "<<size_of_input << endl;
        /// прочитали длину получаемой при разшифровке строки

        

        /// ==================================================================================
        //// ***************** начинаем обрабатывать таблицу кодов ****************************
        /// ==================================================================================
        ///                   ↓        /// текущая позиция курсора в файле после считывания длины строки 
        /// <flag><len_str>.<symb><len_code>.<code> \n
        /// <symb><len_code>.<code> \n
        /// <symb><len_code>.<code> \n
        /// <symb><len_code>.<code> \n
        /// <symb><len_code>.<code> \n
     
        unsigned char* symbols = new unsigned char[256];    /// массив символов из таблицы
        unsigned char* code_lenas = new unsigned char[256]; /// массив длин кодов для символов из таблицы
        unsigned char** codes = new unsigned char* [256];  /// массив кодов для символов из таблицы
        // codes[i] будет динамически изменяться в размерах в зависимости от длины  кода i-го символа
        for (int i = 0; i < 256; i++) {
            codes[i] = new unsigned char[0];  /// пока что "матрица" должна иметь пустые подмассивы
        }
        for (int i = 0; i < 256; code_lenas[i] = symbols[i] = 0, i++);
        // необходимо для реаллока                              
        
        unsigned char current_symbol;
        current_symbol = file_in.get();             /// считали символ <symb>
        
        t = file_in.get();  /// начинаем считывать длину его кода <len_code>
        short int this_code_len = 0;
        while (t != '.') {
            this_code_len = this_code_len * 10 + t - 48;
        }
        symbols[current_symbol] = current_symbol;       /// записали символ
        code_lenas[current_symbol] = this_code_len;     /// записали длину кода этого символа
        ///                                    ↓
        /// <flag><len_str>.<symb><len_code>.<code> \n
        unsigned char this_code_len_per_char = (this_code_len % 8) ? this_code_len / 8 + 1 : this_code_len / 8;
        t = file_in.get();
        codes[current_symbol] = (unsigned char*) realloc(codes[current_symbol], this_code_len_per_char * sizeof(unsigned char));
        short int counter_per_chara = 0;
        while (this_code_len_per_char){
            codes[current_symbol][counter_per_chara] = t;
            t = file_in.get();
            this_code_len_per_char--;
            counter_per_chara++;
        }
        file_in.get();/// считали '\n'
        file_in.close();
        /// ...
        /// <symb><len_code>.<code> \n
        /// "**" - flag, начинается шифр
        /// реализовать эту идею "точки конца таблицы"
        


        ///char* code_lenas = new char[256];
        ///for (int i = 0; i < 256; code_lenas[i] = 0, i++);
         


        delete[] symbols;
        delete[] code_lenas;
        for (int i = 0; i < 256; i++)delete[] codes[i];
        delete[] codes;

        return 0;

    }

    
    


    /// закодирование ГОТОВО
    /*      прописать кол-во символов во входной строке при закодировании (поможет при раскодировании)
    *       т.к. код префиксный - раскодирование единообразное
    * 
    *   ПРОПИСАТЬ РАСКОДИРОВАНИЕ
    
    
    
    */

    return 0;
   
}   

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
