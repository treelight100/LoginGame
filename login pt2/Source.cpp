
#define NDEBUG 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <assert.h>
#include <unordered_map>

void ReadandWrite();
void Writer();
void Reader();
void ReaderStartUp();
void UserCreator(int& Id);
std::string PasswordGenerator();
char SymbolsUse(int NumForSym);
void SignIn(int Id);
void Account();
void SaveAndExit();
void Login();
void TakeOutLoan();
void GameSetup();
void RulesCasino();
void BetCasino();
void PlayCasino(int PlayerBet);
void RulesBlackJack();
void BetBlackJack();
void PlayBlackJack(int BlackJackBet, int Card1, int Card2, int DealerFaceCard, int DealerDownCard, int DealerSum);
bool HitOrStay(int& PlayerSum);
bool DealerHitOrStay(int& DealerSum);
int DealACard();
int ReservedID[9999];
int ReservedIDCount = 0;
int ReservedIDUse = 0;
class User
{
public:
	std::string UserName;
	std::string Password;
	int UserID;
	int Money = 1000;
	int Loan;
private:
	int caps[100];
	int capsSize = 0;
	std::unordered_map<char, char> key;
	bool KeyMade = false;
public:
	void makeUser(std::string UserNames,std::string Passwords,int UserIDs,int Moneys, int Loans)
	{
		UserName = Encrypt(UserNames);
		Password = Encrypt(Passwords);
		UserID = UserIDs;
		Money = Moneys;
		Loan = Loans;
	}
	void makeUser(std::string UserNames, std::string Passwords, int UserIDs)
	{
		UserName = Encrypt(UserNames);
		Password = Encrypt(Passwords);
		UserID = UserIDs;
	}
	void DeleteUser()
	{
		std::string Gone;
		std::cout << "are you sure you want to delete your account? enter yes or no " << std::endl;
		std::cin >> Gone;
		if (Gone == "yes")
		{
			system("CLS");

			std::cout << "ok goodbye" << std::endl;
			UserName = "";
			Password = "";
			ReservedID[ReservedIDCount] = UserID;
			ReservedIDCount++;

			Account();
		}
		else
		{
			std::cout << "account not deleted " << std::endl;
			Login();
		}

	}
	std::string Encrypt(std::string UserData) 
	{
		for (int i = 0; i < UserData.size(); i++)
		{
			if (int(UserData[i]) < 98)
			{
				UserData[i] = tolower(UserData[i]);
				caps[capsSize] = i;
				capsSize++;
			}
		}
		capsSize--;
		if (!KeyMade)
		{
			srand(time(NULL));
			int charOn = 0;
			int lettersUsed[26];
			for (int i = 0; i < 26; i++)
			{
				int ran = rand() % 26 + 97;
				bool same = false;
				do
				{
					for (int i = 0; i < charOn; i++)
					{
						if (ran == lettersUsed[i])
						{
							ran = rand() % 26 + 97;
							same = true;
							break;
						}
						same = false;
					}
				} while (same);
				lettersUsed[charOn] = ran;
				charOn++;
				key[i+ 97] = ran;
				

			}
			KeyMade = true;
		}
		for (int i = 0; i < UserData.size(); i++)
		{
			
			UserData[i] = key[UserData[i]];
		}
		
		return UserData;
	}
	std::string Decrypt(std::string UserData)
	{
		std::unordered_map<char, char> revkey;
		for (int i = 0; i < 26; i++)
		{
			revkey[key[i+97]] = i + 97;
		}
			
			for (int i = 0; i < UserData.size(); i++)
			{

				UserData[i] = revkey[UserData[i]];
			}
		
		
		for (int i = 0; i < capsSize; i++)
		{
			UserData[caps[i]] = toupper(UserData[i]);
		}
		return UserData;
	}
	
};
// makes the users
User Users[99999] = {};
// the logged in username
std::string LogedinUserName;
// the logged in password
//std::string LogedinPassword;
// the login in user id 
int LogedinUserID;
static int ID = 0;
std::unordered_map<std::string, char> loginKey;

