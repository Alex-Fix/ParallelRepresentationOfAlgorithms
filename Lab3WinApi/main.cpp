#include <Windows.h>
#include <ctime>

int** create_matrix(int n);
void delete_matrix(int** matrix, int n);
int** create_matrix_A(int n);
int** create_random_matrix_B(int n, int random_limit, bool singleMatrix);
int** matrix_multiply(int** A, int** B, int n);
int** matrix_multiply_single_assign(int** A, int** B, int n);
int** recursive_multiply_main(int** A, int** B, int n);
void recursive_multiply(int*** matrix3d, int** A, int** B, int n, int& k, int& i, int& j);
void delete_matrix3d(int*** matrix3d, int heigth, int depth);
int** matrix_multiply_single_assign(int** A, int** B, int n);
int** perfomace_recursive_multiply_main(int** A, int** B, int n);
void perfomace_recursive_multiply(int*** matrix3d, int** A, int** B, int n, int& k, int& i, int& j);

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (uMsg) {
		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
		case WM_LBUTTONDOWN:
		{
			int k = 5;
		}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	if (hwnd = CreateWindow(wc.lpszClassName, L"Laba3 by AlexFix", WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
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

int** matrix_multiply(int** A, int** B, int n) {
	int** matrix = create_matrix(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
				matrix[i][j] += A[i][k] * B[k][j];
		}

	return matrix;
}

int*** create_matrix3d(int heigth, int weigth, int depth) {
	int*** matrix3d = new int** [depth];
	for (int k = 0; k < depth; k++) {
		matrix3d[k] = new int* [heigth];
		for (int i = 0; i < heigth; i++) {
			matrix3d[k][i] = new int[weigth];
			for (int j = 0; j < weigth; j++)
				matrix3d[k][i][j] = 0;
		}
	}
	return matrix3d;
}

void delete_matrix3d(int*** matrix3d, int heigth, int depth) {
	for (int k = 0; k < depth; k++) {
		for (int i = 0; i < heigth; i++)
			delete[] matrix3d[k][i];
		delete[] matrix3d[k];
	}
}

int** matrix_multiply_single_assign(int** A, int** B, int n) {
	int*** matrix3d = create_matrix3d(n, n, n + 1);

	// matrix multiply
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix3d[k + 1][i][j] = matrix3d[k][i][j] + A[i][k] * B[k][j];

	// multiply result
	int** matrix = matrix3d[n];

	delete_matrix3d(matrix3d, n, n);

	return matrix;
}

int** recursive_multiply_main(int** A, int** B, int n) {
	int*** matrix3d = create_matrix3d(n, n, n + 1);


	int k = 0, i = 0, j = 0;
	//recursive_multiply
	recursive_multiply(matrix3d, A, B, n, k, i, j);

	// multiply result
	int** matrix = matrix3d[n];

	delete_matrix3d(matrix3d, n, n);

	return matrix;
}

void recursive_multiply(int*** matrix3d, int** A, int** B, int n, int& k, int& i, int& j) {
	if (k < n) {
		if (i < n) {
			if (j < n) {
				matrix3d[k + 1][i][j] = matrix3d[k][i][j] + A[i][k] * B[k][j];
				j++;
				recursive_multiply(matrix3d, A, B, n, k, i, j);
			}
			j = 0;
			i++;
			recursive_multiply(matrix3d, A, B, n, k, i, j);
		}
		i = 0;
		k++;
		recursive_multiply(matrix3d, A, B, n, k, i, j);
	}
}

int** perfomace_recursive_multiply_main(int** A, int** B, int n) {
	int*** matrix3d = create_matrix3d(n, n, n + 1);

	int k = 0, i = 0, j = 0;
	//recursive_multiply
	perfomace_recursive_multiply(matrix3d, A, B, n, k, i, j);

	// multiply result
	int** matrix = matrix3d[n];

	delete_matrix3d(matrix3d, n, n);

	return matrix;
}

void perfomace_recursive_multiply(int*** matrix3d, int** A, int** B, int n, int& k, int& i, int& j) {
	if (k < n) {
		if (i < n) {
			if (j < n) {
				if (A[i][k] != 0 && B[k][j] != 0)
					matrix3d[k + 1][i][j] = A[i][k] * B[k][j];
				else
					matrix3d[k + 1][i][j] = matrix3d[k][i][j];
				j++;
				perfomace_recursive_multiply(matrix3d, A, B, n, k, i, j);
			}
			j = 0;
			i++;
			perfomace_recursive_multiply(matrix3d, A, B, n, k, i, j);
		}
		i = 0;
		k++;
		perfomace_recursive_multiply(matrix3d, A, B, n, k, i, j);
	}
}