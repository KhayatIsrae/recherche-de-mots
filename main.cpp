#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std::chrono;
using namespace std;

int comparer_chaines(string ch1,string ch2){
    string cs,cl,res;
    if(ch1.length()<ch2.length()){
        cs=ch1;
        cl=ch2;
    }else{
        cs=ch2;
        cl=ch1;
    }
    int i,j;
    j=0;
    for(i=0;i<cs.length();i++){
        while((cl.length()-j)>=cs.length()-i){
            if(cl[j]==cs[i]){
                res+=cl[j];
                j++;
                break;
            }
            j++;
        }
    }
    if(res==cs)
        return 1;
    return 0;
}

//chercher un mot complet dans le fichier
int chercher_mot(string nom_fichier, string mot){
    ifstream f(nom_fichier);
    if(!f){
        cout << "Erreur : impossible d'ouvrir " << nom_fichier << endl;
        return -1;
    }
    string courant;
    int nb = 0;
    while(f >> courant){
        if(courant == mot)
            nb++;
    }
    f.close();
    return nb;
}
 //chercher un mot dans le fichier en utilisant la fonction find(sous chaines aussi)
int chercher_mot_find(string nom_fichier, string mot)
{
    ifstream f(nom_fichier);

    if (!f)
    {
        cout << "Erreur : impossible d'ouvrir " << nom_fichier << endl;
        return -1;
    }

    // Lire tout le fichier
    string texte(
        (istreambuf_iterator<char>(f)),
        istreambuf_iterator<char>()
    );

    f.close();

    int nb = 0;
    size_t position = 0;

    while ((position = texte.find(mot, position)) != string::npos)
    {
        nb++;

        // Avancer après l'occurrence trouvée
        position += mot.length();
    }

    return nb;
}

//chercher un mot en utilisant les vecters, on peut aussi remplacer le mot par un autre
int chercher_mot_vector(string nom_fichier, string mot, string remp="")
{
    ifstream f(nom_fichier);
    if(!f){
        cout << "Erreur : impossible d'ouvrir " << nom_fichier << endl;
        return -1;
    }

    vector<string> mots;
    string courant;
    while(f >> courant)
        mots.push_back(courant);        // on stocke chaque mot
    f.close();

    int nb = 0;
    size_t position = 0;
    for(vector<string>::iterator it = mots.begin(); it != mots.end(); ++it){
        if((position = (*it).find(mot, position)) != string::npos){
            nb++;
            if(remp != "")
                *it = remp;               // remplacement dans le vecteur
        }
        position=0;
    }

    if(remp != ""){                       // réécriture du fichier
        ofstream out(nom_fichier);
        for(vector<string>::iterator it = mots.begin(); it != mots.end(); ++it)
            out << *it << " ";
    }
    

    return nb;
}

string ont_ss_ch_commune(string mot1, string mot2){
    string res;                                   // meilleure sous-chaîne trouvée
    for(size_t i = 0; i < mot1.length(); i++){
        for(size_t j = 0; j < mot2.length(); j++){
            size_t k = 0;                         // longueur de la suite commune
            while(i + k < mot1.length() && j + k < mot2.length()
                  && mot1[i + k] == mot2[j + k])
                k++;
            if(k > res.length())
                res = mot1.substr(i, k);          // nouvelle plus longue
        }
    }
    return res;
}

vector<string> plus_longue_ss_fichier(string nom_fichier){
    ifstream f(nom_fichier);
    if(!f){
        cout << "Erreur : impossible d'ouvrir " << nom_fichier << endl;
        return vector<string>();
    }
    vector<string> fichier,mots;
    vector<string> res(3); //[0]=la sous chaine/[1]=mot1/[2]=mot2
    string courant;
    while(f >> courant)
        fichier.push_back(courant);        // on stocke chaque mot
    f.close();

    for(size_t i = 0; i < fichier.size(); i++){
        if(find(mots.begin(), mots.end(),fichier[i]) != mots.end())
            continue;                       // on a déjà traité ce mot
        else{
            mots.push_back(fichier[i]);
            for(size_t j = i + 1; j < fichier.size(); j++){
                if(fichier[i] == fichier[j])
                    continue;
                string ss = ont_ss_ch_commune(fichier[i], fichier[j]);
                if(ss.length() > res[0].length()){
                    res[0] = ss;
                    res[1]= fichier[i];
                    res[2]= fichier[j];
                }
            }
        }
    }
    return res;
}




int main()
{
    /*
    string ch1,ch2;
    cout << "entrez la premiere chaine: ";
    cin >> ch1;
    cout << "entrez la deuxieme chaine: ";
    cin >> ch2;

    auto start = high_resolution_clock::now();
    int res = comparer_chaines(ch1,ch2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if(res)
        cout << ch1 << " contient " << ch2 << endl;
    else
        cout << ch1 << " ne contient pas " << ch2 << endl;
    cout << "temps d'execution: " << duration.count() << " microsecondes" << endl;
    return 0;
*/
    string nom_fichier, mot;
    cout << "entrez le nom du fichier: ";
    cin >> nom_fichier;
    /*cout << "entrez le mot a chercher: ";
    cin >> mot;
    cout<<"entre le mot a remplacer (laisser vide si pas de remplacement): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   // vide le reste de la ligne
    string remp;
    getline(cin, remp);
    auto start = high_resolution_clock::now();
    int nb = chercher_mot_vector(nom_fichier, mot, remp);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if(nb >= 0)
        cout << "le mot " << mot << " apparait " << nb << " fois dans le fichier " << nom_fichier << endl;
    cout << "temps d'execution: " << duration.count() << " microsecondes" << endl;
    */
    auto start = high_resolution_clock::now();
    vector<string> res = plus_longue_ss_fichier(nom_fichier);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (res.size() == 3) {
        cout << "Sous-chaine commune : " << res[0] << endl;
        cout << "Premier mot : " << res[1] << endl;
        cout << "Deuxieme mot : " << res[2] << endl;
    }
    cout << "temps d'execution: " << duration.count() << " microsecondes" << endl;
    return 0;
}
