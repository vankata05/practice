SELECT Num, Fibonacci(Num) FROM Students;

--function fibonacci that returns the number of the student and the fibonacci number for the student number
CREATE FUNCTION Fibonacci(Num INT) RETURNS INT
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
END

