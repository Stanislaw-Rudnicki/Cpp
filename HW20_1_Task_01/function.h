// 3. В файле function.h нужно:
// а) описать прототипы всех функций;
// б) сделать проверку определена ли константа, указывающая на тип данных (#ifdef INTEGER)
// в) создать обобщающие имена функции, которым будет определена функция соответствующего типа
// в зависимости от константы, указанной в файле prog.cpp. (#define show ShowInt)

#pragma once

#ifdef INTEGER
#define DATATYPE int
#define CreateMas CreateMasInt
#define InputMas InputRandInt
#define ShowMas ShowMasInt
#define MinMas MinMasInt
#define MaxMas MaxMasInt
#define SortMas SortMasInt
#define EditMas EditMasInt
#define DelMas DelMasInt
#endif

#ifdef DOUBLE
#define DATATYPE double
#define CreateMas CreateMasDouble
#define InputMas InputRandDouble
#define ShowMas ShowMasDouble
#define MinMas MinMasDouble
#define MaxMas MaxMasDouble
#define SortMas SortMasDouble
#define EditMas EditMasDouble
#define DelMas DelMasDouble
#endif

#ifdef CHAR
#define DATATYPE char
#define CreateMas CreateMasChar
#define InputMas InputRandChar
#define ShowMas ShowMasChar
#define MinMas MinMasChar
#define MaxMas MaxMasChar
#define SortMas SortMasChar
#define EditMas EditMasChar
#define DelMas DelMasChar
#endif

int* CreateMasInt(int n);
void InputRandInt(int* arr, int n, int b = 100, int a = -100);
void ShowMasInt(int* arr, int n);
int MinMasInt(int* arr, int n);
int MaxMasInt(int* arr, int n);
void SortMasInt(int* arr, int n);
void EditMasInt(int* arr, int n);
void DelMasInt(int* arr);

double* CreateMasDouble(int n);
void InputRandDouble(double* arr, int n, int b = 100, int a = -100);
void ShowMasDouble(double* arr, int n);
int MinMasDouble(double* arr, int n);
int MaxMasDouble(double* arr, int n);
void SortMasDouble(double* arr, int n);
void EditMasDouble(double* arr, int n);
void DelMasDouble(double* arr);

char* CreateMasChar(int n);
void InputRandChar(char* arr, int n, int b = 'Z', int a = 'A');
void ShowMasChar(char* arr, int n);
int MinMasChar(char* arr, int n);
int MaxMasChar(char* arr, int n);
void SortMasChar(char* arr, int n);
void EditMasChar(char* arr, int n);
void DelMasChar(char* arr);
