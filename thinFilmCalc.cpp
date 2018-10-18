/**
*email: ambios@me.com
*@date 11-Dec-2014 updated 3-2018
*
*@description  thinFilmCalc calculates the thickness of a thin film assuming it's deposited on Silicon. The program asks the user to select a film from a menu and identify the number of maxima in the spectra. The program uses this information and material data it gets from the "films.txt" file to calculate the thickness of the film using a highly simplistic thin film equation. Implementation of a more sophisticated model is left to others.

*@author Patrick O'Hara
*@version 1.0.1
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

class Thin_film  {
public:
    //default constructor   
    Thin_film();
    
    /**
        overloaded constructor that constructs thin film class for vector
        @param mat Material of thin film
        @param index Index of refraction of thin film
    */
    Thin_film(string mat, double index);
        
    /**
        overloaded constructor that constructs a thin film
        @param mat Name of material of thin film
        @param spectralRange Spectral range of spectra
        @param index Index of refraction of thin film at 632.8nm
        @param numberOfMaxima The number of maxima with spectral range
    */
    Thin_film(string mat, double index, double spectralRange, double numberOfMaxima);
        
    /**
        returns the material of the thin film
        @param mat Material of thin film
    */
    string getMat() const;
    
    /**
        returns spectral range
        @param spectralRange is the spectral range over which
        the measurement is made
    */
    int getspectralRange() const;
    
    /**
        returns index of refraction
        @param index is the real part of the index of refraction
        of the thin film being measured
    */
    double getIndex() const;
    
    /**
        returns approximate thin film thickness assuming Silicon substrate and 
        normal incidence of illumination in accordance with thin film equation
        d = m * delta lambda / 2(n^2 - 1)^1/2
        where:
            d = film thickness in nm
            delta lambda = spectral bandwidth over which the spectra was acquired in nm
            n = real part of the refractive index of the thin film
            m = number of maxima in the spectral bandwidth
        @param getThickness is the calculated thin film thickness
    */
    double getThickness() const;
    
    /**
        changes the material of the thin film
        @param setMat sets the material name of the thin film
    */
    void setMat(string newMat);
    
    /**
        changes the spectral range over which the calculation of
        film thickness is made
        @param setspetralRange sets the spectral range
    */
    void setspectralRange(double newSpectralRange);
    
    /**
        changes the index of refraction
        @param setIndex sets the index of refraction
    */
    void setIndex(double newIndex);
    
    /**
        changes the number of maxima the spectral range
        @param setMaxima sets the maxima
    */
    void setnumberOfMaxima(double newNumberOfMaxima);

    //prints the thin film name and thickness;
    void print() const;
    
    //reads data from user
    void read();
    
    // Read the thin fim information from a file stream
    void read(ifstream& fin);
    
    //reads stream from file - overloaded function
    void readFilm(ifstream& fin);
    
    //prints material name and index to file
    void writeFile(ofstream& fout) const;
	
	/**
	    writes measurement results to file
	    @param takes input file named fileName
    */
	void writeMeasResultFile(ofstream& fout, string fileName)  const;
	
	//prints mat & index of library films
	void printLib() const;
    
private:
    //Instance variables
    string mat;
    double spectralRange;
    double index;
    double numberOfMaxima;
};

//formatting constants
const int MATERIAL_WIDTH = 30;
const int INDEX_WIDTH = 10;
const int MAXIMA_WIDTH = 15;
const int THICKNESS_WIDTH = 20;
    
//default constructor
Thin_film::Thin_film()  {
    spectralRange = 0.0;
    index = 0.0;
    numberOfMaxima = 0.0;
}
    
//overloaded constructor
Thin_film::Thin_film(string mat, double index)  {
    setMat(mat);
    setIndex(index);
}
        
string Thin_film::getMat() const {
    return mat;
}
    
int Thin_film::getspectralRange() const {
    return spectralRange;
}
    
double Thin_film::getIndex() const {
    return index;
}

double Thin_film::getThickness() const  {
    return (numberOfMaxima * spectralRange) / 2.0 *
    sqrt(double ((index * index) - 1));
}

void Thin_film::setMat(string newMat)   {
    mat = newMat;
}

void Thin_film::setspectralRange(double newSpectralRange)  {
    if (newSpectralRange < 0)  {
        spectralRange = 0.0;
    }
        else {
            spectralRange = newSpectralRange;
        }
}

void Thin_film::setIndex(double newIndex)  {
    if (newIndex < 0)  {
        index = 0.0;
    }
        else  {
            index = newIndex;	
        }
}

void Thin_film::setnumberOfMaxima(double newMaxima) {
    if (newMaxima < 0)  {
        numberOfMaxima = 0.0;
    }
        else {
            numberOfMaxima = newMaxima;  
        }
}

