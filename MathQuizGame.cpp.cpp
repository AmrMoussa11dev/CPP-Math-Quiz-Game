#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4,Mixop=5 };
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enQuestionsLevel Questions_Level;
	enOperationType OperationType;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};
struct stQuizz
{
	stQuestion QuuestionList[100];
	int NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

short ReadHowManyQuestions()
{
	short NumberOfQuestions = 0;
	do
	{
		cout << "How Many Questions do you want to answer From[ 1 To 10 ] ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
	return NumberOfQuestions;
}
enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Eas. [2] Med. [3] Hard. [4] Mix. ? ";
		cin >> QuestionsLevel;
	} while (QuestionsLevel < 1 || QuestionsLevel > 4);

	return (enQuestionsLevel)QuestionsLevel;
}
int SimpleCalculator(short Number1,short Number2, enOperationType OPType)
{
	switch (OPType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mul:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;

	}
}
enOperationType ReadOprationTayp()
{
	
	short OpType = 0;
	do
	{
		cout << "Enter Opretion Type [1] Add. [2] Sub. [3] Mul. [4] Div. [5] Mix. ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);
	return (enOperationType)OpType;
}
enOperationType GetRandomOperatoinTaype()
{
	int OP = RandomNumber(1, 4);
	return (enOperationType)OP;
}
stQuestion GenerateQuestion(enQuestionsLevel QuestionsLevel, enOperationType OpType)
{
	stQuestion Question;
	if (QuestionsLevel == enQuestionsLevel::Mix)
	{
		QuestionsLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}
	if (OpType == enOperationType::Mixop)
	{
		OpType = GetRandomOperatoinTaype();
	}
	Question.OperationType = OpType;

	switch (QuestionsLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.Questions_Level = QuestionsLevel;
		return Question;
	case enQuestionsLevel::MedLevel:

		Question.Number1 = RandomNumber(10,50);
		Question.Number2 = RandomNumber(10,50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.Questions_Level = QuestionsLevel;
		return Question;
	case enQuestionsLevel::HardLevel:

			Question.Number1 = RandomNumber(50, 100);
			Question.Number2 = RandomNumber(50, 100);

			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
			Question.Questions_Level = QuestionsLevel;
			return Question;
	}
	return Question;
}
void GenerateQuizzQuestion(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}//here where is QuuestionList

}
string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}
int  ReadQuestionsAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}
void PrintTheQuestion(stQuizz& Quizz,short QuestionNumber)
{
	cout << "\n";
	cout << "Question ["<< QuestionNumber+1<<"/"<< Quizz.NumberOfQuestions<<"] \n\n";
	cout <<  Quizz.QuuestionList[QuestionNumber].Number1 <<endl;
	cout << Quizz.QuuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuuestionList[QuestionNumber].OperationType);//here
	cout << "\n_________" << endl;
}
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
	return arrQuestionLevelText[QuestionLevel - 1];
}
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F"); 
		cout << "\a"; 
	}
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuuestionList[QuestionNumber].PlayerAnswer != Quizz.QuuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Worng Answer :( \n";
		cout << "The right answer is: ";
		cout << Quizz.QuuestionList[QuestionNumber].CorrectAnswer;
	}
	else
	{
		Quizz.QuuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfWrongAnswers++;

		cout << "Right Answer :) \n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswers(stQuizz & Quizz)
{//here
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz,QuestionNumber);
	
		Quizz.QuuestionList[QuestionNumber].PlayerAnswer = ReadQuestionsAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :)";
	else
		return "Fail :(";
}
void PrintQuizzResults(stQuizz Quizz)
{
	system("cls");
	cout << "\n\n";
	cout << "\t\t==============================================\n";
	cout << "\t\tFinal Results is : " << GetFinalResultsText(Quizz.isPass);
	cout << "\n\t\t==============================================\n";
	cout << "\t\tNumber Of Questions : " << Quizz.NumberOfQuestions << "\n";
	cout << "\t\tQuestion Level      : " << GetQuestionLevelText(Quizz.QuestionsLevel) <<endl;
	cout << "\t\tOperation Type      : " << GetOpTypeSymbol(Quizz.OpType) << "\n";
	cout << "\t\tNumber Of Rigth Answers : " << Quizz.NumberOfRightAnswers << "\n";
	cout << "\t\tNumber Of Wrong Answers : " << Quizz.NumberOfWrongAnswers << "\n";
	cout << "\t\t==============================================";
	cout << endl;
}
void PalyMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOprationTayp();

	GenerateQuizzQuestion(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);

	PrintQuizzResults(Quizz);
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PalyMathGame();

		cout << "\nDo you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');


}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

}
