#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
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

#include <vector>

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
            position=0; // réinitialiser la position pour le prochain mot
            if(remp != "")
                *it = remp;               // remplacement dans le vecteur
        }
    }

    /*if(remp != ""){                       // réécriture du fichier
        ofstream out(nom_fichier);
        for(vector<string>::iterator it = mots.begin(); it != mots.end(); ++it)
            out << *it << " ";
    }
    */

    return nb;
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
    cout << "entrez le mot a chercher: ";
    cin >> mot;
    cout<<"entre le mot a remplacer (laisser vide si pas de remplacement): ";
    string remp;
    cin >> remp;
    auto start = high_resolution_clock::now();
    int nb = chercher_mot_vector(nom_fichier, mot, remp);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if(nb >= 0)
        cout << "le mot " << mot << " apparait " << nb << " fois dans le fichier " << nom_fichier << endl;
    cout << "temps d'execution: " << duration.count() << " microsecondes" << endl;
    return 0;

}
