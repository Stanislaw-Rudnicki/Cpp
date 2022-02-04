// Девятка - карточная игра
// Цель игры: избавиться первым от всех своих карт.
// Правила игры.
// Сдатчик карт выбирается по желанию.
// Колода тщательно тасуется и полностью раздается между всеми игроками.
// Карты раздаются строго по одной.
// У игроков должно быть равное количество карт.
// Первым ходит игрок, у которого есть девятка треф.
// Игрок кладет ее по центру стола в открытом виде.
// Следующий игрок по часовой стрелке может положить слева от девятки треф - восьмерку треф или справа от девятки треф - 10 треф
// или он может начать новый ряд, положить под девяткой треф или сверху девятки треф любую девятку другой масти.
// Если у игрока нет возможности положить карту, то он пропускает ход и ход переходит к следующему игроку по часовой стрелке,
// который должен выложить карту по тем же правилам.
// Стратегия игры такова, что игрок должен препятствовать другим игрокам выложить имеющиеся у них карты.
// Тот игрок, который первым избавится от всех своих карт, считается победителем.


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <time.h>

using namespace std;


class Card {
    int suit, value, turnKey;
public:
    Card(int suit, int value) :suit(suit), value(value), turnKey(0) {};
    int GetValue() { return value; };
    int GetSuit() { return suit; };
    int GetTurnKey() { return turnKey; };
    void SetTurnKey(int key) { turnKey = key; };
    friend wostream& operator<<(wostream& out, const Card& obj);
};

wostream& operator<<(wostream& out, const Card& obj) {
    wchar_t suitsList[4] = { L'\u2665', L'\u2666',L'\u2663',L'\u2660' };
    // 0 - червы, 1 - бубны, 2 - трефы, 3 - пики
    const wchar_t* valuesList[9] = { L" 6", L" 7", L" 8", L" 9", L"10", L" В", L" Д", L" К", L" Т" };
    out << valuesList[obj.value] << suitsList[obj.suit];
    return out;
}


class Deck {
    Card** deck;
    int stock;
public:
    Deck();
    ~Deck();
    int GetStock() { return stock; }
    void Clear();
    void Shuffle();
    Card* Pop();
    friend wostream& operator<<(wostream& out, const Deck& obj);
};

Deck::Deck() {
    deck = new Card * [36]{ 0 };
    int i = 0;
    for (int suit = 0; suit <= 3; ++suit) {
        for (int value = 0; value <= 8; ++value) {
            deck[i] = new Card(suit, value);
            ++i;
        }
    }
    stock = 36;
}

Deck::~Deck() {
    Clear();
    delete[]deck;
}

void Deck::Clear() {
    for (size_t i = 0; i < stock; i++)
        delete deck[i];
}

void Deck::Shuffle() {
    srand(time(0));
    int j = stock - 1;
    for (int i = 0; i < j; ++i) {
        int k = i + rand() % (stock - i);
        swap(deck[i], deck[k]);
    }
}

Card* Deck::Pop() {
    Card* temp = deck[--stock];
    deck[stock] = 0;
    return temp;
}

wostream& operator<<(wostream& out, const Deck& obj) {
    for (int i = 0; i < obj.stock; i++) {
        out << *obj.deck[i] << "\t";
        if (!((i + 1) % 9)) out << endl;
    }
    return out;
}


class Player {
protected:
    Card*** set;
    int stock;
public:
    Player();
    ~Player();
    int GetStock() { return stock; }
    void Clear();
    void Push(Card* card);
    Card* FirstTurn();
    Card* Turn(Card***& table);
    friend wostream& operator<<(wostream& out, const Player& obj);
};

Player::Player() {
    set = new Card * *[4];
    for (size_t i = 0; i < 4; i++)
        set[i] = new Card * [9]{ 0 };
    stock = 0;
}

Player::~Player() {
    Clear();
    for (size_t i = 0; i < 4; i++)
        delete[] set[i];
    delete[] set;
    set = nullptr;
}

void Player::Clear() {
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 9; j++)
            delete set[i][j];
}

void Player::Push(Card* card) {
    set[card->GetSuit()][card->GetValue()] = card;
    stock++;
}

Card* Player::FirstTurn() {
    Card* temp;
    if (set[2][3]) {
        temp = set[2][3];
        set[2][3] = 0;
        stock--;
        return temp;
    }
    return 0;
}

Card* Player::Turn(Card***& table) {
    Card* temp = 0;
    int t, k = 1;

    if (!table[2][3] && set[2][3])
        set[2][3]->SetTurnKey(k++);
    else {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 9; j++)
                if (!table[i][3] && set[i][3]) {
                    set[i][3]->SetTurnKey(k++);
                    break;
                }
                else {
                    if (!table[i][j] && table[i][j + 1] && j < 3)
                        if (set[i][j]) set[i][j]->SetTurnKey(k++);
                    if (table[i][j] && !table[i][j + 1] && j >= 3 && j < 8)
                        if (set[i][j + 1]) set[i][j + 1]->SetTurnKey(k++);
                }
    }

    if (k > 1) {
        srand(time(0));
        t = 1 + rand() % (k - 1);
        
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 9; j++) {
                if (set[i][j]) {
                    if (set[i][j]->GetTurnKey() == t) {
                        temp = set[i][j];
                        set[i][j] = 0;
                    }
                    else
                        set[i][j]->SetTurnKey(0);
                }
            }
        stock--;
    }
    return temp;
}

