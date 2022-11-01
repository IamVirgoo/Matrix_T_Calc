#include <iostream>

using namespace std;

/**
 * @name Complex
 * @description Класс для работы с комплексными числами
 * */
class Complex {
    private:
        /**
         * @description параметры комплексного числа (Действительная и мнимая часть)
         * */
        double realPath, imaginaryPath;
    public:
        /**
         * @descripion Конструктор по умолчанию
         * */
        Complex() {}
        /**
         * @description Конструктор с параметрами, для заполнения полей комплексного числа
         * */
        Complex(double realPath, double imaginaryPath) {
            this->realPath = realPath;
            this->imaginaryPath = imaginaryPath;
        }
        /**
         * @description Инициализация оператора для сложение комплексных чисел
         * @param: num - экземляр класса комплексных чисел, является параметром сложения
         * @return Complex
         * */
        Complex operator+ (Complex num) {
            Complex result;
            result.realPath = num.realPath + this->realPath;
            result.imaginaryPath = num.imaginaryPath + this->imaginaryPath;
            return result;
        }
        /**
         * @name RandomNumber
         * @description Статический метод для случайного заполнения действительно и мнимой части комплексного числа
         * @return Complex
         * */
        static Complex RandomNumber() {
            Complex result;
            result.realPath = (rand() % 50) / 3. + 5;
            result.imaginaryPath = (rand() % 50) / 3. + 5;
            return result;
        }
        /**
         * @name Format
         * @description Метод для форматированного вывода
         * @return void
         * */
        void Format(char* str) {
            sprintf(str, "%.2lf + (%.2lf)i", realPath, imaginaryPath);
        }
};
/**
 * @name Limited
 * @description Класс, для реализации предельного числа и работы с ним
 * */
class Limited {
    private:
        /**
         * @description Параметры предельного числа (начальная позиция и конечная позиция)
         * */
        int startPosition, endPosition;
    public:
        /**
         * @description Конструктор по умолчанию
         * */
        Limited() {}
        /**
         * @description Конструктор с параметрами для заполнения полей предельного числа
         * */
        Limited(int startPosition, int endPosition) {
            this->startPosition = startPosition;
            this->endPosition = endPosition;
        }
        /**
         * @description Инициализация оператора для сложение предельных чисел
         * @param num - экземляр класса предельных чисел, является параметром сложения
         * @return Limited
         * */
        Limited operator+ (Limited num) {
            Limited result;
            result.startPosition = this->startPosition + num.startPosition;
            result.endPosition = this->endPosition + num.endPosition;
            return result;
        }
        /**
         * @name RandomNumber
         * @description Статический метод для случайного заполнения начальной и конечной позиции предельного числа
         * @return Complex
         * */
        static Limited RandomNumber() {
            Limited result;
            result.startPosition = -10 + (rand() % static_cast<int>(10 - (-10) + 1));
            result.endPosition = -10 + (rand() % static_cast<int>(10 - (-10) + 1));
            return result;
        }
        /**
         * @name Format
         * @description Метод для форматированного вывода
         * @return void
         * */
        void Format(char* str) {
            sprintf(str, "[%i ... %i]", startPosition, endPosition);
        }
};
/**
 * @NOTE Классы Complex и Limited имеют перегруженные операторы, статический метод RandomNumber и метод Format,
 * таким образом, классы Complex и Limited могут быть использованы в качестве параметра шаблонного класса Matrix
 * */
/**
 * @description объявляем шаблон T для класса Matrix
 * */
template <class T>
/**
 * @description Основной класс для работы с матрицами данных
 * @tparam T */
