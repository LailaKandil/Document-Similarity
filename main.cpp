#include<iostream>
#include<vector>
#include<fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
class StringSet{
private:
    vector <string> StringStorage;
    bool OpenFile(string myfile, ifstream& TheFile){
        TheFile.open(myfile);
        if(TheFile.is_open()){
            cout<<"\nThis File Already Exists\n\n";
            return true;
        }
        else{
            cout<<"\nThis file does not exist\n\n";
            return false;
        }
    }

    bool existsInSet(string myfile){
        for(int i = 0; i< StringStorage.size(); i++){
            if(myfile == StringStorage[i]) return true;
        }
        return false;
    }

public:
    friend ostream& operator <<(ostream& out, const StringSet& storage);
    StringSet operator+ (const StringSet& anotherStringSet);
    StringSet operator* (const StringSet& anotherStringSet);
    StringSet& operator= (const StringSet& anotherStringSet);

    StringSet(){

    }
    StringSet(string fileName, bool justThere){
        ifstream TheFile;
        if(!OpenFile(fileName, TheFile))
            return;
        string line;
        string cont;
        while(!TheFile.eof()){
            getline(TheFile, line);
            for (int i=0; i < line.size(); i++) {
                line[i]=tolower(line[i]);
                if(ispunct(line[i]))    line[i] = ' ';
            }
            stringstream check1(line);

            string intermediate;

            // Tokenizing w.r.t. space ' '
            while(getline(check1, intermediate, ' '))
            {
                if(intermediate == "") continue;
                if(!existsInSet(intermediate))
                    StringStorage.push_back(intermediate);
            }
        }

        TheFile.close();
    }

    StringSet(string line){
        for (int i=0; i < line.size(); i++) {
            line[i]=tolower(line[i]);
            if(ispunct(line[i]))    line[i] = ' ';
        }

        stringstream check1(line);

        string intermediate;

        // Tokenizing w.r.t. space ' '
        while(getline(check1, intermediate, ' '))
        {
            if(intermediate == "") continue;
            if(!existsInSet(intermediate))
                StringStorage.push_back(intermediate);
        }
    }

    void AddString(){
        cout << "Enter string to be added" << endl;
        string newString;
        cin >> newString;
        AddString(newString);
    }
    void AddString(string s){
        if(!existsInSet(s))
            StringStorage.push_back(s);
    }

    void RemoveString(){
        cout << "Enter string to be removed" << endl;
        string newString;
        cin >> newString;
        RemoveString(newString);
    }
    void RemoveString(string s) {
        std::remove(StringStorage.begin(), StringStorage.end(), s);
    }

    void clear(){
        StringStorage.clear();
    }

    int size(){
        return StringStorage.size();
    }

    double binaryCosineCoefficient(StringSet& anotherStringSet){
        StringSet intersection;
        intersection = (*this) * anotherStringSet;
        int countIntersection = intersection.size();
        double denominator = sqrt(this->size()) * sqrt(anotherStringSet.size());
        return countIntersection/denominator;
    }
};

StringSet& StringSet:: operator= (const StringSet& anotherStringSet){
    StringStorage = anotherStringSet.StringStorage;
}

StringSet StringSet::operator+ (const StringSet& anotherStringSet){
    StringSet unionStringSet;
    vector<string> StringStorage1 = this->StringStorage;
    vector<string> StringStorage2 = anotherStringSet.StringStorage;
    for(int i = 0; i < StringStorage1.size(); i++){
        unionStringSet.AddString(StringStorage1[i]);
    }
    for(int i = 0; i < StringStorage2.size(); i++){
        if(!this->existsInSet(StringStorage2[i]))
            unionStringSet.AddString(StringStorage2[i]);
    }
    return unionStringSet;
}

StringSet StringSet::operator* (const StringSet& anotherStringSet){
    StringSet intersectionStringSet;
    vector<string> StringStorage1 = this->StringStorage;
    vector<string> StringStorage2 = anotherStringSet.StringStorage;
    for(int i = 0; i < StringStorage2.size(); i++){
        if(this->existsInSet(StringStorage2[i]))
            intersectionStringSet.AddString(StringStorage2[i]);
    }
    return intersectionStringSet;
}

ostream& operator<<(ostream& out, const StringSet& storage) {
    for(int i=0;i<storage.StringStorage.size();i++){
        out<<storage.StringStorage[i] << endl;
    }
    return out ;
}

int main(){
    StringSet stringSet1("StringSet.txt", false);
    StringSet stringSet2("Chocolate is perfect");
    cout << stringSet1 + stringSet2 << endl;
    cout << " =----------------------------------------------------------------" << endl;
    cout << stringSet1 * stringSet2<< endl;
    cout << " =----------------------------------------------------------------" << endl;
    cout << stringSet1.binaryCosineCoefficient(stringSet2)<< endl;
}
