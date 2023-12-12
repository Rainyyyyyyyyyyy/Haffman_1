// Haffman_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include <malloc.h>
#include <fstream>

/*
bool find_symbol_in_chars(char* a, char b) {
    char* i = a;
    while (*i != '\0') {
        if (*i == b)return true;
        i++;
    }
    return false;
}

template <class T> void Swap(T& a, T& b) {
    T c = a;
    a = b;
    b = c;
}

void Sort_inti(int* a, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (a[j] < a[j + 1])Swap(a[j], a[j + 1]);
        }
    }
}

void chars_plus_chars(char *& a, char*& b) {
    int i = 0;
    while (a[i] != '\0')i++;
    int j = 0;
    while (b[j] != '\0') {
        a[i] = b[j];
        i++;
        b++;
    }
}
typedef struct cod {
    bool* code = NULL; // код символа
    char* symb = NULL;  // сам символ (или кортеж, потому что в процессе "свёртки" там образуются кортежи)
    long long len = 0;  // длина кортежа символов
    int n=0;    // длина кода

    int counter=0;    // счётчик повторений(для функции Хаффмана)


    cod(int lena = 0, int nena = 0, int counter = 0);
    cod(const cod& b);
    cod(char* s, bool* b, int nn) {
        //int i = 0;
        for (len = 0; s[len] != '\0'; len++);
        symb = new char[len];

        for (n = 0; n < nn; code[n] = b[n], n++);
    }
    cod operator=(const cod& b);

    cod operator +(const cod& b);


    ~cod() {
        if (code)delete[] code;
        if (symb)delete[] symb;
        code = NULL;
        symb = NULL;
    }

    friend ostream& operator<<(ostream& out, const cod& a) {
        out << "symb: ";
        for (long long i = 0; i < a.len; out<<a.symb[i]<<ends,i++);
        out << endl << "code: ";
        for (int i = 0; i < a.n; out<<a.code[i]<<ends, i++);
        out << endl << "counter: " << a.counter << endl;
        return out;
    }
}cod;


cod::cod(int lena, int nena, int counter){
    if (lena > 0)symb = new char[(len = lena) + 1];
    if (nena > 0)code = new bool[n = nena];
    for (int i = 0; i < len + 1; symb[i] = '\0', i++);
    for (int j = 0; j < nena; code[j] = false, j++);
}

cod::cod(const cod& b){
    code = new bool[n = b.n];
    symb = new char[len = b.len];
    counter = b.counter;
    for (int i = 0; i < len; symb[i] = b.symb[i], i++);
    for (int j = 0; j < n; code[j] = b.code[j]);
}

cod cod::operator=(const cod& b) {
    if (this == &b)return *this;
    if (code)delete[] code;
    if (symb)delete[] symb;

    len = b.len;
    n = b.n;
    symb = new char[len];
    code = new bool[n];
    for (long long i = 0; i < len; symb[i] = b.symb[i], i++);
    for (long long j = 0; j < n; code[j] = b.code[j], j++);

    return *this;

}

cod cod::operator +(const cod& b) {
    cod local(len + b.len + 1, n + b.n, counter + b.counter);
    int i = 0;
    for (i = 0; i < len; local.symb[i] = symb[i], i++);
    for (int j = 0; j < b.len; local.symb[i] = b.symb[j], j++, i++);
    local.symb[i] = '\0';

    for (i = 0; i < n; local.code[i] = b.code[i], i++);
    for (int j = 0; j < b.n; local.code[i] = b.code[j], i++, j++);

    return local;

}

*/

class String
{
    char* str;
    long long len;

public:
    String(long long l = 0) { str = new char[l + 1]; len = l; str[len] = '\0'; }
    String(char symb) { str = new char[2]; len = 1; str[0] = symb; str[len] = '\0'; }
    String(const char* s) {
        len = 0;
        while (s[len] != '\0')len++;
        str = new char[len + 1];
        for (long long i = 0; i < len; str[i] = s[i], i++);
        str[len] = '\0';
    }

   

    ~String() { if (str) delete[]str; str = NULL; }
    long long Len() { return len; }

    String& operator = (const String&);
    String& operator = (char);


    char& operator[](long long);

   

    String operator+(const String& s);
    String operator+(const char*);
    String operator+(char);


    friend istream& operator>>(istream&, String&);
    friend ostream& operator<<(ostream&, String&);


    long long find_symbol(char);
};