void Thin_film::print()   const  {
    cout.setf(ios::fixed);
    cout << setw(MATERIAL_WIDTH) << left << mat
        << setw(INDEX_WIDTH) << setprecision(2) << right << index
        << setw(MAXIMA_WIDTH) << setprecision(2) << numberOfMaxima
        << setw(THICKNESS_WIDTH) << setprecision(1) << getThickness() << endl;
}

void Thin_film::printLib() const  {
    cout.setf(ios::fixed);
    cout << setw(MATERIAL_WIDTH) << left << mat
        << setw(INDEX_WIDTH) << setprecision(2) << right << index << endl;
}

void Thin_film::read()  {
    cout << "Enter the name of the film: ";
    cin >>ws;
    getline(cin, mat);
    cout << "Enter the refractive index of the film: ";
    cin >> index;
    cout << "Enter the spectral bandwidth over which the spectra was acquired in nm: ";
    cin >> spectralRange;
    cout << "Enter the number of maxima within the spectral range: ";
    cin >> numberOfMaxima;
}

void Thin_film::read(ifstream& fin) {
    fin >> ws;
    getline(fin, mat);
    fin >> index;
}
    
void Thin_film::readFilm(ifstream& fin) {
    fin >> ws;
    getline(fin, mat);
    fin >> index >> spectralRange >> numberOfMaxima;
}

void Thin_film::writeFile(ofstream& fout) const {
    fout << mat << endl << index << endl;
}

void Thin_film::writeMeasResultFile(ofstream& fout, string fileName)  const  {
    cout << "Would you like to save this measurement result (y/n)? ";
    string saveMeasurement = "n";
    cin >> saveMeasurement;
    if (saveMeasurement == "y")  {
        ofstream fout;
        fout.open(fileName, ios::app);
        if (fout.fail()) {
            cout << "Output file failed to open.\n";
            exit(-1);
        }
        fout.setf(ios::fixed);
        fout << setw(MATERIAL_WIDTH) << setprecision(2) << left << mat
            << setw(INDEX_WIDTH) << setprecision(2) << right << index
            << setw(MAXIMA_WIDTH) << setprecision(1) << getThickness()
            << setprecision(1) << endl;
    }
}

/**
adds material to films.txt file
*/
void addMaterial();

/**
    prints film library to terminal
    @param materialList The list of Thin Film objects
*/
void listFilms(vector<Thin_film>& materialList);
    
/**
    deletes a film from the film file
    @param materialList The list of Thin Film objects
*/
void deleteFilm(vector<Thin_film>& materialList);

/**
    gets the film "vector index" (not refractive index)
    @param materialList The list of films in the library
*/
int getFilmIndex(vector<Thin_film>& materialList);

/**
    Loads the film data from the specified file name and returns
    the data in a vector of Thin Film objects
    @param list The vector of Thin Film objects
    @param fileName The name of the file from which to read
*/
void loadData(vector<Thin_film>& materialList, string fileName);

/**
    Calculates film thickness from arbitrary film or from library
    @param list of the vector of the Thin Film objects
*/
void calculateThickness(vector<Thin_film>& materialList);

/**
    Writes thin film data to output file
    @param materialList The name of the file to which to write
*/
void saveData(const vector<Thin_film>& materialList, string filename);

//menu items
const int CAL_THICKNESS = 1;
const int MATERIAL_LIST = 2;
const int ADD_MATERIAL = 3;
const int DEL_MATERIAL = 4;
const int EXIT = 0;

int main()  {
    //load thin films on start up
    vector<Thin_film> materialList;
    loadData(materialList, "films.txt");
        
    cout << endl <<"Thin Film Calculator\n";
    int choice = 1;
    while (choice != 0) {
    cout << "\nPlease choose one of the following operations: \n"
        << EXIT << ". Exit the program\n"
        << CAL_THICKNESS << ". Calculate thickness of arbitrary film\n"
        << MATERIAL_LIST << ". List the materials in the thin film library\n"
        << ADD_MATERIAL << ". Add a new thin film to the library\n"
        << DEL_MATERIAL << ". Delete a thin film from the library\n"
        << "Choice (0-4): ";
        cin >> choice;
    if (choice == CAL_THICKNESS) {
        calculateThickness(materialList);
    } else if (choice == MATERIAL_LIST) {
        listFilms(materialList);
    } else if (choice == ADD_MATERIAL) {
        addMaterial();
    } else if (choice == DEL_MATERIAL)  {
		deleteFilm(materialList);
    }
}
cout << "\nGoodbye!\n";

return 0;
}

