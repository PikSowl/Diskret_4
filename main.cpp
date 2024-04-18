#include <iostream>
#include<vector>
#include<string>
#include<map>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::ifstream;
using std::ofstream;


vector<int> encode(const string &ori){
    map<string,int> dict;
    int dictSize = 32;
    for(int i=0;i<26;++i)
        dict[string(1,i + 97)] = i;
    dict[string(1,32)] = 26;
    dict[string(1,36)] = 27;
    dict[string(1,44)] = 28;
    dict[string(1,46)] = 29;
    dict[string(1,58)] = 30;
    dict[string(1,59)] = 31;

    /*
    int dictSize = 256;
    for(int i=0;i<dictSize;++i)
        dict[string(1,i)] = i;
    */
    vector<int> res;

    string s;
    for(char z : ori){
        if(dict.count(s+z)) s += z;
        else{
            res.emplace_back(dict[s]);
            dict[s+z] = dictSize++;
            s = z;
        }
    }
    if(!s.empty()) res.emplace_back(dict[s]);

    //for (const auto& [st, in] : dict)
    //    cout << st << ":" << in << endl;

    return res;
}

string decode(const vector<int> &v){
    map<int,string> inv_dict;
    int dictSize = 32;
    for(int i=0;i<26;++i)
        inv_dict[i] = string(1, i + 97);
    inv_dict[26] = string(1, 32);
    inv_dict[27] = string(1, 36);
    inv_dict[28] = string(1, 44);
    inv_dict[29] = string(1, 46);
    inv_dict[30] = string(1, 58);
    inv_dict[31] = string(1, 59);

    string s, entry, res;
    s = res = inv_dict[v[0]];
    for(size_t i = 1; i<v.size(); ++i){
        int k = v[i];
        if(inv_dict.count(k))
            entry = inv_dict[k];
        else if(k==dictSize)
            entry = s+s[0];
        res += entry;
        inv_dict[dictSize++] = s + entry[0];
        s = entry;
    }

    for (const auto& [in, st] : inv_dict)
        cout << st << ":" << in << endl;

    cout << res;

    return res;
}

int main(){
    ifstream file(R"(C:\Precols\Code\C++\Diskret_4\text.txt)"); //  change to text file path
    string str;
    getline(file, str);
    vector<int> output = encode(str);

    ofstream out;
    out.open("LZW_bit.txt");
    if (out.is_open())
    {
        for (int an : output) {
            string booly;
            for (int i = 0; 8 > i; i++){
                if (0 == an%2)booly.insert(0,"0");
                else booly.insert(0,"1");
                an/=2;
            }
            out << booly << " ";
        }
    }
    out.close();
    out.open("LZW.txt");
    if (out.is_open())
    {
        for (int an : output) {
            out << an << " ";
        }
        out << endl << endl << "byte number: " << output.size();
    }
    out.close();
    out.open("reverseLZW.txt");
    out << decode(output);
    out.close();
}
