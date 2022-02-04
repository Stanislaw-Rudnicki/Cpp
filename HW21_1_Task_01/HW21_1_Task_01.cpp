// 1. Дан текстовый файл. Удалить из него последнюю строку. Результат записать в другой файл.
// 2. Дан текстовый файл. Найти длину самой длинной строки.
// 3. Дан текстовый файл. Посчитать сколько раз в нем встречается заданное пользователем слово.
// 4. Дан текстовый файл. Найти и заменить в нем заданное слово. Что искать и на что заменять определяется пользователем.

#include <stdio.h>
#include <windows.h>

using namespace std;

void DelLastStr(const char* fn, const char* fn2) {
	FILE* fs = fopen(fn, "rt");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	char c;
	int currlen = 0;
	while (!feof(fs)) {
		c = getc(fs);
		if (!feof(fs))
			if (c == '\n') currlen = 0;
			else currlen++;
	}
	FILE* fs2 = fopen(fn2, "w");
	if (!fs2) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	currlen = ftell(fs) - currlen - 2;
	rewind(fs);
	for (int i = 0; i < currlen; i++) {
		if ((c = getc(fs)) == '\n') i++;
		fputc(c, fs2);
	}
	fclose(fs);
	fclose(fs2);
}

char* LongestStr(const char* fn) {
	FILE* fs = fopen(fn, "rt");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	char c;
	int currlen = 0, maxlen = 0, LongestStrPos = 0;
	while (!feof(fs)) {
		if ((c = getc(fs)) == '\n') {
			if (maxlen < currlen) {
				maxlen = currlen;
				LongestStrPos = ftell(fs) - maxlen - 2;
			}
			currlen = 0;
		}
		else currlen++;
	}
	char* mas = (char*)calloc(maxlen + 1, sizeof(char));
	fseek(fs, LongestStrPos, SEEK_SET);
	fgets(mas, maxlen + 1, fs);
	fclose(fs);
	return mas;
}

int FindStr(const char* fn, const char* str) {
	FILE* fs = fopen(fn, "rt");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	fseek(fs, 0, SEEK_END);
	int len1 = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	int len2 = strlen(str);
	int count = 0;
	if (len2 > len1) return count;
	char c;
	while (!feof(fs)) {
		if ((c = getc(fs)) == *str) {
			int i = 0;
			for (i; c == *str && !feof(fs); i++) {
				c = getc(fs);
				++str;
			}
			if (*str == 0)
				count++;
			str -= i;
			fseek(fs, -i, SEEK_CUR);
		}
	}
	fclose(fs);
	return count;
}

char* str_replace(const char* find, const char* replace, char* source) {
	int find_len = strlen(find);
	int replace_len = strlen(replace);

	char* pointer = strstr(source, find);

	while (pointer != NULL) {
		int i;
		int pointer_len = strlen(pointer);
		int source_len = strlen(source);

		char* new_text = (char*)calloc((source_len - find_len + replace_len + 1), sizeof(char));

		strncpy(new_text, source, source_len - pointer_len);
		strcat(new_text, replace);
		strcat(new_text, pointer + find_len);

		free(source);
		source = new_text;
		pointer = strstr(source, find);
	}
	return source;
}

void ReplaceStr(const char* fn, const char* find, const char* replace) {
	FILE* fs = fopen(fn, "rt");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	fseek(fs, 0, SEEK_END);
	int size = ftell(fs);
	char* source = (char*)calloc(size + 1, sizeof(char));
	fseek(fs, 0, SEEK_SET);
	char t;
	int i = 0;
	while (!feof(fs)) {
		t = fgetc(fs);
		if (feof(fs)) break;
		source[i++] = t;
	}
	fclose(fs);

	fs = fopen(fn, "wt");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	source = str_replace(find, replace, source);
	fputs(source, fs);
	fclose(fs);
	free(source);
}

void Color(unsigned short BackC, unsigned short ForgC) {
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(StdOut, c);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fn[] = "File.txt";
	char fn2[] = "File_2.txt";

	printf("Дан текстовый файл: %s\nУдалить из него последнюю строку. Результат записать в другой файл.", fn);
	DelLastStr(fn, fn2);
	Color(0, 2); printf("\n\nГотово! "); Color(0, 7);
	printf("Последняя строка удалена. Результат записан в файл %s", fn2);
	
	printf("\n\nДан текстовый файл: %s\nНайти длину самой длинной строки.", fn);
	char* LStr = LongestStr(fn);
	int LStrLen = strlen(LStr);
	Color(0, 2); printf("\n\nГотово! "); Color(0, 7);
	printf("Длина самой длинной строки: %d.\n\nВот эта строка:\n%s", LStrLen, LStr);
	free(LStr);
	
	printf("\n\nДан текстовый файл: %s\nПосчитать сколько раз в нем встречается заданное пользователем слово.", fn);
	printf("\n\nВведите поисковый запрос: ");
	char find[100], replace[100];
	scanf("%s", &find);
	printf("\nИскомое слово встречается в файле %d раз.", FindStr(fn, find));

	printf("\n\nДан текстовый файл: %s\nНайти и заменить в нем заданное слово.", fn);
	printf("\n\nВведите что искать: ");
	scanf("%s", &find);
	printf("\nВведите на что заменить: ");
	scanf("%s", &replace);
	ReplaceStr(fn, find, replace);
	Color(0, 2); printf("\nГотово!\n"); Color(0, 7);

	return 0;
}