class Matrix {
    private:
        /**
         * @description поля класса матрицы
         * */
        int row_size, column_size;
        T** matrix;
        /**
         * @name createMatrix
         * @description Метод для инициализации поля матрицы
         * @return void
         * */
        void createMatrix() {
            matrix = new T*[row_size];
            for (int i = 0; i < row_size; i++) {
                matrix[i] = new T[column_size];
            }
        }
        /**
         * @name generateMatrix
         * @description Генерация сулчайных элементов матрицы с последующим его заполнением
         * @return void
         * */
        void generateMatrix() {
            for (int row_index = 0; row_index < row_size; row_index++) {
                for (int column_index = 0; column_index < column_size; column_index++) {
                    matrix[row_index][column_index] = T::RandomNumber();
                }
            }
        }
    public:
        /**
         * @description Конструктор по умолчанию
         * */
        Matrix() {}
        /**
         * @description Конструктор класса с параметрами для заполнения необходимых полей матрицы
         * @param row_size - количество строк в матрице;
         * @param column_size - количество колонок в матрице
         * */
        Matrix(int row_size, int column_size) {
            this->row_size = row_size;
            this->column_size = column_size;

            createMatrix();
            generateMatrix();
        }
        /**
         * @name Output
         * @description Метод для вывода поля матрицы
         * */
        void Output() {
            /**
             * @name str
             * @description инициализируем массив char, для использования в методе Format
             * */
            char* str = new char[100];
            for (int row_index = 0; row_index < row_size; row_index++) {
                for (int column_index = 0; column_index < column_size; column_index++) {
                    cout.width(20);
                    matrix[row_index][column_index].Format(str);
                    cout << str << " ";
                }
                cout << "\n";
            }
        }
        /**
         * @description Инициализация оператора для сложения двух матриц данных
         * @return Matrix*
         * */
        Matrix* operator+ (Matrix& secondMatrix) {
            auto resultMatrix = new Matrix<T>(this->row_size, this->column_size);
            for (int row_index = 0; row_index < this->row_size; row_index++) {
                for (int column_index = 0; column_index < this->column_size; column_index++) {
                    resultMatrix->matrix[row_index][column_index] = matrix[row_index][column_index] + secondMatrix.matrix[row_index][column_index];
                }
            }
            return resultMatrix;
        }
        /**
         * @description Инициализация оператора для присваивания значений одной матрицы другой
         * @return Matrix*
         * */
        Matrix* operator= (Matrix& secondMatrix) {
            auto resultMatrix = new Matrix(secondMatrix.row_size, secondMatrix.column_size);
            for (int row_index = 0; row_index < secondMatrix.row_size; row_index++) {
                for (int column_index = 0; column_index < secondMatrix.column_size; column_index++) {
                    resultMatrix->matrix[row_index][column_index] = secondMatrix.matrix[row_index][column_index];
                }
            }
            return resultMatrix;
        }
};

int main() {
    srand(time(nullptr));
    /**
     * Инициализация переменных - экземпляров класса Matrix с заданными типами T, в данном случае типа Complex
     * */
    auto firstComplexMatrix = new Matrix<Complex>(4, 4);
    auto secondComplexMatrix = new Matrix<Complex>(4, 4);
    Matrix<Complex> *resultComplexMatrix;
    cout << "========================================COMPLEX TYPE=========================================" << '\n' << '\n';
    cout << "========================================FIRST MATRIX=========================================" << '\n' << '\n';
    firstComplexMatrix->Output();
    cout << '\n';
    cout << "========================================SECOND MATRIX========================================" << '\n' << '\n';
    secondComplexMatrix->Output();
    cout << "\n";
    cout << "========================================RESULT MATRIX========================================" << '\n' << '\n';
    /**
     * Выполнение заданного примера C = A + B
     * */
    resultComplexMatrix = *firstComplexMatrix + *secondComplexMatrix;
    resultComplexMatrix->Output();
    cout << "\n";

    auto firstLimitedMatrix = new Matrix<Limited>(5, 5);
    auto secondLimitedMatrix = new Matrix<Limited>(5, 5);
    Matrix<Limited> *resultLimitedMatrix;
    cout << "========================================LIMITED TYPE=========================================" << '\n' << '\n';
    cout << "========================================FIRST MATRIX=========================================" << '\n' << '\n';
    firstLimitedMatrix->Output();
    cout << '\n';
    cout << "========================================SECOND MATRIX========================================" << '\n' << '\n';
    secondLimitedMatrix->Output();
    cout << "\n";
    cout << "========================================RESULT MATRIX========================================" << '\n' << '\n';
    resultLimitedMatrix = *firstLimitedMatrix + *secondLimitedMatrix;
    resultLimitedMatrix->Output();
}