wostream& operator<<(wostream& out, const Player& obj) {
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 9; j++)
            if (obj.set[i][j])
                wcout << *obj.set[i][j] << "  ";
    }
    wcout << "\n";
    return out;
}


class User : public Player {
public:
    Card* Turn(Card***& table);
};

Card* User::Turn(Card***& table) {
    Card* temp = 0;
    int t, k = 1;
    if (!table[2][3] && set[2][3])
        set[2][3]->SetTurnKey(k++);
    else {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 9; j++)
                if (!table[i][3] && set[i][3]) {
                    set[i][3]->SetTurnKey(k++);
                    break;
                }
                else {
                    if (!table[i][j] && table[i][j + 1] && j < 3)
                        if (set[i][j]) set[i][j]->SetTurnKey(k++);
                    if (table[i][j] && !table[i][j + 1] && j >= 3 && j < 8)
                        if (set[i][j + 1]) set[i][j + 1]->SetTurnKey(k++);
                }
    }

    if (k > 1) {
        wcout << L"\nВаши карты: ";
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 9; j++)
                if (set[i][j]) {
                    wcout << *set[i][j];
                    if (set[i][j]->GetTurnKey())
                        wcout << L"(" << set[i][j]->GetTurnKey() << L")";
                    wcout << "  ";
                }
        }
        wcout << endl;

        do {
            wcout << L"\nВаш ход (цифра в скобках возле карты): ";
            wcin >> t; wcin.clear(); wcin.ignore((numeric_limits<streamsize>::max)(), L'\n');
        } while (t < 1 || k <= t);

        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 9; j++) {
                if (set[i][j]) {
                    if (set[i][j]->GetTurnKey() == t) {
                        temp = set[i][j];
                        set[i][j] = 0;
                    }
                    else
                        set[i][j]->SetTurnKey(0);
                }
            }
        stock--;
    }
    return temp;
}


class Game {
    Card*** table;
    Player player;
    User user;
    int stock;
    int nextTurn; // 0 - player, 1 - user
    bool firstTurn;
public:
    Game();
    ~Game();
    void Clear();
    // 0 - червы, 1 - бубны, 2 - трефы, 3 - пики
    // 0 - 6, 1 - 7, 2 - 8, 3 - 9, 4 - 10, 5 - В, 6 - Д, 7 - К, 8 - Т
    void DealCards(Deck& deck);
    void ShowTable();
    void Start();
};

Game::Game() {
    table = new Card * *[4];
    for (size_t i = 0; i < 4; i++)
        table[i] = new Card * [9]{ 0 };
    stock = 0;
    nextTurn = 0;
    firstTurn = true;
}

Game::~Game() {
    Clear();
    for (size_t i = 0; i < 4; i++)
        delete[] table[i];
    delete[] table;
    table = nullptr;
}

void Game::Clear() {
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 9; j++)
            delete table[i][j];
}

void Game::DealCards(Deck& deck) {
    while (deck.GetStock()) {
        player.Push(deck.Pop());
        user.Push(deck.Pop());
    }
}

void Game::ShowTable() {
    wchar_t suitsList[4] = { L'\u2665', L'\u2666',L'\u2663',L'\u2660' };
    for (size_t i = 0; i < 4; i++) {
        wcout << suitsList[i] << "\t";
        for (size_t j = 0; j < 9; j++)
            if (table[i][j])
            wcout << *table[i][j] << "\t";
            else wcout << " \t";
        wcout << "\n";
    }
}

void Game::Start() {
    while (player.GetStock() && user.GetStock()) {
        if (firstTurn) {
            Card* temp = player.FirstTurn();
            if (temp)
                table[temp->GetSuit()][temp->GetValue()] = temp;
            nextTurn = 1;
            firstTurn = false;
        }
        if (!nextTurn) {
            Card* temp = player.Turn(table);
            if (temp)
                table[temp->GetSuit()][temp->GetValue()] = temp;
            nextTurn = 1;
        }
        else {
            system("cls");
            wcout << L"\nУ компьютера карт: \t" << player.GetStock() << endl;
            wcout << L"У вас карт: \t\t" << user.GetStock() << endl << endl;
            ShowTable();
            Card* temp = user.Turn(table);
            if (temp)
                table[temp->GetSuit()][temp->GetValue()] = temp;
            nextTurn = 0;
        }
    }
    system("cls");
    wcout << L"\nУ компьютера карт: \t" << player.GetStock() << endl;
    wcout << L"У вас карт: \t\t" << user.GetStock() << endl << endl;
    ShowTable();
    if (player.GetStock() > user.GetStock())
        wcout << L"\nВы выиграли!\n";
    else {
        wcout << L"\nВы проиграли! :(\n";
    }
}


int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    Deck deck;
    //wcout << deck << endl;
    deck.Shuffle();
    //wcout << deck << endl;

    Game game;
    game.DealCards(deck);
    game.Start();
    
    return 0;
}