void calculateThickness(vector<Thin_film>& materialList)    {
    string repeat = "y";
        while(repeat =="y") {
            cout << "Read material data from library? (y/n): ";
            string libFilm = "y";
            cin >> libFilm;
            if (libFilm == "y") {
                int pos = getFilmIndex(materialList);
                Thin_film film = materialList[pos];
                materialList.push_back(film);
                cout << "Enter the spectral bandwidth over which the spectra was acquired in nm: ";
                double newSpectralRange;
                cin >> newSpectralRange;
                film.setspectralRange(newSpectralRange);
                cout << "Enter the number of maxima within the spectral range: ";
                double newnumberOfMaxima;
                cin >> newnumberOfMaxima;
                film.setnumberOfMaxima(newnumberOfMaxima);
                cout << endl;
                cout << setw(MATERIAL_WIDTH) << left << "Material"
                    << setw(INDEX_WIDTH) << right << "Index"
                    << setw(MAXIMA_WIDTH) << right << "# of maxima"
                    << setw(THICKNESS_WIDTH) << "Thickness (nm)" << endl;
                film.print();
                ofstream fout;
                film.writeMeasResultFile(fout, "data.txt");
            }
              else  {
                  Thin_film unknown;
                  unknown.read();
                  materialList.push_back(unknown);
                  cout << endl;
                  cout << setw(MATERIAL_WIDTH) << left << "Material"
                    << setw(INDEX_WIDTH) << right << "Index"
                    << setw(MAXIMA_WIDTH) << right << "# of maxima"
                    << setw(THICKNESS_WIDTH) << "Thickness (nm)" << endl;
                  unknown.print();
                  cout << "Save material and index of this film (y/n)? ";
                  string saveMatIndex = "y";
                  cin >> saveMatIndex;
                  if (saveMatIndex == "y")  {
                      saveData(materialList, "films.txt");
                  }
              ofstream fout;
              unknown.writeMeasResultFile(fout, "data.txt");
              }
        cout << "Enter another thin film? (y/n): ";
        cin >> repeat;
    }
}

void addMaterial()  {
	Thin_film unknown;
    cout << "Enter the name of the film: ";
    cin >>ws;
	string mat;
    getline(cin, mat);
	unknown.setMat(mat);
    cout << "Enter the refractive index of the film: ";
	double index = 0;
    cin >> index;
	unknown.setIndex(index);
    cout << endl;
    cout << setw(MATERIAL_WIDTH) << left << "Material"
         << setw(INDEX_WIDTH) << right << "Index" << endl
         << setw(MATERIAL_WIDTH) << left << mat
         << setw(INDEX_WIDTH) << right << index <<endl;
    cout << endl << "Save material and index of this film (y/n)? ";
    string saveMatIndex = "n";
    cin >> saveMatIndex;
    if (saveMatIndex == "y")  {
        ofstream fout("films.txt", ios::app);
        if (fout.fail()) {
            cout << "Output file failed to open.\n";
            exit(-1);
        }
        fout << mat << endl << index << endl;
        fout.close();
    }
}

void deleteFilm(vector<Thin_film>& materialList)  {
	Thin_film film;
	int pos = getFilmIndex(materialList);
	    for (unsigned i = pos; i < materialList.size() - 1; i++) {
        materialList[i] = materialList[i + 1];
    }
    materialList.pop_back();
	saveData(materialList, "films.txt");
}

void loadData(vector<Thin_film>& materialList, string fileName) {
    Thin_film film;

    ifstream fin(fileName.c_str());
    if (fin.fail()) {
        cout << "File " << fileName << " failed to open.\n";
        exit(1);
    }

    while(fin.good()) {
        film.read(fin);
        if (fin.good()) {
            materialList.push_back(film);
        }
    }

    fin.close();
}
    
void readFile(vector<Thin_film>& materialList, string films)  {
    ifstream fin(films.c_str());
    if (fin.fail()) {
        cout << "Input file failed to open\n";
        exit(-1);
    }
    while (fin.good()) {
        Thin_film temp;
        temp.readFilm(fin);
        if (fin.good()) {
            materialList.push_back(temp);
        }
    }
    fin.close();
}
    
void listFilms(vector<Thin_film>& materialList)   {
    cout << "\nTHIN FILM LIBRARY\n";
    cout << setw(MATERIAL_WIDTH) << left << "Material"
         << setw(INDEX_WIDTH + 4) << right << "Index" << endl;
    for (unsigned num = 0; num < materialList.size(); num++) {
        cout << setw(2) << right << (num + 1) << " ";
        materialList[num].printLib();
    }
}

void saveData(const vector<Thin_film>& materialList, string fileName) {
    ofstream fout(fileName.c_str());
    if (fout.fail()) {
        cout << "Output file failed to open.\n";
        exit(-1);
    }

    for (unsigned i = 0; i < materialList.size(); i++) {
        materialList[i].writeFile(fout);
    }

    fout.close();
}

int getFilmIndex(vector<Thin_film>& materialList)   {
    listFilms(materialList);
    cout << "Enter the number preceeding the name of the thin film material: ";
                int pos = 0;
                cin >> pos;
                return pos - 1;
}