long long String::find_symbol(char symb) {
    for (long long i = 0; i < len; i++) {
        if (symb == str[i])return i;
    }
    return -1;
}
char& String::operator[](long long k) {
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
    str = new char[2];
    str[0] = s;
    str[1] = '\0';
    return *this;
}
String& String::operator =(const String& s) {
    if (this == &s)return *this;
    if (str)delete[] str;
    len = s.len;
    str = new char[len + 1];
    for (long long i = 0; i < len; str[i] = s.str[i], i++);
    str[len] = '\0';
    return *this;
}



ostream& operator<<(ostream& out, String& s) {
    for (char* i = s.str; i < s.str + s.len; i++) {
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
    char t = 10;
    char* l = (char*)(malloc(0));
    long long l_size = 0;

    ///             input string
    while ((t = getchar()) != '\n') {
        l = (char*)realloc(l, (l_size + 1) * sizeof(char));
        l[l_size++] = t;
    }

    s.len = l_size;
    //for(s.len=0; l[s.len]!='\0'; s.len++); //s.str[s.len] = t[s.len], s.len++);
    s.str = new char[s.len + 1];
    for (long long i = 0; i < s.len; s.str[i] = l[i], i++);
    s.str[s.len] = '\0';

    return in;

}

String String::operator+(const String& s) {
    long long i = 0;

    String local(len + s.len);

    for (i = 0; str[i] != '\0'; local.str[i] = str[i], i++);
    for (i = 0; s.str[i] != '\0'; local.str[i + len] = s.str[i], i++);
    local.str[local.len] = '\0';

    return local;
}

String String::operator+(const char* s) {
    long long i = 0;
    while (s[i] != '\0')i++;
    String local(len + i);
    for (i = 0; str[i] != '\0'; local.str[i] = str[i], i++);
    for (i = 0; s[i] != '\0'; local.str[len + i] = s[i], i++);
    local.str[local.len] = '\0';

    return local;
}

String String::operator+(char s) {
    String local(len + 1);
    for (long long i = 0; i < len; local.str[i] = str[i], i++);
    local.str[local.len - 1] = s;
    local.str[local.len] = '\0';

    return local;

}


template <class T> void Swap(T& a, T& b) {
    T c = a;
    a = b;
    b = c;
}
/*
class  cod {
public:
    bool* code;  // код кортежа
    int len_code;  // длина кода
    int* indexes; // массив индексов символов в алфавите, которые есть в кортеже
    int len_indexes;


    cod(int LEN_code = 0, int lot_of_indexes = 0);

    friend ostream& operator<<(ostream&, const cod&);

    void add_indexes(cod& b);

    void add_codes(cod& b);

    void add_indexes(int* ind, int n);
    /*void add_indexes(int ind[], int n) {
        int* local = new int[len_indexes + n];
        int i = 0;
        for (i; i < len_indexes; local[i] = indexes[i], i++);
        for (int j = 0; j < n; local[i] = ind[j], i++, j++);

        if (indexes)delete[] indexes;
        indexes = new int[len_indexes = i];
        for (int j = 0; j < i; j++) {
            indexes[j] = local[j];
        }
        delete[] local;
    }
    
    void add_indexes(int ind);

    //======================

    void add_codes(bool c);



    cod operator+(cod& b);

    cod& operator=(const cod &b);


};


cod:: cod(int LEN_code, int lot_of_indexes){
    code = new bool[len_code = LEN_code];
    indexes = new int[len_indexes = lot_of_indexes];
    for (int i = 0; i < len_code; code[i] = false, i++);
    for (int i = 0; i < lot_of_indexes; indexes[i] = 0, i++);
}


ostream& operator<<(ostream& out, const cod& a){
    for (int i = 0; i < a.len_code; out << a.code[i], i++);
    out << endl;
    for (int i = 0; i < a.len_indexes; out << a.indexes[i], i++);
    return out;
}

void cod :: add_indexes(cod& b){
    int* local = new int[len_indexes + b.len_indexes];
    int i = 0;
    for (i; i < len_indexes; local[i] = indexes[i], i++);
    for (int j = 0; j < b.len_indexes; local[i] = b.indexes[j], i++, j++);

    if (indexes)delete[] indexes;
    indexes = new int[len_indexes = i];
    for (int j = 0; j < i; j++) {
        indexes[j] = local[j];
    }
    delete[] local;
}

void cod :: add_codes(cod& b) {
    bool* local = new bool[len_code + b.len_code];
    int i = 0;
    for (i; i < len_code; local[i] = code[i], i++);
    for (int j = 0; j < b.len_code; local[i] = b.code[j], i++, j++);

    if (code)delete[] code;
    code = new bool[len_code = i];
    for (int j = 0; j < i; j++) {
        code[j] = local[j];
    }
    delete[] local;
}

void cod::add_indexes(int* ind, int n){
    int* local = new int[len_indexes + n];
    int i = 0;
    for (i; i < len_indexes; local[i] = indexes[i], i++);
    for (int j = 0; j < n; local[i] = ind[j], i++, j++);

    if (indexes)delete[] indexes;
    indexes = new int[len_indexes = i];
    for (i; i >= 0; i--) {
        indexes[i] = local[i];
    }
    delete[] local;
}
void cod::add_indexes(int ind){
    int* local = new int[len_indexes + 1];
    // прописать дописывание индексов для случая obj.add_indexes(int);
    int i = 0;
    for (i; i < len_indexes; local[i] = indexes[i], i++);
    local[i++] = ind;
    if (indexes)delete[] indexes;
    indexes = new int[++len_indexes];
    for (i; i >= 0; indexes[i] = local[i], i--);

    delete[] local;
}

//======================

void cod::add_codes(bool c){
    bool* local = new bool[len_code + 1];
    // прописать дописывание индексов для случая obj.add_indexes(int);
    int i = 0;
    for (i; i < len_code; local[i] = code[i], i++);
    local[i++] = c;
    if (code)delete[] code;
    code = new bool[++len_code];
    for (i; i >= 0; code[i] = local[i], i--);

    delete[] local;
}



cod cod::operator+(cod& b){
    cod local(len_code + b.len_code, len_indexes + b.len_indexes);
    int i = 0;
    for (i; i < len_code; local.code[i] = b.code[i], i++);
    for (int j = 0; j < b.len_code; local.code[i] = b.code[j], i++, j++);
    i = 0;
    for (i; i < len_indexes; local.indexes[i] = b.indexes[i], i++);
    for (int j = 0; j < b.len_indexes; local.indexes[i] = b.indexes[j], i++, j++);




    return local;
}

cod& cod::operator=(const cod &b){
    if (&b == this)return *this;

    if (code)delete[] code;
    if (indexes)delete[] indexes;
    //len_indexes = 0;
    //len_code = 0;

    indexes = new int[len_indexes = b.len_indexes];
    code = new bool[len_code = b.len_code];
    for (int i = 0; i < len_code; code[i] = b.code[i], i++);
    for (int i = 0; i < len_indexes; indexes[i] = b.indexes[i], i++);
    return *this;

}
*/
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


/*void Haffman(int local_len, int* counters, cod*& codesy, cod*& BASE_CODESY) {
    
    
    cod l_lena = codesy[local_len - 2];
    cod r_lena = codesy[local_len - 1];

    int l_lena_len_indexes = l_lena.len_indexes;
    int r_lena_len_indexes = r_lena.len_indexes;
    if(!r_lena_len_indexes)BASE_CODESY[local_len-1].add_codes(true);
    else
    for (int i = 0; i < l_lena.len_indexes; i++) {
        BASE_CODESY[l_lena.indexes[i]].add_codes(false);
    }
    if (!l_lena_len_indexes)BASE_CODESY[local_len - 2].add_codes(false);
    else
    for (int i = 0; i < r_lena.len_indexes; i++) {
        BASE_CODESY[r_lena.indexes[i]].add_codes(true);
    }

    if (local_len > 2) {
        counters[local_len - 2] += counters[local_len - 1];
        codesy[local_len - 2].add_indexes(codesy[local_len - 1]);
        int j = local_len - 2;
        int x = counters[j];
        cod cod_x = codesy[local_len - 2];
        while (j > 0) {
            if (counters[j - 1] < x)counters[j] = counters[j - 1];
            codesy[j] = codesy[j - 1];
            j--;
        }
        counters[j] = x;
        codesy[j] = cod_x;
        Haffman(local_len - 1, counters, codesy, BASE_CODESY);
        cout << j << endl;
    }



    /*

    String lefta = a[local_len - 2];
    String righta = a[local_len - 1];

    if (local_len > 2) {
        
        c[local_len - 2] += c[local_len - 1];
        a[local_len - 2] = a[local_len - 2] + a[local_len - 1];
        for (int i = 0; i < local_len - 1; i++) {
            for (int j = 0; j < local_len - 1 - i; j++) {
                if (c[j] < c[j + 1]) {
                    Swap(c[], c[j + 1]);
                    Swap(a[j], a[j + 1]);
                }
            }
        }

        Haffman(local_len - 1, a, BASE_ALPHABET, c, codesy);
    }
    
    for (int i = 0; i < BASE_ALPHABET.Len(); i++) {
        if (lefta.find_symbol(BASE_ALPHABET[i]) != -1) {
            codesy[BASE_ALPHABET[i]].n++;
            codesy[BASE_ALPHABET[i]].code = (bool*)malloc(codesy[BASE_ALPHABET[i]].n * sizeof(bool));
            codesy[BASE_ALPHABET[i]].code[codesy[BASE_ALPHABET[i]].n - 1] = true;
        }
        if (righta.find_symbol(BASE_ALPHABET[i]) != -1) {
            codesy[BASE_ALPHABET[i]].n++;
            codesy[BASE_ALPHABET[i]].code = (bool*)malloc(codesy[BASE_ALPHABET[i]].n * sizeof(bool));
            codesy[BASE_ALPHABET[i]].code[codesy[BASE_ALPHABET[i]].n - 1] = false;
        }
    }

    
}
*/

typedef struct COD {
    int code;   // битовый код  // max 010...0101       32 бита(4 байта)
    char lena; // длина кода    // max - 128
    int counter;

    friend ostream& operator << (ostream& out, COD& a) {
        //out << " lena " << int(a.lena) << " counter " << a.counter << " code ";
        for (int i = 0; i < a.lena; out << ((a.code & (1<<(a.lena-1-i)))!=0), i++);
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

    ifstream file_in("D://C_projs_Visual_studio_2022//2_Kurs_1_semestr//Kodirovanie//Haffman_1//Haffman_1//file.txt");
    //file_in.open("D:/C_projs_Visual_studio_2022/2_Kurs_1_semestr/Kodirovanie/Haffman_1/Haffman_1/file.txt", "r");
    bool code_or_decode;
    file_in >> code_or_decode;
    //cout << int(code_or_decode) << endl;
    //return 0;
    
    if (!code_or_decode) {
        String a;
        //cin >> a;
        char t;
        while (file_in.get(t)) {
            //t = file_in.get();
            a = a + t;
        }
        
        file_in.close();
        //cout << a << endl;
        //return 0;
        /*int* maket1 = new int[4];
        for (int i = 0; i < 4; cout<<(maket1[i] = rand() % 10), i++);
        int* maket2 = new int[6];
        cout << endl;
        for (int i = 0; i < 6; cout<<(maket2[i] = rand()%10), i++);

        cod c1;
        c1.add_indexes(maket1, 4);
        cout << c1 << endl;
        c1.add_indexes(maket2, 6);
        cout << c1<<endl;

        delete[] maket1;
        delete[] maket2;
        return 0;
        */
        //cod* codes = new cod[256];

        COD* codes = new COD[256];          /// создание таблицы кодов на всю ASCII
        for (int i = 0; i < 256; codes[i].counter = codes[i].lena = codes[i].code = 0, i++);
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


        ofstream file_out("D://C_projs_Visual_studio_2022//2_Kurs_1_semestr//Kodirovanie//Haffman_1//Haffman_1//file.txt");
        file_out << '1';
        
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
            file_out << endl;
        }
        char crypt_out = 0;
        counter8 = 0;
        char this_lena = 0;
        for (long long i = 0; i < a.Len(); i++) {
            for (int j = 0; j < k; j++) {
                if (alphabet[j] == a[i]){
                    this_lena = codes[j].lena;
                    while (counter8 < 8){
                        if (this_lena) {
                            crypt_out = (crypt_out << 1) | ((codes[j].code >> this_lena-1) & 1);
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
                    ////int char_counter = 0;
                    ///for (char_counter; char_counter < this_lena / 8; char_counter++)file_out << (codes[j].code & 255);
                    
                    // продумать заталкивание всех кодов в чары, шоб сжало, а не просто выводить все коды по чарам
                    //char this_lena = (codes[j].lena % 8) ? codes[j].lena / 8 + 1 : codes[j].lena / 8;
                    //if(codes[j].lena >=8)
                }
            }
        }
                    
                    ///int chars_code = (codes[j].lena % 8) ? codes[j].lena / 8 + 1 : codes[j].lena / 8;
                    ///for (int l = 0; l < chars_code; l++)file_out << crypts[j][l];
                
            
        
        file_out.close();

        /*cout << endl;
        for (int i = 0; i < k; i++) {
            cout << alphabet[i] << ": ";
            cout << codes[i];
            int l = ((codes[i].lena % 8) ? codes[i].lena / 8 + 1 : codes[i].lena / 8);
            for (int j = 0; j < l; j++)cout << crypts[i][j];
            cout << '.'<<endl;
        }
        */

        for (int i = 0; i < k; delete[] crypts[i], i++);
        delete[] crypts;
        delete[] codes;
    }
    




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