int main()
{
	// seeds the randomness to the time
	srand(time(NULL));
	bool ReadInfoStartUp = false;

	//std::ifstream StartUp("StartUp.txt");
	//StartUp >> ReadInfoStartUp;
	Users[0].makeUser("test", "test", ID);
	ID++;
	loginKey["test"] = 0;
	std::ofstream StartUpOut("StartUp.txt");
	if (ReadInfoStartUp)
	{
		Reader();
		StartUpOut << "0" << std::endl;

	}
	
	Account();
	

	//StartUpOut.close();
	//StartUp.close();


	Account();

	return 0;
}
void ReadandWrite()
{
	int Passcode = 1080;
	int UserInputPass;
	std::cout << "enter the passcode" << std::endl;
	std::cin >> UserInputPass;
	if (UserInputPass == Passcode)
	{
		std::cout << "enter '1' to read from the txt file or '2' to write to the txt file: " << std::endl;
		std::cin >> UserInputPass;
		switch (UserInputPass)
		{
		case 1:
			Reader();
			Account();
			break;
		case 2:
			Writer();
			Account();
			break;
		default:
			system("CLS");
			Account();
			break;
		}
	}
	else
	{
		system("CLS");
		Account();
	}
}
void Writer()
{
	std::ofstream  UserDataFileOut("UserData.txt");
	std::ofstream GlobalFileOut("Global.txt");
	GlobalFileOut << ID << " " << ReservedIDUse << std::endl;
	for (int Index = 0; Index < ReservedIDCount; )
	{
		UserDataFileOut << ReservedID[Index] << std::endl;
		Index++;
	}
	for (int Index = 0; Index < ID; )
	{
		UserDataFileOut << "user " << Users[Index].UserName << " " << Users[Index].Password << " " << Users[Index].UserID;
		UserDataFileOut << " " << Users[Index].Money << " " << Users[Index].Loan << std::endl;
		Index++;
	}
	UserDataFileOut.close();
	GlobalFileOut.close();
}
void Reader()
{
	

	std::ifstream  UserDataFile("UserData.txt");
	std::ifstream GlobalFile("Global.txt");
	std::string s;
	std::string BackUpUserName;
	std::string BackUpPassword;
	int BackUpID;
	int BackUpMoney;
	int BackUpLoan;
	bool userpass = false;
	int idandpass = 0;
	GlobalFile >> ID;    
	GlobalFile >> ReservedIDUse;
	UserDataFile >> s;
	
	while (!GlobalFile.eof())
	{
		
		GlobalFile >> ReservedID[ReservedIDCount];
		ReservedIDCount++;
	}
	//Searches word by word;
	while (!UserDataFile.eof())
	{




		


		if (userpass)
		{

			switch (idandpass)
			{
			case 0:
				UserDataFile >> BackUpUserName;
				std::cout << " the username is: " << BackUpUserName << std::endl;
				break;
			case 1:

				UserDataFile >> BackUpPassword;
				std::cout << " the password is: " << BackUpPassword << std::endl;

				break;
			case 2:
				UserDataFile >> BackUpID;
				std::cout << " the ID is: " << BackUpID + 1 << std::endl;



				break;
			case 3:
				UserDataFile >> BackUpMoney;
				std::cout << " the money amount is: " << BackUpMoney << std::endl;

				break;
			case 4:
				UserDataFile >> BackUpLoan;
				std::cout << " the Loan amount is: " << BackUpID + 1 << std::endl;

				userpass = false;
				idandpass = 0;
				ID++;
				Users[BackUpID + 1].makeUser(BackUpUserName, BackUpPassword, BackUpID + 1, BackUpMoney, BackUpLoan);
				break;
			default:
				userpass = false;
				break;
			}


			idandpass++;


		}
		else
		{

			UserDataFile >> s;
			std::cout << s << std::endl;
			if (s == "user")
			{
				std::cout << "hi3" << std::endl;
				userpass = true;
				idandpass = 0;
			}

		}

	}
	system("pause");
	system("CLS");
	UserDataFile.close();
	GlobalFile.close();


}
void ReaderStartUp()
{

	std::ifstream  UserDataFile("UserData.txt");
	std::ifstream GlobalFile("Global.txt");
	std::string s;
	std::string BackUpUserName;
	std::string BackUpPassword;
	int BackUpID;
	int BackUpMoney;
	int BackUpLoan;
	bool userpass = false;
	int idandpass = 0;
	GlobalFile >> ID;
	GlobalFile >> ReservedIDUse;
	while (!GlobalFile.eof())
	{
		GlobalFile >> ReservedID[ReservedIDCount];
		ReservedIDCount++;
	}
	//Searches word by word;
	while (!UserDataFile.eof())
	{







		if (userpass)
		{

			switch (idandpass)
			{
			case 0:
				UserDataFile >> BackUpUserName;
				break;
			case 1:

				UserDataFile >> BackUpPassword;


				break;
			case 2:
				UserDataFile >> BackUpID;




				break;
			case 3:
				UserDataFile >> BackUpMoney;

				break;
			case 4:
				UserDataFile >> BackUpLoan;
				idandpass = 0;
				userpass = false;
				Users[BackUpID + 1].makeUser(BackUpUserName, BackUpPassword, BackUpID + 1, BackUpMoney, BackUpLoan);
				ID++;


				break;
			default:
				userpass = false;
				break;
			}


			idandpass++;


		}
		else
		{

			UserDataFile >> s;
			if (s == "user")
			{

				userpass = true;
				idandpass = 0;
			}

		}

	}
	system("CLS");
	UserDataFile.close();
	GlobalFile.close();


}
void SaveAndExit()
{
	std::string SaveAndExit;
	std::cout << "are you sure you want to save an exit? enter yes or no " << std::endl;
	std::cin >> SaveAndExit;
	if (SaveAndExit == "yes")
	{
		system("CLS");

		std::cout << "ok goodbye" << std::endl;
		Writer();
		std::ofstream StartUpOut("StartUp.txt");
		StartUpOut << "1" << std::endl;
		return;


	}
	else
	{
		std::cout << "has not saved and exited " << std::endl;
		Account();
		system("CLS");
		return;

	}
}
void Account()
{


	// ask if they want to sign up or login
	int Accounts;
	std::cout << "If you would like to SIGNUP type '1'" << std::endl << "if you would want to LOGIN type '2' " << std::endl << "if you would like to save and exit type '3'" << std::endl;;
	std::cin >> Accounts;

	std::cin.clear();
	std::cin.ignore();
	std::cout << std::endl;
	switch (Accounts)
	{
	case 1:
		UserCreator(ID);
		return;
		break;
	case 2:

		SignIn(ID);
		return;
		break;
	case 3:
		SaveAndExit();
		break;
	case 59:
		ReadandWrite();
		break;
	default:
		std::cout << "invalid option " << std::endl;
		Account();
		system("CLS");
		return;
		break;
	}

}
void UserCreator(int& Id)
{
	// ask them to create a UserName and password
	std::string* UserName = new std::string;
	std::string* PassWord = new std::string;
	std::cout << "enter a Username: ";
	std::cin >> *UserName;
		if (loginKey.find(*UserName) != loginKey.end())
		{
			std::cout << "the username are already in use" << std::endl;
			system("pause");
			system("CLS");
			Account();
			return;
		}
	std::cout << "enter a password: ";
	std::cin >> *PassWord;
	// checks if the UserName is in use
	if (*PassWord == "1")
	{
		*PassWord = PasswordGenerator();
	}
	
		
		// checks for a reserved id after someone deleted there Account
		if (Id > 0)
		{
			if (ReservedIDCount > 0)
			{
				// creates account with user reserver id 
				Users[ReservedID[ReservedIDUse]].makeUser(*UserName, *PassWord, ReservedID[ReservedIDUse]);
				ReservedIDUse++;
				ReservedIDCount--;
				loginKey[*UserName] = Id;
				system("pause");
				system("CLS");
				Account();
				return;
			}
		}
	
	// creates an account with id
	Users[Id].makeUser(*UserName, *PassWord, Id);
	system("pause");
	system("CLS");
	loginKey[*UserName] = Id;
	if (Users[Id].Encrypt(*UserName) == Users[Id].UserName) { Id++; }
	delete UserName;
	delete PassWord;
	Account();
}
std::string PasswordGenerator()
{
	srand(time(NULL));
	std::string* RandPassWord = new std::string;
	int* NumCap = new int;
	int* CharCap = new int;
	int* IntsUsed = new int;
	int* CharsUsed = new int;
	int* PassLen = new int;
	int* RandChar = new int;
	char* CharInUse = new char;
	int* IntInUse = new int;
	*CharCap = 5;
	*NumCap = 2;
	*CharsUsed = 0;
	*IntsUsed = 0;
	*PassLen = *CharCap + *NumCap;
	for (int i = 0; i < *PassLen; i++)
	{
		*RandChar = rand() % 2 + 1;
		if (*IntsUsed >= *NumCap)
		{
			*RandChar = 2;
		}
		if (*CharsUsed >= *CharCap)
		{
			*RandChar = 1;
		}
			

		switch (*RandChar)
		{
		case 1:
				*IntInUse = rand() % 10;
				*RandPassWord += std::to_string(*IntInUse);;
				++*IntsUsed;
				break;
		case 2:
				*IntInUse = rand() % 26;
				*CharInUse = char(*IntInUse+97);
				*RandPassWord += *CharInUse;

				*CharsUsed++;
				break;
		case 3:
				*IntInUse = rand() % 10;
				*RandPassWord += std::to_string(*IntInUse);;
				*IntsUsed++;
			break;
		}
	}


	std::cout << "your password is: " << *RandPassWord << std::endl;
	return *RandPassWord;
	delete RandPassWord;
	

	
	
}
char SymbolsUse(int NumForSym)
{
	switch (NumForSym)
	{
	
	case 1:
		return '!';
	case 2:
		return '@';
	case 3:
		return '#';
	case 4:
		return '$';
	case 5:
		return '%';
	case 6:
		return '^';
	case 7:
		return '&';
	case 8:
		return '*';
	case 9:
		return '(';
	case 10:
		return ')';
	case 11:
		return '-';
	case 12:
		return '_';
	case 13:
		return '=';
	case 14:
		return '+';
	case 15:
		return '[';
	case 16:
		return ']';
    case 17:
		return '{';
	case 18:
		return '}';
	case 19:
		return '*';
	case 20:
		return '|';
	case 21:
		return ';';
	case 22:
		return ':';
	case 23:
		return '"';
	case 24:
		return ',';
	case 25:
		return '<';
	case 26:
		return '.';
	case 27:
		return '>';
	case 28:
		return '/';
	case 29:
		return '?';
	case 30:
		return '`';
	case 31:
		return '~';
	default:
		return'!';
		break;
	}
}
void SignIn(int Id)
{
	// asks for their username and password
	system("CLS");
	std::string UserName;
	std::string PassWord;
	std::cout << "enter your Username: ";
	std::cin >> UserName;
	int loginId;
	std::cout << "enter your password: ";
	std::cin >> PassWord;
	// checks if the username and password is correct
	if (loginKey.find(UserName) != loginKey.end())
	{
		loginId = loginKey[UserName];
			// checks if the password is correct
			if (PassWord == Users[loginId].Decrypt(Users[loginId].Password))
			{
				LogedinUserName = UserName;
				LogedinUserID = loginId;
				system("CLS");
				Login();
				return;
			}
		}
	// incorrect password or username
	std::cout << "incorrect password or username " << std::endl;
	//std::cout << std::endl;
	system("CLS");
	Account();
	return;
}
void Login()
{

	std::cout << "your User ID is: " << LogedinUserID << std::endl;
	std::cout << "you are logged in as: " << LogedinUserName << std::endl;
	GameSetup();

}
void TakeOutLoan()
{
	std::string* LoanOut = new std::string;
	int* LoanAmount = new int;
	std::cout << "You will have to pay 1.5 times the amount you take out do you still want to take out the loan? type yes or no" << std::endl;
	std::cin >> *LoanOut;
	if (*LoanOut == "yes")
	{
		std::cout << "enter how much you want to take out" << std::endl;
		std::cin >> *LoanAmount;
		Users[LogedinUserID].Money = *LoanAmount;
		Users[LogedinUserID].Loan = *LoanAmount * 1.5;
		if (Users[LogedinUserID].Money > Users[LogedinUserID].Loan)
		{
			Users[LogedinUserID].Money -= Users[LogedinUserID].Loan;
			Users[LogedinUserID].Loan = 0;
			GameSetup();
		}
		else
		{

			GameSetup();
		}
	}
	else
	{
		GameSetup();
		return;
	}
	delete LoanAmount;
}
void GameSetup()
{
	if (Users[LogedinUserID].Money > Users[LogedinUserID].Loan)
	{
		Users[LogedinUserID].Money -= Users[LogedinUserID].Loan;
		Users[LogedinUserID].Loan = 0;
	}
	int* Play = new int;
	std::cout << std::endl;
	//asks what they want to do
	std::cout << "type " << std::endl << "'1' to play the casino game" << std::endl << "'2' to play blackjack" << std::endl << "'3' to add friends " << std::endl << "'4' to take out a loan" << std::endl << "'5' to see your balance" << std::endl << "'6' to get to the menu" << std::endl << "'7' to login or make a new account" << std::endl << "'8' to delete your account" << std::endl;
	std::cin >> *Play;
	std::cin.clear();
	std::cin.ignore();
	// switch statement for what they want to play
	switch (*Play)
	{
	case 1:
		RulesCasino();
		break;
	case 2:
		RulesBlackJack();
		break;
	case 3:
		
		break;
	case 4:
		TakeOutLoan();
		break;
	case 5:
		std::cout << "your current balance is: " << Users[LogedinUserID].Money << " but you owe " << Users[LogedinUserID].Loan << std::endl;
		GameSetup();
		break;
	case 6:
		Login();
		break;
	case 7:
		Account();
		break;
	case 8:
		Users[LogedinUserID].DeleteUser();
		break;
	default:
		std::cout << "invalid request" << std::endl;
		GameSetup();
		break;
	}
	delete Play;
}
void RulesCasino()
{
	//the rules for Casino
	std::cout << "Make a bet then guess three ";
	std::cout << "numbers from 1-10" << std::endl << "if one of your numbers match up with the random numbers you ";
	std::cout << "get half your money back if 2 you earn your money back and" << std::endl << "if all three you get two times your bet " << std::endl;
	BetCasino();

}
void BetCasino()
{
	// betting for Casino
	int* Bet = new int;

	std::cout << "Enter how much you want to bet " << std::endl;
	std::cin >> *Bet;
	std::cin.clear();
	std::cin.ignore();
	if (*Bet > Users[LogedinUserID].Money)
	{
		std::cout << "Insufficient funds " << std::endl;
		std::cout << "Your current balance is: " << Users[LogedinUserID].Money << std::endl;
		BetCasino();
		delete Bet;
		return;
	}
	PlayCasino(*Bet);
	delete Bet;
}
void PlayCasino(int PlayerBet)
{
	// plays the Casino game
	int* HowManyCorrect = new int;
	int* Lost = new int;
	int* Gain = new int;
	*Lost = 0;
	*Gain = 0;
	int Num[3] = { rand() % 11,  rand() % 11,  rand() % 11 };


	for (int i = 0; i <= 10; i++)
	{
		if (Num[0] == Num[1] || Num[0] == Num[2] || Num[1] == Num[2])
		{
			PlayCasino(PlayerBet);
			return;
		}
	}
	int Guess[3];
	std::cout << "Enter your three guess now make sure there are spaces between them and they can't be the same numbers: ";
	std::cin >> Guess[0], Guess[1], Guess[2];
	std::cout << "The three numbers were " << Num[0] << ", " << Num[1] << " and, " << Num[2] << std::endl;
	for (int i = -1; i < 3; i++)
	{
		for (int j = -1; j < 3; j++)
		{
			if (Num[i] = Guess[j])
			{
				*HowManyCorrect++;
			}
		}
	}
	switch (*HowManyCorrect)
	{
	case 1:
		*Lost = PlayerBet / 2;
		break;
	case 2:
		*Lost = 0;
		break;
	case 3:
		*Gain = PlayerBet;
		break;
	default:
		*Lost = PlayerBet;
		break;
	}

	Users[LogedinUserID].Money += *Gain;
	Users[LogedinUserID].Money -= *Lost;
	GameSetup();
	delete HowManyCorrect;
	delete Gain;
	delete Lost;
	return;
}
void RulesBlackJack()
{
	// the rules for blackjack
	//ask them if they know how to play
	std::string Rules;
	std::cout << "Do you know how to play? enter yes or no ";
	std::cin >> Rules;
	std::cout << std::endl;
	if (Rules == "yes")
	{
		BetBlackJack();
		return;
	}
	if (Rules == "no")
	{
		std::cout << "To play you get two card you can type hit to get another card or stay to finish your hand" << std::endl;
		std::cout << "you try to get closer to 21 then the dealer but if you go over 21 you are out" << std::endl;
		BetBlackJack();
		return;
	}
	else
	{
		std::cout << "incorrect option type yes or no" << std::endl;
		system("CLS");
		RulesBlackJack();
		return;
	}
}
void BetBlackJack()
{
	// betting for black jack
	std::cin.clear();
	int* DealerFaceCard = new int;
	int* DealerDownCard = new int;
	int* DealerSum = new int;
	int* BlackJackBet = new int;
	int* Card1 = new int;
	int* Card2 = new int;
	*DealerFaceCard = rand() % 11 + 1;
	*DealerDownCard = rand() % 11 + 1;
	*DealerSum = *DealerDownCard + *DealerFaceCard;

	*Card1 = rand() % DealACard();
	*Card2 = rand() % DealACard();

	std::cout << "To play you get two card you can type hit to get another card or stay to finish your hand" << std::endl;
	std::cout << "Your first card is '" << *Card1 << "' your second card is '" << *Card2 << "' the dealer's face card is '" << *DealerFaceCard << "'" << std::endl;
	std::cout << "if you win you double the money you bet but lose all of the money you bet if you lose " << std::endl;
	std::cout << "Enter how much you want to bet " << std::endl;
	std::cin >> *BlackJackBet;

	std::cin.clear();
	std::cin.ignore();
	//checks if they have the money
	if (*BlackJackBet > Users[LogedinUserID].Money)
	{
		system("CLS");
		std::cout << "Insufficient funds " << std::endl;
		std::cout << "Your current balance is: " << Users[LogedinUserID].Money << std::endl;
		std::cout << std::endl;

		BetBlackJack();
		return;
	}
	PlayBlackJack(*BlackJackBet, *Card1, *Card2, *DealerFaceCard, *DealerDownCard, *DealerSum);

	delete  DealerFaceCard;
	delete DealerDownCard;
	delete DealerSum;
	delete BlackJackBet;
	delete Card1;
	delete Card2;
}
void PlayBlackJack(int BlackJackBet, int Card1, int Card2, int DealerFaceCard, int DealerDownCard, int DealerSum)
{
	// plays the game
	int PlayerSum = Card1 + Card2;
	bool Hit = true;
	while (Hit)
	{

		Hit = HitOrStay(PlayerSum);





	}
	Hit = true;
	while (Hit)
	{

		Hit = DealerHitOrStay(DealerSum);




	}
	if (DealerSum == PlayerSum) { DealerSum += 1; }
	std::cout << "The dealers sum is: " << DealerSum<< std::endl;
	std::cout << "Your sum is: " << PlayerSum << std::endl;

	if (PlayerSum > 21)
	{
		std::cout << "you lost you went over 21 " << std::endl;
		Users[LogedinUserID].Money -= BlackJackBet;
	}
	if (DealerSum > 21)
	{
		std::cout << "you won the dealer went over 21 " << std::endl;
		Users[LogedinUserID].Money += BlackJackBet;
	}
	if (PlayerSum > DealerSum)
	{
		std::cout << "You have won " << std::endl;
		Users[LogedinUserID].Money += BlackJackBet;
	}
	if (PlayerSum < DealerSum)
	{
		std::cout << "You have lost " << std::endl;
		Users[LogedinUserID].Money -= BlackJackBet;
	}
	else
	{
		std::cout << "You have lost " << std::endl;
		Users[LogedinUserID].Money -= BlackJackBet;
	}
	system("pause");
	system("CLS");
	Login();
	return;

}
bool HitOrStay(int& PlayerSum)
{
	srand(time(NULL));
	int* NewNumber = new int;
	*NewNumber = DealACard();
	// checks if they go over 21
	if (PlayerSum > 21)
	{
		std::cout << "you went over 21 " << std::endl;
		return false;
	}
	// asks if they want to hit or stay
	std::string HitorStay;
	std::cout << "hit or stay" << std::endl;
	std::cin >> HitorStay;
	if (HitorStay == "hit")
	{
		PlayerSum = PlayerSum + *NewNumber;
		std::cout << "your new card is " << *NewNumber << " your sum is " << PlayerSum << std::endl;
		delete NewNumber;
		return true;
	}
	else if (HitorStay == "stay")
	{
		delete NewNumber;
		return false;
	}
	delete NewNumber;
	return false;
}
bool DealerHitOrStay(int& DealerSum)
{
	srand(time(NULL));
	int* Prob = new int;
	int* hit = new int;
	int* OneHundred = new int;
	*OneHundred = rand() % 101;
	
	if (DealerSum > 21)
	{
		return false;
	}
	if (DealerSum < 13)
	{
		int num = rand() % 12;

		DealerSum += num;
		return true;

	}
	else if (DealerSum < 15)
	{
		*Prob = 95;
		*hit = *OneHundred - *Prob;

	}
	else if (DealerSum < 16)
	{
		*Prob = 95;
		*hit = *OneHundred - *Prob;

	}
	else if (DealerSum < 18)
	{
		*Prob = 95;
		*hit = *OneHundred - *Prob;
	}
	else if (DealerSum < 22)
	{
		*Prob = 0;
		*hit = *OneHundred - *Prob;

	}
	else
	{
		*Prob = 0;
		*hit = *OneHundred - *Prob;
	}

	if (*hit < 0)
	{
		DealerSum += DealACard();
		delete hit;
		delete Prob;
		delete OneHundred;
		DealerHitOrStay(DealerSum);
		return true;
	}
	else {
		return false;
		delete hit;
		delete Prob;
		delete OneHundred;
	}
}
int DealACard()
{
	int CardValue = rand() % 13 + 1;
		if (CardValue > 10) {CardValue = 10;}
		if (CardValue == 1) {CardValue = 11;}

	return CardValue;
}







