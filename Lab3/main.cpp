#include <iostream>
#include <ctime>
using namespace std;

int** create_matrix(int n);
void delete_matrix(int** matrix, int n);
int** create_matrix_A(int n);
int** create_random_matrix_B(int n, int random_limit, bool singleMatrix);
void print_matrix(int** matrix, int n);
int** matrix_multiply(int** A, int** B, int n);
int** matrix_multiply_single_assign(int** A, int** B, int n);

int main() {
	srand(time(NULL));

	int n = 10;

	int** A = create_matrix_A(n);
	cout << "matrix A:" << endl;
	print_matrix(A, n);
	
	int** B = create_random_matrix_B(n, 10, true);
	cout << endl << "matrix B:" << endl;
	print_matrix(B, n);

	int** C = matrix_multiply(A, B, n);
	cout << endl << "matrix C:" << endl;
	print_matrix(C, n);

	int** CSingle = matrix_multiply_single_assign(A, B, n);
	cout << endl << "matrix CSingle:" << endl;
	print_matrix(CSingle, n);

	delete_matrix(A, n);
	delete_matrix(B, n);
	delete_matrix(C, n);
	delete_matrix(CSingle, n);

	return 0;
}

int** create_matrix(int n) {
	int** matrix = new int* [n];

	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0;
	}

	return matrix;
}

void delete_matrix(int** matrix, int n) {
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}

int** create_matrix_A(int n) {
	int** matrix = create_matrix(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				matrix[i][i] = (i + 1) * (i + 2);

	return matrix;
}

int** create_random_matrix_B(int n, int random_limit = 10, bool singleMatrix = false) {
	int** matrix = create_matrix(n);

	int width = n;
	for (int i = 0; i < n; i++, width -= 2)
		for (int j = 0; j < n; j++)
			if (i <= n / 2 && j >= (n - width) / 2 && j < (n + width) / 2 && width >= 0)
				if (singleMatrix)
					matrix[i][j] = 1;
				else
					matrix[i][j] = rand() % random_limit + 1;

	return matrix;
}

void print_matrix(int** matrix, int n) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == n - 1)
				cout << matrix[i][j];
			else
				cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int** matrix_multiply(int** A, int** B, int n) {
	int** matrix = create_matrix(n);

	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
				matrix[i][j] += A[i][k] * B[k][j];
		}

	return matrix;
}

int** matrix_multiply_single_assign(int** A, int** B, int n) {
	// create matrix
	int*** matrix3d = new int** [n];
	for (int k = 0; k <= n; k++) {
		matrix3d[k] = new int* [n];
		for (int i = 0; i < n; i++) {
			matrix3d[k][i] = new int[n];
			for (int j = 0; j < n; j++)
				matrix3d[k][i][j] = 0;
		}
	}

	// matrix multiply
	for (int k = 0; k < n; k++) 
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) 
				matrix3d[k + 1][i][j] = matrix3d[k][i][j] + A[i][k] * B[k][j];
	
	// multiply result
	int** matrix = matrix3d[n];

	// delete not result matrixes
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++)
			delete[] matrix3d[k][i];
		delete[] matrix3d[k];
	}
		
	return matrix;
}