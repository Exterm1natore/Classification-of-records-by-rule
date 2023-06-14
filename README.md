# Classification of records by rule
 The programme must classify the records according to user-specified rules. Each record has a name and a set of properties. 
 Each property has its own name and a set of integer values that describe the characteristic of the property. 
 Classification rules have a name (class) and the condition(s) under which a record falls into that class.
 
 Purpose: The program is designed to classify a set of records according to a specified set of rules.

 Each record has a name and a set of properties. 
 Each property has its own name and a set of integer values that describe the property's characteristic.

 Classification rules have a name (class) and a condition(s) under which a record falls into that class. 
 The rules are entered in a strictly defined format.
 
 Example record: Шкаф: цвет=[1,55,2], размер=[2, 11, 99, 64], форма=[15].
 Example properties:
 1) Запись принадлежит классу "С покрытием", если у нее есть свойство "покрытие";
 2) Запись принадлежит классу "П л о с к и й", если у нее есть свойство "размер", которое представлено двумя значениями;
 3) Запись принадлежит классу "Синий", если у нее есть свойство "цвет", в составе которого есть значение "1";
 4) Запись принадлежит классу "Матовый", если у нее есть свойство "покрытие" и значение этого свойства равно "[44, 21]".
 P.S. All possible property types are represented here (without additional restriction; with a number of integer values represented
 as text; as a single integer value that occurs in a record property; with an array of integer values).
 
 Шкаф: цвет=[1,2]
   ^______________name record
	     ^________record property name
              ^___integer values that relate to a certain property
			  
 Запись принадлежит классу "Синий", если у нее есть свойство "цвет", в составе которого есть значение "1"
                              ^___________________________________________________________________________name class
                                                                ^_________________________________________text restriction
																									                                                     ^__additional restriction

 The main program is stored in the path (starting with the 'Classification-of-records-by-rule' directory):
 .\CourseworkOnKINPO\ClassificationOfRecordsByRule (Windows)

 The '.exe' file to be run is in the path (starting with the 'Classification-of-records-by-rule' directory):
 .\CourseworkOnKINPO\ClassificationOfRecordsByRule\release\ClassificationOfRecordsByRule.exe (Windows)

 To run the programme, you must:
 1) start the command line
 2) Navigate to the directory with the executable file ('ClassificationOfRecordsByRule.exe')
 3) On the command line, enter the following arguments in the order given:
   ClassificationOfRecordsByRule.exe <Path to records file> <Path to classification rules file> <Path to output result file>
   
 General content of the files (starting with the 'Classification-of-records-by-rule' directory):
 The directory 'CourseworkOnKINPO' contains the test projects and the main programme, as well as a folder with files for the test projects.
 The 'Autotests' directory contains the '.bat' file which launches the autotest project. There are also '.txt' files for tests (input and output).
 The directory 'ManualTesting' contains a file describing manual testing and examples of the input data.
 The 'Autodocs' directory contains the autodocumentation files of the main project.
