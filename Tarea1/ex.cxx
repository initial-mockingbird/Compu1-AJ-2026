#include <vector>
#include <cmath>

using namespace std;

int main(){
  return 0;
}

double mean(vector<double> v){
    if (v.empty()) return 0.0; // Protección por si el vector está vacío
    double sum = 0.0;
    for (size_t i = 0; i < v.size(); ++i) {
        sum += v[i];
    }
    return sum / v.size();
}

double variance(vector<double> v){
    if (v.size() <= 1) return 0.0; // La varianza muestral requiere al menos 2 elementos
    double m = mean(v); // Reutilizamos tu función de promedio
    double sum_sq_diff = 0.0;
    for (size_t i = 0; i < v.size(); ++i) {
        double diff = v[i] - m;
        sum_sq_diff += diff * diff;
    }
    return sum_sq_diff / (v.size() - 1);
}

double pearson_r(vector<double> A, vector<double> B){
    // Si los vectores tienen tamaños diferentes o están vacíos, no se puede calcular
    if (A.size() != B.size() || A.empty()) return 0.0;
    
    // Reutilizamos tu función mean() del Ejercicio 3
    double mean_A = mean(A);
    double mean_B = mean(B);
    
    double numerator = 0.0;
    double sum_sq_A = 0.0;
    double sum_sq_B = 0.0;
    
    // Calculamos las sumatorias necesarias para la fórmula
    for (size_t i = 0; i < A.size(); ++i) {
        double diff_A = A[i] - mean_A;
        double diff_B = B[i] - mean_B;
        
        numerator += diff_A * diff_B;
        sum_sq_A += diff_A * diff_A;
        sum_sq_B += diff_B * diff_B;
    }
    
    // Prevenimos una división por cero en caso de que alguna variable no tenga varianza
    if (sum_sq_A == 0.0 || sum_sq_B == 0.0) return 0.0;
    
    // Retornamos la fórmula final de Pearson usando std::sqrt para la raíz cuadrada
    return numerator / std::sqrt(sum_sq_A * sum_sq_B);
}
// Convierte un carácter individual ('0'-'9', 'A'-'F') a su valor entero
int char_to_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

// Convierte un valor entero (0-15) a su carácter correspondiente
char val_to_char(int v) {
    if (v >= 0 && v <= 9) return '0' + v;
    if (v >= 10 && v <= 15) return 'A' + (v - 10);
    return '0';
}

// Convierte un vector de caracteres en base 'X' a un número entero real
long long base_to_int(vector<char> s, int base) {
    if (s.empty()) return 0;
    long long result = 0;
    int i = 0;
    bool is_negative = false;
    if (s[0] == '-') {
        is_negative = true;
        i = 1;
    }
    for (; i < s.size(); ++i) {
        result = result * base + char_to_val(s[i]);
    }
    return is_negative ? -result : result;
}

// Convierte un número entero real a un vector de caracteres en base 'X'
vector<char> int_to_base(long long n, int base) {
    if (n == 0) return {'0'};
    vector<char> res;
    bool is_negative = false;
    if (n < 0) {
        is_negative = true;
        n = -n;
    }
    while (n > 0) {
        res.push_back(val_to_char(n % base));
        n /= base;
    }
    if (is_negative) res.push_back('-');
    
    // Invertir el vector manualmente para no usar librerías extra
    int left = 0, right = res.size() - 1;
    while (left < right) {
        char temp = res[left];
        res[left] = res[right];
        res[right] = temp;
        left++; right--;
    }
    return res;
}

vector<char> dec_to_septapus(int n){return int_to_base(n, 7);}
vector<char> dec_to_octopus(int n){return int_to_base(n, 8);}
vector<char> dec_to_hexakaidecapus(int n){return int_to_base(n, 16);}
vector<char> septapus_to_dec(vector<char> s){return int_to_base(base_to_int(s, 7), 10);}
vector<char> octopus_to_dec(vector<char> s){return int_to_base(base_to_int(s, 8), 10);}
vector<char> hexakaidecapus_to_dec(vector<char> s){return int_to_base(base_to_int(s, 16), 10);}
vector<char> septapus_to_octopus(vector<char> s){return int_to_base(base_to_int(s, 7), 8);}
vector<char> septapus_to_hexakaidecapus(vector<char> s){return int_to_base(base_to_int(s, 7), 16);}
vector<char> octapus_to_septapus(vector<char> s){return int_to_base(base_to_int(s, 8), 7);}
vector<char> octopus_to_hexakaidecapus(vector<char> s){return int_to_base(base_to_int(s, 8), 16);}
vector<char> hexakaidecapus_to_septapus(vector<char> s){return int_to_base(base_to_int(s, 16), 7);}
vector<char> hexakaidecapus_to_octopus(vector<char> s){return int_to_base(base_to_int(s, 16), 8);}
