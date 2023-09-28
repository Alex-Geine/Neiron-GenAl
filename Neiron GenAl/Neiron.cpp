#include "Neiron.h"



Neiron::Neiron(int layers, int* neironsCount) :
    layers(layers),
    neironsCount(neironsCount) {

  

    //заполнение массива пороговых коэффициентов

    koef = new double* [layers];
    for (int i = 0; i < layers; i++) {
        koef[i] = new double[neironsCount[i]];
        for (int j = 0; j < neironsCount[i]; j++)
            koef[i][j] = -1 + 2 * (double)rand() / RAND_MAX;
    }

    //заполнение массива весов

    w = new double** [layers];
    for (int i = 0; i < layers; i++) {
        w[i] = new double* [neironsCount[i]];

        for (int j = 0; j < neironsCount[i]; j++) {
            int xSize = 3;
            if (i != 0)
                xSize = neironsCount[i - 1];

            w[i][j] = new double[xSize];

            for (int k = 0; k < xSize; k++)
                w[i][j][k] = (double)rand() / RAND_MAX;
        }

    }

    //заполнение массива иксов

    x = new double* [layers + 1];
    x[0] = new double[3];
    for (int i = 1; i <= layers; i++) {
        x[i] = new double[neironsCount[i - 1]];
    }
}


//функция активации
double Neiron::Function(double S) {
    return (1 / (1 + exp(-B * S)));
}

//перебор слоя
void Neiron::LayerFunc(int layer) {
    int xSize = 3;
    if (layer != 0)
        xSize = neironsCount[layer - 1];

    for (int j = 0; j < neironsCount[layer]; j++) {
        double sum = 0;

        for (int i = 0; i < xSize; i++)
            sum += w[layer][j][i] * x[layer][i] - koef[layer][j];
        x[layer + 1][j] = Function(sum);
    }
}


//вывод результатов работы сети
double Neiron::Work(double x1, double x2, double x3) {
    x[0][0] = x1;
    x[0][1] = x2;
    x[0][2] = x3;

    for (int i = 0; i < layers; i++)
        LayerFunc(i);

    return x[layers][0];
}

//деструктор
Neiron::~Neiron() {


    for (int i = 0; i < layers; i++)
        delete[] koef[i];

    delete[] koef;

    for (int i = 0; i < layers; i++) {
        for (int j = 0; j < neironsCount[i]; j++) {
            int xSize = 3;
            if (i != 0)
                xSize = neironsCount[i - 1];

            delete[] w[i][j];
        }
        delete[] w[i];
    }

    delete[] w;

    for (int i = 1; i <= layers; i++)
        delete[] x[i];

    delete[] x;
      
}

//метод скрещивания двух неиросетей
vector<Neiron*> Neiron::Cross(Neiron* parent) {
    vector<Neiron*> res;
    int* mas = new int[this->layers];
    int* mas1 = new int[this->layers];

    for (int i = 0; i < this->layers; i++) {
        mas[i] = this->neironsCount[i];
        mas1[i] = this->neironsCount[i];
    }        

    Neiron* childr = new Neiron(this->layers, mas);
    Neiron* childr1 = new Neiron(this->layers, mas1);
    

    int n = 1 + rand() % 3;

    //поменяли коэффициенты и веса на первом слое
    for (int i = 0; i < n; i++) {
        childr->koef[0][i] = this->koef[0][i];
        childr1->koef[0][i] = parent->koef[0][i];

        for (int j = 0; j < 3; j++) {
            childr->w[0][i][j] = this->w[0][i][j];
            childr1->w[0][i][j] = parent->w[0][i][j];
        }
    }

    for (int i = n; i < 4; i++) {
        childr1->koef[0][i] = this->koef[0][i];
        childr->koef[0][i] = parent->koef[0][i];
        
        for (int j = 0; j < 3; j++) {
            childr1->w[0][i][j] = this->w[0][i][j];
            childr->w[0][i][j] = parent->w[0][i][j];
        }
    }
    int n1 = 1 + rand() % 3;

    //меняем веса на втором слое
    for (int i = 0; i < n1; i++) {
        childr->w[1][0][i] = this->w[1][0][i];
        childr1->w[1][0][i] = parent->w[1][0][i];
    }

    for (int i = n; i < 4; i++) {
        childr1->w[1][0][i] = this->w[1][0][i];
        childr->w[1][0][i] = parent->w[1][0][i];
    }

    //находим средний коэффициент для второго слоя
    double k = (this->koef[1][0] + parent->koef[1][0]) / 2;
    childr1->koef[1][0] = k;
    childr->koef[1][0] = k;

    res.push_back(childr);
    res.push_back(childr1);

    return res;
}

//метод для мутации
Neiron* Neiron::Mutation( double per) {
    int* mas = new int[this->layers];
    for (int i = 0; i < this->layers; i++) 
        mas[i] = this->neironsCount[i];
    Neiron* mutant = new Neiron(this->layers, mas);

    
    //мутация коэф
    for (int i = 0; i < layers; i++) {
        for (int j = 0; j < neironsCount[i]; j++) {
            double s = 1;
            double sign = -1 + 2 * (double)rand() / RAND_MAX;
            double Per = per * (double)rand() / RAND_MAX;
            if (sign < 0)
                s = -1;
            mutant->koef[i][j] = (s * Per  + 1) * this->koef[i][j];
        }            
    }

    //мутация весов
    for (int i = 0; i < layers; i++) {
        for (int j = 0; j < neironsCount[i]; j++) {
            int xSize = 3;
            if (i != 0)
                xSize = neironsCount[i - 1];           

            for (int k = 0; k < xSize; k++) {
                double s = 1;
                double sign = -1 + 2 * (double)rand() / RAND_MAX;
                double Per = per * (double)rand() / RAND_MAX;
                if (sign < 0)
                    s = -1;
                mutant->w[i][j][k] = (s * Per + 1) * this->w[i][j][k];
            }               
        }
    }
    return mutant;
}

//Функция вывода реультата
void Neiron::Result() {
    for (int i = 0; i < 8; i++) {
        double y = (double)(
            (bool)Table[i][0] ^
            (bool)Table[i][1] ^
            (bool)Table[i][2]
            );

        double yy = this->Work(
            Table[i][0],
            Table[i][1],
            Table[i][2]);
        cout << "|  "
            << Table[i][0]
            << "  "
            << Table[i][1]
            << "  "
            << Table[i][2]
            << "  |"
            << " y: "
            << y
            << "  res:  "
            << yy
            << "  |"
            << endl;
    }
}