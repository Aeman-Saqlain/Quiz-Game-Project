#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
// ---------- STRUCT ----------
struct Question 
{
    string ques;
    string opt1, opt2, opt3, opt4;
    char ans;
};
// ---------- FUNCTIONS ----------
void saveHighScore(int score);
void viewHighScores();
// ---------- MAIN ----------
int main() {
    srand(time(0));   // rand() seed
    int ch, choice;
    int score = 0, total = 0;
    char userAns;
    ifstream file;
    vector<Question> questions;
    Question q;

    cout << "\t\tWelcome to QuizMaster\n";
    cout << "1. Start Quiz\n";
    cout << "2. View High Scores\n";
    cout << "3. Exit\n";
    cin >> ch;

    switch (ch) {
    case 1:
        cout << "\nSelect Subject\n";
        cout << "1. Programming Fundamentals\n";
        cout << "2. English Grammar\n";
        cout << "3. Mathematics\n";
        cin >> choice;

        if (choice == 1)
            file.open("pf.txt");
        else if (choice == 2)
            file.open("Eng.txt");
        else if (choice == 3)
            file.open("maths.txt");
        else {
            cout << "Invalid Choice!";
            return 0;
        }
        if (!file) {
            cout << "File not found!";
            return 0;
        }

        // ---------- LOAD QUESTIONS ----------
        while (getline(file, q.ques)) {
            if (q.ques == "") continue;

            getline(file, q.opt1);
            getline(file, q.opt2);
            getline(file, q.opt3);
            getline(file, q.opt4);
            file >> q.ans;
            file.ignore();

            questions.push_back(q);
        }
        file.close();

        // ---------- QUIZ ----------
        while (!questions.empty()) {
            int index = rand() % questions.size(); // RANDOM QUESTION

            cout << "\n" << questions[index].ques << endl;
            cout << questions[index].opt1 << endl;
            cout << questions[index].opt2 << endl;
            cout << questions[index].opt3 << endl;
            cout << questions[index].opt4 << endl;
            cout << "Your answer: ";
            cin >> userAns;

            if (userAns == questions[index].ans ||
                userAns == questions[index].ans - 32)
                score++;

            total++;
            questions.erase(questions.begin() + index);
        }

        // ---------- RESULT ----------
        cout << "\n=========== RESULT ===========\n";
        cout << "Total Questions: " << total << endl;
        cout << "Correct Answers: " << score << endl;
        cout << "Score: " << score << "/" << total << endl;
        if(score==total)
          cout << "Outstanding Performance.";
        else if(score>7)
          cout << "Excellent.";
        else if(score>5)
          cout << "Good Attempt.";
        saveHighScore(score);
        break;

    case 2:
        viewHighScores();
        break;

    case 3:
        cout << "Thank You!\n";
        break;

    default:
        cout << "Invalid Option!";
    }

    return 0;
}

// ---------- SAVE HIGH SCORE ----------
void saveHighScore(int score) {
    ofstream file("highscores.txt", ios::app);
    string name;

    cout << "Enter your name: ";
    cin >> name;

    file << name << " " << score << endl;
    file.close();
}

// ---------- VIEW HIGH SCORES ----------
void viewHighScores() {
    ifstream file("highscores.txt");

    if (!file) {
        cout << "No high scores available!\n";
        return;
    }
  
    string name;
    int score;

    cout << "\n===== HIGH SCORES =====\n";
    while (file >> name >> score) {
        cout << name << " - " << score << endl;
    }

    file.close();
}
