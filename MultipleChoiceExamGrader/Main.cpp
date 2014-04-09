#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

class Student{
public:
	std::string firstName, lastName;
	std::string answers;
	double grade;

	Student(std::string fN, std::string lN, std::string ans) : firstName(fN), lastName(lN), answers(ans), grade(0){}
};

std::string getAnswerKey(std::ifstream* reader){
	std::string answerKey;
	*reader >> answerKey;
	return answerKey;
}

std::vector<Student> gradeStudents(std::ifstream* reader, std::string answerKey){
	std::vector<Student> students;
	std::string fN, lN, ans;

	while(reader->is_open()){
		if(reader->eof()) break;
		else{
			*reader >> fN;
			*reader >> lN;
			*reader >> ans;
			Student temp(fN, lN, ans);
			students.push_back(temp);
		}
	}

	for(int i = 0; i < students.size(); i++){
		Student* temp = &students.at(i);
		int numWrong = 0;

		for(int x = 0; x < answerKey.length(); x++){
			if(temp->answers.at(x) != answerKey.at(x)) numWrong++;
		}

		temp->grade = (((double) answerKey.length() - (double) numWrong) / (double) answerKey.length()) * 100;
	}

	return students;
}

void createFinalGrades(std::vector<Student> students, std::string origFile){
	std::ofstream writer("FinalGrades-" + origFile);

	for(int i = 0; i < students.size(); i++){
		Student temp = students.at(i);
		writer << temp.firstName << " " << temp.lastName << " " << temp.grade << std::endl;
	}

	writer.close();
}

int main(){
	std::string fileName;
	std::ifstream reader;

	std::cout << "Please enter location of file:\n";
	while(!reader.is_open()){
		std::cin >> fileName;
	
		reader.open(fileName);

		if(!reader.is_open()){
			std::cout << "Could not find file...\n";
			std::cout << "Please enter location of file:\n";
		}
	}
	
	std::string answerKey = getAnswerKey(&reader);

	std::vector<Student> students = gradeStudents(&reader, answerKey);

	reader.close();

	createFinalGrades(students, fileName);

	std::cout << "Final scores have been calculated and outputted" << std::endl;
	return 0;
}

