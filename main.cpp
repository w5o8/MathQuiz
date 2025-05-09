#include <iostream>
using namespace std;

enum enDifficulty {Easy = 1, Mid = 2, Hard = 3, MixDifficulty = 4};
enum enOperationType {Add = 1, Sub = 2 , Multi = 3 , Div = 4 , MixOp = 5};

struct stQuestion {
    int number1 = 0;
    int number2 = 0;
    enOperationType operation;
    enDifficulty difficulty;
    int correctAnswer = 0;
    int playerAnswer = 0;
    bool answerResult = false;
};

struct stQuiz {
    stQuestion questionList[100];
    short numberOfQuestions = 0;
    enDifficulty difficulty;
    enOperationType operation;
    short correctAnswers = 0;
    short wrongAnswers = 0;
    bool isPass = false;
};

int generateNumber(int from , int to) {
    int num = 0;
    num = rand() % (to - from + 1) + from;
    return num;
}

short readNumberOfQuestions() {
    short numberOfQuestions = 0;
    do {
        cout<<"How many questions you want in the quiz ?  ( 1 - 10 )\n";
        cin>>numberOfQuestions;
    }while (numberOfQuestions<0);
    return numberOfQuestions;
}

int calculator(int num1, int num2, enOperationType op) {
        switch (op) {
            case Add:
                return num1 + num2;
            case Sub:
                return num1 - num2;
            case Multi:
                return num1*num2;
            case Div:
                return (num2 != 0) ? num1 / num2 : 0;
            default:
               return num1+num2;
        }
}

enDifficulty readDifficulty() {
    short difficulty = 0;
    do {
        cout<<"Choose Difficulty : [1] Easy, [2] Mid, [3] Hard, [4] Mix\n";
        cin>>difficulty;
    }while (difficulty < 1 || difficulty > 4);
    return static_cast<enDifficulty>(difficulty);
}

enOperationType readOperationType() {
    short op = 0;
    do {
        cout<<"Choose operation : [1] Add, [2] Sub, [3] Multi, [4] Div, [5] Mix\n";
        cin>>op;
    }while (op < 1 || op > 5);
    return static_cast<enOperationType>(op);
}

stQuestion generateQuestion(stQuiz& quiz) {
    stQuestion question;
    if (quiz.difficulty == MixDifficulty)
        question.difficulty = (enDifficulty) generateNumber(1,3);
    if (quiz.operation == MixOp)
        question.operation = (enOperationType) generateNumber(1,4);
    else {
        question.operation = quiz.operation;
        question.difficulty = quiz.difficulty;
    }
    enDifficulty questionLevel = question.difficulty;
    switch (questionLevel) {
        case enDifficulty::Easy:
            question.number1 = generateNumber(1,10);
            question.number2 = generateNumber(1,10);
            break;
        case enDifficulty::Mid:
            question.number1 = generateNumber(10,50);
            question.number2 = generateNumber(10,50);
            break;
        case enDifficulty::Hard:
            question.number1 = generateNumber(50,100);
            question.number2 = generateNumber(50,100);
            break;
        default:
            question.number1 = generateNumber(-100,100);
            question.number2 = generateNumber(-100,100);
    }
    question.correctAnswer = calculator(question.number1,question.number2,question.operation);
    return question;
}

void checkAnswer(stQuiz& quiz , int i) {
    if (quiz.questionList[i].correctAnswer == quiz.questionList[i].playerAnswer) {
        cout<<"Right Answer !\n";
        quiz.questionList[i].answerResult = true;
        quiz.correctAnswers++;
    }
    else {
        cout<<"Wrong Answer !\n";

        cout << "\a";
    }
}

string getOpSymbol(enOperationType OpType)
{
    switch (OpType)
    {
        case enOperationType::Add:
            return "+";
        case enOperationType::Sub:
            return "-";
        case enOperationType::Multi:
            return "x";
        case enOperationType::Div:
            return "/";
        default:
            return "Mix";
    }
}

string getDifficultyName(enDifficulty difficulty)
{
    switch (difficulty)
    {
        case enDifficulty::Easy:
            return "Easy";
        case enDifficulty::Mid:
            return "Mid-Level";
        case enDifficulty::Hard:
            return "Hard";
        case enDifficulty::MixDifficulty:
            return "Mix";
        default:
            return "Mix";
    }
}

void askAndCorrect(stQuiz& quiz) {
    for (short i = 0 ; i<quiz.numberOfQuestions ; i++) {
        cout<<"Question ["<<i+1<<"] :\n";
        cout<<quiz.questionList[i].number1<<getOpSymbol(quiz.questionList[i].operation)<<quiz.questionList[i].number2<< " = ";
        cin>>quiz.questionList[i].playerAnswer;
        checkAnswer(quiz,i);
    }
    quiz.isPass = (quiz.correctAnswers >= quiz.wrongAnswers);
}

string passFail(bool isPass) {
    if (isPass)
        return "Passed !\n";
    else
        return "Failed !\n";
}
void gameOver(stQuiz quiz) {
    quiz.wrongAnswers = quiz.numberOfQuestions - quiz.correctAnswers;
    cout<<"- - - - GAME OVER - - - -\n";
    cout<<"Number of questions :" << quiz.numberOfQuestions;
    cout<<"\nDifficulty : "<<getDifficultyName(quiz.difficulty);
    cout<<"\nOperation : " << getOpSymbol(quiz.operation);
    cout<<"\nCorrect answers : " << quiz.correctAnswers<<endl;
    cout<<"Wrong Answers : " << quiz.wrongAnswers<<endl;
    cout<<"Pass or Fail : " << passFail(quiz.isPass);

}
void quizSession() {
    stQuiz quiz;
    quiz.numberOfQuestions = readNumberOfQuestions();
    quiz.difficulty = readDifficulty();
    quiz.operation = readOperationType();
    for (short i = 0 ; i<quiz.numberOfQuestions ; i++) {
        quiz.questionList[i] = generateQuestion(quiz);
    }
    askAndCorrect(quiz);
    gameOver(quiz);
}

void startQuiz() {
    char playAgain = 'Y';
    do {
        quizSession();
        cout<<"\nDo you want to play again ?  (Y/N)\n";
        cin>>playAgain;
    }while (playAgain == 'Y' || playAgain == 'y');
}

int main() {
    srand(time(0));
    startQuiz();
    return 0;
}