#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct RGB{float red; float green; float blue;};

class Rastorize{
    private:
        const int row;      //height
        const int col;      //width
      	RGB ** arr;         //Dynamic rastor array of RGB structs, a pointer to a pointer of array.
    public:
        //constructor to allocate memory for the rastor array
        Rastorize(int w, int h) : col(w), row(h) {
            arr = new RGB *[row];  //remember, arr holds a pointer. this is an array of pointers.
            for(int i=0; i < col; i++){ //pointers are just variables that hold memory addresses.
                arr[i] = new RGB[col];//each array element POINTS to another array, holding the mem address of the array.
            }

	    for (int i=0; i < row; i++){
	    	for (int j=0; j < col; j++){
			arr[i][j].red = 0.0; arr[i][j].green = 0.0; arr[i][j].green = 0.0; 
		}
	    }
        }
        ~Rastorize(){
		for (int i=0;i < row; i++){
		delete[] arr[i]; 
		}
		delete[] arr;
	}
        
        void setRastorArray(){
           // int c = ((col & 0x08) == 0) ^ ((row & 0x08) ==0);
            for(int i=0; i < row; i++){
                for (int j=0; j < col; j++){
		    int c = (((j & 0x08) == 0) ^ ((i & 0x08) == 0));
                    arr[i][j].red = static_cast<float>(c);
                    arr[i][j].green = static_cast<float>(c & 0x00);
                    arr[i][j].blue = static_cast<float>(c & 0x11);
                    
                }
            }
        }
        
        void createRastorFile(string name){
            ofstream txt;
            txt.open(name.c_str());
            if (txt.is_open()){
		    txt <<"P3" << endl;
		    txt << row << " " << col << endl;
		    txt << 255;
                for(int i = row-1; i >= 0; i--){
                  	txt << endl; 
                    for(int j = 0; j < col; j++){
                        int r = (int)floor(arr[i][j].red * 255);
                        int g = (int)floor(arr[i][j].green * 255);
                        int b = (int)floor(arr[i][j].blue * 255);
                        txt << r << " " << g << " " << b << " ";
	    }
            }
        }
            txt.close();
   }
        
        
};

int main(int argc, char *argv[])
{
    //ppm width(column) by height(row). array[h][w]. C++ arrays are row based.
    int w = atoi(argv[1]);//column(width)
    int h = atoi(argv[2]);//row (height)
    string n = argv[3];
    
    Rastorize rastor(w,h);
    rastor.setRastorArray();
    rastor.createRastorFile(n);

    return 0;
}

