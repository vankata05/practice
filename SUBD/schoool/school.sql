DROP DATABASE IF EXISTS school;
CREATE DATABASE school CHARSET 'utf8';
USE school;

CREATE TABLE Students(
	Id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
	Name VARCHAR(150) NOT NULL,
	Num INTEGER NOT NULL,
	ClassNum INTEGER NOT NULL,
	ClassLetter CHAR(1) NOT NULL,
	Birthday DATE,
	EGN CHAR(10),
	EntranceExamResult NUMERIC(3,2)
);

CREATE TABLE Teachers(
	Id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
	Name VARCHAR(150) NOT NULL
);

CREATE TABLE Subjects(
	Id INTEGER NOT NULL AUTO_INCREMENT,
	Name VARCHAR(100),
	
	PRIMARY KEY(Id)
);

CREATE TABLE StudentMarks(
	StudentId INTEGER NOT NULL,
	SubjectId INTEGER NOT NULL,
	ExamDate DATETIME NOT NULL,
	Mark NUMERIC(3,2) NOT NULL,
	
	PRIMARY KEY( StudentId, SubjectId, ExamDate ),
	FOREIGN KEY (StudentId) REFERENCES Students(Id),
	FOREIGN KEY (SubjectId) REFERENCES Subjects(Id)
);

CREATE TABLE MarkWords(
	RangeStart NUMERIC(3,2) NOT NULL,
	RangeEnd NUMERIC(3,2) NOT NULL,
	MarkAsWord VARCHAR(15),
	
	PRIMARY KEY(RangeStart, RangeEnd)
);

INSERT INTO Students(Id, Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 101, 'Зюмбюл Петров', 10, 11, 'а', '1999-02-28', NULL );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 'Исидор Иванов', 15, 10, 'б', '2000-02-29', '0042294120' );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 'Панчо Лалов', 20, 10, 'б', '2000-05-01', NULL );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 'Петраки Ганьов', 20, 10, 'а', '1999-12-25', '9912256301' );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 'Александър Момчев', 1, 8, 'а', '2002-06-11', NULL );

INSERT INTO Teachers(Name) VALUES( 'Георги Георгиев' );
INSERT INTO Teachers(Name) VALUES( 'Петър Петров' );
INSERT INTO Teachers(Name) VALUES( 'Иван Иванов' );

INSERT INTO Subjects(Id, Name) VALUES( 11, 'Английски език' );
INSERT INTO Subjects(Name) VALUES( 'Литература' );
INSERT INTO Subjects(Name) VALUES( 'Математика' );
INSERT INTO Subjects(Name) VALUES( 'СУБД' );

INSERT INTO StudentMarks VALUES( 101, 11, '2017-03-03', 6 );
INSERT INTO StudentMarks VALUES( 101, 11, '2017-03-31', 5.50 );
INSERT INTO StudentMarks VALUES( 102, 11, '2017-04-28', 5 );
INSERT INTO StudentMarks VALUES( 103, 12, '2017-04-28', 4 );
INSERT INTO StudentMarks VALUES( 104, 13, '2017-03-03', 5 );
INSERT INTO StudentMarks VALUES( 104, 13, '2017-04-07', 6 );
INSERT INTO StudentMarks VALUES( 104, 11, '2017-04-07', 4.50 );

INSERT INTO MarkWords VALUES( 2, 2.50, 'Слаб' );
INSERT INTO MarkWords VALUES( 2.50, 3.50, 'Среден' );
INSERT INTO MarkWords VALUES( 3.50, 4.50, 'Добър' );
INSERT INTO MarkWords VALUES( 4.50, 5.50, 'Мн. добър' );
INSERT INTO MarkWords VALUES( 5.50, 6, 'Отличен' );

--1)
SELECT Name, IF(ClassNum IS NULL, 'Teacher', CONCAT(ClassNum, ClassLetter)) AS Class FROM Students 
WHERE ClassNum IN (11, 9, 8) 
UNION ALL 
SELECT Name, 'Teacher' FROM Teachers;

--2)
(SELECT Name, AVG(Mark) AS AverageMark FROM Students
INNER JOIN StudentMarks ON Students.Id = StudentMarks.StudentId
GROUP BY StudentId
ORDER BY AverageMark DESC
LIMIT 3)
UNION
(SELECT Name, AVG(Mark) AS AverageMark FROM Students
INNER JOIN StudentMarks ON Students.Id = StudentMarks.StudentId
GROUP BY StudentId
ORDER BY AverageMark ASC
LIMIT 3);

SELECT Num, Fibonacci(Num) FROM Students;

--1)

DELIMITER $
CREATE FUNCTION Fibonacci(Num INT) RETURNS INT
DETERMINISTIC
BEGIN
	DECLARE a INT DEFAULT 0;
	DECLARE b INT DEFAULT 1;
	DECLARE c INT DEFAULT 0;
	DECLARE i INT DEFAULT 0;
	
	WHILE i < Num DO
		SET c = a + b;
		SET a = b;
		SET b = c;
		SET i = i + 1;
	END WHILE;
	
	RETURN c;
END $
DELIMITER ;


--2)
DELIMITER $
CREATE FUNCTION Fibonacci(Num INT) RETURNS INT
DETERMINISTIC
BEGIN
	IF Num = 0 THEN
		RETURN 0;
	ELSEIF Num = 1 THEN
		RETURN 1;
	ELSE
		RETURN Fibonacci(Num - 1) + Fibonacci(Num - 2);
	END IF;
END $
DELIMITER ;
